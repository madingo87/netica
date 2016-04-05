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
    using System.Windows.Data;

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

        private int[] allJointsForUI = new[] { 4, 5, 8, 9 };
        private CameraSpacePoint nx, ny, nz;
        private CoordinateMapper coordinateMapper = null;
        private Body[] bodies = null;

        private StreamWriter javaData, csvData, csvResult, csvClass;
        private int descriptionNumber, gestureNumber;
        //private int dataInputSize;
        //private int dataOutputSize = 11;
        private string[] gestureWord = new string[] { "A", "C", "H", "I", "K", "L", "M", "O", "T", "V", "X" };
        private string[] gestureNNCode = new string[] { 
            "1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1", 
            "-1 1 -1 -1 -1 -1 -1 -1 -1 -1 -1", 
            "-1 -1 1 -1 -1 -1 -1 -1 -1 -1 -1", 
            "-1 -1 -1 1 -1 -1 -1 -1 -1 -1 -1", 
            "-1 -1 -1 -1 1 -1 -1 -1 -1 -1 -1",
            "-1 -1 -1 -1 -1 1 -1 -1 -1 -1 -1",
            "-1 -1 -1 -1 -1 -1 1 -1 -1 -1 -1",
            "-1 -1 -1 -1 -1 -1 -1 1 -1 -1 -1",
            "-1 -1 -1 -1 -1 -1 -1 -1 1 -1 -1",
            "-1 -1 -1 -1 -1 -1 -1 -1 -1 1 -1",
            "-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 1"};

        //sets the flag for recording new JointPosition Data
        private bool recordMode = false;
        private bool classifyEnabled = false;

        private string gestureText = null;        
        private string statusText = null;
        private ClassificationTypes _type;

        private int maxTestData;
        private int maxTrainData;


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

            descriptionNumber = Convert.ToInt32(Properties.Resources.Precarriage); //Vorlauf Frames

            maxTrainData = Convert.ToInt32(Properties.Resources.MaxTrainData);
            maxTestData = Convert.ToInt32(Properties.Resources.MaxTestData);

            this.InitializeComponent();
        }

       
        #region Properies

        public event PropertyChangedEventHandler PropertyChanged;

        public ImageSource ImageSource
        {
            get { return this.imageSource; }
        }
        
        public string GestureText
        {
            get { return this.gestureText; }
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

        public ClassificationTypes Type 
        { 
            get { return _type; } 
            set { 
                _type = value; 
                if (PropertyChanged != null) 
                    PropertyChanged(this, new PropertyChangedEventArgs("Type")); } 
        }

        #endregion

        #region EventHandler

        private void chk_Record_Checked(object sender, RoutedEventArgs e)
        {
            gestureNumber = 0;
            this.recordMode = true;
        }
        private void chk_Record_Unchecked(object sender, RoutedEventArgs e)
        {
            this.recordMode = false;
            StatusText = Properties.Resources.KinectReady;
            descriptionNumber = -50;
        }
        private void chk_Classify_Checked(object sender, RoutedEventArgs e)
        {
            this.classifyEnabled = true;
            this.recordMode = false;
            
            if (_type != ClassificationTypes.OrientationBayes) StatusText = "Classifying...";
        }
        private void chk_Classify_Unchecked(object sender, RoutedEventArgs e)
        {
            this.classifyEnabled = false;
            StatusText = Properties.Resources.KinectReady;
            GestureText = "";
            txtSuccessRate.Text = "-";
            descriptionNumber = -50;
        }

        private void Sensor_IsAvailableChanged(object sender, IsAvailableChangedEventArgs e)
        {
            // on failure, set the status text
            this.StatusText = this.kinectSensor.IsAvailable ? Properties.Resources.KinectReady : Properties.Resources.NoSensor;
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
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
                if (javaData != null)
                {
                    javaData.Flush();
                    javaData.Close();
                }
                if (csvData != null)
                {
                    csvData.Flush();
                    csvData.Close();
                }
                if (csvResult != null)
                {
                    csvResult.Flush();
                    csvResult.Close();
                }
                if (csvClass != null)
                {
                    csvClass.Flush();
                    csvClass.Close();
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
                            // 1) Calculate All Data (angles or distances)
                            var allData = calculateData(body.Joints);

                            // 2) Write and draw to UI
                            writeData2Gui(allData);
                            dc.DrawImage(colorBitmap, new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                            drawJoints(body.Joints, dc);

                            // 3) Export Data if activated
                            var collectData = descriptionNumber <= (maxTrainData+maxTestData) && recordMode;
                            if (collectData)
                            {                               
                                if (descriptionNumber >= 0)
                                {
                                    if (_type != ClassificationTypes.OrientationBayes)
                                        writeJavaTrainingData(allData);
                                    else
                                        writeCsvTrainingData(allData);
                                }
                                else
                                    StatusText = "Starting to Collect for Gesture === " + gestureWord[gestureNumber] + " ===";                               

                                if (descriptionNumber == (maxTrainData + maxTestData))
                                {
                                    if (gestureNumber + 1 < gestureWord.Length)
                                    {
                                        descriptionNumber = Convert.ToInt32(Properties.Resources.Precarriage);
                                        gestureNumber++;
                                        closeStreams();
                                    }
                                    else
                                        StatusText = "Collecting done!";
                                }

                                descriptionNumber++;
                            }
                            
                           // 4) Classify if activated
                            if (classifyEnabled)
                            {
                                if (_type != ClassificationTypes.OrientationBayes)
                                {
                                    var output = classifyGesture(allData);
                                    updateGestureText(output);
                                }
                                else
                                {
                                    descriptionNumber++;
                                    collectBayesClassData(allData);
                                }
                            }
                        }
                    }
                }
            }
        }
        //*******************

        private double[] calculateData(IReadOnlyDictionary<JointType, Joint> joints)
        {
            List<double> allData = new List<double>();

            if (_type != ClassificationTypes.DistanceNN)
            {
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

            }
            else
            {
                // distances
                allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.ElbowLeft));
                allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.ElbowRight));
                allData.Add(calculateDistances(joints, (int)JointType.ElbowLeft, (int)JointType.ElbowRight));

                allData.Add(calculateDistances(joints, (int)JointType.ElbowRight, (int)JointType.HandLeft));
                allData.Add(calculateDistances(joints, (int)JointType.ElbowLeft, (int)JointType.HandRight));

                allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandLeft));
                allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandRight));
                allData.Add(calculateDistances(joints, (int)JointType.HandRight, (int)JointType.HandLeft));

                //allData.Add(calculateDistances(joints, (int)JointType.HandLeft, (int)JointType.ShoulderLeft));
                //allData.Add(calculateDistances(joints, (int)JointType.HandRight, (int)JointType.ShoulderRight));
            }

            //dataInputSize = allData.Count;
         
            return allData.ToArray<double>();
        }

        private double calculateDistances(IReadOnlyDictionary<JointType, Joint> joints, int joint1, int joint2) 
        {
            var coords = new CameraSpacePoint[2] { joints[(JointType)joint1].Position, joints[(JointType)joint2].Position };
            if (coords[0].Z < 0) coords[0].Z = InferredZPositionClamp;
            if (coords[1].Z < 0) coords[1].Z = InferredZPositionClamp;

            double vec = Math.Sqrt(Math.Pow(coords[0].X - coords[1].X, 2) + Math.Pow(coords[0].Y - coords[1].Y,2) + Math.Pow(coords[0].Z - coords[1].Z,2));
            return Math.Abs(vec);
        }

        private void writeData2Gui(double[] allData) 
        {
            int counter = 0;
            string text = "";
                            
            if (_type != ClassificationTypes.DistanceNN)                
            {
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
            }
            else
            {
                text += String.Format("Abstände\n\tEllbogen Links \t\t{0:0.00} \n\tEllbogen Rechts \t\t{1:0.00} \n\tBeide Ellbogen \t\t{2:0.00}\n\tEllb.Links HandRechts \t{3:0.00}\n\tEllb.Rechts HandLinks \t{4:0.00}" +
                                        "\n\tHand Links \t\t{5:0.00} \n\tHand Rechts \t\t{6:0.00} \n\tBeide Hände \t\t{7:0.00}",
                    allData[counter++], allData[counter++], allData[counter++], allData[counter++], allData[counter++], allData[counter++], allData[counter++], allData[counter++]);
                //\n\tHand->Schulter Links: {8:0.00} \n\tHand->Schulter Rechts {9:0.00}",
            }

            this.txtAngles.Text = text;
        }

        private void updateGestureText(float[] output)
        {
            Dictionary<string, float> dict = new Dictionary<string, float>();

            for (var i = 0; i < output.Length; i++)
                dict.Add(gestureWord[i], output[i]);

            try
            {
                var first = dict.Single(e => e.Value == dict.Values.Max());
                dict.Remove(first.Key);
                var sec = dict.Single(e => e.Value == dict.Values.Max());
                dict.Remove(sec.Key);
                var third = dict.Single(e => e.Value == dict.Values.Max());

                GestureText = first.Key;

                Array.Sort(output);
                this.txtSuccessRate.Text = string.Format("(1)\t{0}\t--\t{1:0.00}\n(2)\t{2}\t--\t{3:0.00}\n(3)\t{4}\t--\t{5:0.00}",
                                                           first.Key, first.Value, sec.Key, sec.Value, third.Key, third.Value);
            }
            catch
            {
                this.txtSuccessRate.Text = "N/A";
                GestureText = "";
            }
        }

        [DllImport("NetWrapperLib.dll")]
        public unsafe static extern int classifyDist(float* input, float* output);
        [DllImport("NetWrapperLib.dll")]
        public unsafe static extern int classifyOrien(float* input, float* output);
        private unsafe float[] classifyGesture(double[] angles)
        {
            float[] inputArray = new float[angles.Length];
            float[] outputArray = new float[gestureNNCode.Length];
            int res;

            for (int i = 0; i < angles.Length; i++)
                inputArray[i] = (float)angles[i];

            fixed (float* input = inputArray)
            {
                fixed (float* output = outputArray)
                {
                    if (_type == ClassificationTypes.DistanceNN)
                        res = classifyDist(input, output);
                    if (_type == ClassificationTypes.OrientationNN)
                        res = classifyOrien(input, output);
                }
            }

            return outputArray;
        }
        private void collectBayesClassData(double[] data) 
        {
            if (descriptionNumber == 0)
            {
                csvClass = new StreamWriter(@"c:/temp/cData.csv", true);
                //csvClass.WriteLine(String.Format("Daten vom {0:dd.MM.yyyy HH:mm:ss}", DateTime.Now));

                StatusText = "Collecting Bayes classification data...";
            }

            if (descriptionNumber > 0)
            {
                var entry = "";
                for (int i = 0; i < data.Length; )
                    entry += String.Format("{0:0.000};", data[i++]);

                entry = entry.Replace(',', '.');
                entry = entry.Replace(';', ',');
                csvClass.WriteLine(entry.TrimEnd(','));
                csvClass.Flush();
            }
        }

        private void writeJavaTrainingData(double[] allData)
        {
            if (descriptionNumber == 0)
            {
                javaData = new StreamWriter(@"c:/temp/trainData.pat", true);
                javaData.WriteLine("#=============================== NEXT ===================================");
                StatusText = "Collecting Traindata...";
            }

            if (descriptionNumber == (maxTrainData + 1))
            {
                javaData.Flush();
                javaData.Close();
                javaData = new StreamWriter(@"c:/temp/testData.pat", true);
                javaData.WriteLine("#=============================== NEXT ===================================");
                StatusText = "Collecting Testdata...";
            }
            
            if (descriptionNumber > 0)
            {
                javaData.WriteLine("#description number " + descriptionNumber);

                var entry = "";
                for (int i = 0; i < allData.Length; )
                    entry += String.Format("{0:0.000} ", allData[i++]);

                javaData.Write(entry.Replace(',', '.'));
                javaData.WriteLine("\n#result ");
                javaData.WriteLine(gestureNNCode[gestureNumber]);
                javaData.WriteLine();
                javaData.Flush();
            }      
        }

        private void writeCsvTrainingData(double[] allData) 
        {
            if (descriptionNumber == 0)
            {
                csvData = new StreamWriter(@"c:/temp/trainData.csv", true);
                csvResult = new StreamWriter(@"c:/temp/result.csv", true);
                //csvData.WriteLine(String.Format("Daten vom {0:dd.MM.yyyy HH:mm:ss}", DateTime.Now));
                //csvResult.WriteLine(String.Format("Daten vom {0:dd.MM.yyyy HH:mm:ss}", DateTime.Now));
                //csvData.Flush();
                //csvResult.Flush();
                StatusText = "Collecting Traindata...";
            }

            if (descriptionNumber > 0)
            {           
                var entry = "";
                for (int i = 0; i < allData.Length; )
                    entry += String.Format("{0:0.000};", allData[i++]);

                entry = entry.Replace(',', '.');
                entry = entry.Replace(';', ',');
                csvData.WriteLine(entry.TrimEnd(','));
                csvData.Flush();

                csvResult.WriteLine(gestureWord[gestureNumber]);
                csvResult.Flush();
            }
        }

        int resizer = 10;
        List<JointType> jointTypes = new List<JointType>() { JointType.Head, JointType.SpineMid, JointType.ShoulderLeft, JointType.ElbowLeft, JointType.WristLeft, JointType.ShoulderRight, JointType.ElbowRight, JointType.WristRight };
        private const float InferredZPositionClamp = 0.1f;
        private Pen orientationPen = new Pen(Brushes.OrangeRed, 10);
        private Pen zPen = new Pen(Brushes.Yellow, 3);
        private Pen yPen = new Pen(Brushes.Magenta, 3);
        private Pen xPen = new Pen(Brushes.Cyan, 3);
        private void drawJoints(IReadOnlyDictionary<JointType, Joint> joints, DrawingContext drawingContext)
        {
            Dictionary<JointType, CameraSpacePoint> jointPoints = new Dictionary<JointType, CameraSpacePoint>();

            // sometimes depth(Z) of an inferred joint may show as negative -> clamp down to 0.1f to prevent coordinatemapper from returning (-Infinity, -Infinity)
            foreach (var type in jointTypes)
            {
                var jointPosition = joints[type].Position;
                if (jointPosition.Z < 0) jointPosition.Z = InferredZPositionClamp;
                jointPoints.Add(type, jointPosition);
            }

            if (_type != ClassificationTypes.DistanceNN)
            {
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
            else
            {
                ColorSpacePoint cSPoint0, cSPoint1, cSPoint2, cSPoint3, cSPoint4;
                Point p0, p1, p2, p3, p4;

                cSPoint0 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.WristLeft]);
                cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.ElbowLeft]);
                cSPoint2 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.Head]);
                cSPoint3 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.WristRight]);
                cSPoint4 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.ElbowRight]);
                p0 = new Point(cSPoint0.X, cSPoint0.Y);
                p1 = new Point(cSPoint1.X, cSPoint1.Y);
                p2 = new Point(cSPoint2.X, cSPoint2.Y);
                p3 = new Point(cSPoint3.X, cSPoint3.Y);
                p4 = new Point(cSPoint4.X, cSPoint4.Y);

                drawingContext.DrawLine(orientationPen, p0, p2);
                drawingContext.DrawLine(orientationPen, p1, p2);
                drawingContext.DrawLine(orientationPen, p3, p2);
                drawingContext.DrawLine(orientationPen, p4, p2);
                drawingContext.DrawLine(orientationPen, p0, p3);
                drawingContext.DrawLine(orientationPen, p0, p4);
                drawingContext.DrawLine(orientationPen, p1, p3);
                drawingContext.DrawLine(orientationPen, p1, p4);
            }
        }
    }

    public enum ClassificationTypes
    {
        DistanceNN,
        OrientationNN,
        OrientationBayes
    }

    public class EnumBooleanConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture) 
        { 
            if (parameter.Equals(value)) 
                return true; 
            else 
                return false; 
        } 

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture) 
        {
            if (((bool)value) == true)
                return parameter;            
            else
                return DependencyProperty.UnsetValue;
        }
    }
}


