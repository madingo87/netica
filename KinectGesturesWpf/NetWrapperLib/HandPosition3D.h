/*********************************************************
  c:\temp\HandPosition3h
  --------------------------------------------------------
  generated at Wed Jul 08 15:55:19 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifyHandPosition(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifyHandPositionREC = { 6, 4, classifyHandPosition };
