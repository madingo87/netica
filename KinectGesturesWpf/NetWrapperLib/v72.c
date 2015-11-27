/*********************************************************
  c:\temp\v72.c
  --------------------------------------------------------
  generated at Fri Nov 27 15:09:05 2015
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
  static UnitType Units[24];
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

  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.335940, -0.005190, 0.007570, -0.574080, 0.184630, 0.711580, 0.136470, -0.374050, 
0.090190, -0.528780, -0.546490, 0.725670, -0.548380, 1.070150, -0.283110, 0.104140, 
-0.091340, 0.299130, -0.628500, -0.997850, -0.292490, -0.062890, -0.910060, 1.083280, 
-0.413410, 1.188810, -0.116580, -0.499910, -0.695210, -0.784160, 1.073880, -0.445910, 
-0.583100, -0.796200, -0.575110, 0.050480, 0.260690, -0.624950, 0.266140, 0.731520, 
-0.114420, -0.411520, 0.348490, -0.393630, 0.156530, -0.476790, -0.214980, 0.909170, 
0.001250, -0.456420, 0.618360, -1.962600, 0.862270, -1.021390, 
0.519540, 0.022300, -0.074770, 0.000190, -0.378460, -0.865350, 
-0.448780, 0.309680, -0.823490, 1.120350, -0.544900, 1.065640, 
0.090240, 0.503660, -1.139200, 2.584300, 0.052870, 0.230570, 
-0.696600, -0.116170, 0.055580, 0.167930, 0.339190, 0.823370, 
-1.023490, 1.404730, -0.294160, 3.290370, -3.192630, -1.422080, 
0.507810, 1.832340, -0.768930, -0.109210, -2.037190, 0.620220, 
-2.510560, -0.018790, 1.892350, 3.081450, 0.581410, 3.407970, 
1.246830, -0.582160, -0.633890, -1.320300, 0.565250, -5.163410, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[24] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -0.492600, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -0.726920, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, 0.710380, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, -0.867670, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.144380, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.146700, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -0.395430, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 0.096100, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 0.366340, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, 0.482190, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, 0.321210, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, -0.496290, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.504910, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.036780, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, 0.606220, 6,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, -0.215880, 6,
       &Sources[54] , 
       &Weights[54] , 
      },
    { /* unit 17 (noName) */
      0.0, -0.936280, 6,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 18 (noName) */
      0.0, -0.664580, 6,
       &Sources[66] , 
       &Weights[66] , 
      },
    { /* unit 19 (noName) */
      0.0, 0.427190, 6,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 20 (noName) */
      0.0, 0.848980, 6,
       &Sources[78] , 
       &Weights[78] , 
      },
    { /* unit 21 (noName) */
      0.0, -1.057040, 6,
       &Sources[84] , 
       &Weights[84] , 
      },
    { /* unit 22 (noName) */
      0.0, -0.844200, 6,
       &Sources[90] , 
       &Weights[90] , 
      },
    { /* unit 23 (noName) */
      0.0, -0.715980, 6,
       &Sources[96] , 
       &Weights[96] , 
      }

  };



int classify72(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[8] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8}; /* members */

  static pUnit Hidden1[6] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14}; /* members */

  static pUnit Hidden2[6] = {Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20}; /* members */

  static pUnit Output1[3] = {Units + 21, Units + 22, Units + 23}; /* members */

  static int Output[3] = {21, 22, 23};

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
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 6; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 3; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for(member = 0; member < 3; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
