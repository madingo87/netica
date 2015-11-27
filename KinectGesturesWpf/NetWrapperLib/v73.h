/*********************************************************
  c:\temp\v73.h
  --------------------------------------------------------
  generated at Fri Nov 27 16:29:04 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classify73(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classify73REC = {4,4,classify73};
