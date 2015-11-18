/*********************************************************
  c:\temp\position.c
  --------------------------------------------------------
  generated at Tue Oct 20 14:55:31 2015
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
  static UnitType Units[20];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, 
Units + 1, Units + 2, Units + 3, 
Units + 1, Units + 2, Units + 3, 
Units + 1, Units + 2, Units + 3, 
Units + 1, Units + 2, Units + 3, 
Units + 1, Units + 2, Units + 3, 
Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, 
Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, 
Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, 
Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, 
Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, 
Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, 
Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, 
Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, 
Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, 
Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-2.595400, -2.669470, -0.963060, 
2.961880, -1.602170, 1.101840, 
2.976510, -1.826620, 0.785440, 
-0.132300, 6.483370, 0.121870, 
-2.552420, -2.652750, -1.008610, 
-2.410830, 5.919800, 1.081650, 
1.599630, 1.373790, 1.616220, -0.402560, 1.609960, -4.148680, 
0.471890, 0.839780, 0.520890, -5.193120, 0.433040, 6.602370, 
-1.956600, 3.174090, 3.008230, -1.603030, -1.927890, 0.726900, 
3.727640, -1.618460, -1.286660, -1.701250, 3.720550, -1.736200, 
1.419000, -3.088470, -3.033970, 1.663170, 1.379220, 1.862780, 
-1.738600, -0.625760, -0.730520, 4.326560, -1.725790, 0.560570, 
-6.945490, 5.126040, -1.081800, -4.076480, 3.035050, 0.863230, 
2.093490, -6.160250, 3.928140, -5.935770, -5.229150, 3.027680, 
0.083770, 4.520740, 1.453350, 3.650040, -3.517750, -7.456270, 
2.092270, -6.424930, -7.045210, 4.924320, 3.769670, 0.265690, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[20] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, 0.340500, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, 0.286660, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.887940, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 2.467050, 3,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -2.529960, 3,
       &Sources[3] , 
       &Weights[3] , 
      },
    { /* unit 6 (noName) */
      0.0, -2.150700, 3,
       &Sources[6] , 
       &Weights[6] , 
      },
    { /* unit 7 (noName) */
      0.0, 1.535710, 3,
       &Sources[9] , 
       &Weights[9] , 
      },
    { /* unit 8 (noName) */
      0.0, 2.500870, 3,
       &Sources[12] , 
       &Weights[12] , 
      },
    { /* unit 9 (noName) */
      0.0, -2.880480, 3,
       &Sources[15] , 
       &Weights[15] , 
      },
    { /* unit 10 (noName) */
      0.0, 0.179750, 6,
       &Sources[18] , 
       &Weights[18] , 
      },
    { /* unit 11 (noName) */
      0.0, 0.853530, 6,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 12 (noName) */
      0.0, -0.047990, 6,
       &Sources[30] , 
       &Weights[30] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.125890, 6,
       &Sources[36] , 
       &Weights[36] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.352420, 6,
       &Sources[42] , 
       &Weights[42] , 
      },
    { /* unit 15 (noName) */
      0.0, 0.573600, 6,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, -0.544590, 6,
       &Sources[54] , 
       &Weights[54] , 
      },
    { /* unit 17 (noName) */
      0.0, -0.750840, 6,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 18 (noName) */
      0.0, -1.460180, 6,
       &Sources[66] , 
       &Weights[66] , 
      },
    { /* unit 19 (noName) */
      0.0, -2.172920, 6,
       &Sources[72] , 
       &Weights[72] , 
      }

  };



int classifyPosition(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[3] = {Units + 1, Units + 2, Units + 3}; /* members */

  static pUnit Hidden1[6] = {Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9}; /* members */

  static pUnit Hidden2[6] = {Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15}; /* members */

  static pUnit Output1[4] = {Units + 16, Units + 17, Units + 18, Units + 19}; /* members */

  static int Output[4] = {16, 17, 18, 19};

  for(member = 0; member < 3; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 6; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 6; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 4; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for(member = 0; member < 4; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
