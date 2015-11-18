/*********************************************************
  c:\temp\HandPosition3D
  --------------------------------------------------------
  generated at Wed Jul 08 15:55:19 2015
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

#include <math.h>

#define Act_Logistic(sum, bias)  ( (sum+bias<10000.0) ? ( 1.0/(1.0 + exp(-sum-bias) ) ) : 0.0 )
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
  static UnitType Units[27];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, 
Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 

Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 

Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 

Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 

Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 

Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 

Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.962190, -2.061110, 4.387310, 1.241200, -1.718950, 3.901610, 
-1.501570, -5.893180, -2.432960, -0.235660, -8.983370, -2.489900, 
1.288210, -5.210450, -1.063450, -0.882070, -7.108060, 0.166670, 
-2.261790, -4.866170, -1.906890, 0.975940, -4.699080, -1.541230, 
1.825270, 3.325720, -1.245150, -1.130980, 2.367350, -1.167670, 
-0.262080, 0.168620, 0.847570, 0.399270, 1.499620, -0.240530, 
0.423240, -1.883260, -3.740000, 0.091350, -3.152800, -2.795210, 
-5.085710, -3.635530, -0.296980, 1.518560, -2.367370, -1.518710, 
5.174980, 0.085370, -0.255920, -0.750210, -3.568870, 1.081730, 
-5.383550, -1.383010, -1.445640, 2.213320, -1.303180, -0.969540, 
-7.123660, -2.867450, -3.672800, 3.822960, 1.276030, -0.464160, 1.994720, 2.550960, -4.270380, 2.557650, 

1.481560, -4.603730, -1.056800, -5.907950, 1.918150, 3.150750, -1.903060, -2.536200, 2.252740, -2.493050, 

4.374060, -8.815460, -5.760280, 0.622600, -3.372310, 0.861950, -7.414820, 3.549500, -4.294070, 3.208770, 

0.969610, -0.276300, 1.263490, -0.073350, 0.324320, 0.434280, 0.152870, -0.160810, -0.119840, -0.380450, 

-5.025110, -1.253360, -2.205450, -2.398240, 4.534790, 2.450420, 2.364160, -1.799070, 0.281920, -0.391810, 

2.232400, 3.587280, 3.652200, 0.531540, -1.987160, -1.836790, -0.906220, -0.688460, 1.016630, -1.683670, 

-7.695990, -4.902620, -10.442830, 1.018960, -4.159420, 5.550130, 
3.008530, -6.654440, 11.540280, -1.658020, -6.581350, -3.017750, 
-6.601880, 9.145510, -1.670620, -0.566720, 2.253610, -4.169890, 
7.532630, -3.253780, -7.070410, -1.746220, 3.952410, -4.169700, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[27] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -0.153720, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -0.436020, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.354960, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.717700, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.503040, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.334270, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -7.535270, 6,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 1.241340, 6,
       &Sources[6] , 
       &Weights[6] , 
      },
    { /* unit 9 (noName) */
      0.0, -1.257180, 6,
       &Sources[12] , 
       &Weights[12] , 
      },
    { /* unit 10 (noName) */
      0.0, 3.923440, 6,
       &Sources[18] , 
       &Weights[18] , 
      },
    { /* unit 11 (noName) */
      0.0, 3.081500, 6,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 12 (noName) */
      0.0, 0.730880, 6,
       &Sources[30] , 
       &Weights[30] , 
      },
    { /* unit 13 (noName) */
      0.0, 5.183680, 6,
       &Sources[36] , 
       &Weights[36] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.836360, 6,
       &Sources[42] , 
       &Weights[42] , 
      },
    { /* unit 15 (noName) */
      0.0, -1.258110, 6,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, 1.393450, 6,
       &Sources[54] , 
       &Weights[54] , 
      },
    { /* unit 17 (noName) */
      0.0, -0.113140, 10,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 18 (noName) */
      0.0, 0.892100, 10,
       &Sources[70] , 
       &Weights[70] , 
      },
    { /* unit 19 (noName) */
      0.0, -1.678720, 10,
       &Sources[80] , 
       &Weights[80] , 
      },
    { /* unit 20 (noName) */
      0.0, 0.671600, 10,
       &Sources[90] , 
       &Weights[90] , 
      },
    { /* unit 21 (noName) */
      0.0, 2.389980, 10,
       &Sources[100] , 
       &Weights[100] , 
      },
    { /* unit 22 (noName) */
      0.0, -0.985670, 10,
       &Sources[110] , 
       &Weights[110] , 
      },
    { /* unit 23 (noName) */
      0.0, 3.063650, 6,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 24 (noName) */
      0.0, -3.398300, 6,
       &Sources[126] , 
       &Weights[126] , 
      },
    { /* unit 25 (noName) */
      0.0, -2.241250, 6,
       &Sources[132] , 
       &Weights[132] , 
      },
    { /* unit 26 (noName) */
      0.0, -2.617400, 6,
       &Sources[138] , 
       &Weights[138] , 
      }

  };



int classifyHandPosition(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[6] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6}; /* members */

  static pUnit Hidden1[10] = {Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16}; /* members */

  static pUnit Hidden2[6] = {Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22}; /* members */

  static pUnit Output1[4] = {Units + 23, Units + 24, Units + 25, Units + 26}; /* members */

  static int Output[4] = {23, 24, 25, 26};

  for(member = 0; member < 6; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 10; member++) {
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
