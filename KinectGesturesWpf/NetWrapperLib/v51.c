/*********************************************************
  c:\temp\v51.c
  --------------------------------------------------------
  generated at Wed Nov 18 17:25:59 2015
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
  static UnitType Units[25];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.001110, 3.492250, -3.926980, 1.405250, -1.216140, 1.172340, -2.127720, 0.686720, 
-0.386720, -0.526190, -0.016540, -4.668540, 0.795830, -0.932020, 1.306420, -0.961350, 
-3.465310, 2.077570, 2.031730, -1.555280, -2.249330, 3.294220, 0.897170, -2.801410, 
-1.090900, -0.555570, -0.898630, 0.625150, 0.462570, -1.467600, -2.551350, -0.760970, 
0.303310, -0.483440, -2.097070, 1.062710, 0.553900, 0.356490, -0.515610, 0.127390, 
2.482320, -0.043180, -0.853360, -0.926900, 1.213480, -0.164950, -0.937680, -0.457080, 
3.480380, 0.004790, -1.040780, -0.607740, 0.499340, 4.994350, 
3.139940, -2.725010, 3.875430, -0.160990, -0.953390, -5.626130, 
3.003570, -0.514460, -2.097910, 1.133830, 11.665270, -2.060880, 
-3.286900, 1.817730, 2.404700, 0.111580, -1.402030, -2.657710, 
-3.648890, -0.745710, -4.958580, 0.573440, 0.221560, -0.634700, 
1.339810, 1.687800, -0.089690, 0.170890, -0.308270, 10.566650, 
3.290050, -6.873620, -15.381540, -6.109360, 2.660140, 6.411730, 
-6.014940, -8.140620, 15.615630, 5.369150, 2.658370, -4.365400, 
0.621410, 7.962300, -1.610430, -6.614950, 6.272670, -9.799550, 
-0.643680, 3.242740, 1.062340, 2.990150, -10.571680, 3.017330, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[25] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, 0.742790, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -0.141450, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.972170, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.113680, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.355450, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, -0.021210, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -0.680410, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, -0.105620, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 13.989700, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, 0.693320, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, 14.617740, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, 21.973619, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, 176.799347, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.988170, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, -1.094230, 6,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, 1.145800, 6,
       &Sources[54] , 
       &Weights[54] , 
      },
    { /* unit 17 (noName) */
      0.0, 4.079520, 6,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 18 (noName) */
      0.0, 4.493450, 6,
       &Sources[66] , 
       &Weights[66] , 
      },
    { /* unit 19 (noName) */
      0.0, -2.281050, 6,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 20 (noName) */
      0.0, 0.368820, 6,
       &Sources[78] , 
       &Weights[78] , 
      },
    { /* unit 21 (noName) */
      0.0, -3.411860, 6,
       &Sources[84] , 
       &Weights[84] , 
      },
    { /* unit 22 (noName) */
      0.0, -0.970820, 6,
       &Sources[90] , 
       &Weights[90] , 
      },
    { /* unit 23 (noName) */
      0.0, -4.618860, 6,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 24 (noName) */
      0.0, -0.155380, 6,
       &Sources[102] , 
       &Weights[102] , 
      }

  };



int classify51(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[8] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8}; /* members */

  static pUnit Hidden1[6] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14}; /* members */

  static pUnit Hidden2[6] = {Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20}; /* members */

  static pUnit Output1[4] = {Units + 21, Units + 22, Units + 23, Units + 24}; /* members */

  static int Output[4] = {21, 22, 23, 24};

  for(member = 0; member < 8; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 6; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Identity(sum, unit->Bias);
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
