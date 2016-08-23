using System;
using System.Collections;
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
    /// Interaktionslogik für EvaluationWindow.xaml
    /// </summary>
    public partial class EvaluationWindow : Window
    {
        public EvaluationWindow()
        {
            InitializeComponent();
        }

        string outputFile, mappingFile;

        private void btn_select_output_click(object sender, RoutedEventArgs e)
        {
            box_eval.Document.Blocks.Clear();
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.InitialDirectory = @"c:\CNTK\nets\";
            var result = dlg.ShowDialog();

            if (result.HasValue && result.Value)
            {
                outputFile = dlg.FileName;
                lbl_output.Content = dlg.FileName;
            }

            btn_selectMappingFile.IsEnabled = true;
            btn_writeMappings.IsEnabled = true;
            var reader = new StreamReader(new FileStream(outputFile, FileMode.Open));
            char[] buf = new char[10];
            reader.BaseStream.Seek(-10, SeekOrigin.End);
            reader.ReadBlock(buf, 0, 10);
            string strBuf = new string(buf);
            if (strBuf.Contains("mapped"))
            {
                lbl_mapping.Content = "already mapped";
                btn_selectMappingFile.IsEnabled = false;
                btn_writeMappings.IsEnabled = false;
            }
            reader.Close();

        }

        private void btn_select_mapping_click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.InitialDirectory = @"c:\CNTK\nets\Data\";
            var result = dlg.ShowDialog();

            if (result.HasValue && result.Value)
            {
                mappingFile = dlg.FileName;
                lbl_mapping.Content = dlg.FileName.Split('\\').Last();
            }
        }

        private void btn_eval_click(object sender, RoutedEventArgs e)
        {
            var reader = new StreamReader(new FileStream(outputFile, FileMode.Open));

            var calculatedSequence = new List<string>();
            var calculatedLatency = new List<KeyValuePair<string,int>>();
            float countAll = 0;
            float countHit = 0;
            int latency = 0;

            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                if (line.Contains("==="))               
                {
                    calculatedSequence.Clear();
                    latency = 0;
                }

                if (line.Contains("%"))
                {
                    int sequenceHit = 0;
                    countAll++;

                    calculatedSequence.Add(line.Split('%')[0].Trim());

                    var originalLabel = line.Split('%')[1].Substring(1).Trim();

                    foreach (string lbl in calculatedSequence)
                    {
                        if (!lbl.Equals(originalLabel) && sequenceHit == 0)
                            latency++;
                        else
                            sequenceHit++;
                    }
                                                  
                    // EVALUATION: berechnete Werte entsprechen zu einem drittel des erwarteten Labels und das ziellabel ist mindestens einmal in den letzten 5 Frames enthalten
                    if (sequenceHit >= calculatedSequence.Count*0.33 && calculatedSequence.GetRange(calculatedSequence.Count-6,5).Contains(originalLabel))
                        countHit++;
                    else
                        latency = -1;

                    calculatedLatency.Add(new KeyValuePair<string,int>(originalLabel,latency));
                }
                else
                {
                    if (!String.IsNullOrWhiteSpace(line))
                        calculatedSequence.Add(line.Trim());
                }
            }

            reader.Close();

            float q = countHit / countAll;
            double latOverall =  calculatedLatency.Sum(i => i.Value) / calculatedLatency.Count;

            box_eval.Document.Blocks.Add(new Paragraph(new Run(String.Format("Gesamt:\t{0}\nTreffer:\t{1}\nQuote:\t{2} %\n=================================\n",
                countAll, countHit, q * 100, latOverall*100))));

            var latencyOutput = "";
            var latencySum = 0.0;
            var latencyCount = 0;
            foreach (var lat in calculatedLatency)
            {                
                if (lat.Value >= 0)
                {
                    latencyOutput += String.Format("'{0}' erkannt nach {1} Frames. (= {2} ms)\n", lat.Key, lat.Value, lat.Value * 100);//100ms (3*33ms bei 30 fps)
                    latencySum += lat.Value;
                    latencyCount++;
                }
                else
                    latencyOutput += String.Format("'{0}' nicht erkannt!\n", lat.Key);
            }
            box_eval.Document.Blocks.Add(new Paragraph(new Run(String.Format("{0}\nDurchschnittliche Latenz aller erkannten Labels: {1:000.0} ms",latencyOutput, (latencySum/latencyCount)*100))));
        }

        private void btn_write_mappings_click(object sender, RoutedEventArgs e)
        {
            int mCount;
            string[] words;
            try
            {
                mCount = Convert.ToInt32(mappingsCount.Text);
                mappingsCount.ClearValue(TextBox.BackgroundProperty);               
            }
            catch
            {
                //MessageBox.Show("Bitte Anzahl (int) der Testdaten pro Wort eintragen!");
                mappingsCount.Background = Brushes.OrangeRed;
                return;
            }
            try
            {
                var mappings = new StreamReader(new FileStream(mappingFile, FileMode.Open));
                lbl_mapping.ClearValue(TextBox.BackgroundProperty);  
                words = mappings.ReadToEnd().Split('\n');
                for (var i = 0; i < words.Length; i++)
                    words[i] = String.Format(" {0}\n",words[i].Trim().Replace('\r', ' '));

                mappings.Close();
            }
            catch
            {
                lbl_mapping.Background = Brushes.OrangeRed;
                return;
            }

            try
            {
                var output = new FileStream(outputFile, FileMode.Open, FileAccess.ReadWrite);
                lbl_output.ClearValue(TextBox.BackgroundProperty);  

                byte[] line = new byte[8];
                output.Seek(-8, SeekOrigin.End);
                output.Read(line, 0, 8);
                var mappedEntry = Encoding.UTF8.GetString(line);
                if (mappedEntry.Contains("mapped"))
                {
                    MessageBox.Show("Bereits gemapped");
                    return;
                }
                output.Seek(0, SeekOrigin.Begin);

                var count = 0;
                var index = 0;
                byte[] word;

                for (int i = 0; i < output.Length; i++)
                {
                    var thisByte = new byte[1] { (byte)output.ReadByte() };
                    var thisChar = Encoding.UTF8.GetString(thisByte);

                    if (thisChar.Contains("%"))
                    {                        
                        word = Encoding.UTF8.GetBytes(words[index]);
                        output.Write(word, 0, word.Length);

                        count++;
                        if (count % mCount == 0)
                            index++;
                    }
                }

                word = Encoding.UTF8.GetBytes("\nmapped");
                output.Write(word, 0, word.Length);

                output.Flush();
                output.Close();
            } 
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                lbl_output.Background = Brushes.OrangeRed;
                return;
            }
        }

        private void btn_graph_click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.InitialDirectory = @"c:\CNTK\nets\";
            dlg.Filter = "*.log|*.*";
            var result = dlg.ShowDialog();

            if (result.HasValue && result.Value)
            {
                Graph g = new Graph(dlg.FileName);
                g.Show();
            }
            else
                MessageBox.Show("Fehler beim öffnen...");
        }
    }
}
