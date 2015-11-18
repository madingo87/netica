/*********************************************************
  c:\temp\v51.h
  --------------------------------------------------------
  generated at Wed Nov 18 17:25:59 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classify51(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classify51REC = {8,4,classify51};
