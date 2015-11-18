/*********************************************************
  c:\temp\AngleAdvanced.h
  --------------------------------------------------------
  generated at Fri Oct 09 17:18:33 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifyAngleAdvanced(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifyAngleAdvancedREC = {14,7,classifyAngleAdvanced};
