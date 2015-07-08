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

    /// <summary>
    /// Interaction logic for the MainWindow
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        /// <summary>
        /// Size of the RGB pixel in the bitmap
        /// </summary>
        private const int BytesPerPixel = 4;

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

        //body(512x424) | color(1920x1080) 

        StreamWriter sw;
        int descriptionNumber;

        //sets the falg for recording new JointPosition Data
        bool recordMode = false;     
        string gestureText;        
        private string statusText = null;

        string resultForFile;
        int[] jointKeys = new[] { 1, 3, 5, 6, 7, 9, 10, 11 };
        int dataInputSize;
        int dataOutputSize;
        

        //[DllImport("NetWrapperLib.dll")]
        //public unsafe static extern int FirstNet(float* input, float* output);
        [DllImport("NetWrapperLib.dll")]
        public unsafe static extern int HandPosition3D(float* input, float* output);


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
            this.gestureText = Properties.Resources.None;

            this.DataContext = this;


            //###### DATA TO CHANGE FOR RECORDING ########
            resultForFile = "0 0 0 1";
            sw = new StreamWriter(@"c:\temp\gestureData4.txt", true);
            //---------------------------------------

            descriptionNumber = 1;
            dataInputSize = jointKeys.Length*3;
            dataOutputSize = 4;

            sw.WriteLine("SNNS pattern definition file V3.2");
            sw.WriteLine(string.Format("generated at {0:d} - {0:t}", DateTime.Now));
            sw.WriteLine("#(c) Martin Weschta - HAW Hamburg");
            sw.WriteLine();
            sw.WriteLine("No. of patterns : ??? ");
            sw.WriteLine("No. of input units : " + dataInputSize);
            sw.WriteLine("No. of output units : 4");
            sw.WriteLine();
            sw.WriteLine("#========================================================================");
            sw.WriteLine("#########################################################################");
            sw.WriteLine("#=============================== DATA ===================================");
            //############################################

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
        }

        private void Sensor_IsAvailableChanged(object sender, IsAvailableChangedEventArgs e)
        {
            // on failure, set the status text
            this.StatusText = this.kinectSensor.IsAvailable ? Properties.Resources.KinectReady : Properties.Resources.NoSensor;
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            sw.Flush();
            sw.Close();

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

                    foreach (Body body in this.bodies)
                    {
                        Pen jointPen = new Pen(Brushes.Red, 4);

                        if (body.IsTracked)
                        {
                            var collectData = body.HandRightState.Equals(HandState.Open) && recordMode;
                            if (collectData) sw.WriteLine("#image description number " + descriptionNumber++);

                            //this.DrawClippedEdges(body, dc);
                            IReadOnlyDictionary<JointType, Joint> joints = body.Joints;

                            // convert the joint points to depth (display) space
                            Dictionary<JointType, Point3D> jointPoints = new Dictionary<JointType, Point3D>();

                            foreach (JointType jointType in jointKeys)
                            {
                                // sometimes the depth(Z) of an inferred joint may show as negative
                                // clamp down to 0.1f to prevent coordinatemapper from returning (-Infinity, -Infinity)
                                CameraSpacePoint position = joints[jointType].Position;
                                if (position.Z < 0)
                                {
                                    position.Z = InferredZPositionClamp;
                                }

                                //Collect joint Coordinates (Camera) for clasification
                                if (!recordMode) jointPoints[jointType] = new Point3D(position.X, position.Y, position.Z);

                                //Collect JointPoint
                                if (collectData) sw.WriteLine(string.Format("{0} {1} {2}", position.X, position.Y, position.Z));                                                                 
                            }

                            if (collectData)
                            {
                                sw.WriteLine("#result ");
                                sw.WriteLine(this.resultForFile);
                                sw.WriteLine();
                            }
                            //reset collectData
                            collectData = false;
                                                        
                            //draw colorImage as Background
                            dc.DrawImage(colorBitmap, new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                            // Draw borders for JointImage
                            dc.DrawRectangle(null, new Pen(Brushes.White, 10), new Rect(0.0, 0.0, this.frameDescription.Width+20, this.frameDescription.Height+20));

                            //draw markings for joints and hands
                            this.DrawJoints(joints, dc, jointPen);
                            this.DrawHand(body.HandLeftState, joints, JointType.HandLeft, dc);
                            this.DrawHand(body.HandRightState, joints,JointType.HandRight, dc);


                            //Classify Gesture
                            if (!recordMode)
                            {
                                var output = classifyGesture(jointPoints);
                                updateStatusText(output);                       
                            }
                        }
                    }

                    // prevent drawing outside of our render area
                    this.bodyDrawingGroup.ClipGeometry = new RectangleGeometry(new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                }
            }
        }

        //********************
        #endregion

        #region Helper

        private void updateStatusText(float[] output)
        {
            var highest = 0;
            for (var i = 1; i< output.Length; i++)
            {
                highest = output[i] >= output[i-1] ? i : highest;
            }

            //MUSS mit dem Input für die Trainingsdaten übereinstimmen!!!!
            if (highest == 0) GestureText = Properties.Resources.HandsDown;
            else if (highest == 1) GestureText = Properties.Resources.HandsOut;
            else if (highest == 2) GestureText = Properties.Resources.HandsUp;
            else if (highest == 3) GestureText = Properties.Resources.HandsFront;   
            else GestureText = Properties.Resources.None;
        }

        private unsafe float[] classifyGesture(Dictionary<JointType, Point3D> jointPoints)
        {
            float[] inputArray = new float[dataInputSize];
            float[] outputArray = new float[dataOutputSize];

            int counter = 0;
            int res;

            foreach (var point in jointPoints)
            {
                inputArray[counter++] = (float)point.Value.X;
                inputArray[counter++] = (float)point.Value.Y;
                inputArray[counter++] = (float)point.Value.Z;
            }

            fixed (float* input = inputArray)
            {
                fixed (float* output = outputArray)
                {
                    res = HandPosition3D(input, output);
                }
            }

            return outputArray;
        }

        private Brush trackedJointBrush = new SolidColorBrush(Color.FromArgb(224, 192, 64, 64));
        private Brush inferredJointBrush = new SolidColorBrush(Color.FromArgb(224, 64, 64, 192));
        private readonly double circleSize = 30;

        private void DrawJoints(IReadOnlyDictionary<JointType, Joint> joints, DrawingContext drawingContext, Pen drawingPen)
        {
            // Draw the joints
            foreach (JointType jointType in jointKeys)
            {
                
                //DepthSpacePoint depthSpacePoint = this.coordinateMapper.MapCameraPointToDepthSpace(position);
                //ColorSpacePoint colorSpacePoint = this.coordinateMapper.MapCameraPointsToColorSpace(position);
                CameraSpacePoint position = joints[jointType].Position;
                DepthSpacePoint depthSpacePoint = this.coordinateMapper.MapCameraPointToDepthSpace(position);

                Point jointPoint = new Point(depthSpacePoint.X, depthSpacePoint.Y);

                Brush drawBrush = null;

                TrackingState trackingState = joints[jointType].TrackingState;

                if (trackingState == TrackingState.Tracked)
                {
                    drawBrush = this.trackedJointBrush;
                }
                else // trackingState == TrackingState.Inferred)
                {
                    drawBrush = this.inferredJointBrush;
                }

                if (drawBrush != null)
                {
                    //Z in meter | Opacity 0-1 --> -0.5 da bereich 0.5m - 1.5m interessant
                    var opacity = 1 - (position.Z - 0.5);
                    if (opacity > 1) opacity = 1;
                    if (opacity < 0) opacity = 0;
                    drawBrush.Opacity = opacity;
                    drawingContext.DrawEllipse(drawBrush, null, jointPoint, circleSize, circleSize);
                }
            }
        }

        private const double HandSize = 40;
        private readonly Brush handClosedBrush = new SolidColorBrush(Color.FromArgb(128, 255, 0, 0));
        private readonly Brush handOpenBrush = new SolidColorBrush(Color.FromArgb(128, 0, 255, 0));

        private void DrawHand(HandState handState, IReadOnlyDictionary<JointType, Joint> joints, JointType jointType, DrawingContext drawingContext)
        {
            CameraSpacePoint position = joints[jointType].Position;
            DepthSpacePoint depthSpacePoint = this.coordinateMapper.MapCameraPointToDepthSpace(position);

            switch (handState)
            {
                case HandState.Closed:
                    drawingContext.DrawEllipse(this.handClosedBrush, null, new Point(depthSpacePoint.X, depthSpacePoint.Y), HandSize, HandSize);
                    break;

                case HandState.Open:
                    drawingContext.DrawEllipse(this.handOpenBrush, null, new Point(depthSpacePoint.X, depthSpacePoint.Y), HandSize, HandSize);
                    break;
            }
        }

        #endregion
    }
}
