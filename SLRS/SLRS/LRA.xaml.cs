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
        }
    }
}
