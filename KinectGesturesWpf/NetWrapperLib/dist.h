/*********************************************************
  c:\temp\dist.h
  --------------------------------------------------------
  generated at Sat Apr 09 14:20:00 2016
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifyDistance(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifyDistanceREC = {8,15,classifyDistance};
