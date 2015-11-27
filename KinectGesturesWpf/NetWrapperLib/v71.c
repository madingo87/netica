/*********************************************************
  c:\temp\v71.c
  --------------------------------------------------------
  generated at Fri Nov 27 14:54:37 2015
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
  static UnitType Units[21];
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
Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 15, Units + 16, Units + 17, Units + 18, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.100020, 0.239180, 0.102700, 0.253170, 0.107410, 0.083990, 0.144340, -0.451930, 
-0.073420, -0.622090, -0.059750, 0.024460, -0.051520, 0.995600, -0.288580, 0.143360, 
0.066010, -0.177260, -0.082630, -0.189190, -0.099060, -0.029680, -0.082460, -0.202650, 
0.665420, -0.200960, 0.374920, -0.111420, 0.400680, 0.526770, -0.085320, 0.417920, 
0.006810, 0.083010, -0.004210, -0.105400, -0.000310, 0.183710, -0.121180, 0.183090, 
0.444020, 0.815820, -0.208610, -0.453590, -0.452510, -1.054690, 0.393110, 0.199110, 
0.120610, -1.622310, 0.191750, -2.325530, 0.131490, 1.151470, 
-0.715140, 2.125680, 0.442190, 2.324800, 0.473590, -0.388140, 
-0.126390, -0.801850, -0.119830, -0.926850, 0.005680, -0.069530, 
-0.432570, 1.107440, -0.086240, 1.202930, 0.068000, -0.040860, 
-2.056320, 3.051520, -0.776960, 1.377050, 
2.221020, -2.839890, 0.868550, -1.401200, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[21] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -0.922850, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -0.495830, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.621450, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, -0.504620, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.692980, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.240640, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, 0.770740, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 0.878170, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 0.169350, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, 0.140010, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, -0.088890, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, -0.682200, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, 0.016160, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, -0.139760, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, 0.800860, 6,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, 0.147340, 6,
       &Sources[54] , 
       &Weights[54] , 
      },
    { /* unit 17 (noName) */
      0.0, -0.059510, 6,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 18 (noName) */
      0.0, 0.147000, 6,
       &Sources[66] , 
       &Weights[66] , 
      },
    { /* unit 19 (noName) */
      0.0, -0.185000, 4,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 20 (noName) */
      0.0, 0.171280, 4,
       &Sources[76] , 
       &Weights[76] , 
      }

  };



int classify71(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[8] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8}; /* members */

  static pUnit Hidden1[6] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14}; /* members */

  static pUnit Hidden2[4] = {Units + 15, Units + 16, Units + 17, Units + 18}; /* members */

  static pUnit Output1[2] = {Units + 19, Units + 20}; /* members */

  static int Output[2] = {19, 20};

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

  for (member = 0; member < 4; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 2; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for(member = 0; member < 2; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
