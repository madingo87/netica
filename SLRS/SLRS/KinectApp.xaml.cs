﻿using System;
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
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using Microsoft.Kinect;
using System.Windows.Media.Media3D;


namespace SLRS
{
    /// <summary>
    /// Interaktionslogik für KinectApp.xaml
    /// </summary>
    public partial class KinectApp : Window, INotifyPropertyChanged
    {
                /// <summary>
        /// Size of the RGB pixel in the bitmap
        /// </summary>
        private const int BytesPerPixel = 4;
        // body/depth(512x424) | color(1920x1080) 

        private KinectSensor kinectSensor = null;

        private FrameDescription depthFrameDescription = null;
        private DepthFrameReader depthFrameReader = null;
        private byte[] depthPixels;
        private const int MapDepthToByte = 8000 / 256;
        private WriteableBitmap depthBitmapLeft = null;
        private WriteableBitmap depthBitmapRight = null;
        private int windowSize = 200;
        
        private ColorFrameReader colorFrameReader = null;
        private FrameDescription colorFrameDescription = null;
        private WriteableBitmap colorBitmap = null;

        private BodyFrameReader bodyFrameReader = null;
        private DrawingGroup bodyDrawingGroup, leftHandDrawingGroup, rightHandDrawingGroup;
        private DrawingImage imageSource;
        private DrawingImage leftHandImage;
        private DrawingImage rightHandImage;

        private CameraSpacePoint leftHandPostition;
        private CameraSpacePoint rightHandPostition;

        private int[] allJointsForUI = new[] { 4, 5, 8, 9 };
        private CameraSpacePoint nx, ny, nz;
        private CoordinateMapper coordinateMapper = null;
        private Body[] bodies = null;

        private StreamWriter swData = new StreamWriter(@"c:/temp/lstm/trainData.txt", true);
        private int sequenceID = 0; 
        private int gestureNumber;
        private string[] gestureWord = new string[] { 
            "arbeiten", "alle", "begleiten", "besprechung", "bruder/schwester", 
            "helfen", "immer", "internet", "was", "schluss", 
            "schreiben", "termin", "verschieben", "warten", "besser", 
            "danke", "idee", "sonne", "warum", "kinder" }; 
        private string[] gestureCode = new string[] { 
            "1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0", 
            "0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
            "0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
            "0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
            "0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
            "0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
            "0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0",
            "0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0",
            "0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0",
            "0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0",
            "0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0",
            "0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0",
            "0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0",
            "0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0",
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0",
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0",
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0",
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0",
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0",
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1"};  

        private int maxTestData = 6;
        private int maxTrainData = 24;

        private string statusText = null;


        public KinectApp()
        {
            this.kinectSensor = KinectSensor.GetDefault();

            this.depthFrameDescription = this.kinectSensor.DepthFrameSource.FrameDescription;
            this.depthFrameReader = this.kinectSensor.DepthFrameSource.OpenReader();
            this.depthFrameReader.FrameArrived += depthFrameReader_FrameArrived;
            this.depthBitmapLeft = new WriteableBitmap(windowSize, windowSize, 96.0, 96.0, PixelFormats.Gray8, null);
            this.depthBitmapRight = new WriteableBitmap(windowSize, windowSize, 96.0, 96.0, PixelFormats.Gray8, null);

            this.depthPixels = new byte[windowSize * windowSize];

            this.colorFrameDescription = this.kinectSensor.ColorFrameSource.CreateFrameDescription(ColorImageFormat.Bgra);
            this.colorFrameReader = this.kinectSensor.ColorFrameSource.OpenReader();
            this.colorFrameReader.FrameArrived += this.colorFrameReader_FrameArrived;     
            this.colorBitmap = new WriteableBitmap(colorFrameDescription.Width, colorFrameDescription.Height, 96.0, 96.0, PixelFormats.Bgr32, null);

            this.bodyFrameReader = this.kinectSensor.BodyFrameSource.OpenReader();
            this.bodyFrameReader.FrameArrived += bodyFrameReader_FrameArrived;
            
            this.bodyDrawingGroup = new DrawingGroup();
            this.imageSource = new DrawingImage(bodyDrawingGroup);
            this.leftHandDrawingGroup = new DrawingGroup();
            this.leftHandImage = new DrawingImage(leftHandDrawingGroup);
            this.rightHandDrawingGroup = new DrawingGroup();
            this.rightHandImage = new DrawingImage(rightHandDrawingGroup);

            leftHandPostition = new CameraSpacePoint();
            rightHandPostition = new CameraSpacePoint();
            pl_old = new DepthSpacePoint() { X = depthFrameDescription.Width / 2, Y = depthFrameDescription.Height / 2 };
            pr_old = new DepthSpacePoint() { X = depthFrameDescription.Width / 2, Y = depthFrameDescription.Height / 2 };

            this.coordinateMapper = this.kinectSensor.CoordinateMapper;

            this.kinectSensor.IsAvailableChanged += this.Sensor_IsAvailableChanged;

            this.kinectSensor.Open();

            this.DataContext = this;

            this.InitializeComponent();
        }

       
        #region Properies

        public event PropertyChangedEventHandler PropertyChanged;

        public ImageSource LeftHandSource
        {
            get { return this.depthBitmapLeft; }
        }
        public ImageSource RightHandSource
        {
            get { return this.depthBitmapRight; }
        }
        public ImageSource ImageSource
        {
            get { return this.imageSource; }
        }     

        public string StatusText
        {
            get { return this.statusText; }
            set
            {
                if (this.statusText != value)
                {
                    this.statusText = value;

                    // notify any bound elements that the text has changed
                    if (this.PropertyChanged != null)
                    {
                        this.PropertyChanged(this, new PropertyChangedEventArgs("StatusText"));
                    }
                }
            }
        }

        #endregion

        #region EventHandler

        private void btn_record_click(object sender, RoutedEventArgs e)
        {
            switch (btn_record.Content.ToString())
            {             
                case "Begin Record":
                    sequenceID++;           
                    btn_record.Content = "Start";
                    break;

                case "Start":
                    btn_record.Content = "Stop";
                    break;

                case "Stop":
                    sequenceID++; 
                    btn_record.Content = "Start";
                    break;
            }
            if (sequenceID != 0)
            {
                var dataType = sequenceID <= maxTrainData ? "train" : "test";
                StatusText = gestureWord[gestureNumber] + " (" + dataType + " [" + ((maxTrainData + maxTestData) - sequenceID + 1) + "])";
            }
             
            if (sequenceID == maxTrainData)
            {
                swData.Flush();
                swData.Close();
                swData = new StreamWriter(@"c:/temp/lstm/testData.txt", true);
            }           

            if (sequenceID == (maxTrainData + maxTestData))
            {
                if (gestureNumber + 1 < gestureWord.Length)
                {
                    sequenceID = 0;
                    gestureNumber++;

                    swData.Flush();
                    swData.Close();
                    swData = new StreamWriter(@"c:/temp/lstm/trainData.txt", true);
                }
                else
                {
                    StatusText = "Done";
                    btn_record.IsEnabled = false;
                    closeStreams();
                    return;
                }
            }    
        }

        private void Sensor_IsAvailableChanged(object sender, IsAvailableChangedEventArgs e)
        {
            // on failure, set the status text
            StatusText = this.kinectSensor.IsAvailable ? "Kinect Ready :)" : "Keine Kinect gefunden...";
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            closeStreams();

            if (this.colorFrameReader != null)
            {
                this.colorFrameReader.FrameArrived -= this.colorFrameReader_FrameArrived;

                this.colorFrameReader.Dispose();
                this.colorFrameReader = null;
            }

            if (this.bodyFrameReader != null)
            {
                this.bodyFrameReader.FrameArrived -= this.bodyFrameReader_FrameArrived;

                this.bodyFrameReader.Dispose();
                this.bodyFrameReader = null;
            }

            if (this.kinectSensor != null)
            {
                this.kinectSensor.Close();
                this.kinectSensor = null;
            }
        }
        private void closeStreams()
        {
            try
            {
                if (swData != null)
                {
                    swData.Flush();
                    swData.Close();
                    swData = null;
                }
            }
            catch (IOException ex)
            {
                MessageBox.Show("Fehler\n" + ex.Message);
            }
        }
        
        #endregion

        //** FRAME READER ***
        private void colorFrameReader_FrameArrived(object sender, ColorFrameArrivedEventArgs e)
        {

            // ColorFrame is IDisposable
            using (ColorFrame colorFrame = e.FrameReference.AcquireFrame())
            {
                if (colorFrame != null)
                {
                    FrameDescription colorFrameDescription = colorFrame.FrameDescription;

                    using (KinectBuffer colorBuffer = colorFrame.LockRawImageBuffer())
                    {
                        this.colorBitmap.Lock();

                        // verify data and write the new color frame data to the display bitmap
                        if ((colorFrameDescription.Width == this.colorBitmap.PixelWidth) && (colorFrameDescription.Height == this.colorBitmap.PixelHeight))
                        {
                            colorFrame.CopyConvertedFrameDataToIntPtr(
                                this.colorBitmap.BackBuffer,
                                (uint)(colorFrameDescription.Width * colorFrameDescription.Height * 4),
                                ColorImageFormat.Bgra);

                            this.colorBitmap.AddDirtyRect(new Int32Rect(0, 0, this.colorBitmap.PixelWidth, this.colorBitmap.PixelHeight));
                        }

                        this.colorBitmap.Unlock();
                    }
                }
            }
        }

        int frameSelector = 0;
        private void bodyFrameReader_FrameArrived(object sender, BodyFrameArrivedEventArgs e)
        {
            bool dataReceived = false;

            using (BodyFrame bodyFrame = e.FrameReference.AcquireFrame())
            {
                if (bodyFrame != null)
                {
                    if (this.bodies == null)
                        this.bodies = new Body[bodyFrame.BodyCount];

                    bodyFrame.GetAndRefreshBodyData(this.bodies);
                    dataReceived = true;
                }
            }

            if (dataReceived)
            {
                using (DrawingContext dc = this.bodyDrawingGroup.Open())
                {
                    // Draw a transparent background to set the render size 
                    dc.DrawRectangle(Brushes.Black, null, new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                    // prevent drawing outside of our render area
                    bodyDrawingGroup.ClipGeometry = new RectangleGeometry(new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                    dc.DrawImage(colorBitmap, new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));

                    //Draw recordState
                    bool record = btn_record.Content.Equals("Stop");
                    if (record)
                    {
                        dc.DrawRectangle(Brushes.Firebrick, null, new Rect(new Point(80, 80), new Size(80, 80)));
                        dc.DrawText(new FormattedText("Rec",CultureInfo.CurrentUICulture,FlowDirection.LeftToRight,new Typeface("Arial"),35,Brushes.Black), new Point(90, 95));
                    }

                    foreach (Body body in this.bodies)
                    {
                        if (body.IsTracked)
                        {
                            leftHandPostition = body.Joints[JointType.HandLeft].Position;
                            rightHandPostition = body.Joints[JointType.HandRight].Position;

                            drawUI(body.Joints, dc);

                            frameSelector++;
                            if (frameSelector == 2)
                            {
                                // 1) Calculate All Data (angles or distances)
                                var allData = calculateData(body.Joints);
                                // 2) Write and draw to UI
                                writeData2Gui(allData);
                                // 3) Export Data if activated
                                if (record && sequenceID <= maxTrainData + maxTestData)
                                        writeTrainingData(allData);

                                frameSelector = 0;
                            }
                        }
                    }                                         
                }
            }
        }

        DepthSpacePoint pl_old;
        DepthSpacePoint pr_old;
        private void depthFrameReader_FrameArrived(object sender, DepthFrameArrivedEventArgs e)
        {
            using (DepthFrame depthFrame = e.FrameReference.AcquireFrame())
            {
                if (depthFrame != null)
                {
                    using (KinectBuffer depthBuffer = depthFrame.LockImageBuffer())
                    {
                        if ((this.depthFrameDescription.Width * this.depthFrameDescription.Height) == (depthBuffer.Size / this.depthFrameDescription.BytesPerPixel))
                        {
                            DepthSpacePoint pl = coordinateMapper.MapCameraPointToDepthSpace(leftHandPostition);
                            DepthSpacePoint pr = coordinateMapper.MapCameraPointToDepthSpace(rightHandPostition);

                            int range = 100;

                            // === Links
                            if (pl.X <= range || pl.X >= depthFrameDescription.Width - range || pl.Y <= range || pl.Y >= depthFrameDescription.Height - range)
                                pl = pl_old;

                            ProcessDepthFrameData(depthBuffer.UnderlyingBuffer, depthBuffer.Size, 0, ushort.MaxValue, pl);
                            this.depthBitmapLeft.WritePixels(
                                new Int32Rect(0, 0, this.depthBitmapLeft.PixelWidth, this.depthBitmapLeft.PixelHeight),
                                this.depthPixels,
                                this.depthBitmapLeft.PixelWidth,
                                0);

                            using (DrawingContext dc = leftHandDrawingGroup.Open())
                            {
                                dc.DrawImage(LeftHandSource, new Rect(0.0, 0.0, depthFrameDescription.Width, depthFrameDescription.Height));
                            }
                            pl_old = pl;
                            

                            // === Rechts
                            if (pr.X <= range || pr.X >= depthFrameDescription.Width - range || pr.Y <= range || pr.Y >= depthFrameDescription.Height - range)
                                pr = pr_old;

                            ProcessDepthFrameData(depthBuffer.UnderlyingBuffer, depthBuffer.Size, 0, ushort.MaxValue, pr);
                            this.depthBitmapRight.WritePixels(
                                new Int32Rect(0, 0, this.depthBitmapRight.PixelWidth, this.depthBitmapRight.PixelHeight),
                                this.depthPixels,
                                this.depthBitmapRight.PixelWidth,
                                0);

                            using (DrawingContext dc = rightHandDrawingGroup.Open())
                            {
                                dc.DrawImage(RightHandSource, new Rect(0.0, 0.0, depthFrameDescription.Width, depthFrameDescription.Height));
                            }
                            pr_old = pr;
                        }
                    }
                }
            }
        }
        // Note: In order to see the full range of depth (including the less reliable far field depth) we are setting maxDepth (ushort.MaxValue) to the extreme potential depth threshold
        // If you wish to filter by reliable depth distance, use:  depthFrame.DepthMaxReliableDistance
        private unsafe void ProcessDepthFrameData(IntPtr depthFrameData, uint depthFrameDataSize, ushort minDepth, ushort maxDepth, DepthSpacePoint p)
        {
            ushort* frameData = (ushort*)depthFrameData; // depth frame data is a 16 bit value
            //ushort initDepth = frameData[depthFrameDescription.Width * ((int)p.Y) + ((int)p.X)];
            //byte initPos = (byte)(initDepth / MapDepthToByte);

            int index = 0, frame = 100;
            for (int y = -frame; y < frame; y++)
            {
                for (int x = -frame; x < frame; x++)
                {                    
                    //Select index for smaller frame and get Depth value
                    int i = (depthFrameDescription.Width * ((int)p.Y + y) + ((int)p.X + x));
                    ushort depth = frameData[i];                   
                    byte greyValue = (byte)(depth >= minDepth && depth <= maxDepth ? (depth / MapDepthToByte) : 0);

                    this.depthPixels[index++] = greyValue;
                }
            }
        }
        //*******************

        private double[] calculateData(IReadOnlyDictionary<JointType, Joint> joints)
        {
            List<double> allData = new List<double>();

            CameraSpacePoint vec = new CameraSpacePoint();
            CameraSpacePoint newSpineShoulder = new CameraSpacePoint();

            nz = Helper.getNormalVector(joints[JointType.ShoulderLeft].Position, joints[JointType.ShoulderRight].Position, joints[JointType.SpineMid].Position);
            newSpineShoulder.X = joints[JointType.SpineShoulder].Position.X - nz.X;
            newSpineShoulder.Y = joints[JointType.SpineShoulder].Position.Y - nz.Y;
            newSpineShoulder.Z = joints[JointType.SpineShoulder].Position.Z - nz.Z;
            ny = Helper.getNormalVector(joints[JointType.ShoulderLeft].Position, joints[JointType.ShoulderRight].Position, newSpineShoulder);
            nx = Helper.getNormalVector(joints[JointType.SpineShoulder].Position, joints[JointType.SpineMid].Position, newSpineShoulder);

            //LEFT
            //Shoulder->Elbow
            vec.X = joints[JointType.ElbowLeft].Position.X - joints[JointType.ShoulderLeft].Position.X;
            vec.Y = joints[JointType.ElbowLeft].Position.Y - joints[JointType.ShoulderLeft].Position.Y;
            vec.Z = joints[JointType.ElbowLeft].Position.Z - joints[JointType.ShoulderLeft].Position.Z;
            allData.Add(Helper.getAngle(vec, nz));
            allData.Add(Helper.getAngle(vec, ny));
            allData.Add(Helper.getAngle(vec, nx));

            //Elbow->Hand
            vec.X = joints[JointType.WristLeft].Position.X - joints[JointType.ElbowLeft].Position.X;
            vec.Y = joints[JointType.WristLeft].Position.Y - joints[JointType.ElbowLeft].Position.Y;
            vec.Z = joints[JointType.WristLeft].Position.Z - joints[JointType.ElbowLeft].Position.Z;
            allData.Add(Helper.getAngle(vec, nz));
            allData.Add(Helper.getAngle(vec, ny));
            allData.Add(Helper.getAngle(vec, nx));

            //RIGHT
            //Shoulder->Elbow
            vec.X = joints[JointType.ElbowRight].Position.X - joints[JointType.ShoulderRight].Position.X;
            vec.Y = joints[JointType.ElbowRight].Position.Y - joints[JointType.ShoulderRight].Position.Y;
            vec.Z = joints[JointType.ElbowRight].Position.Z - joints[JointType.ShoulderRight].Position.Z;
            allData.Add(Helper.getAngle(vec, nz));
            allData.Add(Helper.getAngle(vec, ny));
            allData.Add(Helper.getAngle(vec, nx));

            //Elbow->Hand
            vec.X = joints[JointType.WristRight].Position.X - joints[JointType.ElbowRight].Position.X;
            vec.Y = joints[JointType.WristRight].Position.Y - joints[JointType.ElbowRight].Position.Y;
            vec.Z = joints[JointType.WristRight].Position.Z - joints[JointType.ElbowRight].Position.Z;
            allData.Add(Helper.getAngle(vec, nz));
            allData.Add(Helper.getAngle(vec, ny));
            allData.Add(Helper.getAngle(vec, nx));
         
            return allData.ToArray<double>();
        }

        private void writeData2Gui(double[] allData) 
        {
            int counter = 0;
            string text = "";
                            
            text += "\nOrientierung\n";
            for (int i = 0; i < allJointsForUI.Length; i++)
            {               
                string obj = "";
                switch (allJointsForUI[i])
                {
                    case 4: obj = "Oberarm Links"; break;
                    case 5: obj = "Unterarm Links"; break;
                    case 8: obj = "Oberarm Rechts"; break;
                    case 9: obj = "Unterarm Rechts"; break;
                }
                text += String.Format("\n{0}\tZ: {1:0.00} \tY: {2:0.00} \tX: {3:0.00}",
                    obj, allData[counter++], allData[counter++], allData[counter++]);                
            }

            this.txtAngles.Text = text;
        }

        int addId = 48;
        private void writeTrainingData(double[] allData) 
        {
            // seqID = xxxyy, xxx = LabelCode , yy = sequence
            // 00000     |L 0 0 0 0 0   |F <features ...>
            // 00000     |L 0 0 0 0 0    |F <features ...>
            // 00001     |L 0 0 0 0 0    |F <features ...>
            //  ...
            // 00100     |L 1    |F <features ...>
            var entry = String.Format("{0:000}{1:00}\t|L {2}\t|F", gestureNumber, sequenceID+addId, gestureCode[gestureNumber]);
            for (int i = 0; i < allData.Length; )
                entry += String.Format(" {0:0.000000}", allData[i++]);

            entry = entry.Replace(',', '.');
            swData.WriteLine(entry);
            swData.Flush();            
        }

        int resizer = 10;
        List<JointType> jointTypes = new List<JointType>() { JointType.Head, JointType.SpineMid, JointType.ShoulderLeft, JointType.ElbowLeft, JointType.WristLeft, JointType.ShoulderRight, JointType.ElbowRight, JointType.WristRight };
        private const float InferredZPositionClamp = 0.1f;
        private Pen orientationPen = new Pen(Brushes.OrangeRed, 10);
        private Pen zPen = new Pen(Brushes.Yellow, 3);
        private Pen yPen = new Pen(Brushes.Magenta, 3);
        private Pen xPen = new Pen(Brushes.Cyan, 3);
        private void drawUI(IReadOnlyDictionary<JointType, Joint> joints, DrawingContext drawingContext)
        {
            Dictionary<JointType, CameraSpacePoint> jointPoints = new Dictionary<JointType, CameraSpacePoint>();

            // sometimes depth(Z) of an inferred joint may show as negative -> clamp down to 0.1f to prevent coordinatemapper from returning (-Infinity, -Infinity)
            foreach (var type in jointTypes)
            {
                var jointPosition = joints[type].Position;
                if (jointPosition.Z < 0) jointPosition.Z = InferredZPositionClamp;
                jointPoints.Add(type, jointPosition);
            }

            // ====== Draw Orientation
            ColorSpacePoint cSPoint0, cSPoint1;
            Point p0, p1;
            CameraSpacePoint p = new CameraSpacePoint();

               
            foreach (int thisJoint in allJointsForUI)
            {
                int neighbour = 0;
                switch (thisJoint)
                {
                    case 4: neighbour = 5; break;
                    case 5: neighbour = 6; break;
                    case 8: neighbour = 9; break;
                    case 9: neighbour = 10; break;
                }

                cSPoint0 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[(JointType)thisJoint]);
                cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[(JointType)neighbour]);
                p0 = new Point(cSPoint0.X, cSPoint0.Y);
                p1 = new Point(cSPoint1.X, cSPoint1.Y);
                drawingContext.DrawLine(orientationPen, p0, p1);
            }

            // ====== Draw Normals
            cSPoint0 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.SpineMid]);
            p0 = new Point(cSPoint0.X, cSPoint0.Y);

            p.X = jointPoints[JointType.SpineMid].X - nx.X * resizer;
            p.Y = jointPoints[JointType.SpineMid].Y + nx.Y * resizer;
            p.Z = jointPoints[JointType.SpineMid].Z - nx.Z * resizer;
            cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(p);
            p1 = new Point(cSPoint1.X, cSPoint1.Y);
            drawingContext.DrawLine(xPen, p0, p1);

            p.X = jointPoints[JointType.SpineMid].X - ny.X * resizer;
            p.Y = jointPoints[JointType.SpineMid].Y + ny.Y * resizer;
            p.Z = jointPoints[JointType.SpineMid].Z + ny.Z * resizer;
            cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(p);
            p1 = new Point(cSPoint1.X, cSPoint1.Y);
            drawingContext.DrawLine(yPen, p0, p1);

            p.X = jointPoints[JointType.SpineMid].X + nz.X * resizer;
            p.Y = jointPoints[JointType.SpineMid].Y - nz.Y * resizer;
            p.Z = jointPoints[JointType.SpineMid].Z - nz.Z * resizer;
            cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(p);
            p1 = new Point(cSPoint1.X, cSPoint1.Y);
            drawingContext.DrawLine(zPen, p0, p1);


            
        }
    }
}