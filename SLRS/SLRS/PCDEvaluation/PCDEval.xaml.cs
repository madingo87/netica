using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

using System.Runtime.InteropServices;
using System.IO;
using System.Threading;

namespace SLRS
{
    /// <summary>
    /// Interaktionslogik für PCDEval.xaml
    /// </summary>
    public partial class PCDEval : Window
    {
        string pcdPath = @"C:\temp\SLRS\pcd\";
        string vfhPath = @"C:\temp\SLRS\vfh\";
        string kfhPath = @"C:\temp\SLRS\kfh\";
        string ctdPath = @"C:\temp\SLRS\";

        public PCDEval()
        {
            InitializeComponent();
            lbl_file.Content = pcdPath;
        }

        [DllImport("PCDWrapperLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int evaluatePCD(StringBuilder filename, bool print, StringBuilder exportFile, int offset, bool plot);

        private void selectFolder_Click(object sender, RoutedEventArgs e)
        {
            FileDialog dlg = new OpenFileDialog();
            dlg.InitialDirectory = @"C:\temp";

            if (dlg.ShowDialog().Value)
            {
                selectFolder(dlg.FileName);
            }
        }

        public void selectFolder(string folder)
        {
            var file = folder.Split('\\').Last();
            FileInfo fInfo = new FileInfo(folder);
            var parentDir = fInfo.DirectoryName.Split('\\').Last();
            var dir = fInfo.DirectoryName.Remove(fInfo.DirectoryName.IndexOf(parentDir));
            //lbl_file.Content = dir;

            pcdPath = dir + "pcd\\";
            vfhPath = dir + "vfh\\";
            kfhPath = dir + "kfh\\";
            ctdPath = dir;

            checkDirs();
        }

        bool plot, print;
        DateTime time;
        private void convert_Click(object sender, RoutedEventArgs e)
        {
            time = DateTime.Now;
            listBox.Items.Add(String.Format("Konvertierung gestartet... ( {0:HH:mm:ss} )\n", time));

            plot = this.chk_plot.IsChecked ?? false;
            print = this.chk_print.IsChecked ?? false;

            new Thread(new ThreadStart(convert)).Start();
        }

        private void addMessage(string info)
        {
            Dispatcher.BeginInvoke(new Action(delegate()
            {
                listBox.Items.Add(info);
            }));
        }

        private void convert()
        {
            checkDirs();
            var dirInfo = new DirectoryInfo(pcdPath);
            var files = dirInfo.GetFiles("*.pcd");

            foreach (var file in files)
            {
                var filename = file.FullName.Split('\\').Last().Split('.').First();
                var vfhFile = vfhPath + filename + ".vfh";
                var kfhFile = kfhPath + filename + ".kfh";

                var res = exportVFH(file.FullName, vfhFile);
                addMessage("Histogramm erstellt (\"" + vfhFile + "\") [Returncode: " + res + "]");

                createKFH(vfhFile, kfhFile);
                addMessage("KFH Datei erstellt: \"" + kfhFile + "\"");
                var t = DateTime.Now - time;
                time = DateTime.Now;
                addMessage(String.Format("--- Time needed: {1}.{2} s\n", t.Minutes, t.Seconds, t.Milliseconds));
            }
            createCTD();
            addMessage(String.Format("\nKonvertierung abgeschlossen ==> CTD Dateien erstellt! ( {0:HH:mm:ss} )\n", DateTime.Now));

        }

        private int exportVFH(string file, string exportFile)
        {
            //pcd datei-header ggf hinzufügen
            if (addHeader(file))
                addMessage("Header bereits vorhanden!");
            else
                addMessage("Header hinzugefügt!");

            int res = evaluate(file, exportFile, false, plot);

            if (print)
            {
                if (File.Exists(exportFile))
                {
                    StreamReader sr = new StreamReader(exportFile);
                    addMessage(sr.ReadToEnd());
                    sr.Close();
                }
                else
                    addMessage("Datei \"" + exportFile + "\" nicht vorhanden!");
            }

            return res;
        }

        private unsafe int evaluate(string fileName, string exportFile, bool print, bool plot)
        {
            var file = new StringBuilder(fileName);
            var export = new StringBuilder(exportFile);

            var test = Environment.CurrentDirectory;

            return evaluatePCD(file, print, export, 0, plot);
        }

        private void createKFH(string filename, string exportFile)
        {
            StreamReader sr = new StreamReader(filename);
            var entries = sr.ReadToEnd().Split(' ');
            sr.Close();

            StreamWriter sw = new StreamWriter(exportFile, false);

            int entriesCounter = 0;
            for (int i = 0; i < 308; i++)
            {
                //avoid empty strings
                if (entries[entriesCounter] == "" || entries[entriesCounter] == "\r\n")
                    sw.Write(0);
                else
                {
                    var pair = entries[entriesCounter].Split(':');
                    if (Convert.ToInt16(pair[0]) == i)
                    {
                        sw.Write(pair[1].Replace('.', ','));
                        entriesCounter++;
                    }
                    else
                        sw.Write(0);
                }

                sw.Write(" ");
            }

            sw.Flush();
            sw.Close();
        }


        private void createCTD()
        {
            var dirInfo = new DirectoryInfo(kfhPath);
            var files = dirInfo.GetFiles("*.kfh");

            StreamWriter swRight = new StreamWriter(ctdPath + "cntkDataRight.ctd", false); // ctd = CNTK Train Data
            StreamWriter swLeft = new StreamWriter(ctdPath + "cntkDataLeft.ctd", false); // ctd = CNTK Train Data

            int gestureNo = 0;
            int sequenceNo = 0;
            bool left = true;

            foreach (var file in files)
            {
                //FileCode: dd_[left/right]_[gestureNumber]_[sequence]_[sequenceIndex]
                var fileCode = file.FullName.Split('_');

                left = fileCode[1] == "left";
                gestureNo = Convert.ToInt16(fileCode[2]);
                sequenceNo = Convert.ToInt16(fileCode[3]);

                StreamReader sr = new StreamReader(file.FullName);
                var content = sr.ReadToEnd().Split(' ');
                sr.Close();

                if (left)
                {
                    //      String.Format("{0:000}{1:000}\t|L {2}\t|F", gestureNumber, sequenceID+addId, Helper.gestureCode[gestureNumber]);
                    string line = String.Format("{0:000}{1:000}\t|L {2}\t|F", gestureNo, sequenceNo, Helper.gestureCode[gestureNo]);
                    foreach (var entry in content)
                    {
                        line += " " + entry.ToString().Replace(',', '.');
                    }
                    swLeft.WriteLine(line);
                }
                else
                {
                    string line = String.Format("{0:000}{1:000}\t|L {2}\t|F ", gestureNo, sequenceNo, Helper.gestureCode[gestureNo]);
                    foreach (var entry in content)
                    {
                        line += entry.ToString().Replace(',', '.') + " ";
                    }
                    swRight.WriteLine(line);
                }
                addMessage(file.Name + " konvertiert");
            }

            swLeft.Flush();
            swLeft.Close();
            swRight.Flush();
            swRight.Close();

            //Create Single File
            StreamReader srLeft = new StreamReader(ctdPath + "cntkDataLeft.ctd");
            StreamReader srRight = new StreamReader(ctdPath + "cntkDataRight.ctd");
            StreamWriter sw = new StreamWriter(ctdPath + "cntkAllData.ctd", false);

            while (!srLeft.EndOfStream)
            {
                var leftFeatures = srLeft.ReadLine();
                var rightFeatures = srRight.ReadLine().Split('F')[1];
                sw.WriteLine(leftFeatures + " " + rightFeatures);
            }
            sw.Flush();
            sw.Close();
            srLeft.Close();
            srRight.Close();
        }


        #region LIVE
        public List<double> convertExtern()
        {
            checkDirs();
            var dirInfo = new DirectoryInfo(pcdPath);
            var files = dirInfo.GetFiles("*.pcd");

            var fileL = pcdPath + "dd_left.pcd";
            var fileR = pcdPath + "dd_right.pcd";


            var filename = fileL.Split('\\').Last().Split('.').First();
            var vfhFile = vfhPath + filename + ".vfh";
            var res = exportVFHExtern(fileL, vfhFile);
            var kfhDataL = createKFH(vfhFile);

            filename = fileR.Split('\\').Last().Split('.').First();
            vfhFile = vfhPath + filename + ".vfh";
            res = exportVFHExtern(fileR, vfhFile);
            var kfhDataR = createKFH(vfhFile);

            return createCTD(kfhDataL, kfhDataR);
        }

        private int exportVFHExtern(string file, string exportFile)
        {
            //pcd datei-header ggf hinzufügen
            addHeader(file);
            return evaluate(file, exportFile, false, plot);
        }

        private List<double> createKFH(string filename)
        {
            StreamReader sr = new StreamReader(filename);
            var entries = sr.ReadToEnd().Split(' ');
            sr.Close();

            var kfhData = new List<double>();

            int entriesCounter = 0;
            for (int i = 0; i < 308; i++)
            {
                //avoid empty strings
                if (entries[entriesCounter] == "" || entries[entriesCounter] == "\r\n")
                    kfhData.Add(0);
                else
                {
                    var pair = entries[entriesCounter].Split(':');
                    if (Convert.ToInt16(pair[0]) == i)
                    {
                        kfhData.Add(double.Parse(pair[1].Replace('.', ',')));
                        entriesCounter++;
                    }
                    else
                        kfhData.Add(0);
                }
            }
            return kfhData;
        }

        private List<double> createCTD(List<double> kfhDataLeft, List<double> kfhDataRight)
        {
            var features = new List<double>();

            foreach (var entry in kfhDataLeft)
                features.Add(entry);

            foreach (var entry in kfhDataRight)
                features.Add(entry);

            return features;
        }

        #endregion

        #region HelperMethods
        private bool addHeader(string file)
        {
            string content;
            int width = 0;
            using (StreamReader sr = new StreamReader(file))
            {
                var firstline = sr.ReadLine();

                if (firstline.Contains(".PCD v.7"))
                    return true;

                content = firstline + "\n";
                width++;

                while (!sr.EndOfStream)
                {
                    content += sr.ReadLine() + "\n";
                    width++;
                }

                sr.Close();
            }

            using (StreamWriter sw = new StreamWriter(file, false))
            {
                sw.Write("# .PCD v.7 - Point Cloud Data file format\n" +
                            "VERSION .7\n" +
                            "FIELDS x y z\n" +
                            "SIZE 4 4 4\n" +
                            "TYPE F F F\n" +
                            "COUNT 1 1 1\n" +
                            "WIDTH " + width + "\n" +
                            "HEIGHT 1  \n" +
                            "VIEWPOINT 0 0 0 1 0 0 0\n" +
                            "POINTS " + width + "\n" +
                            "DATA ascii\n");

                sw.Write(content);

                sw.Flush();
                sw.Close();
            }

            return false;
        }

        private void checkDirs()
        {
            var pcdPathInfo = new DirectoryInfo(pcdPath);
            var vfhPathInfo = new DirectoryInfo(vfhPath);
            var kfhPathInfo = new DirectoryInfo(kfhPath);

            if (!pcdPathInfo.Exists) pcdPathInfo.Create();
            if (!vfhPathInfo.Exists) vfhPathInfo.Create();
            if (!kfhPathInfo.Exists) kfhPathInfo.Create();
        }

        private void listBoxClear_click(object sender, MouseEventArgs e)
        {
            this.listBox.Items.Clear();
        }

        #endregion
    }
}