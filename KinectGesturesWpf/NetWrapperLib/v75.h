/*********************************************************
  c:\temp\v75.h
  --------------------------------------------------------
  generated at Fri Nov 27 17:21:39 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classify75(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classify75REC = {8,6,classify75};
