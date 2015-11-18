/*********************************************************
  c:\temp\position.h
  --------------------------------------------------------
  generated at Tue Oct 20 14:55:31 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifyPosition(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifyPositionREC = {3,4,classifyPosition};
