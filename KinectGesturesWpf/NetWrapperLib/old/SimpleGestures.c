/*********************************************************
  c:\temp\SimpleGestures.c
  --------------------------------------------------------
  generated at Tue Oct 13 11:30:34 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

#include <math.h>

#define Act_Logistic(sum, bias)  ( (sum+bias<10000.0) ? ( 1.0/(1.0 + exp(-sum-bias) ) ) : 0.0 )
#define Act_Identity(sum, bias)     ( sum )
#ifndef NULL
#define NULL (void *)0
#endif

typedef struct UT {
          float act;         /* Activation       */
          float Bias;        /* Bias of the Unit */
          int   NoOfSources; /* Number of predecessor units */
   struct UT   **sources; /* predecessor units */
          float *weights; /* weights from predecessor units */
        } UnitType, *pUnit;

  /* Forward Declaration for all unit types */
  static UnitType Units[34];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, 
Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, 
Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, 
Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, 
Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-1.060720, -2.914010, 0.902830, -2.131660, -0.334770, -1.638590, 3.421830, 3.262930, 
0.609170, -2.264350, -1.921860, -1.201940, 1.034640, -1.865690, 0.066140, 3.672920, 
-2.609560, 2.867360, -1.523870, 1.585800, -0.384510, 0.556730, -0.818810, 0.846440, 
1.692930, -0.694120, -0.527730, 1.028640, -2.484470, 1.874730, -5.114510, -0.135400, 
-0.642340, 0.536910, -2.592390, 0.494830, 1.080290, -0.843370, -1.082230, 1.327130, 
-4.011810, 3.778150, -2.765470, 2.340440, -0.455300, -0.085690, 0.420980, 0.907390, 
2.295300, 0.660240, 0.789060, 0.458730, 1.974430, -0.083680, -0.110920, -3.098210, 
2.563990, -1.136990, 2.886390, -0.191550, -0.052430, 0.575360, 0.250700, -2.562990, 
-1.175820, 1.046010, -0.911000, 0.308420, 3.440800, -1.933180, 3.225410, -0.308800, 
-1.017040, -0.379170, 1.083260, -0.237810, -3.023780, 1.553490, -0.842840, 1.174820, 
2.993320, -2.336090, -1.361290, -0.645140, 1.668420, -1.711360, -1.513970, 0.498200, 
-1.391160, 0.452140, 2.795520, 0.023730, -2.839430, 1.958840, 1.096810, -0.363520, 
-4.859660, -7.721950, 1.560440, 4.006460, 1.242050, 3.411690, 1.969470, -4.031620, 
1.254670, 1.723100, -5.995740, -4.217880, -4.738790, 2.360750, 5.006660, -4.603020, 
1.587600, -2.429860, 3.633530, -2.091200, -4.475120, 2.272930, -7.016260, 4.366440, 
2.817240, 1.497060, -3.539500, 4.442120, 2.478490, -5.139490, -6.123460, -2.628860, 
-5.986450, 1.953520, 0.705260, -5.897870, 1.787680, -7.233580, 3.680820, 4.501370, 
-0.507290, 0.731040, 0.211130, 3.888320, 0.347820, -0.527050, -1.482040, -0.800900, -3.518250, 2.090990, 
0.517680, 0.508920, 
-3.456940, -1.792080, 2.529690, 2.584430, 0.755740, 3.008630, 0.226970, -0.940780, -0.935100, 0.689970, 
-1.264560, 0.482100, 
3.335850, 0.194860, -0.228510, -3.316540, -0.817550, 0.326060, -1.320010, -0.303950, 1.815700, 0.452450, 
-1.720700, 1.815430, 
1.010580, -0.283570, -3.021550, 1.190510, -2.008140, -4.561680, 1.210450, 3.501420, -1.846600, 0.426950, 
1.357240, 1.169830, 
-0.607360, -2.287720, -0.797200, -0.900700, -1.698320, -1.096460, 2.246320, 2.853340, 0.740230, -0.355870, 
-0.792500, 1.598710, 
4.099140, 4.462790, -1.315260, -0.509940, 1.385820, -1.516580, -2.584330, -2.066920, 0.433470, 0.170960, 
2.425990, -1.810910, 
-1.391910, 0.746930, 0.388000, -2.398540, 1.500810, 1.244210, 2.284460, -0.395020, 3.651900, -3.507980, 
1.786280, -3.502140, 
0.995860, -1.262410, 1.858370, -2.691280, -0.257690, 3.154620, -1.573470, -1.736870, 1.372220, 0.972440, 
-3.486720, 2.194170, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[34] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -2.668020, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -1.743860, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.171480, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 2.465130, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -1.668600, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 2.892880, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -0.739680, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, -0.593550, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 0.718070, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, 0.610570, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, -0.716180, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, 1.161550, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.145980, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, -0.685260, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, -0.165430, 8,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, -0.224970, 8,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 17 (noName) */
      0.0, -1.362820, 8,
       &Sources[64] , 
       &Weights[64] , 
      },
    { /* unit 18 (noName) */
      0.0, 0.390240, 8,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 19 (noName) */
      0.0, 0.989770, 8,
       &Sources[80] , 
       &Weights[80] , 
      },
    { /* unit 20 (noName) */
      0.0, -0.175810, 8,
       &Sources[88] , 
       &Weights[88] , 
      },
    { /* unit 21 (noName) */
      0.0, -1.462200, 8,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 22 (noName) */
      0.0, -0.940430, 8,
       &Sources[104] , 
       &Weights[104] , 
      },
    { /* unit 23 (noName) */
      0.0, -1.602560, 8,
       &Sources[112] , 
       &Weights[112] , 
      },
    { /* unit 24 (noName) */
      0.0, -0.871670, 8,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 25 (noName) */
      0.0, -1.503650, 8,
       &Sources[128] , 
       &Weights[128] , 
      },
    { /* unit 26 (noName) */
      0.0, 0.191170, 12,
       &Sources[136] , 
       &Weights[136] , 
      },
    { /* unit 27 (noName) */
      0.0, -0.039300, 12,
       &Sources[148] , 
       &Weights[148] , 
      },
    { /* unit 28 (noName) */
      0.0, 0.246850, 12,
       &Sources[160] , 
       &Weights[160] , 
      },
    { /* unit 29 (noName) */
      0.0, 0.520410, 12,
       &Sources[172] , 
       &Weights[172] , 
      },
    { /* unit 30 (noName) */
      0.0, 0.447010, 12,
       &Sources[184] , 
       &Weights[184] , 
      },
    { /* unit 31 (noName) */
      0.0, 0.088700, 12,
       &Sources[196] , 
       &Weights[196] , 
      },
    { /* unit 32 (noName) */
      0.0, -0.219410, 12,
       &Sources[208] , 
       &Weights[208] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.381650, 12,
       &Sources[220] , 
       &Weights[220] , 
      }

  };



int classifySimpleGestures(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[8] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8}; /* members */

  static pUnit Hidden1[12] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20}; /* members */

  static pUnit Output1[5] = {Units + 21, Units + 22, Units + 23, Units + 24, Units + 25}; /* members */

  static pUnit Hidden2[8] = {Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33}; /* members */

  static int Output[5] = {21, 22, 23, 24, 25};

  for(member = 0; member < 8; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 12; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 8; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 5; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for(member = 0; member < 5; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
