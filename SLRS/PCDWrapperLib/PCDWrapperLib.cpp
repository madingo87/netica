// PCDWrapperLib.cpp : Definiert die exportierten Funktionen f�r die DLL-Anwendung.
//

// Dies ist die Haupt-DLL.

#include "stdafx.h"

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
	std::cout << "Berechne OUR-CVFH..." << std::endl;

	pcl::PointCloud<pcl::PointXYZ>::Ptr object(new pcl::PointCloud<pcl::PointXYZ>);							// Cloud for storing the object.	
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);							// Object for storing the normals.	
	pcl::PointCloud<pcl::VFHSignature308>::Ptr descriptors(new pcl::PointCloud<pcl::VFHSignature308>);		// Object for storing the OUR-CVFH descriptors.
	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);					// KDTree as SearchMethod for Normalestimation
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;										// Object for estimating the normals - NormalEstimation estimates local surface properties (surface normals and curvatures)at each 3D point. 

	// Read a PCD file from disk.
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(filename, *object) != 0) {
		std::cout << "Unable to open or read file : " << filename << std::endl;
		return -1;
	}

	// Estimate the normals.
	normalEstimation.setInputCloud(object);
	normalEstimation.setRadiusSearch(0.05);				//0.03 -- radius: the sphere radius used as the maximum distance to consider a point a neighbor | Set the sphere radius that is to be used for determining the nearest neighbors used for the feature estimation. 
	normalEstimation.setSearchMethod(kdtree);
	normalEstimation.compute(*normals);

	// OUR-CVFH estimation object.
	pcl::OURCVFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::VFHSignature308> ourcvfh;
	ourcvfh.setInputCloud(object);
	ourcvfh.setInputNormals(normals);
	ourcvfh.setSearchMethod(kdtree);
	ourcvfh.setEPSAngleThreshold(15.0 / 180.0 * M_PI);	// 5.0 degrees. Sets max. deviation of the normals between two points so they can be clustered together
	ourcvfh.setCurvatureThreshold(3.0);					// 1.0 -- Sets curvature threshold for removing normals. 
	ourcvfh.setNormalizeBins(true);						// false -- Sets wether if the signatures should be normalized or not. 
	ourcvfh.setAxisRatio(1.0);							// 0.8 -- Set the minimum axis ratio between the SGURF axes. At the disambiguation phase, this will decide if additional Reference Frames need to be created, if ambiguous.
	ourcvfh.compute(*descriptors);

	std::cout << "Anzahl Punkte in Wolke: " << object->points.size() << std::endl;
	std::cout << "Berechnung des OUR-CVFH abgeschlossen!" << std::endl;


	int histo_bins = 308; // 308 is the standard of CVFH
	int histogram_std_idx = 0;

	//========================== print histogram values =================================
	if (print)
	{
		double xy[2];
		std::cout << "Histogrammwerte:" << std::endl;
		std::cout << "----------------------------" << std::endl;
		for (int binIdx = 0; binIdx < histo_bins; ++binIdx){
			xy[0] = binIdx;
			std::cout << binIdx;
			xy[1] = descriptors->points[histogram_std_idx].histogram[binIdx];
			std::cout << ": " << descriptors->points[histogram_std_idx].histogram[binIdx] << std::endl;
		}
	}

	//========================== write histogram values to file ======================
	std::ofstream output_file;
	std::cout << "Output: " << exportFile << std::endl;
	output_file.open(exportFile, ios::out);// | ios::app);

	bool gnuplot = false;
	for (int binIdx = 0; binIdx < histo_bins; ++binIdx){
		if (gnuplot){
			output_file << (binIdx + offset) << " " << descriptors->points[histogram_std_idx].histogram[binIdx] << "\n";
		}
		else {
			output_file << (binIdx + offset) << ":" << descriptors->points[histogram_std_idx].histogram[binIdx] << " ";
		}
	}
	output_file << "\n";
	output_file.close();


	//======================== visualize the histogram =============================
	if (plot)
	{
		std::cout << "Visualisieren der Histogrammwerte startet!" << std::endl;
		pcl::visualization::PCLPlotter plotter;
		plotter.addFeatureHistogram(*descriptors, histo_bins, filename, 1000, 1000); 		// (cloud, horizontal length of histogram, name of legend)
		plotter.setTitle("OUR-CVFH Histogram");
		plotter.setXTitle("histogram bins");
		plotter.setYTitle("histogram values");
		plotter.plot();
	}

	std::cout << "=========\n" << std::endl;

	return 0;
}


