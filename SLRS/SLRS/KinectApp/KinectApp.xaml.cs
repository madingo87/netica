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
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Drawing;
using System.Runtime.InteropServices;

using Emgu.CV;
using Emgu.CV.Structure; 

using System.Windows.Media.Media3D;
using Microsoft.Kinect;
using System.Drawing.Imaging;


namespace SLRS
{
    public partial class KinectApp : Window, INotifyPropertyChanged
    {
        #region definitions
        /// <summary>
        /// Size of the RGB pixel in the bitmap
        /// </summary>
        private const int BytesPerPixel = 4;
        // body/depth(512x424) | color(1920x1080) 

        private KinectSensor kinectSensor = null;

        private FrameDescription depthFrameDescription = null;
        private DepthFrameReader depthFrameReader = null;
        private byte[] depthPixels;
        private byte[] colorFrameData;
                                    
        private const int MapDepthToByte = 8000 / 256;
        private WriteableBitmap depthBitmapLeft = null;
        private WriteableBitmap depthBitmapRight = null;

        private ColorFrameReader colorFrameReader = null;
        private FrameDescription colorFrameDescription = null;
        private WriteableBitmap colorBitmap = null;

        private BodyFrameReader bodyFrameReader = null;
        private DrawingGroup bodyDrawingGroup;
        private DrawingImage imageSource;

        private CameraSpacePoint leftHandPostition;
        private CameraSpacePoint rightHandPostition;
        private CameraSpacePoint headPosition;

        private int[] allAngleJointsForUI = new[] { 4, 5, 8, 9 };
        private CameraSpacePoint nx, ny, nz;
        private CoordinateMapper coordinateMapper = null;
        private Body[] bodies = null;

        private StreamWriter distanceData = new StreamWriter(@"c:/temp/distanceTrainData.txt", true);
        private StreamWriter pcdData;

        private int sequenceID = 0; 
        private int gestureNumber = 0;

        private string statusText = null;
        #endregion

        private int maxTestData = 10;
        private int maxTrainData = 50;

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

            this.colorFrameData = new byte[colorFrameDescription.Width * colorFrameDescription.Height * BytesPerPixel];

            this.bodyFrameReader = this.kinectSensor.BodyFrameSource.OpenReader();
            this.bodyFrameReader.FrameArrived += bodyFrameReader_FrameArrived;
            
            this.bodyDrawingGroup = new DrawingGroup();
            this.imageSource = new DrawingImage(bodyDrawingGroup);

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
                    btn_record.Content = "Start";
                    depthFrameIndexL = 0;
                    depthFrameIndexR = 0;

                    break;

                case "Start":
                    btn_record.Content = "Stop";          
                    break;

                case "Stop":
                    btn_record.Content = "Start";

                    sequenceID++;
                    depthFrameIndexL = 0;
                    depthFrameIndexR = 0;

                    if (sequenceID == maxTrainData)
                    {
                        distanceData.Flush();
                        distanceData.Close();
                        distanceData = new StreamWriter(@"c:/temp/distanceTestData.txt", true);
                    }   

                    if (sequenceID == (maxTrainData + maxTestData))
                    {
                        if (gestureNumber + 1 < Helper.gestureWord.Length)
                        {
                            sequenceID = 0;
                            gestureNumber++;

                            distanceData.Flush();
                            distanceData.Close();
                            distanceData = new StreamWriter(@"c:/temp/distanceTrainData.txt", true);
                        }
                        else
                        {
                            StatusText = "Done";
                            btn_record.Content = "Done";
                            btn_record.IsEnabled = false;
                            closeStreams();
                            return;
                        }
                    }

                    break;
            }

            var dataType = sequenceID < maxTrainData ? "train" : "test";
            StatusText = Helper.gestureWord[gestureNumber] + " (" + dataType + " [" + ((maxTrainData + maxTestData) - sequenceID) + "] )";         
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
                //this.kinectSensor = null;
            }
        }
        private void closeStreams()
        {
            try
            {
                if (distanceData != null)
                {
                    distanceData.Flush();
                    distanceData.Close();
                }
            }
            catch (IOException ex)
            {
                MessageBox.Show("Fehler\n" + ex.Message);
            }
        }
        
        #endregion

        #region ** FRAME READER ***
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
                            if ((bool)chk_skin.IsChecked)
                            {
                                var handLeft = coordinateMapper.MapCameraPointToColorSpace(leftHandPostition);
                                var handRight = coordinateMapper.MapCameraPointToColorSpace(rightHandPostition);

                                colorFrame.CopyConvertedFrameDataToArray(colorFrameData, ColorImageFormat.Bgra);
                                getSkinColor(handLeft, handRight);
                            }

                            colorFrame.CopyConvertedFrameDataToIntPtr(
                                this.colorBitmap.BackBuffer,
                                (uint)(colorFrameDescription.Width * colorFrameDescription.Height * BytesPerPixel),
                                ColorImageFormat.Bgra); //32Bit(4Byte)

                            this.colorBitmap.AddDirtyRect(new Int32Rect(0, 0, this.colorBitmap.PixelWidth, this.colorBitmap.PixelHeight));
                        }

                        this.colorBitmap.Unlock();
                    }
                }
            }
        }

        float skinColorHue = 0.0f;
        private unsafe void getSkinColor(ColorSpacePoint leftHand, ColorSpacePoint rightHand)
        {
            byte bl, gl, rl, al, br, gr, rr, ar;
            int handLeftOffset = ((colorFrameDescription.Width * ((int)leftHand.Y) + ((int)leftHand.X)) * BytesPerPixel);
            int handRightOffset = ((colorFrameDescription.Width * ((int)rightHand.Y) + ((int)rightHand.X)) * BytesPerPixel);

            if (handLeftOffset > 0 && handRightOffset > 0 && handLeftOffset < 8294400 && handRightOffset < 8294400)
            {
                bl = colorFrameData[handLeftOffset];
                gl = colorFrameData[handLeftOffset + 1];
                rl = colorFrameData[handLeftOffset + 2];
                al = colorFrameData[handLeftOffset + 3];
                br = colorFrameData[handRightOffset];
                gr = colorFrameData[handRightOffset + 1];
                rr = colorFrameData[handRightOffset + 2];
                ar = colorFrameData[handRightOffset + 3];

                var color = new System.Windows.Media.Color();
                color.B = (byte)((bl + br) / 2);
                color.G = (byte)((gl + gr) / 2);
                color.R = (byte)((rl + rr) / 2);
                color.A = (byte)((al + ar) / 2);

                skinColorHue = System.Drawing.Color.FromArgb(color.A, color.R, color.G, color.B).GetHue();
                this.ellipseSkinColor.Fill = new System.Windows.Media.SolidColorBrush(color);
            }
        }
        private unsafe bool isSkinColor(ColorSpacePoint point)
        {
            int offset = ((colorFrameDescription.Width * ((int)point.Y) + ((int)point.X)) * BytesPerPixel);

            if (offset > 0 && offset < 8294400)
            {
                byte b = colorFrameData[offset];
                byte g = colorFrameData[offset + 1];
                byte r = colorFrameData[offset + 2];
                byte a = colorFrameData[offset + 3];

                var color = System.Drawing.Color.FromArgb(r, g, b);
                var hue = color.GetHue(); //290 - 340
                //var sat = color.GetSaturation(); //0-100
                //var bri = color.GetBrightness(); //0-100

                //if (hue > skinColorHue - colorThreshold && hue < skinColorHue + colorThreshold)
                if (hue > 280 && hue < 350)
                    return true;

                return false;
            }

            return false;
        }

        int bodyFrameSelector = 0;
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
                    dc.DrawRectangle(System.Windows.Media.Brushes.Black, null, new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                    // prevent drawing outside of our render area
                    bodyDrawingGroup.ClipGeometry = new RectangleGeometry(new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));
                    dc.DrawImage(colorBitmap, new Rect(0.0, 0.0, this.colorFrameDescription.Width, this.colorFrameDescription.Height));

                    //Draw recordState
                    bool record = btn_record.Content.Equals("Stop");
                    if (record)
                    {
                        dc.DrawRectangle(System.Windows.Media.Brushes.Firebrick, null, new Rect(new System.Windows.Point(80, 80), new System.Windows.Size(80, 80)));
                        dc.DrawText(new FormattedText("Rec", CultureInfo.CurrentUICulture, FlowDirection.LeftToRight, new Typeface("Arial"), 35, System.Windows.Media.Brushes.Black), new System.Windows.Point(90, 95));
                    }

                    foreach (Body body in this.bodies)
                    {
                        if (body.IsTracked)
                        {
                            leftHandPostition = body.Joints[JointType.HandLeft].Position;
                            rightHandPostition = body.Joints[JointType.HandRight].Position;
                            headPosition = body.Joints[JointType.Head].Position;

                            bool angleMode = radio_angle.IsChecked ?? false;
                            drawUI(body.Joints, dc, angleMode);

                            bodyFrameSelector++;
                            if (bodyFrameSelector == 2)
                            {
                                // 1) Calculate All Data (angles or distances)
                                var allData = calculateData(body.Joints, angleMode, body.JointOrientations);
                                // 2) Write and draw to UI
                                writeData2Gui(allData, angleMode);
                                // 3) Export Data if activated
                                if (record && sequenceID <= maxTrainData + maxTestData)
                                {
                                    //show recorded frames
                                    lbl_fpsBody.Content = Convert.ToUInt64(lbl_fpsBody.Content) + 1;
                                    writeTrainingData(allData);
                                }                                   

                                bodyFrameSelector = 0;
                            }
                        }
                    }                                         
                }
            }
        }

        DepthSpacePoint pl_old;
        DepthSpacePoint pr_old;
        private int windowSize = Helper.DepthFrameWidth;
        private int depthFrameSelector = 0;
        private int depthFrameThreshold = 5; 
        private int depthFrameIndexL = 0;
        private int depthFrameIndexR = 0;
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
                            //Frame handler
                            depthFrameSelector++;
                            if (depthFrameSelector != depthFrameThreshold) return;

                            depthFrameSelector = 0;
                                
                            bool record = btn_record.Content.Equals("Stop");
                            if (record)
                                lbl_fpsDepth.Content = Convert.ToUInt64(lbl_fpsBody.Content) + 1;                                                           

                            int frame = windowSize / 2;
                            DepthSpacePoint pl = coordinateMapper.MapCameraPointToDepthSpace(leftHandPostition);
                            DepthSpacePoint pr = coordinateMapper.MapCameraPointToDepthSpace(rightHandPostition);

                            // === Links
                            if (pl.X <= frame || pl.X >= depthFrameDescription.Width - frame || pl.Y <= frame || pl.Y >= depthFrameDescription.Height - frame)
                                pl = pl_old;

                            ProcessDepthFrameData(depthBuffer.UnderlyingBuffer, frame, 0, ushort.MaxValue, pl, record, true);
                            this.depthBitmapLeft.WritePixels(
                                new Int32Rect(0, 0, this.depthBitmapLeft.PixelWidth, this.depthBitmapLeft.PixelHeight),
                                this.depthPixels,
                                this.depthBitmapLeft.PixelWidth,
                                0);
                            pl_old = pl;


                            // === Rechts
                            if (pr.X <= frame || pr.X >= depthFrameDescription.Width - frame || pr.Y <= frame || pr.Y >= depthFrameDescription.Height - frame)
                                pr = pr_old;

                            ProcessDepthFrameData(depthBuffer.UnderlyingBuffer, frame, 0, ushort.MaxValue, pr, record, false);
                            this.depthBitmapRight.WritePixels(
                                new Int32Rect(0, 0, this.depthBitmapRight.PixelWidth, this.depthBitmapRight.PixelHeight),
                                this.depthPixels,
                                this.depthBitmapRight.PixelWidth,
                                0);
                            pr_old = pr;
                        }                                           
                    }
                }
            }
        }

        private unsafe void ProcessDepthFrameData(IntPtr depthFrameData, int frameSize, ushort minDepth, ushort maxDepth, DepthSpacePoint p, bool rec, bool left)
        {
            ushort* frameData = (ushort*)depthFrameData; // depth frame data is a 16 bit value
            ushort initDepth = frameData[depthFrameDescription.Width * ((int)p.Y) + ((int)p.X)];

            if (rec && (bool)chk_recDepth.IsChecked)
            {
                string file = "";
                //FileCode: [left/right]_[gestureNumber]_[sequence]_[sequneceIndex]
                if (left)   file = String.Format("c:/temp/PCD/pcd/dd_left_{0:00}_{1:00}_{2:00}.pcd", gestureNumber, sequenceID, depthFrameIndexL++);
                else        file = String.Format("c:/temp/PCD/pcd/dd_right_{0:00}_{1:00}_{2:00}.pcd", gestureNumber, sequenceID, depthFrameIndexR++);

                pcdData = new StreamWriter(file, false);
            }

            int distanceFactor = 80;
            int index = 0;

            for (int y = -frameSize; y < frameSize; y++)
            {
                for (int x = -frameSize; x < frameSize; x++)
                {
                    //Select index for smaller frame and get Depth value
                    int offset = (depthFrameDescription.Width * ((int)p.Y + y) + ((int)p.X + x));
                    ushort depth = frameData[offset];

                    bool isNearPalm = depth < initDepth + distanceFactor && depth > initDepth - distanceFactor;         

                    //  ==== Record DepthData for nextStep (Segmentation)
                    if ((bool)chk_recDepth.IsChecked && rec)
                    {
                        if (isNearPalm)
                        {
                            var point = Helper.depthToPCD(p.X + (float)x, p.Y + (float)y, depth);
                            pcdData.WriteLine(String.Format("{0} {1} {2}", point.X.ToString().Replace(',', '.'), point.Y.ToString().Replace(',', '.'), point.Z.ToString().Replace(',', '.')));
                            pcdData.Flush();
                        }
                    }

                    //show depth image
                    depth = isNearPalm ? (ushort)(depth + (depth - initDepth) * 5) : (ushort)0;
                    depthPixels[index] = (byte)(depth / MapDepthToByte);
                    index++;
                }
            }

            if ((bool)chk_recDepth.IsChecked && rec)
                pcdData.Close();

        }
        #endregion //*******************

        private double[] calculateData(IReadOnlyDictionary<JointType, Joint> joints, bool angleMode, IReadOnlyDictionary<JointType,JointOrientation> orientations)
        {
            List<double> allData = new List<double>();

            if (angleMode)
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
                allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.ElbowLeft));
                allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.ElbowRight));

                allData.Add(calculateDistances(joints, (int)JointType.ElbowRight, (int)JointType.HandLeft));
                allData.Add(calculateDistances(joints, (int)JointType.ElbowLeft, (int)JointType.HandRight));

                allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandLeft));
                allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandRight));

                allData.Add(calculateDistances(joints, (int)JointType.ElbowLeft, (int)JointType.ElbowRight));
                allData.Add(calculateDistances(joints, (int)JointType.HandRight, (int)JointType.HandLeft));

                allData.Add(calculateDistances(joints, (int)JointType.HandLeft, (int)JointType.SpineMid));
                allData.Add(calculateDistances(joints, (int)JointType.HandRight, (int)JointType.SpineMid));
            }
         
            return allData.ToArray<double>();
        }
        private double calculateDistances(IReadOnlyDictionary<JointType, Joint> joints, int joint1, int joint2)
        {
            var coords = new CameraSpacePoint[2] { joints[(JointType)joint1].Position, joints[(JointType)joint2].Position };
            if (coords[0].Z < 0) coords[0].Z = InferredZPositionClamp;
            if (coords[1].Z < 0) coords[1].Z = InferredZPositionClamp;

            double vec = Math.Sqrt(Math.Pow(coords[0].X - coords[1].X, 2) + Math.Pow(coords[0].Y - coords[1].Y, 2) + Math.Pow(coords[0].Z - coords[1].Z, 2));
            return Math.Abs(vec);
        }

        private void writeData2Gui(double[] allData, bool angleMode) 
        {
            int counter = 0;
            string text = "";

            if (angleMode)
            {
                text += "\nOrientierung\n";
                for (int i = 0; i < allAngleJointsForUI.Length; i++)
                {
                    string obj = "";
                    switch (allAngleJointsForUI[i])
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
                text += "Abstände\n";
                text += String.Format("\nHead -> E(l)\t{0:0.00}",allData[counter++]);
                text += String.Format("\nHead -> E(r)\t{0:0.00}",allData[counter++]);
                text += String.Format("\nE(r) -> H(l)\t{0:0.00}",allData[counter++]);
                text += String.Format("\nE(l) -> H(r)\t{0:0.00}",allData[counter++]);
                text += String.Format("\nHead -> H(l)\t{0:0.00}",allData[counter++]);
                text += String.Format("\nHead -> H(r)\t{0:0.00}",allData[counter++]);
                text += String.Format("\nE(r) -> E(l)\t{0:0.00}",allData[counter++]);
                text += String.Format("\nH(l) -> H(r)\t{0:0.00}",allData[counter++]);
                text += String.Format("\nH(l) -> S\t{0:0.00}", allData[counter++]);
                text += String.Format("\nH(r) -> S\t{0:0.00}", allData[counter++]);
            }

            this.txtAngles.Text = text;
        }

        int addId = 0;
        private void writeTrainingData(double[] allData) 
        {
            var mean = allData.Sum() / allData.Length;
            for (var i = 0; i < allData.Length; i++)
                allData[i] -= mean;

            // seqID = xxxyyy, xxx = Label , yyy = sequence
            var entry = String.Format("{0:000}{1:000}\t|L {2}\t|F", gestureNumber, sequenceID+addId, Helper.gestureCode[gestureNumber]);
            for (int i = 0; i < allData.Length; )
                entry += String.Format(" {0:0.000000}", allData[i++]);

            entry = entry.Replace(',', '.');
            distanceData.WriteLine(entry);
            distanceData.Flush();            
        }

        int resizer = 10;
        List<JointType> jointTypes = new List<JointType>() { JointType.Head, JointType.SpineMid, JointType.ShoulderLeft, JointType.ElbowLeft, JointType.WristLeft, JointType.ShoulderRight, JointType.ElbowRight, JointType.WristRight, JointType.HandLeft, JointType.HandRight };
        private const float InferredZPositionClamp = 0.1f;
        private System.Windows.Media.Pen orientationPen = new System.Windows.Media.Pen(System.Windows.Media.Brushes.OrangeRed, 10);
        private System.Windows.Media.Pen zPen = new System.Windows.Media.Pen(System.Windows.Media.Brushes.Yellow, 3);
        private System.Windows.Media.Pen yPen = new System.Windows.Media.Pen(System.Windows.Media.Brushes.Magenta, 3);
        private System.Windows.Media.Pen xPen = new System.Windows.Media.Pen(System.Windows.Media.Brushes.Cyan, 3);
        private void drawUI(IReadOnlyDictionary<JointType, Joint> joints, DrawingContext drawingContext, bool angleMode)
        {
            Dictionary<JointType, CameraSpacePoint> jointPoints = new Dictionary<JointType, CameraSpacePoint>();

            // sometimes depth(Z) of an inferred joint may show as negative -> clamp down to 0.1f to prevent coordinatemapper from returning (-Infinity, -Infinity)
            foreach (var type in jointTypes)
            {
                var jointPosition = joints[type].Position;
                if (jointPosition.Z < 0) jointPosition.Z = InferredZPositionClamp;
                jointPoints.Add(type, jointPosition);
            }

            if (angleMode)
            {
                // ====== Draw Orientation
                ColorSpacePoint cSPoint0, cSPoint1;
                System.Windows.Point p0, p1;
                CameraSpacePoint p = new CameraSpacePoint();

                foreach (int thisJoint in allAngleJointsForUI)
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
                    p0 = new System.Windows.Point(cSPoint0.X, cSPoint0.Y);
                    p1 = new System.Windows.Point(cSPoint1.X, cSPoint1.Y);
                    drawingContext.DrawLine(orientationPen, p0, p1);
                }

                // ====== Draw Normals
                cSPoint0 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.SpineMid]);
                p0 = new System.Windows.Point(cSPoint0.X, cSPoint0.Y);

                p.X = jointPoints[JointType.SpineMid].X - nx.X * resizer;
                p.Y = jointPoints[JointType.SpineMid].Y + nx.Y * resizer;
                p.Z = jointPoints[JointType.SpineMid].Z - nx.Z * resizer;
                cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(p);
                p1 = new System.Windows.Point(cSPoint1.X, cSPoint1.Y);
                drawingContext.DrawLine(xPen, p0, p1);

                p.X = jointPoints[JointType.SpineMid].X - ny.X * resizer;
                p.Y = jointPoints[JointType.SpineMid].Y + ny.Y * resizer;
                p.Z = jointPoints[JointType.SpineMid].Z + ny.Z * resizer;
                cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(p);
                p1 = new System.Windows.Point(cSPoint1.X, cSPoint1.Y);
                drawingContext.DrawLine(yPen, p0, p1);

                p.X = jointPoints[JointType.SpineMid].X + nz.X * resizer;
                p.Y = jointPoints[JointType.SpineMid].Y - nz.Y * resizer;
                p.Z = jointPoints[JointType.SpineMid].Z - nz.Z * resizer;
                cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(p);
                p1 = new System.Windows.Point(cSPoint1.X, cSPoint1.Y);
                drawingContext.DrawLine(zPen, p0, p1);

            }
            else 
            {
                ColorSpacePoint cSPoint0, cSPoint1, cSPoint2, cSPoint3, cSPoint4, cSPoint5;
                System.Windows.Point p0, p1, p2, p3, p4, p5;

                cSPoint0 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.HandLeft]);
                cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.ElbowLeft]);
                cSPoint2 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.Head]);
                cSPoint3 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.HandRight]);
                cSPoint4 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.ElbowRight]);
                cSPoint5 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.SpineMid]);
                p0 = new System.Windows.Point(cSPoint0.X, cSPoint0.Y);
                p1 = new System.Windows.Point(cSPoint1.X, cSPoint1.Y);
                p2 = new System.Windows.Point(cSPoint2.X, cSPoint2.Y);
                p3 = new System.Windows.Point(cSPoint3.X, cSPoint3.Y);
                p4 = new System.Windows.Point(cSPoint4.X, cSPoint4.Y);
                p5 = new System.Windows.Point(cSPoint5.X, cSPoint5.Y);

                drawingContext.DrawLine(orientationPen, p0, p2);
                drawingContext.DrawLine(orientationPen, p1, p2);
                drawingContext.DrawLine(orientationPen, p3, p2);
                drawingContext.DrawLine(orientationPen, p4, p2);
                drawingContext.DrawLine(orientationPen, p0, p3);
                drawingContext.DrawLine(orientationPen, p0, p4);
                drawingContext.DrawLine(orientationPen, p1, p3);
                drawingContext.DrawLine(orientationPen, p1, p4);

                drawingContext.DrawLine(orientationPen, p0, p5);
                drawingContext.DrawLine(orientationPen, p3, p5);
            }
            
        }
    }
}
