/*********************************************************
  c:\temp\v41.c
  --------------------------------------------------------
  generated at Mon Nov 02 20:38:18 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

#include <math.h>

#define Act_TanH(sum, bias)         ( tanh(sum + bias) )
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
  static UnitType Units[33];
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
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 

Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 


  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.231120, -0.484100, -0.025310, -0.142890, 0.149120, -0.669530, 0.043780, -0.357680, 
1.158340, -0.901890, 0.013640, -0.060550, 0.953970, -1.601810, -0.079560, 0.473930, 
-0.175370, 0.490130, 0.457350, -0.237680, -0.285780, -0.034320, 0.754900, 0.015040, 
0.486800, 0.663950, -0.916380, -0.161040, 0.556250, -0.162130, -1.371190, 0.054820, 
0.110530, -0.263370, -0.124660, -0.511810, -0.665450, -0.664870, -0.196810, -0.379480, 
0.506870, 0.254090, 0.236620, 0.605090, -0.230080, 0.854860, -0.035670, 0.492770, 
-0.904770, -0.696910, 0.330700, 0.029500, -0.277190, -0.529590, 0.489830, -0.173620, 
-0.581820, -1.166610, -0.061580, 0.783640, -0.588750, -0.067470, 0.001290, 0.368040, 
0.449320, -0.375090, 0.261670, 1.090830, -0.153060, -0.394510, 0.342670, 0.613890, 
0.039880, 0.718130, 0.269440, -0.271460, 0.843920, 0.759750, 0.579260, -0.165450, 
0.363380, 0.973270, 0.075150, 1.221260, -0.268150, -0.483160, -0.947020, 0.882110, -0.047610, 1.003830, 

-0.245240, 0.273300, 0.118840, 0.375190, 0.029760, -0.138120, -0.185760, -1.229280, -0.347740, 0.371520, 

0.340810, 0.585640, 0.048560, 0.849320, -0.205540, -0.284650, -0.726120, 0.677770, 0.068880, 0.698800, 

0.338620, 0.448180, -0.591550, -0.226050, 0.241090, -0.315930, 0.927490, 0.216210, 0.530130, -1.000300, 

-0.104230, 0.734730, -0.367310, -0.129360, -0.182480, 0.331550, 0.419880, 0.309800, 0.845770, 0.039630, 

-0.442190, -0.064320, 0.530090, 0.345200, -0.026170, 0.005540, -0.235650, -0.957030, -0.522690, 0.361660, 

-0.327980, -1.330610, 0.387180, -1.055040, -0.324610, 0.757280, -0.400980, 0.388020, 0.036060, -0.244760, 

-0.044340, -0.328510, -0.877300, 0.785050, -0.139950, 0.270260, -0.244840, 0.836370, 0.111570, -0.118330, 

1.323990, 0.596340, -0.126970, 0.280240, 0.762660, -1.417880, 0.926240, -0.664960, -0.349100, -0.547560, 

0.122240, -0.391860, 0.149700, 0.037970, 0.089570, -0.120790, -0.303810, -0.036030, -0.619200, 0.055430, 

-0.513120, 1.752530, -0.905680, -1.279800, -0.172890, 1.878900, -1.575990, -0.410730, 0.892480, -0.278470, 

1.230800, -0.058350, 0.656430, 1.763150, 1.653440, -1.339560, -1.318520, 1.840730, 0.079870, -1.045290, 

0.813600, -0.535520, 0.258140, -1.066250, 0.431600, 0.099970, 1.530390, 0.692440, -2.889880, -0.354290, 

-2.491160, 0.594500, -1.901780, 0.630400, -0.253050, -0.105000, 0.699070, -0.344960, 0.543690, 0.080010, 


  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[33] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -0.399520, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, 0.999760, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.569810, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.523060, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, 0.285990, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.289770, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, 0.149510, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 0.710200, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 0.031310, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, -0.961730, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, 0.862660, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, -0.291580, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.274560, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.168000, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, -0.918850, 8,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, 0.882470, 8,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 17 (noName) */
      0.0, 0.180880, 8,
       &Sources[64] , 
       &Weights[64] , 
      },
    { /* unit 18 (noName) */
      0.0, 0.671210, 8,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 19 (noName) */
      0.0, 0.502580, 10,
       &Sources[80] , 
       &Weights[80] , 
      },
    { /* unit 20 (noName) */
      0.0, -0.522520, 10,
       &Sources[90] , 
       &Weights[90] , 
      },
    { /* unit 21 (noName) */
      0.0, 0.304560, 10,
       &Sources[100] , 
       &Weights[100] , 
      },
    { /* unit 22 (noName) */
      0.0, 0.337620, 10,
       &Sources[110] , 
       &Weights[110] , 
      },
    { /* unit 23 (noName) */
      0.0, -0.161920, 10,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 24 (noName) */
      0.0, -0.158310, 10,
       &Sources[130] , 
       &Weights[130] , 
      },
    { /* unit 25 (noName) */
      0.0, -0.017490, 10,
       &Sources[140] , 
       &Weights[140] , 
      },
    { /* unit 26 (noName) */
      0.0, -0.568690, 10,
       &Sources[150] , 
       &Weights[150] , 
      },
    { /* unit 27 (noName) */
      0.0, 0.239670, 10,
       &Sources[160] , 
       &Weights[160] , 
      },
    { /* unit 28 (noName) */
      0.0, 0.396630, 10,
       &Sources[170] , 
       &Weights[170] , 
      },
    { /* unit 29 (noName) */
      0.0, -1.009830, 10,
       &Sources[180] , 
       &Weights[180] , 
      },
    { /* unit 30 (noName) */
      0.0, -0.931580, 10,
       &Sources[190] , 
       &Weights[190] , 
      },
    { /* unit 31 (noName) */
      0.0, -0.706360, 10,
       &Sources[200] , 
       &Weights[200] , 
      },
    { /* unit 32 (noName) */
      0.0, -0.739440, 10,
       &Sources[210] , 
       &Weights[210] , 
      }

  };



int classify41(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[8] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8}; /* members */

  static pUnit Hidden1[10] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18}; /* members */

  static pUnit Hidden2[10] = {Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28}; /* members */

  static pUnit Output1[4] = {Units + 29, Units + 30, Units + 31, Units + 32}; /* members */

  static int Output[4] = {29, 30, 31, 32};

  for(member = 0; member < 8; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 10; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 10; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 4; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for(member = 0; member < 4; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
