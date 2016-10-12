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
    /// Interaktionslogik für LRA.xaml
    /// </summary>
    public partial class LRA : Window
    {
        List<Vector<double>> features;
        Matrix<double> E;
        Matrix<double> M;
        List<int> mask;
        double threshold = 0.05;


        public LRA()
        {
            InitializeComponent();
            features = new List<Vector<double>>();
        }

        private void initLRA(Vector<double> firstFeatures, int featureCount)
        {
            threshold = Convert.ToDouble(epsilon.Text.Replace('.',','));

            E = firstFeatures.ToColumnMatrix();

            var m = 1 / firstFeatures.DotProduct(firstFeatures); 
            M = DenseMatrix.Create(1,1,m);

            mask = null;
            mask = new List<int>();
        }

        private void calulateLRA(int featureCount)
        {
            var mBuilder = DenseMatrix.Build;
            List<double> collected_e = new List<double>();
            for (int i = 1; i < featureCount; i++)
            {
                Vector<double> fc = features.ElementAt(i);
                Vector<double> beta = M * E.Transpose() * fc;
                var temp_e = fc - E * M * E.Transpose() * fc;
                var e = temp_e.DotProduct(temp_e);
                collected_e.Add(e);

                if (e > threshold)
                {
                    E = E.Append(fc.ToColumnMatrix());

                    var y = beta.DotProduct(beta) / e;
                    M = M.Add(y);

                    //Build new bigger CoreMatrix and fill it
                    var betaE = -beta / e;
                    var newM = mBuilder.Dense(M.RowCount + 1, M.ColumnCount + 1);
                    for (var r = 0; r < newM.RowCount; r++)
                    {
                        if (r == newM.RowCount - 1)
                        {
                            for (var c = 0; c < newM.ColumnCount; c++)
                            {
                                if (c == newM.ColumnCount - 1)
                                    newM[r, c] = 1 / e;
                                else
                                    newM[r, c] = betaE[c];
                            }
                        }
                        else
                        {
                            for (var c = 0; c < newM.ColumnCount; c++)
                            {
                                if (c == newM.ColumnCount - 1)
                                    newM[r, c] = betaE[r];
                                //else if(c == r)
                                //    newM[r, c] = M[r, c] + y;
                                else
                                    newM[r, c] = M[r, c];
                            }
                        }
                    }
                    M = newM;

                    mask.Add(1);
                }
                else
                {
                    mask.Add(0);
                }
            }

            textBox.AppendText("\n================ " + select.Content + " ============ (e= " + epsilon.Text +") ===================");
            textBox.AppendText("\nMask:\t");
            foreach (var el in mask)
                textBox.AppendText(el.ToString() + " ");

            textBox.AppendText("\nValues:\t");
            foreach (var el in collected_e)
                textBox.AppendText(String.Format("{0:0,0.0} -- ",el.ToString()));

        }    

        private void select_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            fd.InitialDirectory = @"C:\CNTK\nets\Data\lra_test\";
            fd.ShowDialog();

            StreamReader sr = new StreamReader(fd.FileName);
            select.Content = fd.FileName.Split('\\').Last();
            features.Clear();

            while (!sr.EndOfStream)
            {
                var line = sr.ReadLine().Replace('.',',');
                var values = line.Split(' ');
                double[] convVals = Array.ConvertAll<string, double>(values, val => Convert.ToDouble(val));
                features.Add(DenseVector.OfEnumerable(convVals));
            }
            sr.Close();

            var firstfeature = features.First();
            features.RemoveAt(0);

            initLRA(firstfeature, features.Count);
            calulateLRA(features.Count);
        }

        private void textBox_Clear(object sender, MouseButtonEventArgs e)
        {
            textBox.Document.Blocks.Clear();

            //StreamReader sr = new StreamReader(@"C:\temp\SLRS\Handnet\SimpleOutput.Sll");
            //var entries = sr.ReadLine().Split(' ');
            //sr.Close();

            //StreamWriter sw = new StreamWriter(@"C:\temp\SLRS\Handnet\SimpleOutput4.Sll", false);
            //for (var i = 0; i < entries.Length; i++)
            //{
            //    if (i % 60 == 0) sw.Write("\n");

            //    var str = float.Parse(entries[i].Replace('.', ',')) < 3 ? 1 : 0;
            //    sw.Write(str + " ");
            //}
            //sw.Close();

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
