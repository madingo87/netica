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
        string resultForFile;

        //sets the falg for recording new JointPosition Data
        bool recordMode = false;
        bool classifyEnabled = false;
        string gestureText;        
        private string statusText = null;

        
        int[] allJointKeys = new[] { 3, 4, 5, 6, 7, 8, 9, 10, 11, 20 };
        List<int> jointKeysWithoutAngles = new List<int> { 3, 7, 11 };
        List<KeyValuePair<int, int[]>> jointNeighbours = new List<KeyValuePair<int, int[]>> { 
            new KeyValuePair<int, int[]>(4, new int[] { 20, 5 }),
            new KeyValuePair<int, int[]>(5, new int[] { 4, 6 }),
            new KeyValuePair<int, int[]>(6, new int[] { 5, 7 }),
            new KeyValuePair<int, int[]>(8, new int[] { 20, 9 }),
            new KeyValuePair<int, int[]>(9, new int[] { 8, 10 }),
            new KeyValuePair<int, int[]>(10, new int[] { 9, 11 }),
            new KeyValuePair<int, int[]>(20, new int[] { 3, 4 }),
            new KeyValuePair<int, int[]>(20, new int[] { 3, 8 }),
            new KeyValuePair<int, int[]>(20, new int[] { 4, 8 })
        };
        int numberOfAngles = 9; //jointNeighbours.Count;
        
        int dataInputSize;
        int dataOutputSize;
        

        //[DllImport("NetWrapperLib.dll")]
        //public unsafe static extern int HandPosition3D(float* input, float* output);
        [DllImport("NetWrapperLib.dll")]
        public unsafe static extern int AngleSimple(float* input, float* output);


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
            this.gestureText = Properties.Resources.NotAvailable;

            this.DataContext = this;

            //###### DATA TO CHANGE FOR RECORDING ########
            //var maxTrainData = 300;
            //var maxTestData = 100;
            resultForFile = Properties.Resources.Result;
            dataOutputSize = Int32.Parse(Properties.Resources.OutputSize);
            //---------------------------------------------         

            descriptionNumber = 1;
            dataInputSize = numberOfAngles * 2;

            swData = new StreamWriter(@"c:/temp/data.txt", true);
                    
            //SNNS pattern definition file V3.2
            //generated at 24.9.2015 - 13.45
            //#(c) Martin Weschta - HAW Hamburg");
            //
            //No. of patterns : ??? 
            //No. of input units : ???
            //No. of output units : ???
            
            swData.WriteLine();
            swData.WriteLine("#========================================================================");
            swData.WriteLine("#########################################################################");
            swData.WriteLine("#=============================== NEXT ===================================");

            swData.Flush();

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
            StatusText = "Collecting...";
        }
        private void chk_Record_Unchecked(object sender, RoutedEventArgs e)
        {
            this.recordMode = false;
            StatusText = "Idle";
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

        bool takeFrame = true;
        private const float InferredZPositionClamp = 0.1f;
        private void bodyFrameReader_FrameArrived(object sender, BodyFrameArrivedEventArgs e)
        {
            //take only every second picture
            takeFrame = !takeFrame;
            if (!takeFrame) return; 

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
                            var collectData = descriptionNumber <= 400 && recordMode;// && body.HandLeftState.Equals(HandState.Open);
                            if (collectData)
                            {
                                if (descriptionNumber == 301)
                                {
                                    swData.WriteLine("#========================================================================");
                                    swData.WriteLine("#########################################################################");
                                    swData.WriteLine("#=============================== NEXT ===================================");
                                } 
                                if (descriptionNumber == 400) StatusText = "Collecting Done";
                                swData.WriteLine("#image description number " + descriptionNumber++);
                            }      

                            IReadOnlyDictionary<JointType, Joint> joints = body.Joints;
                            //Dictionary<JointType, Point3D> jointPoints = new Dictionary<JointType, Point3D>();

                            double[] allAngles = new double[numberOfAngles * 2];
                            int index = 0;

                            foreach (JointType jointType in allJointKeys)
                            {
                                // sometimes depth(Z) of an inferred joint may show as negative -> clamp down to 0.1f to prevent coordinatemapper from returning (-Infinity, -Infinity)
                                CameraSpacePoint position = joints[jointType].Position;
                                if (position.Z < 0) position.Z = InferredZPositionClamp;

                                double[] angles = new double[2];
                                int thisJoint = (int)jointType;
                                //Wenn der Joint nicht am Rand liegt, also der Winkel nicht berrechnet werden muss
                                if (!jointKeysWithoutAngles.Contains(thisJoint))
                                {
                                    //Wähle Nachbar des derzeitigen Joints - bei Joint 20 sind es drei Winkel, daher foreach!
                                    var neighbourCollection = jointNeighbours.Where(i => i.Key == thisJoint).Select(i => i.Value);
                                    if (!neighbourCollection.Any()) continue;

                                    foreach (var neighbour in neighbourCollection) 
                                    { 
                                        angles = calculateAngles(position, thisJoint, neighbour, joints);
                                        allAngles[index++] = angles[0];
                                        allAngles[index++] = angles[1];

                                        //Collect Angles
                                        if (collectData)
                                        {
                                            swData.WriteLine(string.Format("{0} {1}", angles[0], angles[1]));
                                            swData.Flush();
                                        }
                                    }
                                }                                                                                   
                            }

                            if (collectData)
                            {
                                swData.WriteLine("#result ");
                                swData.WriteLine(this.resultForFile);
                                swData.WriteLine();

                                swData.Flush();
                            }

                            this.txtAngles.Text = String.Format("04  x: {0:0}   z: {1:0}\n05  x: {2:0}   z: {3:0}\n06  x: {4:0}   z: {5:0}\n08  x: {6:0}   z: {7:0}\n" +
                                                                "09  x: {8:0}   z: {9:0}\n10  x: {10:0}   z: {11:0}\n20l x: {12:0}   z: {13:0}\n20r x: {14:0}   z: {15:0}\n20u x: {16:0}   z: {17:0}",
                                        allAngles[0], allAngles[1], allAngles[2], allAngles[3], allAngles[4], allAngles[5], allAngles[6], allAngles[7], allAngles[8], allAngles[9], 
                                        allAngles[10], allAngles[11], allAngles[12], allAngles[13], allAngles[14], allAngles[15], allAngles[16], allAngles[17]);
                                   
                            //DRAW
                            dc.DrawImage(colorBitmap, new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                            this.DrawJoints(joints, dc, jointPen);
                            this.DrawHand(body.HandLeftState, joints, JointType.HandLeft, dc);
                            this.DrawHand(body.HandRightState, joints,JointType.HandRight, dc);

                            //CLASSIFY
                            if (classifyEnabled)
                            {
                                var output = classifyGesture(allAngles);
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

        private double[] calculateAngles(CameraSpacePoint point, int jointType, int[] neighbours, IReadOnlyDictionary<JointType, Joint> joints)
        {
            //Collect Coordinates for joint and its neighbours and convert to ColorSpace
            var coords = new CameraSpacePoint[3] { joints[(JointType)jointType].Position, joints[(JointType)neighbours[0]].Position, joints[(JointType)neighbours[1]].Position };

            //TODO xa-xb usw vorberechnen
            //Get SideLenghts of Triangle
            var lengthA_y = Math.Abs(Math.Sqrt(Math.Pow(coords[1].X - coords[2].X,2) + Math.Pow(coords[1].Y - coords[2].Y,2))); // Sqrt((xb - xc)^2 + (yb - yc)^2)
            var lengthB_y = Math.Abs(Math.Sqrt(Math.Pow(coords[1].X - coords[0].X,2) + Math.Pow(coords[1].Y - coords[0].Y,2))); // Sqrt((xb - xa)^2 + (yb - ya)^2)
            var lengthC_y = Math.Abs(Math.Sqrt(Math.Pow(coords[0].X - coords[2].X,2) + Math.Pow(coords[0].Y - coords[2].Y,2))); // Sqrt((xa - xc)^2 + (ya - yc)^2)
            var lengthA_z = Math.Abs(Math.Sqrt(Math.Pow(coords[1].X - coords[2].X,2) + Math.Pow(coords[1].Z - coords[2].Z,2))); // Sqrt((xb - xc)^2 + (zb - zc)^2)
            var lengthB_z = Math.Abs(Math.Sqrt(Math.Pow(coords[1].X - coords[0].X,2) + Math.Pow(coords[1].Z - coords[0].Z,2))); // Sqrt((xb - xa)^2 + (zb - za)^2)
            var lengthC_z = Math.Abs(Math.Sqrt(Math.Pow(coords[0].X - coords[2].X,2) + Math.Pow(coords[0].Z - coords[2].Z,2))); // Sqrt((xa - xc)^2 + (za - zc)^2)

            //calculate Angle
            var val_y = (Math.Pow(lengthB_y, 2) + Math.Pow(lengthC_y, 2) - Math.Pow(lengthA_y, 2)) / (2 * lengthB_y * lengthC_y);
            var val_z = (Math.Pow(lengthB_z, 2) + Math.Pow(lengthC_z, 2) - Math.Pow(lengthA_z, 2)) / (2 * lengthB_z * lengthC_z);
            var angle_y = RadianToDegree(Math.Acos(val_y));
            var angle_z = RadianToDegree(Math.Acos(val_z));

            return new double[2] {angle_y, angle_z};
        }

        private void updateStatusText(float[] output)
        {
            var highest = 0;
            for (var i = 1; i< output.Length; i++)
            {
                highest = output[i] >= output[i-1] ? i : highest;
            }

            //MUSS mit dem Input für die Trainingsdaten übereinstimmen!!!!
            if (highest == 0) GestureText = Properties.Resources.None;
            else if (highest == 1) GestureText = Properties.Resources.Left;
            else if (highest == 2) GestureText = Properties.Resources.Right; 
            else GestureText = Properties.Resources.NotAvailable;
        }

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
                    res = AngleSimple(input, output);
                }
            }

            return outputArray;
        }

        private Brush trackedJointBrush = new SolidColorBrush(Color.FromArgb(255, 192, 64, 64));
        private Brush inferredJointBrush = new SolidColorBrush(Color.FromArgb(255, 64, 64, 192));
        private readonly double circleSize = 30;

        private void DrawJoints(IReadOnlyDictionary<JointType, Joint> joints, DrawingContext drawingContext, Pen drawingPen)
        {
            // Draw the joints
            foreach (JointType jointType in allJointKeys)
            {
                CameraSpacePoint position = joints[jointType].Position;
                ColorSpacePoint colorSpacePoint = this.coordinateMapper.MapCameraPointToColorSpace(position);

                Point jointPoint = new Point(colorSpacePoint.X, colorSpacePoint.Y);

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
                    //Z in meter | Opacity 0-1 --> bereich 0.7m - 1.7m interessant
                    drawBrush.Opacity = 0.5f;
                    drawingContext.DrawEllipse(drawBrush, null, jointPoint, circleSize, circleSize);
                }
            }
        }

        private const double HandSize = 50;
        private readonly Brush handClosedBrush = new SolidColorBrush(Color.FromArgb(128, 255, 0, 0));
        private readonly Brush handOpenBrush = new SolidColorBrush(Color.FromArgb(128, 0, 255, 0));

        private void DrawHand(HandState handState, IReadOnlyDictionary<JointType, Joint> joints, JointType jointType, DrawingContext drawingContext)
        {
            CameraSpacePoint position = joints[jointType].Position;
            ColorSpacePoint depthSpacePoint = this.coordinateMapper.MapCameraPointToColorSpace(position);

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

        private double RadianToDegree(double angle)
        {
            return angle * (180.0 / Math.PI);
        }
        #endregion
    }
}
