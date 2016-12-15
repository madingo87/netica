using OxyPlot;
using OxyPlot.Series;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
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

namespace SLRS
{
    /// <summary>
    /// Interaktionslogik für Graph.xaml
    /// </summary>
    public partial class Graph : Window
    {
        public static PlotModel GraphPlott { get; set; }

        public Graph()
        {
            InitializeComponent();
            calculateGraphData();
        }

        public void calculateGraphData()
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.InitialDirectory = @"c:\CNTK\nets\";
            dlg.Filter = "*.log|*.*";
            var result = dlg.ShowDialog();

            if (!(result.HasValue && result.Value))
            {
                MessageBox.Show("Fehler beim öffnen...");
                return;
            }

            string ceValue = "", errValue = "", epochTime = "", firstCE = "";
            
            //double y_factor = 1, x_factor = 1;
            int hitMax = 1, hit = 0;
            int epochs = 0;
            double epochSum = 0;

            // Create the plot model
            GraphPlott = new PlotModel { Title = "Training", Subtitle = dlg.FileName };

            // Create two line series (markers are hidden by default)
            var ceSeries = new LineSeries { Title = "CrossEntropy", MarkerType = MarkerType.Circle };
            var errSeries = new LineSeries { Title = "Error", MarkerType = MarkerType.Square };

            try
            {
                StreamReader reader = new StreamReader(dlg.FileName);

                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    if (line.Contains("maxEpochs = "))
                    {
                        epochs = Convert.ToInt16(line.Substring(line.IndexOf("maxEpochs = ") + 12).Replace('.', ','));
                    }
                    if (line.StartsWith("Finished Epoch"))
                    {
                        hit++;
                        if (hit % hitMax == 0)
                        {
                            line = line.ToLower();
                            ceValue = line.Substring(line.IndexOf("ce =") + 5, 10).Replace('.', ',');                       
                            if (String.IsNullOrWhiteSpace(firstCE)) firstCE = ceValue;

                            errValue = line.Substring(line.IndexOf("err = ") + 6, 11).Replace('.', ',');
                            if (errValue.Contains("e"))
                                errValue = convertExp(line.Substring(line.IndexOf("err = ") + 6, 15));
                            else
                                errValue.Trim();
                                
                            epochTime = line.Substring(line.IndexOf("epochtime") + 10, (line.Length - 1) - (line.IndexOf("epochtime") + 10)).Replace('.', ',');
                            epochSum += Convert.ToDouble(epochTime);

                            ceSeries.Points.Add(new DataPoint(hit,Convert.ToDouble(ceValue)));
                            errSeries.Points.Add(new DataPoint(hit, Convert.ToDouble(errValue)));
                        }
                    }
                }

                // Add the series to the plot model
                GraphPlott.Series.Add(errSeries);
                GraphPlott.Series.Add(ceSeries);
                graph.Model = Graph.GraphPlott;
                
                lbl_epochSum.Content = epochs;
                lbl_timeSum.Content = String.Format("{0:0.000} s", epochSum);

                reader.Close();
            }
            catch (Exception e)
            {
                MessageBox.Show("Fehler beim Lesen der Datei!\n\n"+e.Message);
                this.Close();
            }
        }

        private string convertExp(string expr)
        {
            //9.52925481e-005 -> 0.0000952925481
            var exp = int.Parse(expr.Substring(expr.IndexOf('-')+1));
            expr = expr.Remove(10);
            expr = expr.Replace(".", string.Empty);

            var zeros = "";
            for (var i = 1; i < exp; i++)
                zeros += "0";

            var newExpr = string.Format("0,{0}{1}", zeros, expr);
            return newExpr;
        }

        private void newGraph_Click(object sender, RoutedEventArgs e)
        {
            calculateGraphData();
        }
    }
}
