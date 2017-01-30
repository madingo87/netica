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
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Double;
using MathNet.Numerics.Providers.LinearAlgebra;
using System.IO;
using Microsoft.Win32;
using System.Drawing;

namespace SLRS
{
    public partial class Tools : Window
    {
        public Tools()
        {
            InitializeComponent();
        }

        int takeLastFew = 4;
        private void convertToFinalData_Click(object sender, RoutedEventArgs e)
        {
            var outData = readOutputData();
            var listDist = outData[0];
            var listHand = outData[1];
            var listColor = outData[2];

            //StreamWriter sw = new StreamWriter(@"C:\temp\finalTrainData.txt", false);
            StreamWriter sw = new StreamWriter(@"C:\temp\finalTestData.txt", false);

            int seqPerGesture = 30;
            int gestureNo = 0;
            int sequenceNo = 0;

            for (var i = 0; i < listColor.Count; i++)
            {
                sw.WriteLine(String.Format("{0:000}{1:000} |L {2} |F {3} {4} {5}", gestureNo,sequenceNo, Helper.gestureCode[gestureNo], listDist[i], listHand[i], listColor[i]));

                if (i % takeLastFew == (takeLastFew-1)) sequenceNo++;
                if (sequenceNo == seqPerGesture)
                {
                    sequenceNo = 0;
                    gestureNo++;
                }
            }
            sw.Flush();
            sw.Close();

            MessageBox.Show("Done");
        }

        private void extractTestData_Click(object sender, RoutedEventArgs e)
        {
            //var testNbrs = new[] { "075", "076", "077", "078", "079", "080", "081", "082", "083", "084", "085", "086", "087", "088", "089" };
            var testNbrs = new[] { "070", "071", "072", "073", "074"};
            var trainData = new List<string>();
            //StreamReader handsTrainData = new StreamReader(@"C:\temp\cntkAllData.ctd");
            //StreamWriter handsTestData = new StreamWriter(@"C:\temp\handsTestData.ctd");
            StreamReader handsTrainData = new StreamReader(@"C:\CNTK\SLRS_train\final\finalData.txt");
            StreamWriter handsTestData = new StreamWriter(@"C:\CNTK\SLRS_train\final\finalTestData.txt");

            while (!handsTrainData.EndOfStream)
            {
                var line = handsTrainData.ReadLine();
                var sequenceNo = line.Substring(3, 3);
                if (testNbrs.Any(i => i == sequenceNo))
                    handsTestData.WriteLine(line);
                else
                    trainData.Add(line);
            }

            handsTestData.Flush();
            handsTestData.Close();
            handsTrainData.Close();

            //StreamWriter handsTrainDataNew = new StreamWriter(@"C:\temp\handsTrainData.ctd", false);
            StreamWriter handsTrainDataNew = new StreamWriter(@"C:\CNTK\SLRS_train\final\finalTrainData.ctd", false);

            foreach (var line in trainData)
            {
                handsTrainDataNew.WriteLine(line);
            }

            handsTrainDataNew.Flush();
            handsTrainDataNew.Close();
        }

        private void extractSingleData_Click(object sender, RoutedEventArgs e)
        {
            var distData = new List<KeyValuePair<string, string>>();
            var handsData = new List<string>();

            StreamReader distTrainData = new StreamReader(@"C:\CNTK\tests\single_test\distanceTrainData70-79.txt");
            StreamReader handsTrainData = new StreamReader(@"C:\CNTK\tests\single_test\handsTrainData70-79.ctd");

            while (!distTrainData.EndOfStream)
            {
                var line = distTrainData.ReadLine().Split('|');
                if (line.Length > 0)
                    distData.Add(new KeyValuePair<string, string>(line[0].Trim(), line[2].Split('F')[1].Trim()));
            }
            while (!handsTrainData.EndOfStream)
            {
                var line = handsTrainData.ReadLine();
                if (!string.IsNullOrWhiteSpace(line))
                    handsData.Add(line);
            }

            StreamWriter trainData = new StreamWriter(@"C:\CNTK\tests\single_test\singleTestData.txt", false);
            string lastSeq = "";
            foreach (var dat in distData)
            {
                var sequenceDist = distData.Where(i => i.Key.StartsWith(dat.Key));
                if (lastSeq == sequenceDist.ElementAt(0).Key)
                    continue;
                lastSeq = sequenceDist.ElementAt(0).Key;

                var last4dist = sequenceDist.Skip(sequenceDist.Count() - takeLastFew);
                var sequenceHands = handsData.Where(i => i.StartsWith(dat.Key));
                var last4hands = sequenceHands.Skip(sequenceHands.Count() - takeLastFew);

                for (var i = 0; i < takeLastFew; i++)
                {
                    try
                    {
                        var line = last4hands.ElementAt(i) + " " + last4dist.ElementAt(i).Value;
                        trainData.WriteLine(line);
                        trainData.Flush();
                    }
                    catch // if not all last few possible
                    { }
                }
            }

            distTrainData.Close();
            handsTrainData.Close();
            trainData.Close();

            distData.Clear();
            handsData.Clear();

            MessageBox.Show("Done");
        }

        private void sortData_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            fd.DefaultExt = @"c:\temp";
            fd.ShowDialog();

            StreamReader sr = new StreamReader(fd.FileName);
            List<KeyValuePair<int, string>> entries = new List<KeyValuePair<int, string>>();

            if (fd.FileName.EndsWith("map"))
            {
                while (!sr.EndOfStream)
                {
                    var line = sr.ReadLine();
                    if (!string.IsNullOrWhiteSpace(line))
                    {
                        var key = line.Substring(13,10).Replace("_",string.Empty);
                        entries.Add(new KeyValuePair<int, string>(int.Parse(key), line));
                    }
                }
                sr.Close();

                entries = entries.OrderBy(i => i.Key).ToList();

                StreamWriter sw = new StreamWriter(fd.FileName + "S");
                foreach (var entry in entries)
                {
                    sw.WriteLine(entry.Value);
                    sw.Flush();
                }
                sw.Close();
            }
            else
            {
                while (!sr.EndOfStream)
                {
                    var line = sr.ReadLine().Split('L');
                    if (!string.IsNullOrWhiteSpace(line[0]))
                        entries.Add(new KeyValuePair<int, string>(int.Parse(line[0].Substring(0, 6)), line[1].Trim()));
                }
                sr.Close();

                entries = entries.OrderBy(i => i.Key).ToList();

                StreamWriter sw = new StreamWriter(fd.FileName + "S");
                foreach (var entry in entries)
                {
                    sw.WriteLine(String.Format("{0:000000}\t|L {1}", entry.Key, entry.Value));
                    sw.Flush();
                }
                sw.Close();
            }
        }

        private void multiplyData_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            fd.DefaultExt = @"c:\temp";
            fd.ShowDialog();

            StreamReader sr = new StreamReader(fd.FileName);
            List<KeyValuePair<int, string>> entries = new List<KeyValuePair<int, string>>();
            while (!sr.EndOfStream)
            {
                var line = sr.ReadLine().Split('L');
                if (!string.IsNullOrWhiteSpace(line[0]))
                    entries.Add(new KeyValuePair<int, string>(int.Parse(line[0].Substring(0, 6)), line[1].Trim()));
            }
            sr.Close();

            int factor = 3;
            int entryCount = 60; //anzahl der schritte pro geste
            StreamWriter sw = new StreamWriter(fd.FileName+"M");
            for (var i = 0; i < factor; i++)
            {
                foreach (var entry in entries)
                {
                    int key = entry.Key + (entryCount * i);
                    sw.WriteLine("{0:000000}\t|L {1}", key, entry.Value);
                    sw.Flush();
                }
            }
            sw.Close();
        }

        private void createRDFData_Click(object sender, RoutedEventArgs e)
        {
            var outData = readOutputData();
            var listDist = outData[0];
            var listHand = outData[1];

            //StreamWriter sw = new StreamWriter(@"C:\temp\rdfTrainData.txt", false);
            StreamWriter sw = new StreamWriter(@"C:\temp\rdfTestData.txt", false);
            for (int i = 0; i < 80; i++)
                sw.Write(String.Format("f{0} ", i));
            sw.Write("Class\n");

            int seqPerGesture = 20;
            int gestureNo = 0;
            int sequenceNo = 0;

            for (var i = 0; i < listDist.Count; i++)
            {
                if (listDist[i].Length > 0 && listHand[i].Length > 0)
                    sw.WriteLine(String.Format("{0} {1} {2}", listDist[i], listHand[i], gestureNo));

                if (i % takeLastFew == (takeLastFew - 1)) sequenceNo++;
                if (sequenceNo == seqPerGesture)
                {
                    sequenceNo = 0;
                    gestureNo++;
                }
            }
            sw.Flush();
            sw.Close();

            MessageBox.Show("Done");
        }

        private List<string>[] readOutputData()
        {
            StreamReader srHand = new StreamReader(@"C:\temp\handsOutput.out");
            StreamReader srDist = new StreamReader(@"C:\temp\distOutput.out");
            StreamReader srColor = new StreamReader(@"C:\temp\colorOutput.out");

            List<string> listHandTemp = new List<string>();
            List<string> listDistTemp = new List<string>();
            List<string> listHand = new List<string>();
            List<string> listDist = new List<string>();
            List<string> listColorTemp = new List<string>();
            List<string> listColor = new List<string>();

            while (!srDist.EndOfStream)
            {
                var line = srDist.ReadLine();
                if (!line.Contains("==="))
                {
                    if (line.Contains('%')) line = line.Remove(line.IndexOf('%'));
                    if (!string.IsNullOrWhiteSpace(line)) listDistTemp.Add(line.Trim());
                }
                else
                {
                    while (listDistTemp.Count < takeLastFew)
                        listDistTemp = padList(listDistTemp);

                    for (var i = takeLastFew; i > 0; i--)
                        listDist.Add(listDistTemp.ElementAt(listDistTemp.Count - i));
                    listDistTemp.Clear();
                }
            }
            srDist.Close();

            while (!srHand.EndOfStream)
            {
                var line = srHand.ReadLine();
                if (!line.Contains("==="))
                {
                    if (line.Contains('%')) line = line.Remove(line.IndexOf('%'));
                    if (!string.IsNullOrWhiteSpace(line)) listHandTemp.Add(line.Trim());
                }
                else
                {
                    while (listHandTemp.Count < takeLastFew)
                        listHandTemp = padList(listHandTemp);

                    for (var i = takeLastFew; i > 0; i--)
                        listHand.Add(listHandTemp.ElementAt(listHandTemp.Count - i));
                    listHandTemp.Clear();
                }
            }
            srHand.Close();

            while (!srColor.EndOfStream)
            {
                var line = srColor.ReadLine();
                if (!line.Contains("==="))
                {
                    if (line.Contains('%')) line = line.Remove(line.IndexOf('%'));
                    if (!string.IsNullOrWhiteSpace(line))
                        listColorTemp.Add(line.Trim());
                }
                else
                {
                    while (listColorTemp.Count < takeLastFew)
                        listColorTemp = padList(listColorTemp);

                    for (var i = takeLastFew; i > 0; i--)
                        listColor.Add(listColorTemp.ElementAt(listColorTemp.Count - i));
                    listColorTemp.Clear();
                }
            }
            srColor.Close();

            return new List<string>[3] { listDist, listHand, listColor };
        }

        private List<string> padList(List<string> list)
        {
            string[] newList = new string[list.Count*2];
            int i = 0;
            foreach (var el in list)
            {
                newList[i++] = el;
                newList[i++] = el;
            }

            return newList.ToList();
        }

        private void mergeImages_Click(object sender, RoutedEventArgs e)
        {
            var files = Directory.GetFiles(@"c:\temp\single");

            //map - file creator
            //StreamWriter sw = new StreamWriter(@"C:\CNTK\tests\color_test\data\colorMap.map",false);
            //foreach (var file in files)
            //{
            //    try
            //    {
            //        var filename = file.Split('\\').Last();
            //        var gestureNo = int.Parse(filename.Substring(filename.IndexOf("Hand") + 4, 3));
            //        sw.WriteLine(String.Format("...\\{0}\t{1}", filename, gestureNo));
            //        sw.Flush();
            //    }
            //    catch { }
            //}
            //sw.Close();

            foreach (var file in files)
            {
                FileInfo fi = new FileInfo(file);
                if (file.Contains("_00.png") || file.Contains("_01.png") || file.Contains("_02.png"))
                {
                    fi.Delete();
                    continue;
                }

                if (fi.FullName.Contains("colorHandL"))
                {
                    string rightImg = fi.FullName.Replace("colorHandL", "colorHandR");
                    Bitmap bmpL = new Bitmap(fi.FullName);
                    Bitmap bmpR = new Bitmap(rightImg);

                    Bitmap bitmap = new Bitmap(bmpL.Width + bmpR.Width, Math.Max(bmpL.Height, bmpR.Height));
                    using (Graphics g = Graphics.FromImage(bitmap))
                    {
                        g.DrawImage(bmpL, 0, 0);
                        g.DrawImage(bmpR, bmpL.Width, 0);
                    }
                    //colorHandL000_001_03.png
                    var newFilename = file.Substring(file.IndexOf("colorHandL") + 10, 14);
                    bitmap.Save(@"C:\temp\colorHand" + newFilename);
                }
            }

            StreamReader sr = new StreamReader(@"C:\temp\colorMapOld.map");
            List<string> entries = new List<string>();
            while (!sr.EndOfStream)
            {
                var evenLine = sr.ReadLine();
                if (!(evenLine.Contains("_00.png") || evenLine.Contains("_01.png") || evenLine.Contains("_02.png")))
                    entries.Add(evenLine.Replace("colorHandL", "colorHand"));
                sr.ReadLine();
            }
            sr.Close();

            StreamWriter sw = new StreamWriter(@"C:\temp\colorMap.map", false);
            foreach (var entry in entries)
                sw.WriteLine(entry);
            sw.Flush();
            sw.Close();

            MessageBox.Show("Done");
        }
    }
}
