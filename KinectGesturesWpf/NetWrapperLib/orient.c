/*********************************************************
  c:\temp\orient.c
  --------------------------------------------------------
  generated at Sat Apr 09 15:09:31 2016
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
  static UnitType Units[64];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
0.322420, -0.147210, -0.150850, -0.188760, 0.113020, -0.851820, -0.536020, 0.326490, 0.088270, 0.432260, 
-0.564010, 0.475230, 
0.973780, 0.278900, 0.430220, 0.302830, 0.760260, -0.735640, -0.550120, -0.361100, -0.583650, -0.209310, 
0.140160, 0.746020, 
0.761660, 0.711590, -0.091590, -0.254970, 0.862180, -0.427490, 0.544720, 0.992810, -0.302500, -0.112350, 
0.589520, 0.245590, 
0.630780, -0.678680, -0.351540, 0.211620, 0.119330, -0.653650, 0.424580, -0.926120, 0.198970, 0.223580, 
-0.784870, 0.291690, 
0.055810, 0.847100, 0.376160, 0.797680, -1.289210, 0.178370, -0.594900, 0.691650, 0.302290, -0.415140, 
0.631720, -0.939270, 
0.832830, 0.209840, -0.640250, 0.625550, 0.386330, 0.382840, 0.588040, -0.509740, 1.535290, 0.741270, 
0.384490, -0.108860, 
-0.591800, -0.381960, -0.275480, 0.707780, 0.762430, 1.278980, -0.537760, 0.338570, -0.108120, -0.421000, 
0.543940, -1.251080, 
-0.298110, 0.085790, -0.390800, 1.012580, -0.099510, -0.186840, 0.831780, 0.701060, -0.503280, 0.484310, 
-0.260360, -0.190880, 
0.383330, -0.224300, 0.371600, -0.347000, 0.612890, 0.277450, -0.041090, -0.537010, -0.207900, 0.393330, 
-1.153630, -0.501030, 
0.785390, -0.088440, -0.355930, -0.312510, -0.180310, 0.444410, -0.136440, -0.837390, 1.058820, -0.667800, 
0.088170, -0.429160, 
0.104670, -0.105360, 0.119290, 0.214940, 0.084260, -0.041850, 0.138240, -0.127140, -0.223750, 0.034030, 
0.016330, -0.263450, 
0.172330, -1.216410, 0.526520, 0.237400, -0.300390, 0.816200, 0.186170, 0.046650, -0.159400, 0.400910, 
0.876330, 0.414090, 
-0.770770, -0.708410, -0.045070, -0.205990, 0.107970, -0.814770, -0.156520, -0.340950, 0.587840, 0.848600, 
0.257200, -0.024070, 
0.678660, -0.399950, -0.059780, -0.490330, -1.091300, -0.911670, 0.726940, 0.164530, -0.715750, -0.198600, 
-0.432960, 0.498290, 
0.117590, -0.459380, -0.129970, -0.830560, 0.031310, -0.252370, 0.973610, 0.329940, 0.661930, -0.223010, 
1.213400, -0.261140, 
-0.080020, -0.224030, 0.682810, 0.690550, 0.188660, -0.548960, 0.113820, -0.473930, -0.457840, -0.191440, 
0.949870, -0.231890, 
0.653230, -0.488600, -0.182330, 0.671370, -1.406320, 0.174150, -0.444780, 0.523330, -0.652260, -0.060180, 
0.743870, 0.357540, 
-0.219670, 0.564940, -0.181310, 0.012720, -0.104060, 0.043200, -0.202820, 0.368930, 0.143770, -0.050790, 
0.350460, 0.233330, 
0.343480, 0.705750, 0.234150, 0.511460, -0.551790, -1.042180, -0.469870, -0.235540, 0.609370, -0.200310, 
-0.403160, -0.405350, -0.123880, 0.757540, -0.285800, 0.428020, -0.688720, -0.675890, 
-0.147390, 0.583580, 1.287850, 0.459330, -0.662850, 0.049400, 0.143520, 0.162980, -0.035960, 0.182690, 
-0.438160, 0.194590, -0.591040, 0.439620, 0.140720, -0.543830, 0.026000, 0.497520, 
0.104110, -0.027320, 0.092990, 0.846330, 0.304930, -1.045640, 0.930940, 0.316750, 0.891900, -0.007400, 
-0.438560, -1.020520, 0.392070, 0.195150, -1.907870, 0.396200, 0.412860, -0.133170, 
-0.755520, 0.556640, 0.331090, 0.576410, -0.576120, 0.448200, 0.889390, 0.251200, 0.234190, 1.077150, 
-0.692110, -0.368740, -0.441250, -0.888330, 0.198710, -0.222060, -0.365120, 0.048940, 
0.036180, -1.131730, -0.541330, -0.121680, -0.484760, -0.904820, -0.081980, -0.577140, 0.372970, 1.104970, 
-0.278600, 0.674090, -0.135000, -0.735090, -0.174090, -1.443420, -0.168160, -0.501900, 
-0.049930, 0.045810, 0.441230, 0.099760, 0.425390, 0.904630, -0.701270, 0.892570, -0.668290, 0.227020, 
-0.790150, 0.661660, -0.298760, 0.464690, 0.544930, 0.218040, 0.820010, 0.532560, 
-0.031230, -0.066760, 0.798180, 1.147640, 0.058680, 1.023870, 0.344910, -0.241180, -0.090890, 0.644340, 
0.625450, -0.273920, 0.013090, 0.039290, 0.770520, 0.231360, -0.694910, 0.147370, 
0.195360, 0.384300, -0.641980, -0.156010, -0.241140, 0.508720, 0.039080, 0.136630, -0.312630, 0.170600, 
0.033990, 0.347960, 1.064440, -0.731340, 0.151910, -0.311820, -0.562980, 0.600950, 
-0.866410, 1.124050, 0.449450, 0.814200, -0.047240, -0.226760, 0.515860, 0.190440, 0.281440, -0.358770, 
-0.506040, 1.440060, -0.482500, -0.514260, -0.164220, 0.734750, 0.518270, 0.016200, 
0.075100, 0.153360, 0.008080, 0.087530, -0.944310, 1.595080, 0.329540, 0.161550, -0.058120, 0.112570, 
-0.656500, 0.902860, 0.824140, 0.498100, -0.848690, -0.039210, 0.656210, -0.086260, 
-0.256960, -0.463440, 0.836640, 0.721060, 1.049620, -1.418050, 0.356190, 0.190260, -0.930350, 0.401770, 
-0.367750, -0.055220, 0.122960, 0.497050, -0.459020, -0.334420, 0.345710, 0.373240, 
0.111740, -0.128630, -0.871720, 0.544290, -0.331980, 0.147090, 0.583070, -0.037050, 0.333000, 0.035920, 
0.212900, 0.271740, -0.038720, 0.517220, -0.252990, 0.157870, 0.174470, -0.520320, 
0.092060, -0.511610, 0.510360, -0.184580, -0.306990, -1.090410, -0.871790, -1.667510, -0.237480, 1.101920, 
-0.153420, 0.468750, -0.249610, 0.340630, 0.208910, 0.500460, -0.905560, -1.004030, 
0.132410, -0.429110, -0.332300, 0.853740, -0.160870, 0.469760, -0.281680, 0.088500, -0.189020, 0.397240, 
0.228780, 0.498720, 0.255680, 1.150240, 0.659540, 0.325490, 0.618490, -0.163860, 
0.105700, -0.036500, 0.007010, -0.083920, 0.048340, 0.174330, 0.052110, 0.375830, -0.080070, 0.130100, 
-0.385350, -0.318720, 0.288890, -0.041600, -0.139000, -0.309430, -0.065420, 0.282060, 
0.086350, -0.051210, 0.087980, -0.129510, -0.028570, 0.129710, -0.031360, 0.230240, -0.154440, 0.180560, 
-0.381370, -0.223650, 0.266360, -0.088700, -0.191960, -0.373140, -0.039380, 0.331310, 
0.645540, 0.179220, 0.319980, 0.113220, -1.023130, -0.407190, -1.309590, 0.946310, 0.164410, -0.554300, 
-0.404300, -0.125130, -0.203780, 0.604420, -0.516290, -0.145190, 0.749220, 0.614640, 
0.343350, 0.940220, -0.250290, -0.018160, -0.125480, -1.164410, -0.470140, -0.686040, -1.062050, -0.238280, 
-0.534700, 0.474740, 0.772320, 0.634010, 0.248820, -0.313660, 0.142140, 0.192970, 
0.666490, 2.150970, -0.485560, -0.406760, 0.137730, 0.374000, 0.677290, 0.051270, -0.094630, -1.687530, 
0.071500, -0.719680, -0.209980, 0.105250, 0.800130, 0.787860, 1.490710, 1.372690, 
0.575830, 0.424740, 1.074120, -0.786310, -1.420070, 0.844100, -0.082980, 0.495550, -3.112980, -1.566430, 
-0.070480, -0.475530, -0.315690, 0.791710, 1.069170, 1.118620, -0.718900, -0.455240, 
0.842600, -0.333680, -1.134120, 0.429490, -1.392930, 1.628000, -0.269870, 0.799570, -0.063860, 0.355200, 
0.059900, 0.010630, -2.515340, -0.577260, 0.883800, 0.884670, 1.867920, -0.704510, 
-1.541630, 0.794520, 2.203680, -0.282240, -0.006790, -0.485670, 0.338280, 0.523090, -0.237390, 1.619000, 
-0.018430, -0.454250, -2.328210, -0.183360, 0.952180, 0.801960, -1.230020, 0.058500, 
0.766580, 2.497390, -0.399320, 1.971080, -0.171160, 0.356400, -0.548320, -0.164750, -0.111470, 1.532130, 
0.518030, -0.318560, -0.153230, 0.312510, 0.931160, 0.556610, -0.910260, -0.583110, 
0.162920, 0.680470, -0.531980, -0.184910, 2.265820, -0.085860, 0.468820, 0.150340, -2.338220, 1.117040, 
0.451470, -0.978740, 0.495430, -0.267410, 0.243660, 0.917200, 1.451550, -0.451740, 
-1.486950, 0.283710, -0.025050, -0.326800, 0.255450, 3.540560, 0.076710, 0.117540, -0.522150, 0.887720, 
0.083770, -0.228390, 1.053100, 0.072290, 0.669690, 0.556610, -0.690130, 0.049440, 
1.148020, -0.047990, 2.018750, 2.085750, 0.285780, 0.483540, 0.317180, 0.657130, 0.462760, -0.500390, 
-0.490990, 0.129770, -0.661410, -1.985060, 0.630520, 0.727010, 0.080470, 0.165870, 
0.445280, 0.884710, 2.025100, -0.277260, 1.972690, 0.289770, 0.131420, 0.411450, 0.246890, -0.369310, 
2.526800, -0.631300, 0.491160, 0.768710, 0.476950, 0.971460, -0.205400, -0.380840, 
0.505910, 0.039960, 2.172030, 0.344410, 0.114210, -0.059440, -2.083700, 0.050270, 0.036140, 1.086260, 
-0.000470, -0.369940, 0.286480, -0.391220, 0.569910, 0.646500, 1.205240, 1.529900, 
-0.762800, 0.894330, 0.035510, -0.878220, 1.839120, 0.455210, -1.981880, 0.462290, -0.035750, -0.352660, 
-0.986180, 0.324560, -0.440510, -2.218950, 0.578820, 0.454160, -0.023280, -0.231420, 
-0.733710, 0.287200, -0.702730, 0.362010, -0.595090, 0.070130, 0.678490, 0.362950, -0.337420, -0.156410, 
1.201760, -2.444300, -0.178510, -1.196750, 0.233820, 0.660730, 0.242330, -0.579510, 
-1.368440, -0.299890, -0.701450, 2.385990, 2.031050, 0.056450, 0.888790, 0.674530, 0.014180, -1.133960, 
-0.710010, -0.517660, -0.701690, 1.074840, 0.977770, 0.768380, 0.078220, 0.691020, 
0.521830, -0.234980, -0.371940, -0.011700, 0.006640, 0.037770, 0.401160, 3.171940, -0.266180, 0.787770, 
0.125710, -0.358860, -0.070510, -0.480430, 0.545480, 0.567870, -0.794780, 1.559370, 
-1.007350, 0.190700, -0.469080, -0.103170, -0.543270, 0.616450, -1.667190, 0.322300, -0.424160, -0.597230, 
1.441120, 0.281250, -1.270130, 0.688920, 0.859550, 0.614360, -0.521710, 1.428030, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[64] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, 0.056790, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, 0.234900, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.770200, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, -0.343730, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.854060, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.360820, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, 0.691090, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, -0.302960, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, -0.073820, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, 0.785390, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 11 (noName) */
      0.0, 0.703970, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 12 (noName) */
      0.0, -0.947390, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 13 (noName) */
      0.0, 0.083290, 12,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 14 (noName) */
      0.0, -0.243590, 12,
       &Sources[12] , 
       &Weights[12] , 
      },
    { /* unit 15 (noName) */
      0.0, -0.777940, 12,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 16 (noName) */
      0.0, 0.418570, 12,
       &Sources[36] , 
       &Weights[36] , 
      },
    { /* unit 17 (noName) */
      0.0, 0.565710, 12,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 18 (noName) */
      0.0, -0.514100, 12,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 19 (noName) */
      0.0, 0.916440, 12,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 20 (noName) */
      0.0, -0.975120, 12,
       &Sources[84] , 
       &Weights[84] , 
      },
    { /* unit 21 (noName) */
      0.0, 0.032710, 12,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 22 (noName) */
      0.0, -0.167190, 12,
       &Sources[108] , 
       &Weights[108] , 
      },
    { /* unit 23 (noName) */
      0.0, 0.944210, 12,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 24 (noName) */
      0.0, -0.556850, 12,
       &Sources[132] , 
       &Weights[132] , 
      },
    { /* unit 25 (noName) */
      0.0, -0.659990, 12,
       &Sources[144] , 
       &Weights[144] , 
      },
    { /* unit 26 (noName) */
      0.0, -0.225990, 12,
       &Sources[156] , 
       &Weights[156] , 
      },
    { /* unit 27 (noName) */
      0.0, 0.974720, 12,
       &Sources[168] , 
       &Weights[168] , 
      },
    { /* unit 28 (noName) */
      0.0, 0.273840, 12,
       &Sources[180] , 
       &Weights[180] , 
      },
    { /* unit 29 (noName) */
      0.0, -0.625990, 12,
       &Sources[192] , 
       &Weights[192] , 
      },
    { /* unit 30 (noName) */
      0.0, -0.403140, 12,
       &Sources[204] , 
       &Weights[204] , 
      },
    { /* unit 31 (noName) */
      0.0, -0.467590, 18,
       &Sources[216] , 
       &Weights[216] , 
      },
    { /* unit 32 (noName) */
      0.0, -0.527320, 18,
       &Sources[234] , 
       &Weights[234] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.903990, 18,
       &Sources[252] , 
       &Weights[252] , 
      },
    { /* unit 34 (noName) */
      0.0, -0.490660, 18,
       &Sources[270] , 
       &Weights[270] , 
      },
    { /* unit 35 (noName) */
      0.0, -0.154160, 18,
       &Sources[288] , 
       &Weights[288] , 
      },
    { /* unit 36 (noName) */
      0.0, -0.809960, 18,
       &Sources[306] , 
       &Weights[306] , 
      },
    { /* unit 37 (noName) */
      0.0, 0.362410, 18,
       &Sources[324] , 
       &Weights[324] , 
      },
    { /* unit 38 (noName) */
      0.0, -0.121420, 18,
       &Sources[342] , 
       &Weights[342] , 
      },
    { /* unit 39 (noName) */
      0.0, -0.045410, 18,
       &Sources[360] , 
       &Weights[360] , 
      },
    { /* unit 40 (noName) */
      0.0, 0.438720, 18,
       &Sources[378] , 
       &Weights[378] , 
      },
    { /* unit 41 (noName) */
      0.0, 0.076400, 18,
       &Sources[396] , 
       &Weights[396] , 
      },
    { /* unit 42 (noName) */
      0.0, 0.453760, 18,
       &Sources[414] , 
       &Weights[414] , 
      },
    { /* unit 43 (noName) */
      0.0, -0.458200, 18,
       &Sources[432] , 
       &Weights[432] , 
      },
    { /* unit 44 (noName) */
      0.0, 0.216380, 18,
       &Sources[450] , 
       &Weights[450] , 
      },
    { /* unit 45 (noName) */
      0.0, -0.489450, 18,
       &Sources[468] , 
       &Weights[468] , 
      },
    { /* unit 46 (noName) */
      0.0, -0.464060, 18,
       &Sources[486] , 
       &Weights[486] , 
      },
    { /* unit 47 (noName) */
      0.0, -0.041080, 18,
       &Sources[504] , 
       &Weights[504] , 
      },
    { /* unit 48 (noName) */
      0.0, -0.550360, 18,
       &Sources[522] , 
       &Weights[522] , 
      },
    { /* unit 49 (noName) */
      0.0, -0.760050, 18,
       &Sources[540] , 
       &Weights[540] , 
      },
    { /* unit 50 (noName) */
      0.0, -0.701810, 18,
       &Sources[558] , 
       &Weights[558] , 
      },
    { /* unit 51 (noName) */
      0.0, -0.365570, 18,
       &Sources[576] , 
       &Weights[576] , 
      },
    { /* unit 52 (noName) */
      0.0, -0.658780, 18,
       &Sources[594] , 
       &Weights[594] , 
      },
    { /* unit 53 (noName) */
      0.0, -0.734850, 18,
       &Sources[612] , 
       &Weights[612] , 
      },
    { /* unit 54 (noName) */
      0.0, -0.231450, 18,
       &Sources[630] , 
       &Weights[630] , 
      },
    { /* unit 55 (noName) */
      0.0, -0.926380, 18,
       &Sources[648] , 
       &Weights[648] , 
      },
    { /* unit 56 (noName) */
      0.0, -0.879390, 18,
       &Sources[666] , 
       &Weights[666] , 
      },
    { /* unit 57 (noName) */
      0.0, -0.659610, 18,
       &Sources[684] , 
       &Weights[684] , 
      },
    { /* unit 58 (noName) */
      0.0, -0.577200, 18,
       &Sources[702] , 
       &Weights[702] , 
      },
    { /* unit 59 (noName) */
      0.0, -0.908240, 18,
       &Sources[720] , 
       &Weights[720] , 
      },
    { /* unit 60 (noName) */
      0.0, -0.546900, 18,
       &Sources[738] , 
       &Weights[738] , 
      },
    { /* unit 61 (noName) */
      0.0, -1.418570, 18,
       &Sources[756] , 
       &Weights[756] , 
      },
    { /* unit 62 (noName) */
      0.0, -0.445830, 18,
       &Sources[774] , 
       &Weights[774] , 
      },
    { /* unit 63 (noName) */
      0.0, -0.847030, 18,
       &Sources[792] , 
       &Weights[792] , 
      }

  };



int classifyOrientation(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[12] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12}; /* members */

  static pUnit Hidden1[18] = {Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30}; /* members */

  static pUnit Hidden2[18] = {Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48}; /* members */

  static pUnit Output1[15] = {Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, Units + 55, Units + 56, Units + 57, Units + 58, Units + 59, Units + 60, Units + 61, Units + 62, Units + 63}; /* members */

  static int Output[15] = {49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

  for(member = 0; member < 12; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 18; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 18; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 15; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for(member = 0; member < 15; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
