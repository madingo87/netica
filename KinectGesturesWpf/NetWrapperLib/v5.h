/*********************************************************
  c:\temp\v5.h
  --------------------------------------------------------
  generated at Wed Mar 23 12:43:21 2016
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classify5(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classify5REC = {12,5,classify5};
