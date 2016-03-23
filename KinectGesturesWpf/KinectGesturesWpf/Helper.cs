using Microsoft.Kinect;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Media3D;

namespace KinectGesturesWpf
{
    static class Helper
    {
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

        public static CameraSpacePoint getEinsvektor(CameraSpacePoint point)
        {
            var e = (float)Math.Sqrt(Math.Pow(point.X, 2) + Math.Pow(point.Y, 2) + Math.Pow(point.Z, 2));
            point.X = point.X / e;
            point.Y = point.Y / e;
            point.Z = point.Z / e; 

            return point;
        }

        /**
         * Only values between 0-1 because einsvectors
         */ 
        public static float getAngle(CameraSpacePoint point, CameraSpacePoint normal)
        {
            var p = getEinsvektor(point);
            var n = getEinsvektor(normal);
            return p.X * n.X + p.Y * n.Y + p.Z * n.Z;
        }

        public static double RadianToDegree(double angle)
        {
            return angle * (180.0 / Math.PI);
        }

    }
}
