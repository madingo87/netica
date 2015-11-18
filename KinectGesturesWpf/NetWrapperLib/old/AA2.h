/*********************************************************
  c:\temp\AA2.h
  --------------------------------------------------------
  generated at Mon Oct 12 16:43:13 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classifyAngleAdvanced2(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classifyAngleAdvanced2REC = {14,7,classifyAngleAdvanced2};
