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

namespace SLRS
{
    /// <summary>
    /// Interaktionslogik für FinalDataCreator.xaml
    /// </summary>
    public partial class Tools : Window
    {
        public Tools()
        {
            InitializeComponent();
        }

        private void convertToFinalData_Click(object sender, RoutedEventArgs e)
        {
            //TODO: Dateien gleich --> evtl in einem durchgang?????

            StreamReader srHand = new StreamReader(@"C:\temp\handsOutput.out");
            StreamReader srDist = new StreamReader(@"C:\temp\distOutput.out");

            List<string> listHandTemp = new List<string>();
            List<string> listDistTemp = new List<string>();
            List<string> listHand = new List<string>();
            List<string> listDist = new List<string>();

            int takeLastFew = 5;

            while (!srDist.EndOfStream)
            {
                var line = srDist.ReadLine();
                if (!line.Contains("==="))
                {
                    if (line.Contains('%'))
                        line = line.Remove(line.IndexOf('%'));
                    listDistTemp.Add(line.Trim());
                }
                else
                {
                    for (var i = takeLastFew; i > 0; i--)
                        listDist.Add(listDistTemp.ElementAt(listDistTemp.Count - i));
                    listDistTemp.Clear();
                }
            }
            srDist.Close();

            //TODO: Datei manuell abändern, da nach 0 die 10 folgt ?????
            while (!srHand.EndOfStream)
            {
                var line = srHand.ReadLine();
                if (!line.Contains("==="))
                {
                    if (line.Contains('%'))
                        line = line.Remove(line.IndexOf('%'));
                    listHandTemp.Add(line.Trim());
                }
                else
                {
                    for (var i = takeLastFew; i > 0; i--)
                        listHand.Add(listHandTemp.ElementAt(listHandTemp.Count - i));
                    listHandTemp.Clear();
                }
            }
            srHand.Close();


            StreamWriter sw = new StreamWriter(@"C:\CNTK\tests\final_test\rnnTrainData.txt", false);
            //StreamWriter sw = new StreamWriter(@"C:\CNTK\tests\final_test\rnnTestData.txt", false);

            int seqPerGesture = 150;
            int gestureNo = 0;
            int sequenceNo = 0;

            for (var i = 0; i < listDist.Count; i++)
            {
                sw.WriteLine(String.Format("{0:000}{1:000} |L {2} |F {3} {4}", gestureNo,sequenceNo, Helper.gestureCode[gestureNo], listDist[i], listHand[i]));

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
            int lastFew = 4;

            StreamReader distTrainData = new StreamReader(@"C:\CNTK\tests\single_test\MSdistanceData0-849.txt");
            StreamReader handsTrainData = new StreamReader(@"C:\CNTK\tests\single_test\MShandsData0-849.ctd");

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

            StreamWriter trainData = new StreamWriter(@"C:\CNTK\tests\single_test\singleTrainData.txt", false);
            string lastSeq = "";
            foreach (var dat in distData)
            {
                var sequenceDist = distData.Where(i => i.Key.StartsWith(dat.Key));
                if (lastSeq == sequenceDist.ElementAt(0).Key)
                    continue;
                lastSeq = sequenceDist.ElementAt(0).Key;

                var last4dist = sequenceDist.Skip(sequenceDist.Count() - lastFew);
                var sequenceHands = handsData.Where(i => i.StartsWith(dat.Key));
                var last4hands = sequenceHands.Skip(sequenceHands.Count() - lastFew);

                for (var i = 0; i < lastFew; i++)
                {
                    var line = last4hands.ElementAt(i) + " " + last4dist.ElementAt(i).Value;
                    trainData.WriteLine(line);
                    trainData.Flush();
                }
            }

            distTrainData.Close();
            handsTrainData.Close();
            trainData.Close();

            distData.Clear();
            handsData.Clear();

            //StreamReader distTestData = new StreamReader(@"C:\CNTK\tests\single_test\distanceTestData.txt");
            //StreamReader handsTestData = new StreamReader(@"C:\CNTK\tests\single_test\handsTestData.ctd");

            //while (!distTestData.EndOfStream)
            //{
            //    var line = distTestData.ReadLine().Split('|');
            //    if (line.Length > 0)
            //        distData.Add(new KeyValuePair<string, string>(line[0].Trim(), line[2].Split('F')[1].Trim()));
            //}
            //while (!handsTestData.EndOfStream)
            //{
            //    var line = handsTestData.ReadLine();
            //    if (!string.IsNullOrWhiteSpace(line))
            //        handsData.Add(line);
            //}

            //StreamWriter testData = new StreamWriter(@"C:\CNTK\tests\single_test\singleTestData.txt", false);
            //lastSeq = "";
            //foreach (var dat in distData)
            //{
            //    var sequenceDist = distData.Where(i => i.Key.StartsWith(dat.Key));
            //    if (lastSeq == sequenceDist.ElementAt(0).Key)
            //        continue;
            //    lastSeq = sequenceDist.ElementAt(0).Key;
            //    var last4dist = sequenceDist.Skip(sequenceDist.Count() - lastFew);
            //    var sequenceHands = handsData.Where(i => i.StartsWith(dat.Key));
            //    var last4hands = sequenceHands.Skip(sequenceHands.Count() - lastFew);

            //    for (var i = 0; i < lastFew; i++)
            //    {
            //        var line = last4hands.ElementAt(i) + " " + last4dist.ElementAt(i).Value;
            //        testData.WriteLine(line);
            //    }
            //}

            //distTestData.Close();
            //handsTestData.Close();
            //testData.Flush();
            //testData.Close();
        }

        private void sortData_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            fd.DefaultExt = @"c:\temp";
            fd.ShowDialog();

            StreamReader sr = new StreamReader(fd.FileName);
            //StreamReader sr = new StreamReader(@"c:\temp\distanceData0-169.txt");
            List<KeyValuePair<int, string>> entries = new List<KeyValuePair<int, string>>();
            while (!sr.EndOfStream)
            {
                var line = sr.ReadLine().Split('L');
                if (!string.IsNullOrWhiteSpace(line[0]))
                    entries.Add( new KeyValuePair<int,string>(int.Parse(line[0].Substring(0,6)),line[1].Trim()));
            }
            sr.Close();

            entries = entries.OrderBy(i => i.Key).ToList();

            StreamWriter sw = new StreamWriter(fd.FileName+"S");
            //StreamWriter sw = new StreamWriter(@"c:\temp\SdistanceData0-169.txt");

            foreach (var entry in entries)
            {
                sw.WriteLine(String.Format("{0:000000}\t|L {1}", entry.Key, entry.Value));
                sw.Flush();
            }
            sw.Close();
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
    }
}
