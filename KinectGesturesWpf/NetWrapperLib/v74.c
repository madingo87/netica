/*********************************************************
  c:\temp\v74.c
  --------------------------------------------------------
  generated at Fri Nov 27 17:01:09 2015
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
  static UnitType Units[53];
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
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, 
Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 
Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
0.169410, -1.009980, -0.585620, 0.422680, 0.966660, 1.942230, 0.389330, -0.857990, 
-0.772540, -0.220590, 0.549040, 0.068590, -0.955190, 0.636490, 0.786270, 0.626750, 
0.614390, -0.790390, -0.663550, -0.364730, 2.375580, 0.409090, -0.021850, -0.402060, 
-0.467090, -0.207040, 0.540320, 0.056360, -0.769080, 0.759850, 0.784610, 0.033800, 
-0.098970, -0.602800, -0.070710, -0.148360, 0.596390, 0.153690, 0.508970, 0.914070, 
0.125350, -0.450050, -0.135840, -0.241530, 1.099100, 0.740610, 0.471700, -0.969410, 
-0.677030, 1.236480, 0.271810, 0.119640, -2.277880, 1.021220, 0.877930, -0.735390, 
0.497990, 0.626100, -0.151340, 0.049620, -0.693410, -2.145300, -0.970190, 1.445620, 
0.427490, 1.553050, -0.433160, -0.208130, -0.681680, -1.651620, -1.322910, 1.105570, 
-0.235060, -0.953840, 0.020320, -0.473900, 1.328990, -0.095460, 0.645310, 1.995440, 
-0.444810, 0.740510, -0.073590, -0.165250, -1.476690, -1.303890, 0.388310, 0.954400, 
0.564770, 0.717870, -0.455620, -0.027170, 0.609690, -0.282250, -0.653800, -1.217910, 
-0.543380, 0.007300, 0.001530, -0.225990, -0.322980, -0.056150, 0.422630, 0.776510, 
1.028490, -0.206800, -0.753100, -0.509190, 1.477890, -0.503760, -0.774620, -0.233350, 
0.808510, -0.367300, 0.151010, 0.560950, -0.688870, 1.728890, 0.528310, -1.942020, 
-0.307850, -0.005820, 0.247520, 0.120310, -0.743830, 0.540040, 0.560830, 0.154190, 
0.057760, 0.485980, -0.310110, -0.634350, 0.045130, -1.484930, -0.213680, 1.009090, 
0.631500, 0.775080, -0.387490, 0.067480, 0.442480, -0.417040, -0.653960, -1.414370, 
0.044580, -0.035020, -0.599300, -0.496750, 1.764670, -0.823280, -0.565960, 0.139120, 
0.231290, -0.358940, -0.347690, -0.569450, 0.974290, -1.457900, -0.469180, 1.616390, 
-0.230700, -0.843770, -0.117090, -0.268120, 1.252010, -0.031010, 0.521430, 1.616190, 
0.597830, 0.618620, -0.351090, 0.105020, 0.060570, -0.255460, -0.556360, -1.175010, 
0.355190, 0.110670, -0.009390, 0.398680, 0.264560, 0.408460, -0.239740, -1.134040, 
0.267130, -0.556190, -0.876070, 0.069400, 2.042850, -0.766930, -0.811700, 0.322030, 
-1.262870, 0.620990, -1.485480, 0.541980, -0.572350, -0.830150, 1.318020, 1.479990, 1.271580, -1.314020, 
1.296660, -0.322140, 0.227250, -0.871580, -0.183850, 0.367180, 0.569250, -0.114850, -0.885710, 0.046230, 
-0.845500, 0.142860, -0.042990, -1.084590, 
-0.196700, -0.193460, -0.527520, -0.071980, -0.628200, -0.141300, 0.731060, 0.081540, 0.343190, -1.105890, 
0.065670, 0.378280, -0.260770, -0.120410, 0.692910, -0.006490, -0.186520, 0.500040, -0.344190, -0.643540, 
-0.972980, 0.543080, 0.381380, -0.465150, 
0.809690, 0.260590, -0.074820, 0.474040, -0.199460, 0.465750, 1.165880, -1.003990, -0.766200, -0.578520, 
-0.458140, 0.267310, -0.233430, -0.230890, 1.661380, 0.357530, -0.876670, 0.366980, -0.465180, -1.183530, 
-0.492290, 0.393470, 0.604680, -0.543620, 
0.260350, 0.763860, -0.294180, 0.663620, 0.453560, 0.003170, 0.606810, -0.414670, -0.482290, 0.252930, 
0.209300, -0.782680, 0.403520, -0.738290, 0.091190, 0.529680, -0.232940, -0.881310, -0.542570, -0.132960, 
0.342020, -0.710130, -0.416180, -0.623490, 
-1.021820, 0.349970, -0.872410, 0.021320, -0.002450, -0.901150, 0.115200, 0.818700, 0.894480, 0.065560, 
0.875970, -0.876010, 0.533820, -0.764840, -1.183020, 0.294060, 0.686480, -0.902080, -0.527930, 0.470310, 
0.172480, -0.756530, -0.678640, -0.651700, 
1.077470, -0.552030, 1.120720, -0.061010, 0.002270, 1.002560, -0.263300, -0.904560, -0.930680, -0.060870, 
-1.114510, 0.937380, -0.425940, 0.892340, 1.238310, -0.092680, -0.622490, 1.008620, 0.604260, -0.506640, 
-0.146230, 0.767280, 0.691350, 0.741870, 
-1.009690, -0.353860, -0.210140, -0.420100, -0.262920, -0.523750, -0.340760, 1.281430, 1.242150, -0.233960, 
0.650160, 0.321240, 0.033390, 0.279830, -0.890780, -0.237610, 0.808550, 0.321360, 0.317260, 0.800000, 
-0.178020, 0.285410, -0.020940, 0.297670, 
-1.176900, 0.368950, -1.452880, 0.360210, -0.214020, -0.837490, 1.236640, 1.186760, 1.410730, -1.317210, 
1.213520, -0.317290, 0.455500, -0.744000, -0.239070, 0.324290, 0.382330, -0.086800, -0.710590, -0.173620, 
-0.706980, 0.030780, -0.022420, -1.084290, 
0.923490, -0.423370, 0.842040, -0.404470, 0.327860, 0.405420, -1.325810, -0.683670, -1.061010, 0.983450, 
-0.782260, 0.075590, -0.093500, 0.637380, -0.037260, -0.262800, -0.319380, 0.058950, 0.720350, 0.359470, 
0.924800, -0.097740, -0.074430, 0.909630, 
0.216070, 0.843420, -0.308480, 0.689330, 0.392710, -0.031090, 0.587590, -0.391000, -0.410710, 0.331830, 
0.297220, -0.871510, 0.486880, -0.778370, 0.029670, 0.548420, -0.222410, -0.913180, -0.548060, -0.175430, 
0.260880, -0.742780, -0.435480, -0.625050, 
-0.184450, -0.178260, -0.515180, -0.083090, -0.600790, -0.201260, 0.714970, 0.132170, 0.288090, -1.084010, 
0.088410, 0.405390, -0.255750, -0.102370, 0.671740, -0.001320, -0.208680, 0.495520, -0.372980, -0.671720, 
-0.994610, 0.506510, 0.402560, -0.466220, 
0.195920, 0.839560, -0.309740, 0.653940, 0.432340, -0.012780, 0.605280, -0.347290, -0.398150, 0.370860, 
0.275720, -0.855650, 0.460050, -0.772530, 0.038250, 0.465730, -0.196110, -0.919640, -0.545680, -0.216970, 
0.337920, -0.735980, -0.428420, -0.643880, 
0.265880, 0.128460, 0.648670, 0.019630, 0.647960, 0.234480, -0.836780, -0.167160, -0.286350, 1.185860, 
-0.160490, -0.364380, 0.264810, 0.190690, -0.730780, -0.013500, 0.225700, -0.468750, 0.447040, 0.725720, 
1.091720, -0.590690, -0.393510, 0.550080, 
-0.107350, -0.970910, 0.457830, -0.735680, -0.364550, 0.074320, -0.734760, 0.211760, 0.342810, -0.247350, 
-0.394790, 0.889800, -0.547000, 0.872620, -0.010420, -0.599400, 0.087800, 0.994390, 0.626470, 0.209770, 
-0.226710, 0.819490, 0.446360, 0.720760, 
0.904480, 0.313550, -0.103260, 0.475940, -0.147130, 0.454730, 1.180990, -0.929340, -0.731540, -0.677860, 
-0.495660, 0.296380, -0.149670, -0.190270, 1.703900, 0.245710, -0.833180, 0.332310, -0.451060, -1.219030, 
-0.497590, 0.377760, 0.537740, -0.587480, 
-0.731910, -0.385590, 0.254660, -0.474770, 0.334990, -0.431930, -1.198210, 0.833360, 0.582940, 0.671470, 
0.383370, -0.174270, 0.115710, 0.323850, -1.514400, -0.433330, 0.707410, -0.258310, 0.558140, 1.123770, 
0.507030, -0.338020, -0.601450, 0.640170, 
2.749670, -0.857370, -2.388060, 0.882270, 3.131740, -4.383550, 0.900730, 2.196750, -2.107890, 1.167030, 
-0.817120, 1.136760, -0.616980, -2.625680, -2.373290, 0.814370, 
-2.600340, -0.885850, 2.185050, 1.622480, -1.675070, 1.140830, -3.764040, -2.336370, 0.730330, 1.605920, 
-0.886030, 1.424680, 0.222530, -2.151000, 2.145370, -2.724740, 
1.873750, 2.314790, 1.302380, -1.434750, -0.876030, -0.274700, 0.052020, 1.721650, -2.757990, -1.498260, 
2.313460, -1.483930, -3.315680, 0.571180, 1.329530, -2.246100, 
-3.034890, -1.531410, -2.561310, -2.365470, -1.378060, 1.514930, 0.841570, -2.745860, 1.833030, -2.418140, 
-1.545380, -2.372620, 1.606360, 2.162390, -2.486450, 2.366750, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[53] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, 0.189550, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, 0.186250, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.611500, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.957760, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.536970, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, -0.915400, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -0.521900, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, -0.489730, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 0.323090, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, -0.561630, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, 0.136060, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, -0.209680, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.077240, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.379720, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, -0.392490, 8,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, 0.020440, 8,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 17 (noName) */
      0.0, -0.204860, 8,
       &Sources[64] , 
       &Weights[64] , 
      },
    { /* unit 18 (noName) */
      0.0, -0.052890, 8,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 19 (noName) */
      0.0, -0.753890, 8,
       &Sources[80] , 
       &Weights[80] , 
      },
    { /* unit 20 (noName) */
      0.0, 0.468100, 8,
       &Sources[88] , 
       &Weights[88] , 
      },
    { /* unit 21 (noName) */
      0.0, -0.251670, 8,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 22 (noName) */
      0.0, 0.452920, 8,
       &Sources[104] , 
       &Weights[104] , 
      },
    { /* unit 23 (noName) */
      0.0, 0.197730, 8,
       &Sources[112] , 
       &Weights[112] , 
      },
    { /* unit 24 (noName) */
      0.0, -0.285680, 8,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 25 (noName) */
      0.0, -0.046630, 8,
       &Sources[128] , 
       &Weights[128] , 
      },
    { /* unit 26 (noName) */
      0.0, 0.485930, 8,
       &Sources[136] , 
       &Weights[136] , 
      },
    { /* unit 27 (noName) */
      0.0, 0.171960, 8,
       &Sources[144] , 
       &Weights[144] , 
      },
    { /* unit 28 (noName) */
      0.0, 0.083060, 8,
       &Sources[152] , 
       &Weights[152] , 
      },
    { /* unit 29 (noName) */
      0.0, -0.017620, 8,
       &Sources[160] , 
       &Weights[160] , 
      },
    { /* unit 30 (noName) */
      0.0, 0.349290, 8,
       &Sources[168] , 
       &Weights[168] , 
      },
    { /* unit 31 (noName) */
      0.0, 0.222380, 8,
       &Sources[176] , 
       &Weights[176] , 
      },
    { /* unit 32 (noName) */
      0.0, 0.529130, 8,
       &Sources[184] , 
       &Weights[184] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.120970, 24,
       &Sources[192] , 
       &Weights[192] , 
      },
    { /* unit 34 (noName) */
      0.0, 0.072230, 24,
       &Sources[216] , 
       &Weights[216] , 
      },
    { /* unit 35 (noName) */
      0.0, 0.220760, 24,
       &Sources[240] , 
       &Weights[240] , 
      },
    { /* unit 36 (noName) */
      0.0, 0.005230, 24,
       &Sources[264] , 
       &Weights[264] , 
      },
    { /* unit 37 (noName) */
      0.0, -0.318380, 24,
       &Sources[288] , 
       &Weights[288] , 
      },
    { /* unit 38 (noName) */
      0.0, 0.275060, 24,
       &Sources[312] , 
       &Weights[312] , 
      },
    { /* unit 39 (noName) */
      0.0, 0.097790, 24,
       &Sources[336] , 
       &Weights[336] , 
      },
    { /* unit 40 (noName) */
      0.0, -0.008210, 24,
       &Sources[360] , 
       &Weights[360] , 
      },
    { /* unit 41 (noName) */
      0.0, 0.045790, 24,
       &Sources[384] , 
       &Weights[384] , 
      },
    { /* unit 42 (noName) */
      0.0, 0.042540, 24,
       &Sources[408] , 
       &Weights[408] , 
      },
    { /* unit 43 (noName) */
      0.0, 0.089070, 24,
       &Sources[432] , 
       &Weights[432] , 
      },
    { /* unit 44 (noName) */
      0.0, -0.016630, 24,
       &Sources[456] , 
       &Weights[456] , 
      },
    { /* unit 45 (noName) */
      0.0, -0.121560, 24,
       &Sources[480] , 
       &Weights[480] , 
      },
    { /* unit 46 (noName) */
      0.0, 0.019040, 24,
       &Sources[504] , 
       &Weights[504] , 
      },
    { /* unit 47 (noName) */
      0.0, 0.184470, 24,
       &Sources[528] , 
       &Weights[528] , 
      },
    { /* unit 48 (noName) */
      0.0, -0.247280, 24,
       &Sources[552] , 
       &Weights[552] , 
      },
    { /* unit 49 (noName) */
      0.0, -1.029910, 16,
       &Sources[576] , 
       &Weights[576] , 
      },
    { /* unit 50 (noName) */
      0.0, -0.848690, 16,
       &Sources[592] , 
       &Weights[592] , 
      },
    { /* unit 51 (noName) */
      0.0, -0.855020, 16,
       &Sources[608] , 
       &Weights[608] , 
      },
    { /* unit 52 (noName) */
      0.0, 0.011350, 16,
       &Sources[624] , 
       &Weights[624] , 
      }

  };



int classify74(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[8] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8}; /* members */

  static pUnit Hidden1[24] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32}; /* members */

  static pUnit Hidden2[16] = {Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48}; /* members */

  static pUnit Output1[4] = {Units + 49, Units + 50, Units + 51, Units + 52}; /* members */

  static int Output[4] = {49, 50, 51, 52};

  for(member = 0; member < 8; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 24; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 16; member++) {
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
