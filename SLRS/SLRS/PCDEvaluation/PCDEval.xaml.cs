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

namespace SLRS
{
    /// <summary>
    /// Interaktionslogik für PCDEval.xaml
    /// </summary>
    public partial class PCDEval : Window
    {
        public PCDEval()
        {
            InitializeComponent();
        }

        [DllImport("PCDWrapperLib.dll", CallingConvention=CallingConvention.Cdecl)]
        private static extern int evaluatePCD(StringBuilder filename, bool print, StringBuilder exportFile, int offset, bool plot);

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            FileDialog dlg = new OpenFileDialog();
            dlg.InitialDirectory = @"C:\temp\SLRS\hands";

            if (dlg.ShowDialog().Value)
            {
                var file = dlg.FileName.Split('\\').Last();
                lbl_file.Content = file;

                var exportFile = @"C:\temp\SLRS\PCDexport\" + file + ".vfh";

                if (addHeader(dlg.FileName))
                    listBox.Items.Add("Header bereits vorhanden!");
                else
                    listBox.Items.Add("Header hinzugefügt!");

                //Calc PCD
                listBox.Items.Add("Berechne Histrogramm und exportiere...");
                var print = this.chk_print.IsChecked ?? false;
                var plot = this.chk_plot.IsChecked ?? false;
                int res = evaluate(dlg.FileName, exportFile, print, plot);

                listBox.Items.Add("Exportiert nach \"" + exportFile + "\"");
                listBox.Items.Add("Returncode: " + res);
                listBox.Items.Add("=========== \n\n");
            }
        }
        private unsafe int evaluate(string fileName, string exportFile, bool print, bool plot)
        {
            var file = new StringBuilder(fileName);
            var export = new StringBuilder(exportFile);

            return evaluatePCD(file, print, export, 0, plot);           
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
                writePCDHeader(sw, width);

                sw.Write(content);

                sw.Flush();
                sw.Close();
            }

            return false;
        }

        private void writePCDHeader(StreamWriter sw, int width)
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
        }

        private void listBoxClear_click(object sender, MouseEventArgs e)
        {
            this.listBox.Items.Clear();
        }
    }
}