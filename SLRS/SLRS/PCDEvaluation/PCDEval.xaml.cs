﻿using Microsoft.Win32;
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
        string pcdPath = @"C:\temp\PCD\pcd\";
        string vfhPath = @"C:\temp\PCD\vfh\";
        string kfhPath = @"C:\temp\PCD\kfh\";
        string ctdPath = @"C:\temp\PCD\hands\";

        public PCDEval()
        {
            InitializeComponent();
            lbl_file.Content = @"C:\temp\PCD\";
        }

        [DllImport("PCDWrapperLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int evaluatePCD(StringBuilder filename, bool print, StringBuilder exportFile, int offset, bool plot);

        private void selectFolder_Click(object sender, RoutedEventArgs e)
        {
            FileDialog dlg = new OpenFileDialog();
            dlg.InitialDirectory = @"C:\temp";

            if (dlg.ShowDialog().Value)
            {
                var file = dlg.FileName.Split('\\').Last();
                FileInfo fInfo = new FileInfo(dlg.FileName);
                var parentDir = fInfo.DirectoryName.Split('\\').Last();
                var dir = fInfo.DirectoryName.Remove(fInfo.DirectoryName.IndexOf(parentDir));
                lbl_file.Content = dir;

                pcdPath = dir + "pcd\\";
                vfhPath = dir + "vfh\\";
                kfhPath = dir + "kfh\\";
                ctdPath = dir + "hands\\";

                checkDirs();
            }
        }


        bool plot, print;
        DateTime time;
        private void convert_Click(object sender, RoutedEventArgs e)
        {
            time = DateTime.Now;
            listBox.Items.Add(String.Format("Konvertierung gestartet... ( {0:HH:mm:ss} )\n", time));

            plot = this.chk_plot.IsChecked ?? false;
            print = this.chk_print.IsChecked ?? false;

            //var o = new { pcd = file.FullName, vfh = vfhFile, kfh = kfhFile };
            //Action<object> action = (object obj) =>
            //{
            //calculateHistogram(o);                   
            //};
            //var thisTask = Task.Factory.StartNew(action, o);
            //allTasks.Add(thisTask);
            //if (allTasks.Count > 5)
            //    Task.WaitAll(allTasks.ToArray());
            //}
            //Task.WaitAll(allTasks.ToArray());

            new Thread(new ThreadStart(convert)).Start();
        }

        private void convert()
        {
            checkDirs();
            var dirInfo = new DirectoryInfo(pcdPath);
            var files = dirInfo.GetFiles("*.pcd");

            foreach (var file in files)
            {
                try
                {
                    if (file.Length > 0)
                    {
                        var filename = file.FullName.Split('\\').Last().Split('.').First();
                        var vfhFile = vfhPath + filename + ".vfh";
                        var kfhFile = kfhPath + filename + ".kfh";

                        //pcd datei-header ggf hinzufügen
                        addHeader(file.FullName);
                        //if (addHeader(file))
                        //addMessage("Header bereits vorhanden!");
                        //else
                        //addMessage("Header hinzugefügt!");

                        var res = exportVFH(file.FullName, vfhFile);
                        //addMessage("Histogramm erstellt (\"" + vfhFile + "\") [Returncode: " + res + "]");

                        createKFH(vfhFile, kfhFile);
                        //addMessage("KFH Datei erstellt: \"" + kfhFile + "\"");
                        var t = DateTime.Now - time;
                        time = DateTime.Now;
                        addMessage(String.Format("-- (" + kfhFile + ") - [{0}.{1} s]", t.Seconds, t.Milliseconds));
                    }
                    else
                    {
                        if (file.FullName.Contains("left"))
                        {
                            //dann lösche datei mit right + filename
                            var vfhFilePath = vfhPath + file.FullName.Split('\\').Last().Split('.').First() + ".vfh";
                            var kfhFilePath = kfhPath + file.FullName.Split('\\').Last().Split('.').First() + ".kfh";
                            new FileInfo(vfhFilePath.Replace("left", "right")).Delete();
                            new FileInfo(kfhFilePath.Replace("left", "right")).Delete();
                            new FileInfo(file.FullName.Replace("left", "right")).Delete();
                            file.Delete();
                            files.ToList().Remove(file);
                        }
                        else
                        {
                            //dann lösche im nachgang die zugehörigen left datei
                            var vfhFilePath = vfhPath + file.FullName.Split('\\').Last().Split('.').First() + ".vfh";
                            var kfhFilePath = kfhPath + file.FullName.Split('\\').Last().Split('.').First() + ".kfh";
                            new FileInfo(vfhFilePath.Replace("right", "left")).Delete();
                            new FileInfo(kfhFilePath.Replace("right", "left")).Delete();
                            new FileInfo(file.FullName.Replace("right", "left")).Delete();
                            file.Delete();
                            files.ToList().Remove(file);
                        }
                    }
                }
                catch
                { }
            }
        
            createCTD();
            addMessage(String.Format("\nKonvertierung abgeschlossen ==> CTD Dateien erstellt! ( {0:HH:mm:ss} )\n", DateTime.Now));
        }

        private int exportVFH(string file, string exportFile)
        {
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

            var allEntries = new float[308];
            int entriesCounter = 0;
            for (int i = 0; i < 308; i++)
            {
                //avoid empty strings and line feeds
                if (!entries[entriesCounter].Contains(":"))
                    continue;

                else
                {
                    var pair = entries[entriesCounter].Split(':');
                    if (Convert.ToInt16(pair[0]) == i)
                    {
                        allEntries[i] = float.Parse(pair[1].Replace('.', ','));
                        entriesCounter++;
                    }
                    else
                        allEntries[i] = 0;
                }
            }

            var mean = allEntries.Sum() / allEntries.Length;
            var max = allEntries.Max<float>();

            StreamWriter sw = new StreamWriter(exportFile, false);
            foreach (var entry in allEntries)
            {
                sw.Write((entry-mean) / max);
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
                //addMessage(file.Name + " konvertiert");
            }

            swLeft.Flush();
            swLeft.Close();
            swRight.Flush();
            swRight.Close();

            //Create Single File
            StreamReader srLeft = new StreamReader(ctdPath + "cntkDataLeft.ctd");
            StreamReader srRight = new StreamReader(ctdPath + "cntkDataRight.ctd");
            StreamWriter sw = new StreamWriter(@"c:\temp\handsData.ctd", false);

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


        #region HelperMethods

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
            var ctdPathInfo = new DirectoryInfo(ctdPath);

            if (!pcdPathInfo.Exists) pcdPathInfo.Create();
            if (!vfhPathInfo.Exists) vfhPathInfo.Create();
            if (!kfhPathInfo.Exists) kfhPathInfo.Create();
            if (!ctdPathInfo.Exists) ctdPathInfo.Create();
        }

        private void listBoxClear_click(object sender, MouseEventArgs e)
        {
            this.listBox.Items.Clear();
        }

        #endregion
    }
}