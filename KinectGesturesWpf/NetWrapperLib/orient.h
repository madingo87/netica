/*********************************************************
  c:\temp\orient.h
  --------------------------------------------------------
  generated at Sat Apr 09 15:09:31 2016
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifyOrientation(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifyOrientationREC = {12,15,classifyOrientation};
