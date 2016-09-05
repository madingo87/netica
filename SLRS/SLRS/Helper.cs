using Microsoft.Kinect;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Media3D;

namespace SLRS
{
    static class Helper
    {
        #region Depricated 
        /*  Depricated */
        public static CameraSpacePoint getNormalVector(CameraSpacePoint p1, CameraSpacePoint p2, CameraSpacePoint p3)
        {
	        var a = new CameraSpacePoint();
            a.X = p1.X - p2.X; 
            a.Y = p1.Y - p2.Y; 
            a.Z = p1.Z - p2.Z;
	        var b = new CameraSpacePoint();
            b.X = p1.X - p3.X;
            b.Y = p1.Y - p3.Y;
            b.Z = p1.Z - p3.Z;

            var n = new CameraSpacePoint();
            n.X = a.Y * b.Z - a.Z * b.Y;
            n.Y = a.X * b.Z - a.Z * b.X;
            n.Z = a.X * b.Y - a.Y * b.X;

            return n;
        }

        /*  Depricated  */
        public static CameraSpacePoint getEinsvektor(CameraSpacePoint point)
        {
            var e = (float)Math.Sqrt(Math.Pow(point.X, 2) + Math.Pow(point.Y, 2) + Math.Pow(point.Z, 2));
            point.X = point.X / e;
            point.Y = point.Y / e;
            point.Z = point.Z / e; 

            return point;
        }

        /*  Depricated */        
        public static float getAngle(CameraSpacePoint point, CameraSpacePoint normal)
        {
            var p = getEinsvektor(point);   //Only values between 0-1 because einsvectors
            var n = getEinsvektor(normal);  //Only values between 0-1 because einsvectors
            return p.X * n.X + p.Y * n.Y + p.Z * n.Z;
        }

        /*  Depricated 
        public static double RadianToDegree(double angle)
        {
            return angle * (180.0 / Math.PI);
        }
        */
        #endregion

        public static void writePCDHeader(StreamWriter sw)
        {
            sw.Write("# .PCD v.7 - Point Cloud Data file format\n" +
                    "VERSION .7  \n" +
                    "FIELDS x y z  \n" +
                    "SIZE 1 1 1  \n" +
                    "TYPE F F F  \n" +
                    "COUNT 1 1 1  \n" +
                    "WIDTH 100  \n" +
                    "HEIGHT 100  \n" +
                    "VIEWPOINT 0 0 0 1 0 0 0  \n" +
                    "OINTS 10000  \n" +
                    "DATA ascii  \n");
        }

        public static Point3D depthToPCD(int frameSize, float x, float y, int depthVal)
        {
            Point3D point = new Point3D();
            point.Z = (depthVal);	 //    / 1.0f 		//Convert from mm to meters
            point.X = (x - CameraParams.cx) * point.Z / CameraParams.fx;    //(x + frameSize) * depthVal / CameraParams.fx; 
            point.Y = (y - CameraParams.cy) * point.Z / CameraParams.fy;    //(y + frameSize) * depthVal / CameraParams.fy;   

            // finalVertex.x = (x - width/2) *( ((float)(current)) / depthFrame.stereoCameraParameters.depthIntrinsics.fx);
            // finalVertex.y = (y - height/2)*( ((float)(current)) / depthFrame.stereoCameraParameters.depthIntrinsics.fy);
            // finalVertex.z = current;
	
            return point;
        }

    }

    static class CameraParams
    {
        public static float cx = 254.878f;
        public static float cy = 205.395f;
        public static float fx = 365.456f;
        public static float fy = 365.456f;
        public static float k1 = 0.0905474f;
        public static float k2 = -0.26819f;
        public static float k3 = 0.0950862f;
        public static float p1 = 0.0f;
        public static float p2 = 0.0f;

        /* ==== https://github.com/OpenKinect/libfreenect2/issues/41
            depth camera intrinsic parameters:
            fx 365.402802, fy 365.402802, cx 260.925507, cy 205.594604
            depth camera radial distortion coeffs:
            k1 0.095575, k2 -0.277055, p1 0.000000, p2 0.000000, k3 0.097539
         */
    }
}
