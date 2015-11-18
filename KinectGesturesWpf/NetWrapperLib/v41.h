/*********************************************************
  c:\temp\v41.h
  --------------------------------------------------------
  generated at Mon Nov 02 20:38:18 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int classify41(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} classify41REC = {8,4,classify41};
