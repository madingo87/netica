/*********************************************************
  c:\temp\SimpleGestures.h
  --------------------------------------------------------
  generated at Tue Oct 13 11:30:34 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifySimpleGestures(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifySimpleGesturesREC = {8,5,classifySimpleGestures};
