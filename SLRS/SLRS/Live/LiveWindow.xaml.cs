using Microsoft.Kinect;
using Microsoft.MSR.CNTK.Extensibility.Managed;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.IO;
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

namespace SLRS
{
    public partial class LiveWindow : Window
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
        private const int MapDepthToByte = 8000 / 256;
        private WriteableBitmap depthBitmapLeft = null;
        private WriteableBitmap depthBitmapRight = null;        
        
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

        private CoordinateMapper coordinateMapper = null;
        private Body[] bodies = null;

        private string statusText = null;
        #endregion

        public LiveWindow()
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

        private void Sensor_IsAvailableChanged(object sender, IsAvailableChangedEventArgs e)
        {
            // on failure, set the status text
            StatusText = this.kinectSensor.IsAvailable ? "Kinect Ready :)" : "Keine Kinect gefunden...";
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (this.colorFrameReader != null)
            {
                this.colorFrameReader.FrameArrived -= this.colorFrameReader_FrameArrived;
                this.colorFrameReader.Dispose();
            }

            if (this.bodyFrameReader != null)
            {
                this.bodyFrameReader.FrameArrived -= this.bodyFrameReader_FrameArrived;
                this.bodyFrameReader.Dispose();
            }

            if (this.kinectSensor != null)
            {
                this.kinectSensor.Close();
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
                                ColorImageFormat.Bgra); //32Bit(4Byte)

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

                    foreach (Body body in this.bodies)
                    {
                        if (body.IsTracked)
                        {
                            leftHandPostition = body.Joints[JointType.HandLeft].Position;
                            rightHandPostition = body.Joints[JointType.HandRight].Position;

                            drawUI(body.Joints, dc);

                            if (started)
                            {
                                frameSelector++;
                                if (frameSelector == 2)
                                {

                                    var allData = calculateData(body.Joints, body.JointOrientations);
                                    evaluateDistances(allData);
                                    frameSelector = 0;
                                }
                            }
                        }
                    }                                         
                }
            }
        }


        DepthSpacePoint pl_old;
        DepthSpacePoint pr_old;
        private int windowSize = 100;
        private int depthFrameSelector = 0;
        private int depthFrameThreshold = 15;
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
                            bool recordThisFrame = depthFrameSelector == depthFrameThreshold;
                            if (recordThisFrame) depthFrameSelector = 0;


                            int frame = windowSize / 2;
                            DepthSpacePoint pl = coordinateMapper.MapCameraPointToDepthSpace(leftHandPostition);
                            DepthSpacePoint pr = coordinateMapper.MapCameraPointToDepthSpace(rightHandPostition);

                            // === Links
                            if (pl.X <= frame || pl.X >= depthFrameDescription.Width - frame || pl.Y <= frame || pl.Y >= depthFrameDescription.Height - frame)
                                pl = pl_old;

                            ProcessDepthFrameData(depthBuffer.UnderlyingBuffer, frame, 0, ushort.MaxValue, pl, true);
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
                            if (pr.X <= frame || pr.X >= depthFrameDescription.Width - frame || pr.Y <= frame || pr.Y >= depthFrameDescription.Height - frame)
                                pr = pr_old;

                            ProcessDepthFrameData(depthBuffer.UnderlyingBuffer, frame, 0, ushort.MaxValue, pr, false);
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

                        if (started)
                        {
                            PCDEval pcdEvaluate = new PCDEval();
                            pcdEvaluate.selectFolder(@"c:\CNTK\models\pcd\dd_left.pcd");
                            var pclOutput = pcdEvaluate.convertExtern();
                            evaluateHands(pclOutput.ToArray());
                        }
                    }
                }
            }
        }
        // Note: In order to see the full range of depth (including the less reliable far field depth) we are setting maxDepth (ushort.MaxValue) to the extreme potential depth threshold
        // If you wish to filter by reliable depth distance, use:  depthFrame.DepthMaxReliableDistance
        private unsafe void ProcessDepthFrameData(IntPtr depthFrameData, int frameSize, ushort minDepth, ushort maxDepth, DepthSpacePoint p, bool left)
        {
            string file = "";
            //FileCode: [left/right]_[gestureNumber]_[sequence]_[sequneceIndex]
            if (left)
                file = @"c:/CNTK/models/pcd/dd_left.pcd";
            else
                file = @"c:/CNTK/models/pcd/dd_right.pcd";

            StreamWriter depthData = new StreamWriter(file, false);

            ushort* frameData = (ushort*)depthFrameData; // depth frame data is a 16 bit value
            ushort initDepth = frameData[depthFrameDescription.Width * ((int)p.Y) + ((int)p.X)];
            byte initPos = (byte)(initDepth / MapDepthToByte);

            int factor = 80;
            int index = 0;
            int pixelOffset = 5;
            for (int y = -frameSize; y < frameSize; y++)
            {
                for (int x = -frameSize; x < frameSize; x++)
                {                    
                    //Select index for smaller frame and get Depth value
                    int offset = (depthFrameDescription.Width * ((int)p.Y + y) + ((int)p.X + x));
                    ushort depth = frameData[offset];

                    // if this depth is near to the initpoint (handpalm) ...  
                    if (depth < initDepth + factor && depth > initDepth - factor)
                    {
                        //... record to PointCloud ...
                        if ((x % pixelOffset == 0))
                        {
                            var point = Helper.depthToPCD(frameSize, (int)p.X + x, (int)p.Y + y, depth);
                            depthData.WriteLine(String.Format("{0:0.00000} {1:0.00000} {2}",
                                point.X.ToString().Replace(',', '.'), point.Y.ToString().Replace(',', '.'), point.Z.ToString().Replace(',', '.')));
                        }

                        //...and adapt depth for visualization in UI
                        depth += (ushort)((depth - initDepth) * 10);
                    }
                    else
                        depth = 0;

                    this.depthPixels[index++] = (byte)(depth / MapDepthToByte);
                }
            }
            depthData.Flush();
            depthData.Close();
        }
        //*******************

        private double[] calculateData(IReadOnlyDictionary<JointType, Joint> joints, IReadOnlyDictionary<JointType,JointOrientation> orientations)
        {
            List<double> allData = new List<double>();

            allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.ElbowLeft));
            allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.ElbowRight));

            allData.Add(calculateDistances(joints, (int)JointType.ElbowRight, (int)JointType.HandLeft));
            allData.Add(calculateDistances(joints, (int)JointType.ElbowLeft, (int)JointType.HandRight));

            allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandLeft));
            allData.Add(calculateDistances(joints, (int)JointType.Head, (int)JointType.HandRight));

            allData.Add(calculateDistances(joints, (int)JointType.ElbowLeft, (int)JointType.ElbowRight));
            allData.Add(calculateDistances(joints, (int)JointType.HandRight, (int)JointType.HandLeft));
         
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

        List<JointType> jointTypes = new List<JointType>() { JointType.Head, JointType.SpineMid, JointType.ShoulderLeft, JointType.ElbowLeft, JointType.WristLeft, JointType.ShoulderRight, JointType.ElbowRight, JointType.WristRight, JointType.HandLeft, JointType.HandRight };
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
         
            ColorSpacePoint cSPoint0, cSPoint1, cSPoint2, cSPoint3, cSPoint4;
            Point p0, p1, p2, p3, p4;

            cSPoint0 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.HandLeft]);
            cSPoint1 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.ElbowLeft]);
            cSPoint2 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.Head]);
            cSPoint3 = this.coordinateMapper.MapCameraPointToColorSpace(jointPoints[JointType.HandRight]);
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
    
        //    var entry = String.Format("{0:000}{1:000}\t|L {2}\t|F", gestureNumber, sequenceId + addId, Helper.gestureCode[gestureNumber]);
        //    for (int i = 0; i < allData.Length; ) entry += String.Format(" {0:0.000000}", allData[i++]);
        private void evaluateDistances(double[] allData)
        {
            using (var model = new IEvaluateModelManagedD())
            {
                // Load model
                string modelFilePath = @"C:\CNTK\models\sw.dnn";
                if (!File.Exists(modelFilePath))
                {
                    MessageBox.Show("Model-Datei nicht gefunden!");
                    return;
                }

                model.CreateNetwork(string.Format("modelPath=\"{0}\"", modelFilePath), deviceId: -1);


            }
        }

        private void evaluateHands(double[] pclOutput)
        {
            using (var model = new IEvaluateModelManagedD())
            {
                // Load model
                string modelFilePath = @"C:\CNTK\models\rnn.dnn";
                if (!File.Exists(modelFilePath))
                {
                    MessageBox.Show("Model-Datei nicht gefunden!");
                    return;
                }

                model.CreateNetwork(string.Format("modelPath=\"{0}\"", modelFilePath), deviceId: -1);
                //model.Init(@"C:\CNTK\nets\RNN_hands\RNN.cntk");

                //StreamReader testDataFile = new StreamReader(@"C:\CNTK\nets\RNN_hands\Data\cntkDataTest.ctd");
                //while (!testDataFile.EndOfStream)
                //{
                //    var line = testDataFile.ReadLine();
                //    var sets = line.Split('|');
                //    var labels = sets[1].Trim().Split(' ').Skip(1);
                //    var features = sets[2].Trim().Split(' ').Skip(1);

                //    // Retrieve the 1-hot vector with the label index
                //    var expected = labels.Select(double.Parse).Select((v, index) => new { Value = v, Index = index })
                //        .Aggregate((a, b) => (a.Value > b.Value) ? a : b)
                //        .Index;

                //    // Retrieve the features
                //    var featureSet = features.Where(i => !string.IsNullOrWhiteSpace(i)).Select(double.Parse).ToList(); ;
                //    // Collect Input
                //    var inDims = model.GetNodeDimensions(NodeGroup.Input).First();

                //    var inputs = new Dictionary<string, List<double>>() { { inDims.Key, featureSet } };

                //    var outDims = model.GetNodeDimensions(NodeGroup.Output).First();

                //    List<double> outputs = model.Evaluate(inputs, outDims.Key);
                //    var hit = EvaluateRecord(labels, outputs);
                //    //OutputResults(outDims.Key, outputs);
                //    OutputResult(sets[1].Split('L')[1].Trim(), hit);
                //}
            }
        }


        private static void OutputResult(string expected, bool hit)
        {
            Console.WriteLine(expected + " --> " + hit);
        }

        private static void OutputResults(string layer, List<double> values)
        {
            if (values == null)
            {
                Console.WriteLine("No Output for layer: {0}", layer);
                return;
            }

            Console.WriteLine("Output layer: {0}", layer);
            foreach (var entry in values)
            {
                Console.WriteLine(entry);
            }
        }

        /// <summary>
        /// Evaluates a test record
        /// </summary>
        /// <param name="record">A tab-delimited string containing as the first entry the expected outcome, values after that are the input data</param>
        /// <returns>true if the record's expected outcome value matches the computed value</returns>
        private bool EvaluateRecord(IEnumerable<string> labels, List<double> outputs)
        {
            // The first value in the line is the expected label index for the record's outcome
            var expected = labels.Select(double.Parse).Select((v, index) => new { Value = v, Index = index })
                            .Aggregate((a, b) => (a.Value > b.Value) ? a : b)
                            .Index;

            // Retrieve the outcome index (so we can compare it with the expected index)
            int idx = 0;
            var max = outputs.Select(v => new { Value = v, Index = idx++ })
                .Aggregate((a, b) => (a.Value > b.Value) ? a : b)
                .Index;

            return (expected == max);
        }

        private bool started = false;
        private void start_Click(object sender, RoutedEventArgs e)
        {
            started = true;
        }
    }
}
