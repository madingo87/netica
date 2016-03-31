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
        StreamWriter csvData;
        StreamWriter csvResult;
        int descriptionNumber, gestureNumber;
        string[] gesture = new string[] { "Y", "M", "C", "A", "I" };

        //sets the flag for recording new JointPosition Data
        bool recordMode = false;
        bool classifyEnabled = false;
        private string gestureText;        
        private string statusText = null;

        int maxTestData;
        int maxTrainData;

        int[] allJointKeys = new[] { 4, 5, 8, 9 };
        CameraSpacePoint nx, ny, nz;
    
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

            maxTrainData = Convert.ToInt32(Properties.Resources.MaxTrainData);
            maxTestData = Convert.ToInt32(Properties.Resources.MaxTestData);

            csvData = new StreamWriter(@"c:/temp/trainData.csv", false);
            csvResult = new StreamWriter(@"c:/temp/result.csv", false);
            csvData.WriteLine(String.Format("Daten vom {0:dd.MM.yyyy HH:mm:ss}", DateTime.Now));
            csvResult.WriteLine(String.Format("Daten vom {0:dd.MM.yyyy HH:mm:ss}", DateTime.Now));
            csvData.Flush();

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
            gestureNumber = 0;
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
            if (csvData != null) csvData.Close();
            csvData = new StreamWriter(@"c:\temp\classify.csv");

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
                            var allData = calculateData(body.Joints);

                            var collectData = descriptionNumber <= (maxTrainData+maxTestData) && recordMode;
                            if (collectData)
                            {
                                if (descriptionNumber > 0)
                                {
                                    //writeJavaTrainingData(allData);
                                    writeCsvTrainingData(allData);
                                }
                                else
                                    StatusText = "Starting to Collect for Gesture === " + gesture[gestureNumber] + "===";                               
    
                                descriptionNumber++;

                                if (descriptionNumber == (maxTrainData + maxTestData))
                                {
                                    if (gestureNumber + 1 < gesture.Length)
                                    {
                                        descriptionNumber = Convert.ToInt32(Properties.Resources.Precarriage);
                                        gestureNumber++;
                                    }
                                    else
                                        StatusText = "Collecting done!";
                                }
                            }
                            
                            writeData2Gui(allData);
                                  
                            dc.DrawImage(colorBitmap, new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                            drawJoints(body.Joints, dc);

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

        private double[] calculateData(IReadOnlyDictionary<JointType, Joint> joints)
        {
            List<double> allData = new List<double>();
            CameraSpacePoint vec = new CameraSpacePoint();
            CameraSpacePoint newSpineShoulder = new CameraSpacePoint();

            nz = Helper.getNormalVector(joints[JointType.ShoulderLeft].Position, joints[JointType.ShoulderRight].Position, joints[JointType.SpineMid].Position);
            newSpineShoulder.X = joints[JointType.SpineShoulder].Position.X - nz.X;
            newSpineShoulder.Y = joints[JointType.SpineShoulder].Position.Y - nz.Y;
            newSpineShoulder.Z = joints[JointType.SpineShoulder].Position.Z - nz.Z;            
            ny = Helper.getNormalVector(joints[JointType.ShoulderLeft].Position, joints[JointType.ShoulderRight].Position, newSpineShoulder );
            nx = Helper.getNormalVector(joints[JointType.SpineShoulder].Position, joints[JointType.SpineMid].Position, newSpineShoulder);

            //LEFT
            //Shoulder->Elbow
            vec.X = joints[JointType.ElbowLeft].Position.X - joints[JointType.ShoulderLeft].Position.X;
            vec.Y = joints[JointType.ElbowLeft].Position.Y - joints[JointType.ShoulderLeft].Position.Y;
            vec.Z = joints[JointType.ElbowLeft].Position.Z - joints[JointType.ShoulderLeft].Position.Z;
            allData.Add(Helper.getAngle(vec,nz));
            allData.Add(Helper.getAngle(vec,ny));
            allData.Add(Helper.getAngle(vec,nx));

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


            // distances
            //allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.ElbowLeft));
            //allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.ElbowRight));
            //allData.Add(calculateDistances(joints, (int)JointType.ElbowLeft, (int)JointType.ElbowRight));

            //allData.Add(calculateDistances(joints, (int)JointType.ElbowRight, (int)JointType.HandLeft));
            //allData.Add(calculateDistances(joints, (int)JointType.ElbowLeft, (int)JointType.HandRight));

            //allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandLeft));
            //allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandRight));
            //allData.Add(calculateDistances(joints, (int)JointType.HandRight, (int)JointType.HandLeft));

            //allData.Add(calculateDistances(joints, (int)JointType.HandLeft, (int)JointType.ShoulderLeft));
            //allData.Add(calculateDistances(joints, (int)JointType.HandRight, (int)JointType.ShoulderRight));

            dataInputSize = allData.Count;
         
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

        #region Helper
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

                text += String.Format("\n\t{0} Z: {1:0.00} Y: {2:0.00} X: {3:0.00}",
                    obj, allData[counter++], allData[counter++], allData[counter++]);

            }
            //text += String.Format("\n\nAbstände\n\tEllb L: {0:0.00} \n\tEllb R: {1:0.00} \n\tBeide Ellb {2:0.00}\n\tEllbLinks->HandRechts {3:0.00}\n\tEllbRechts->HandLinks{4:0.00}" +
            //                        "\n\tHand Links: {5:0.00} \n\tHand Rechts: {6:0.00} \n\tBeide Hände {7:0.00}\n\tHand->Schulter Links: {8:0.00} \n\tHand->Schulter Rechts {9:0.00}",
            //    allData[counter++], allData[counter++], allData[counter++], allData[counter++], allData[counter++],
            //    allData[counter++], allData[counter++], allData[counter++], allData[counter++], allData[counter++]);
            this.txtAngles.Text = text;
        }

        private void updateGestureText(float[] output)
        {
            Dictionary<string, float> dict = new Dictionary<string, float>();
            var words = new string[]{"Y", "M", "C", "A", "I"};

            for (var i = 0; i < output.Length; i++)
                dict.Add(words[i], output[i]);

            try
            {
                var first = dict.Single(e => e.Value == dict.Values.Max());
                dict.Remove(first.Key);
                var sec = dict.Single(e => e.Value == dict.Values.Max());
                dict.Remove(sec.Key);
                var third = dict.Single(e => e.Value == dict.Values.Max());

                GestureText = first.Key;

                Array.Sort(output);
                this.txtSuccessRate.Text = string.Format("Output\n\tWin:\t {0:0.00} {1} \n\tSec:\t {2:0.00} {3}\n\tThrd:\t {4:0.00} {5}",
                                                           first.Value, first.Key, sec.Value, sec.Key, third.Value, third.Key);
            }
            catch (Exception e)
            {
                this.txtSuccessRate.Text = "N/A";
                GestureText = "";
            }
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

        private void writeJavaTrainingData(double[] allData)
        {
            if (descriptionNumber == 1)
            {
                swData = new StreamWriter(@"c:/temp/trainData.pat", true);
                swData.WriteLine("#=============================== NEXT ===================================");
            }

            if (descriptionNumber == (maxTrainData + 1))
            {
                swData.Flush();
                swData.Close();
                swData = new StreamWriter(@"c:/temp/testData.pat", true);
                StatusText = "Collecting Testdata...";
                swData.WriteLine("#=============================== NEXT ===================================");
            }
            
            if (descriptionNumber > 1)
            {
                swData.WriteLine("#description number " + descriptionNumber + 1);

                var entry = "";
                for (int i = 0; i < allData.Length; )
                    entry += String.Format("{0:0.000} ", allData[i++]);

                swData.Write(entry.Replace(',', '.'));
                swData.WriteLine("\n#result ");
                swData.WriteLine(Properties.Resources.Result);
                swData.WriteLine();
                swData.Flush();
            }      
        }

        private void writeCsvTrainingData(double[] allData) 
        {
            if (descriptionNumber == 1)           
                StatusText = "Collecting Traindata for  === " + gesture[gestureNumber] + "===";
            
            var entry = "";
            for (int i = 0; i < allData.Length; )
                entry += String.Format("{0:0.000};", allData[i++]);

            entry = entry.Replace(',', '.');
            entry = entry.Replace(';', ',');
            csvData.WriteLine(entry.TrimEnd(','));
            csvData.Flush();

            csvResult.WriteLine(gesture[gestureNumber]);
        }

        int resizer = 10;
        List<JointType> jointTypes = new List<JointType>() { JointType.SpineMid, JointType.ShoulderLeft, JointType.ElbowLeft, JointType.WristLeft, JointType.ShoulderRight, JointType.ElbowRight, JointType.WristRight };
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

            ColorSpacePoint cSPoint0, cSPoint1;
            Point p0, p1;
            CameraSpacePoint p = new CameraSpacePoint();

            // ====== Draw Orientation
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
        #endregion
    }
}


