// PCDWrapperLib.cpp : Definiert die exportierten Funktionen für die DLL-Anwendung.
//

// Dies ist die Haupt-DLL.

#include "stdafx.h"

//#include "PCDWrapperLib.h"

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#undef max
#undef min

#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/our_cvfh.h>
#include <pcl/visualization/pcl_plotter.h>


extern "C" __declspec(dllexport) int evaluatePCD(const char* filename, bool print, const char* exportFile, int offset, bool plot);
int evaluatePCD(const char* filename, bool print, const char* exportFile, int offset, bool plot)
{
	std::cout <<
		"\nourCVFH -- 160408\n"
		"This program loads a Point Cloud Data File and extracts ourCVFH features from it. \n\n";
	// Cloud for storing the object.
	pcl::PointCloud<pcl::PointXYZ>::Ptr object(new pcl::PointCloud<pcl::PointXYZ>);
	// Object for storing the normals.
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	// Object for storing the OUR-CVFH descriptors.
	pcl::PointCloud<pcl::VFHSignature308>::Ptr descriptors(new pcl::PointCloud<pcl::VFHSignature308>);

	// Note: you should have performed preprocessing to cluster out the object
	// from the cloud, and save it to this individual file.

	//============================================================
	// Read a PCD file from disk.
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(filename, *object) != 0)
	{
		std::cout << "Unable to open or read file : " << filename << std::endl;
		return -1;
	}

	//return 200;

	//============================================================
	// Estimate the normals.
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
	normalEstimation.setInputCloud(object);
	normalEstimation.setRadiusSearch(0.01); //0.03

	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
	normalEstimation.setSearchMethod(kdtree);
	normalEstimation.compute(*normals);

	// OUR-CVFH estimation object.
	pcl::OURCVFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::VFHSignature308> ourcvfh;
	ourcvfh.setInputCloud(object);
	ourcvfh.setInputNormals(normals);
	ourcvfh.setSearchMethod(kdtree);
	ourcvfh.setEPSAngleThreshold(3.0 / 180.0 * M_PI); // 5.0 degrees.
	ourcvfh.setCurvatureThreshold(5.0);				 // 1.0
	ourcvfh.setNormalizeBins(false);
	ourcvfh.setAxisRatio(0.6); //0.8  // Set the minimum axis ratio between the SGURF axes. At the disambiguation phase, this will decide if additional Reference Frames need to be created, if ambiguous.
	ourcvfh.compute(*descriptors);

	std::cout << "\nBerechnung von OUR-CVFH abgeschlossen!" << std::endl;
	std::cout << "Anzahl Punkte in Wolke: " << object->points.size() << std::endl;

	int histo_bins = 308; // 308 is the standard of CVFH
	int histogram_std_idx = 0;
	double xy[2];

	// print histogram values
	if (print)
	{
		std::cout << "\nAusgabe der Histogrammwerte:" << std::endl;
		std::cout << "----------------------------" << std::endl;
		for (int binIdx = 0; binIdx < histo_bins; ++binIdx){
			xy[0] = binIdx;
			std::cout << binIdx;
			xy[1] = descriptors->points[histogram_std_idx].histogram[binIdx];
			std::cout << ": " << descriptors->points[histogram_std_idx].histogram[binIdx] << std::endl;
		}
	}

	//============================================================
	// write histogram values to file
	std::ofstream output_file;
	std::cout << "output: " << exportFile << std::endl;
	output_file.open(exportFile, ios::out | ios::app);

	bool gnuplot = false;
	for (int binIdx = 0; binIdx < histo_bins; ++binIdx){
		if (descriptors->points[histogram_std_idx].histogram[binIdx] != 0) //zero not needed for libsvm
			if (gnuplot){
				output_file << (binIdx + offset) << " " << descriptors->points[histogram_std_idx].histogram[binIdx] << "\n";
			}
			else {
				output_file << (binIdx + offset) << ":" << descriptors->points[histogram_std_idx].histogram[binIdx] << " ";
			}
	}
	output_file << "\n";
	output_file.close();


	//============================================================
	// visualize the histogram
	if (plot)
	{
		std::cout << "\nVisualisieren der Histogrammwerte startet!" << std::endl;
		pcl::visualization::PCLPlotter plotter;
		// (cloud, horizontal length of histogram, name of legend)
		plotter.addFeatureHistogram(*descriptors, histo_bins, filename, 1000, 1000);
		plotter.setTitle("OUR-CVFH Histogram");
		plotter.setXTitle("histogram bins");
		plotter.setYTitle("histogram values");
		plotter.plot();
	}

	return 0;
}


