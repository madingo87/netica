/*********************************************************
  c:\temp\orient1.h
  --------------------------------------------------------
  generated at Tue Apr 05 16:37:53 2016
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifyOrientation(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifyOrientationREC = { 12, 11, classifyOrientation };
