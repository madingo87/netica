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

        [DllImport("PCDWrapperLib.dll")]
        private static extern int evaluatePCD(StringBuilder filename, bool print, StringBuilder exportFile, int offset, bool plot);

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            FileDialog dlg = new OpenFileDialog();
            dlg.InitialDirectory = @"C:\temp\SLRS\hands";

            if (dlg.ShowDialog().Value)
            {
                lbl_file.Content = dlg.FileName.Split('\\').Last();

                var exportFile = @"C:\temp\SLRS\PCDexport";

                //Calc PCD
                int res = evaluate(dlg.FileName, exportFile);

                listBox.Items.Add("Exportiert nach \" " + exportFile +" \"");
                listBox.Items.Add("Returncode: " + res);
            }
        }
        private unsafe int evaluate(string fileName, string exportFile)
        {
            var file = new StringBuilder(fileName);
            var export = new StringBuilder(exportFile);

            return evaluatePCD(file, false, export, 0, false);           
        }
    }
}