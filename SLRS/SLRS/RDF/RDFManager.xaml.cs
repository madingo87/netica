using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace SLRS
{
    public struct KinectData
    {
        public float X;
        public float Y;
        public float Depth;
    }
    public partial class RDFManager : Window
    {
        [DllImport("RDF.dll")]
        private unsafe static extern IntPtr initRDF(StringBuilder forest_file);
        IntPtr forest;

        [DllImport("RDF.dll")]
        private unsafe static extern int predictRDF(StringBuilder input, IntPtr Forest);

        [DllImport("RDF.dll")]
        private unsafe static extern int predictFileRDF(StringBuilder input_file, StringBuilder forest_file);

        [DllImport("RDF.dll")]
        private unsafe static extern void createForest(StringBuilder input_data);


        public int[] offsets;
        int depthFrameWidth = int.Parse(Properties.Resources.DepthHandFrame);  
        string workingDir = @"c:\temp\Tree\depth\";
        string forestDir = @"c:\temp\Tree\ranger.forest";


        public RDFManager()
        {
            InitializeComponent();

            offsets = new int[24];
            offsets[0] = -2;
            offsets[1] = -4;
            offsets[2] = -6;
            offsets[3] = -(2 * depthFrameWidth + 2);
            offsets[4] = -(4 * depthFrameWidth + 4);
            offsets[5] = -(6 * depthFrameWidth + 6);
            offsets[6] = -(2 * depthFrameWidth);
            offsets[7] = -(4 * depthFrameWidth);
            offsets[8] = -(6 * depthFrameWidth);
            offsets[9] = -(2 * depthFrameWidth - 2);
            offsets[10] = -(4 * depthFrameWidth - 4);
            offsets[11] = -(6 * depthFrameWidth - 6);
            offsets[12] = 2;
            offsets[13] = 4;
            offsets[14] = 6;
            offsets[15] = (2 * depthFrameWidth + 2);
            offsets[16] = (4 * depthFrameWidth + 4);
            offsets[17] = (6 * depthFrameWidth + 6);
            offsets[18] = (2 * depthFrameWidth);
            offsets[19] = (4 * depthFrameWidth);
            offsets[20] = (6 * depthFrameWidth);
            offsets[21] = (2 * depthFrameWidth - 2);
            offsets[22] = (4 * depthFrameWidth - 4);
            offsets[23] = (6 * depthFrameWidth - 6);

            lbl_forest.Content = forestDir;
            lbl_predictionPath.Content = workingDir;
        }

        private void btn_createForest_Click(object sender, RoutedEventArgs e)
        {
            //var trainData = @"C:\temp\tree\trainData.dat"; //dummy
            FileDialog fd = new OpenFileDialog();
            fd.InitialDirectory = @"c:\temp";
            fd.ShowDialog();

            createForest(new StringBuilder(fd.FileName));
        }

        private void btn_predictAll_Click(object sender, RoutedEventArgs e)
        {
            //if (forest == IntPtr.Zero )
            //    forest = initRDF(new StringBuilder(forestDir));

            new Thread(new ThreadStart(predictionThread)).Start();         
        }

        private void predictionThread()
        {
            DirectoryInfo dir = new DirectoryInfo(workingDir);
            var files = dir.GetFiles();
            addMessage(String.Format("Prediction gestartet... ( {0:HH:mm:ss} )\n", DateTime.Now));

            foreach (var f in files)
            {
                var startTime = DateTime.Now.Ticks;
                predictFrame(f.FullName);
                var endTime = DateTime.Now.Ticks;
                addMessage(String.Format("Predicted {0} in {1:0.0} s", f.Name, new TimeSpan(endTime - startTime).TotalSeconds));
            }
            addMessage(String.Format("Prediction fertig! ( {0:HH:mm:ss} )\n", DateTime.Now));
        }

        private void btn_predict_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.FolderBrowserDialog fd = new System.Windows.Forms.FolderBrowserDialog();
            fd.SelectedPath = @"c:\temp\Tree\depth";
            fd.ShowDialog();

            workingDir = fd.SelectedPath;
            lbl_predictionPath.Content = fd.SelectedPath;
        }

        private void btn_forest_Click(object sender, RoutedEventArgs e)
        {
            //forestFile = @"C:\temp\tree\ranger.forest"; //dummy
            FileDialog fd = new OpenFileDialog();
            fd.InitialDirectory = @"c:\temp\Tree";
            fd.ShowDialog();

            lbl_forest.Content = fd.FileName;
            forestDir = fd.FileName;

            forest = initRDF(new StringBuilder(forestDir));
        }

        private void predictFrame(string file)
        {
            StreamReader depthFile = new StreamReader(file);
            List<KinectData> depths = new List<KinectData>();

            //LOAD KINECT DATA (X Y Z)
            while (!depthFile.EndOfStream)
            {
                var line = depthFile.ReadLine().Split(' ');
                if (line.Length > 1)
                {
                    var dat = new KinectData();
                    dat.X = float.Parse(line[0]);
                    dat.Y = float.Parse(line[1]);
                    dat.Depth = float.Parse(line[2]);
                    depths.Add(dat);
                }
            }
            depthFile.Close();

            //WRITE PREDICTION INPUT
            StreamWriter predictionInput = new StreamWriter(@"C:\temp\predictionInput.dat",false);
            predictionInput.WriteLine("f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 f12 f13 f14 f15 f16 f17 f18 f19 f20 f21 f22 f23 f24 Class");

            float initDepth = depths[depths.Count / 2].Depth;

            for (int i = 0; i < depths.Count ; i++)
            {
                string featStr = "";
                foreach (var o in offsets)
                {
                    float entry = 0;
                    if (i + o < 0 || i + o >= depths.Count)
                        entry = 0; // if out of bounds --> 0
                    else
                    {
                        float thisDepth = depths[i + o].Depth != 0.0f ? depths[i + o].Depth : depths[i].Depth;
                        entry = (depths[i].Depth - initDepth) / thisDepth;
                     
                        if (float.IsInfinity(entry))
                            entry = 0; //Pixel invalid (infinite)
                    }       
                    featStr += (entry.ToString().Replace(',', '.') + " ");
                }

                predictionInput.WriteLine(featStr + "0");
                predictionInput.Flush();
            }
            predictionInput.Close();

            //CREATE PREDICTION FILE
            predictFileRDF(new StringBuilder(@"C:\temp\predictionInput.dat"), new StringBuilder(forestDir));

            //READ PREDICTION FILE
            StreamReader sr = new StreamReader(@"C:\Users\Martin\Documents\Visual Studio 2013\Projects\netica\SLRS\SLRS\bin\Debug\ranger.prediction");
            var predictions = sr.ReadToEnd().Split(' ').ToList();
            sr.Close();
            predictions.Remove(predictions.First());

            //CREATE PCD FILE
            string fileName = file.Split('\\').Last();
            string newFileName = fileName.Replace(".dth", ".pcd");
            string newPath = @"C:\temp\PCD\pcd\";
            StreamWriter pcdFile = new StreamWriter(newPath + newFileName, false);

            for (int i=0; i< predictions.Count; i++)
            {
                if (predictions[i] == "1")
                {
                    var point = Helper.depthToPCD(depths[i].X, depths[i].Y, depths[i].Depth);
                    pcdFile.WriteLine(String.Format("{0} {1} {2}", point.X.ToString().Replace(',', '.'), point.Y.ToString().Replace(',', '.'), point.Z.ToString().Replace(',', '.')));
                    pcdFile.Flush();
                }
            }
            
            pcdFile.Close();
        }

        private void addMessage(string info)
        {
            Dispatcher.BeginInvoke(new Action(delegate()
            {
                listBox.Items.Add(info);
                if (listBox.Items.Count > 10)
                {
                    listBox.SelectedIndex = listBox.Items.Count - 3; //index of filename
                    listBox.ScrollIntoView(listBox.Items[listBox.SelectedIndex]);
                }
            }));
        }
    }

}
//f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 f12 f13 f14 f15 f16 f17 f18 f19 f20 f21 f22 f23 f24 f25 f26 f27 f28 f29 f30 f31 f32 f33 f34 f35 f36 f37 f38 f39 f40 f41 f42 f43 f44 f45 f46 f47 f48 Class