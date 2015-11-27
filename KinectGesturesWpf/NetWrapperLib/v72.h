/*********************************************************
  c:\temp\v72.h
  --------------------------------------------------------
  generated at Fri Nov 27 15:09:05 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classify72(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classify72REC = {8,3,classify72};
