namespace SLRS
{
    using System;
    using System.ComponentModel;
    using System.Windows;

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
            LRA lraWindow = new LRA();
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


