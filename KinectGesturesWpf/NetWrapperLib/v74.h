/*********************************************************
  c:\temp\v74.h
  --------------------------------------------------------
  generated at Fri Nov 27 17:01:09 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classify74(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classify74REC = {8,4,classify74};
