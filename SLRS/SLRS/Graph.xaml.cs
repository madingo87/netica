using System;
using System.Collections.Generic;
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

        public Graph(string outputFile)
        {
            InitializeComponent();
            calculateGraph(outputFile);
        }

        public void calculateGraph(string outputFile)
        {
            string ceValue = "", errValue = "", epochTime = "", epochNum = "", firstCE = "";
            
            double y_factor = 1, x_factor = 1;
            int hitMax = 1, hit = 0;
            int epochs = 0;
            double epochSum = 0;

            Point err_p1 = new Point(0, 0), err_p2 = new Point(0, 0), ce_p1 = new Point(0, 0), ce_p2 = new Point(0, 0);

            try
            {
                StreamReader reader = new StreamReader(outputFile);

                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    if (line.StartsWith("CNTKCommandTrainInfo: train :"))
                    {
                        epochs = Convert.ToInt16(line.Substring(line.IndexOf("train : ") + 8).Replace('.', ','));

                        if (epochs <= 2000)
                        {
                            hitMax = 1;
                            y_factor = 150; // 500/150 = 3.3333 ist höchste ce zahl (angenommen)
                            x_factor = 2000 / epochs; //trainGraph.Width
                        }
                        else
                        {
                            hitMax = epochs / 2000;
                            y_factor = 125; // 4 ist höchste ce zahl (angenommen)
                            x_factor = 1;
                        }
                    }
                    if (line.StartsWith("Finished Epoch"))
                    {
                        hit++;
                        if (hit % hitMax == 0)
                        {
                            line = line.ToLower();
                            ceValue = line.Substring(line.IndexOf("ce =") + 5, 10).Replace('.', ',');
                            if (String.IsNullOrWhiteSpace(firstCE)) firstCE = ceValue;
                            errValue = line.Substring(line.IndexOf("err =") + 6, 10).Replace('.', ',');
                            epochTime = line.Substring(line.IndexOf("epochtime") + 10, (line.Length - 1) - (line.IndexOf("epochtime") + 10)).Replace('.', ',');
                            //epochNum = line.Substring(line.IndexOf('[') + 1, (line.IndexOf(" of ") - (line.IndexOf('[') + 1)));

                            epochSum += Convert.ToDouble(epochTime);

                            var x = hit * x_factor;
                            var ce_y = (trainGraph.Height - (Convert.ToDouble(ceValue) * y_factor));
                            var err_y = (trainGraph.Height - (Convert.ToDouble(errValue) * y_factor));

                            err_p2 = new Point(x, err_y);
                            ce_p2 = new Point(x, ce_y);

                            Line ce = new Line();
                            ce.Visibility = System.Windows.Visibility.Visible;
                            ce.Opacity = 0.5;
                            ce.StrokeThickness = 1;
                            ce.Stroke = Brushes.Tomato;
                            ce.X1 = ce_p1.X;
                            ce.Y1 = ce_p1.Y;
                            ce.X2 = ce_p2.X;
                            ce.Y2 = ce_p2.Y;

                            Line err = new Line();
                            err.Visibility = System.Windows.Visibility.Visible;
                            err.Opacity = 0.5;
                            err.StrokeThickness = 1;
                            err.Stroke = Brushes.Green;
                            err.X1 = err_p1.X;
                            err.Y1 = err_p1.Y;
                            err.X2 = err_p2.X;
                            err.Y2 = err_p2.Y;

                            trainGraph.Children.Add(ce);
                            trainGraph.Children.Add(err);

                            err_p1 = err_p2;
                            ce_p1 = ce_p2;
                        }
                    }
                }

                lbl_epochs.Content = epochs;
                lbl_maxErr.Content = String.Format("{0:0.000}", Convert.ToDouble(firstCE) + 1);
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

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            trainGraph.Width = window.Width-120;
        }
    }
}
