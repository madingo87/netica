using Microsoft.MSR.CNTK.Extensibility.Managed;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Windows;

namespace SLRS
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void btn_eval_click(object sender, RoutedEventArgs e)
        {
            EvaluationWindow evalWindow = new EvaluationWindow();
            evalWindow.Show();
            //this.Close();
        }

        private void btn_start_click(object sender, RoutedEventArgs e)
        {
            KinectApp kinectApp = new KinectApp();
            kinectApp.Show();
            //this.Close();
        }

        private void btn_lra(object sender, RoutedEventArgs e)
        {
            FinalDataCreator lraWindow = new FinalDataCreator();
            lraWindow.Show();
            //this.Close();
        }

        private void btn_graph_click(object sender, RoutedEventArgs e)
        {
            Graph g = new Graph();
            g.Show();
            //this.Close();
        }

        private void btn_pcl_click(object sender, RoutedEventArgs e)
        {
            PCDEval pcdEval = new PCDEval();
            pcdEval.Show();
        }        
    }
}


