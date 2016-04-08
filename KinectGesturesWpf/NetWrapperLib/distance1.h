/*********************************************************
  c:\temp\distance1.h
  --------------------------------------------------------
  generated at Tue Apr 05 13:34:02 2016
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifyDistance(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifyDistanceREC = { 8, 11, classifyDistance };
