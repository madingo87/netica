/*********************************************************
  c:\temp\v71.h
  --------------------------------------------------------
  generated at Fri Nov 27 14:54:37 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classify71(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classify71REC = {8,2,classify71};
