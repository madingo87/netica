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
    public partial class FinalDataCreator : Window
    {
        List<Vector<double>> features;
        Matrix<double> E;
        Matrix<double> M;
        List<int> mask;
        double threshold = 0.05;


        public FinalDataCreator()
        {
            InitializeComponent();
            features = new List<Vector<double>>();
        }    

        private void convertToLSTMData_Click(object sender, RoutedEventArgs e)
        {
            //TODO: Dateien gleich --> evtl in einem durchgang?????

            StreamReader srHand = new StreamReader(@"C:\CNTK\SLRS\hands\Output.out");
            StreamReader srDist = new StreamReader(@"C:\CNTK\SLRS\distance\Output.out");

            List<string> listHandTemp = new List<string>();
            List<string> listDistTemp = new List<string>();
            List<string> listHand = new List<string>();
            List<string> listDist = new List<string>();

            int takeLastFew = 2;

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

            //TODO: Datei manuell abändern, da nach 0 die 10 folgt
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


            StreamWriter sw = new StreamWriter(@"C:\CNTK\SLRS\final\finalEvalData.txt", false);
            int seqPerGesture = 3;
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
            var testNbrs = new[] { "003", "004"};
            var trainData = new List<string>();
            StreamReader handsTrainData = new StreamReader(@"C:\temp\SLRS\hands\cntkAllData.ctd");
            StreamWriter handsTestData = new StreamWriter(@"C:\temp\SLRS\handsTestData.ctd");

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

            StreamWriter handsTrainDataNew = new StreamWriter(@"C:\temp\SLRS\handsTrainData.ctd", false);

            foreach (var line in trainData)
            {
                handsTrainDataNew.WriteLine(line);
            }

            handsTrainDataNew.Flush();
            handsTrainDataNew.Close();
        }

    }
}
