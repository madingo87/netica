namespace KinectGesturesWpf
{
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Globalization;
    using System.IO;
    using System.Runtime.InteropServices;
    using System.Windows;
    using System.Windows.Media;
    using System.Windows.Media.Imaging;
    using Microsoft.Kinect;
    using System.Collections.Generic;
    using System.Windows.Media.Media3D;
    using System.Linq;

    /// <summary>
    /// Interaction logic for the MainWindow
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        /// <summary>
        /// Size of the RGB pixel in the bitmap
        /// </summary>
        private const int BytesPerPixel = 4;
        //body(512x424) | color(1920x1080) 

        private KinectSensor kinectSensor = null;
        private FrameDescription frameDescription = null;

        private DepthFrameReader depthFrameReader = null;
        private byte[] depthPixels;
        private const int MapDepthToByte = 8000 / 256;
        private WriteableBitmap depthBitmap = null;
        
        private ColorFrameReader colorFrameReader = null;
        private FrameDescription colorFrameDescription = null;
        private WriteableBitmap colorBitmap = null;

        private BodyFrameReader bodyFrameReader = null;
        private DrawingGroup bodyDrawingGroup;
        private DrawingImage imageSource;

        private CoordinateMapper coordinateMapper = null;
        private Body[] bodies = null;

        StreamWriter swData;
        int descriptionNumber;

        //sets the flag for recording new JointPosition Data
        bool recordMode = false;
        bool classifyEnabled = false;
        private string gestureText;        
        private string statusText = null;

        int maxTestData;
        int maxTrainData;

        int[] jointsToDraw = new[] { 4, 5, 6, 8, 9, 10 };
        int[] allJointKeys = new[] { 4, 5, 8, 9 };
    
        int dataInputSize;
        int dataOutputSize;    

        public MainWindow()
        {
            this.kinectSensor = KinectSensor.GetDefault();

            this.frameDescription = this.kinectSensor.DepthFrameSource.FrameDescription;
            this.colorFrameDescription = this.kinectSensor.ColorFrameSource.CreateFrameDescription(ColorImageFormat.Bgra);

            this.depthFrameReader = this.kinectSensor.DepthFrameSource.OpenReader();
            //this.depthFrameReader.FrameArrived += depthFrameReader_FrameArrived;
            this.depthBitmap = new WriteableBitmap(colorFrameDescription.Width, colorFrameDescription.Height, 96.0, 96.0, PixelFormats.Bgr32, null);
            this.depthPixels = new byte[this.frameDescription.Width * this.frameDescription.Height];

            this.colorFrameReader = this.kinectSensor.ColorFrameSource.OpenReader();
            this.colorFrameReader.FrameArrived += this.colorFrameReader_FrameArrived;     
            this.colorBitmap = new WriteableBitmap(colorFrameDescription.Width, colorFrameDescription.Height, 96.0, 96.0, PixelFormats.Bgr32, null);

            this.bodyFrameReader = this.kinectSensor.BodyFrameSource.OpenReader();
            this.bodyFrameReader.FrameArrived += bodyFrameReader_FrameArrived;
            
            this.bodyDrawingGroup = new DrawingGroup();
            this.imageSource = new DrawingImage(bodyDrawingGroup);

            this.coordinateMapper = this.kinectSensor.CoordinateMapper;

            this.kinectSensor.IsAvailableChanged += this.Sensor_IsAvailableChanged;

            this.kinectSensor.Open();
    
            this.StatusText = this.kinectSensor.IsAvailable ? Properties.Resources.KinectReady : Properties.Resources.NoSensor;
            this.GestureText = "";

            this.DataContext = this;

            dataOutputSize = Int32.Parse(Properties.Resources.OutputSize);
            descriptionNumber = Convert.ToInt32(Properties.Resources.Precarriage); //Vorlauf Frames
            //dataInputSize = jointNeighbours.Count * inputDataPerJoint; 
            swData = new StreamWriter(@"c:/temp/trainData.pat", true);
            maxTrainData = Convert.ToInt32(Properties.Resources.MaxTrainData);
            maxTestData = Convert.ToInt32(Properties.Resources.MaxTestData); 

            this.InitializeComponent();
        }

       
        #region Properies

        public event PropertyChangedEventHandler PropertyChanged;

        public ImageSource ImageSource
        {
            get
            {
                return this.imageSource;
            }
        }
        
        public string GestureText
        {
            get
            {
                return this.gestureText;
            }
            set
            {
                if (this.gestureText != value)
                {
                    this.gestureText = value;

                    // notify any bound elements that the text has changed
                    if (this.PropertyChanged != null)
                    {
                        this.PropertyChanged(this, new PropertyChangedEventArgs("GestureText"));
                    }
                }
            }
        }

        public string StatusText
        {
            get
            {
                return this.statusText;
            }

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

        private void chk_Record_Checked(object sender, RoutedEventArgs e)
        {
            this.recordMode = true;
        }
        private void chk_Record_Unchecked(object sender, RoutedEventArgs e)
        {
            this.recordMode = false;
            StatusText = "Idle";
            descriptionNumber = -50;
        }
        private void chk_Classify_Checked(object sender, RoutedEventArgs e)
        {
            this.classifyEnabled = true;
            this.recordMode = false;
            StatusText = "Classifying...";
        }
        private void chk_Classify_Unchecked(object sender, RoutedEventArgs e)
        {
            this.classifyEnabled = false;
            StatusText = "Idle";
        }

        private void Sensor_IsAvailableChanged(object sender, IsAvailableChangedEventArgs e)
        {
            // on failure, set the status text
            this.StatusText = this.kinectSensor.IsAvailable ? Properties.Resources.KinectReady : Properties.Resources.NoSensor;
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (swData != null)
            {
                swData.Flush();
                swData.Close();
            }

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

        private const float InferredZPositionClamp = 0.1f;
        private void bodyFrameReader_FrameArrived(object sender, BodyFrameArrivedEventArgs e)
        {
            bool dataReceived = false;

            using (BodyFrame bodyFrame = e.FrameReference.AcquireFrame())
            {
                if (bodyFrame != null)
                {
                    if (this.bodies == null)
                    {
                        this.bodies = new Body[bodyFrame.BodyCount];
                    }

                    // The first time GetAndRefreshBodyData is called, Kinect will allocate each Body in the array.
                    // As long as those body objects are not disposed and not set to null in the array,
                    // those body objects will be re-used.
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

                    foreach (Body body in this.bodies)
                    {
                        if (body.IsTracked)
                        {
                            //Calculate All Data (angles and distances)
                            var allData = calculateData(body.Joints, body.JointOrientations);

                            var collectData = descriptionNumber <= (maxTrainData+maxTestData) && recordMode;
                            if (collectData)
                                writeTrainingData(allData);
                            
                            writeData2Gui(allData);
                                  
                            //DRAW
                            dc.DrawImage(colorBitmap, new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                            drawJoints(body.Joints, dc);
                            //this.DrawHand(body.HandLeftState, joints, JointType.HandLeft, dc);
                            //this.DrawHand(body.HandRightState, joints,JointType.HandRight, dc);

                            //CLASSIFY
                            if (classifyEnabled)
                            {
                                var output = classifyGesture(allData);
                                updateGestureText(output);                       
                            }
                        }
                    }
                }
            }
        }

        //********************
        #endregion

        #region Helper
        private double[] calculateData(IReadOnlyDictionary<JointType, Joint> joints, IReadOnlyDictionary<JointType, JointOrientation> orientations)
        {
            List<double> allData = new List<double>();
            //int index = 0;

            foreach (JointType jointType in allJointKeys)        
            {
                // sometimes depth(Z) of an inferred joint may show as negative -> clamp down to 0.1f to prevent coordinatemapper from returning (-Infinity, -Infinity)
                CameraSpacePoint position = joints[jointType].Position;
                if (position.Z < 0) position.Z = InferredZPositionClamp;


                //http://www.iti.fh-flensburg.de/lang/algorithmen/grundlagen/quat.htm
                allData.Add(orientations[jointType].Orientation.X);
                allData.Add(orientations[jointType].Orientation.Y);
                allData.Add(orientations[jointType].Orientation.Z);           
            }

            allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandLeft));
            allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandRight));
            allData.Add(calculateDistances(joints, (int)JointType.HandRight, (int)JointType.HandLeft));

            dataInputSize = allData.Count;
         
            return allData.ToArray<double>();
        }

        private double calculateDistances(IReadOnlyDictionary<JointType, Joint> joints, int joint1, int joint2) 
        {
            var coords = new CameraSpacePoint[2] { joints[(JointType)joint1].Position, joints[(JointType)joint2].Position };
            double vec = Math.Sqrt(Math.Pow(coords[0].X - coords[1].X, 2) + Math.Pow(coords[0].Y - coords[1].Y,2) + Math.Pow(coords[0].Z - coords[1].Z,2));
            return Math.Abs(vec);
        }

        private void writeData2Gui(double[] allData) 
        {
            int counter = 0;
            string text = "\nOrientierung";
            for (int i = 0; i < allJointKeys.Length; i++)
            {
                string obj = "";
                switch (allJointKeys[i])
                {
                    case 4: obj = "Oberarm Links"; break;
                    case 5: obj = "Unteram Links"; break;
                    case 8: obj = "Oberarm Rechts"; break;
                    case 9: obj = "Unteram Rechts"; break;
                }

                text += String.Format("\n\t{0} XY: {1:0.00} YZ: {2:0.00} XZ: {3:0.00}",
                    obj, allData[counter++], allData[counter++], allData[counter++]);

            }
            text += String.Format("\n\nAbstände\n\tHand Links: {0:0.00} \n\tHand Rechts: {1:0.00} \n\tBeide Hände {2:0.00}", allData[counter++], allData[counter++], allData[counter++]);
            this.txtAngles.Text = text;
        }

        private void updateGestureText(float[] output)
        {
            var highestPropability = 0;
            for (var i = 1; i< output.Length; i++)
                highestPropability = output[i] > output[i - 1] ? i : highestPropability;
         
            switch (highestPropability) 
            {
                case 0: GestureText = "Ich"; break;
                case 1: GestureText = "Du"; break;
                case 2: GestureText = "Er"; break;
                case 3: GestureText = "Was"; break;
                case 4: GestureText = "Party"; break;
                case 5: GestureText = "Müsli"; break;
            }

            Array.Sort(output);
            this.txtSuccessRate.Text = string.Format("Output Winner: {0:0.000} \nOutput Second: {1:0.000}\nOutput Third: {2:0.000}",
                                                       output[output.Length - 1], output[output.Length - 2], output[output.Length - 3]);
        }

        [DllImport("NetWrapperLib.dll")]
        //public unsafe static extern int position(float* input, float* output);
        public unsafe static extern int classify(float* input, float* output);
        private unsafe float[] classifyGesture(double[] angles)
        {
            float[] inputArray = new float[dataInputSize];
            float[] outputArray = new float[dataOutputSize];
            int res;

            for (int i = 0; i < angles.Length; i++)
                inputArray[i] = (float)angles[i];

            fixed (float* input = inputArray)
            {
                fixed (float* output = outputArray)
                {
                    res = classify(input, output);
                }
            }

            return outputArray;
        }

        private void writeTrainingData(double[] allData)
        {
            if (descriptionNumber < 1)
            {
                StatusText = "Starting to Collect!";
                descriptionNumber++;
            }
            else
            {
                if (descriptionNumber == 1)
                {
                    StatusText = "Collecting Traindata...";
                    swData.WriteLine("#========================================================================");
                    swData.WriteLine("#########################################################################");
                    swData.WriteLine("#=============================== NEXT ===================================");
                }
                if (descriptionNumber == (maxTrainData + 1))
                {
                    swData.Flush();
                    swData.Close();
                    swData = new StreamWriter(@"c:/temp/testData.pat", true);
                    StatusText = "Collecting Testdata...";
                    swData.WriteLine("#========================================================================");
                    swData.WriteLine("#########################################################################");
                    swData.WriteLine("#=============================== NEXT ===================================");
                }
                if (descriptionNumber == (maxTrainData + maxTestData)) StatusText = "Collecting Done";

                swData.WriteLine("#image description number " + descriptionNumber++);
                swData.Flush();
            }

            if (descriptionNumber > 1)
            {
                var entry = "";
                for (int i = 0; i < allData.Length; )
                    entry += String.Format("{0:0.000} {1:0.000} {2:0.000}\n", allData[i++], allData[i++], allData[i++]);

                swData.Write(entry.Replace(',', '.'));
                swData.WriteLine("#result ");
                swData.WriteLine(Properties.Resources.Result);
                swData.WriteLine();
                swData.Flush();
            }
        }

        private Brush trackedJointBrush = new SolidColorBrush(Color.FromArgb(255, 192, 64, 64));
        private Brush inferredJointBrush = new SolidColorBrush(Color.FromArgb(255, 64, 64, 192));
        private readonly double circleSize = 20;
        private Pen orientationPen = new Pen(Brushes.Red, 15);
        private Pen distancePen = new Pen(Brushes.Yellow, 5);
        private void drawJoints(IReadOnlyDictionary<JointType, Joint> joints, DrawingContext drawingContext)
        {
            // Draw the joints
            foreach (JointType jointType in jointsToDraw)
            {
                CameraSpacePoint position = joints[jointType].Position;
                ColorSpacePoint colorSpacePoint = this.coordinateMapper.MapCameraPointToColorSpace(position);
                Point jointPoint = new Point(colorSpacePoint.X, colorSpacePoint.Y);
                Brush drawBrush = null;

                TrackingState trackingState = joints[jointType].TrackingState;

                if (trackingState == TrackingState.Tracked) 
                    drawBrush = this.trackedJointBrush;                
                else // trackingState == TrackingState.Inferred)
                    drawBrush = this.inferredJointBrush;               

                if (drawBrush != null)
                {
                    //Z in meter | Opacity 0-1 --> bereich 0.7m - 1.7m interessant
                    drawBrush.Opacity = 0f;
                    drawingContext.DrawEllipse(drawBrush, null, jointPoint, circleSize, circleSize);                    
                }
            }

            ColorSpacePoint cSPoint0, cSPoint1, cSPoint2;
            Point jointPoint0, jointPoint1, jointPoint2;
            // Draw Orientation
            foreach (int thisJoint in allJointKeys)
            {
                int neighbour = 0;
                switch (thisJoint)
                {
                    case 4: neighbour = 5; break;
                    case 5: neighbour = 6; break;
                    case 8: neighbour = 9; break;
                    case 9: neighbour = 10; break;
                }

                cSPoint0 = this.coordinateMapper.MapCameraPointToColorSpace(joints[(JointType)thisJoint].Position);
                cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(joints[(JointType)neighbour].Position);
                jointPoint0 = new Point(cSPoint0.X, cSPoint0.Y);
                jointPoint1 = new Point(cSPoint1.X, cSPoint1.Y);
                drawingContext.DrawLine(orientationPen, jointPoint0, jointPoint1);
            }

            cSPoint0 = this.coordinateMapper.MapCameraPointToColorSpace(joints[JointType.HandLeft].Position);
            cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(joints[JointType.HandRight].Position);
            cSPoint2 = this.coordinateMapper.MapCameraPointToColorSpace(joints[JointType.Head].Position);
            jointPoint0 = new Point(cSPoint0.X, cSPoint0.Y);
            jointPoint1 = new Point(cSPoint1.X, cSPoint1.Y);
            jointPoint2 = new Point(cSPoint2.X, cSPoint2.Y);
            drawingContext.DrawLine(distancePen, jointPoint0, jointPoint1);
            drawingContext.DrawLine(distancePen, jointPoint1, jointPoint2);
            drawingContext.DrawLine(distancePen, jointPoint0, jointPoint2);
        }

        private double RadianToDegree(double angle)
        {
            return angle * (180.0 / Math.PI);
        }
        #endregion
    }
}


