/*********************************************************
  segementationNet.h
  --------------------------------------------------------
  generated at Thu Oct 20 15:51:34 2016
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifyPixel(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifyPixelREC = {24,1,classifyPixel};
