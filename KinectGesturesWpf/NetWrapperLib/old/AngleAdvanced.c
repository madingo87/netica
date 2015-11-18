/*********************************************************
  c:\temp\AngleAdvanced.c
  --------------------------------------------------------
  generated at Fri Oct 09 17:18:33 2015
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
  static UnitType Units[62];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, 


  };

  /* Weigths definition section */
  static float Weights[] =  {
0.252080, -0.696910, -0.766050, 0.158820, -0.859090, 1.703380, 0.085010, -0.646060, 0.794270, 0.539950, 
-0.488310, 0.000860, 0.712320, 1.005080, 
0.104760, -0.349370, -2.284770, 0.470370, 0.755100, 0.233040, 0.396480, -0.076080, 0.797380, 0.081520, 
1.005910, 1.003430, 0.488420, -1.193600, 
0.107970, -0.732390, 0.780320, 0.731860, 0.836820, -0.454960, -0.404600, -0.138680, -0.219790, -0.009890, 
-0.321420, 1.309080, -0.121650, -0.010110, 
0.496720, 0.266220, -0.023790, -1.052880, 0.684030, 0.010820, 0.848090, -0.678180, 0.254210, -0.595720, 
0.278950, -0.009040, -0.098800, 0.265480, 
0.668810, 0.744390, 0.018920, -0.475780, -1.033380, 0.400760, 0.586260, 0.014040, -1.042230, 0.015270, 
-0.626770, 0.207700, 0.675770, -0.580620, 
-0.555510, -0.551100, 1.239590, -1.137910, -0.946900, -1.191000, 0.673690, 0.289940, -1.239910, 0.796420, 
3.520350, -0.321420, -0.459000, -0.637700, 
-0.300490, -0.404290, 0.707470, -0.591270, -0.519120, -0.975230, -0.967180, 0.182300, -0.088070, 0.608750, 
0.224100, 2.102310, -0.083480, -0.102740, 
-0.829830, 0.533490, 1.228990, 0.953090, 0.865190, 0.415650, -1.327800, -0.641700, -0.372680, -0.455330, 
-0.080620, -0.487020, 0.108080, -1.078930, 
-0.607430, -0.047020, 0.018910, 0.339260, 0.446620, 0.068810, -0.743610, 0.182550, 0.356070, 0.242820, 
0.189710, -0.918320, -0.284730, 0.180550, 
-0.206910, 0.465560, -0.752500, 0.685860, 0.519710, 0.634470, 0.260430, -0.458930, 0.481910, 0.412790, 
0.953630, -0.612010, -0.384720, -0.248480, 
0.762890, 0.156050, -0.559090, -0.087640, 0.378750, -1.496820, -0.207130, -0.667700, -1.102980, 1.112060, 
0.286770, -1.024850, 0.730450, 0.785720, 
-0.187440, 0.062280, -0.241700, -0.160770, -0.032980, 0.013870, -0.013950, -0.269100, 0.120240, -0.214340, 
-0.008870, -0.052570, 0.112820, -0.325790, 
0.024550, -0.055660, -0.315380, 0.581960, 0.234240, -0.356310, -0.184650, 0.058680, 1.707400, -0.576790, 
0.350420, -0.383370, -0.127950, -0.537830, 
0.569090, -0.226410, 0.513010, -0.344850, 0.848490, 0.111760, 0.428200, -0.511930, -0.541150, -0.901760, 
0.653660, -1.044090, -0.220990, 0.069110, 
0.962050, 0.412790, -0.865420, 0.513600, -0.811920, 0.623060, -0.071240, 0.805410, -0.330850, 0.499790, 
-1.002570, -0.936350, 0.057810, -0.599840, 
-0.253490, -0.340640, -0.107230, -0.494290, 0.760860, 1.091210, -0.153240, 0.626830, -1.279160, 0.939700, 
-0.041290, 0.569380, -0.537160, 0.347750, 
-0.136620, 0.151240, -0.358150, 0.333880, 0.191820, -0.179060, -0.511350, -0.044010, 0.496360, -0.279100, 
0.401020, -0.026490, -0.328900, -0.088850, 
0.075090, -0.307800, -0.118390, -1.428590, 0.242670, -0.194690, 1.004660, 0.795570, 1.065550, -1.007590, 
-0.160420, -0.847470, 0.191980, -0.300690, 
-0.490710, 0.772480, 0.543830, -0.373470, -0.082690, 0.804610, 0.164920, -0.386130, -0.477040, 0.221150, 
1.142000, 0.705000, -0.344700, 0.102840, 
-0.163550, 0.760000, -0.157630, -0.067070, 0.209470, -0.357160, 0.689210, 0.064590, -0.357080, -0.287970, 
-0.951790, 0.013720, 0.579470, -0.255560, 
0.626610, 1.245300, 0.129310, -0.067570, 0.350920, 0.228660, 0.468090, -0.545530, -0.264790, 0.419120, 
0.121940, 0.115010, -0.566920, -0.550780, 0.174500, 0.843460, -0.156080, -1.030990, 0.846160, -0.302910, 

0.195740, 0.229260, -0.069030, 0.068310, 0.647470, -0.762130, 0.665980, -0.881400, -0.684870, -0.743980, 
0.195420, 0.396290, 0.124640, -0.654790, 0.317310, -1.187360, 0.067300, 0.303260, -1.115220, 0.310060, 

-0.171670, -0.024240, 0.859760, -0.078330, 0.558270, -0.468820, 1.139400, 0.176390, -0.713500, -0.487450, 
-0.354170, 0.232070, -0.846820, -0.341470, -0.404680, 0.918910, -0.261670, -0.628600, 0.578680, 0.258300, 

-0.804780, -1.527230, 0.185560, 0.867170, 0.766440, 0.856270, 0.213490, 0.152260, -0.321490, -0.800200, 
-0.353570, -0.275440, -0.727270, 0.704690, -0.457480, 0.340620, -0.463000, 0.958950, 0.179090, 0.489450, 

-0.633660, -0.339480, -0.083240, 0.829110, 0.466990, 1.258410, 0.715270, -0.444170, -0.746330, -0.289990, 
0.112170, 0.191870, -0.094870, -0.017410, -0.549170, -0.151360, 0.134470, 0.418800, 0.782240, -0.223250, 

-0.258380, 0.625460, 0.175540, 0.210770, 0.208160, -0.009920, 0.724760, 0.100030, -0.213030, 0.190190, 
-0.834670, -0.257380, 0.487960, -0.738000, -0.019030, -0.389660, -0.090950, 0.087510, 0.311700, -0.062270, 

0.037040, 0.020130, -0.082540, -0.187470, -0.058040, 0.010460, 0.008800, -0.065500, -0.107670, -0.019910, 
0.036250, 0.459720, 0.020260, 0.019790, -0.126160, -0.005060, 0.283390, -0.163960, 0.037390, 0.281870, 

-0.358160, 0.365440, 1.177410, -0.166760, -0.893130, -0.235120, 1.413890, 0.959570, 0.321150, -0.098080, 
-0.814950, -0.065620, 0.713930, -0.674770, -0.709400, -0.157590, 0.289130, -0.469910, 0.118700, -0.557150, 

-0.498580, -0.922100, 0.210800, 0.794360, 0.601340, 0.481370, 0.042540, -0.174550, -0.264830, -0.685380, 
-0.078380, -0.111610, -0.527150, 0.540250, -0.246900, 0.236170, -0.425250, 0.596170, -0.152150, -0.150530, 

-0.080140, -0.077370, 0.083240, 0.210200, 0.085140, 0.035190, 0.006830, 0.032690, 0.082070, -0.036310, 
-0.038710, -0.418500, -0.022920, -0.005980, 0.102330, -0.029080, -0.281320, 0.222640, -0.059410, -0.235190, 

0.000070, -0.142010, 0.199880, -0.128840, 0.228060, -0.905850, 0.322550, -0.035880, -0.345910, -0.515050, 
-0.361170, 0.263740, 0.048130, -0.324150, 0.101050, -0.304150, 0.065990, 0.045480, -0.449940, 0.445480, 

0.154440, 0.044310, -0.242780, 0.293610, -0.522880, 0.013530, -0.478490, 0.495570, 0.223090, 0.757010, 
-1.267550, 0.102660, 0.529470, 0.364910, -0.434760, 0.260530, 0.334660, 0.354550, 0.957660, -0.202100, 

-0.675380, -0.893470, -0.329030, 1.300580, 0.157150, 1.216270, 0.354110, -0.102770, -0.177350, -0.233090, 
-0.889840, 0.581640, 0.408910, 0.369900, -0.791950, -0.663010, 0.130730, 1.214110, 0.513360, 0.381710, 

0.958030, 0.931410, -0.212490, 0.521960, 0.505370, -1.835110, -0.508800, -0.250080, -0.552080, 0.133370, 
-2.261670, 0.306380, 0.125650, 0.074910, 0.167300, 0.510960, -0.076160, 0.956980, 0.461450, 0.439620, 

-0.075490, -0.045860, 0.100230, 0.191600, 0.069020, 0.014240, 0.003700, 0.063250, 0.099590, 0.017680, 
-0.011730, -0.461490, -0.030900, -0.033630, 0.137780, 0.007190, -0.301410, 0.156810, -0.044740, -0.274620, 

0.479360, 0.124500, 0.618220, -0.206700, 0.188320, -1.455210, -0.305210, 0.563900, 0.060150, -0.050910, 
-0.200710, -0.431020, -0.864540, -0.127860, 0.492490, 1.269950, -0.126950, -0.914300, -0.080430, -0.271290, 

0.077670, 0.038270, -0.098400, -0.179520, -0.042420, -0.015850, -0.020300, -0.108550, -0.135770, -0.024930, 
0.027250, 0.471210, -0.008340, 0.041170, -0.141010, 0.029890, 0.293950, -0.164810, 0.072860, 0.301730, 

0.212410, -0.228630, -0.531680, 0.048750, 0.338440, -0.024110, -0.384400, 0.034060, 0.290630, 0.265220, 
0.338120, -0.189720, -0.134330, -0.394020, 0.817150, -0.194760, -0.236140, -0.199710, -0.122730, -0.083590, 

-0.797430, -1.818100, 0.316720, -0.591640, -0.173670, 0.257940, 0.087660, 1.176410, 0.502750, -0.210170, 
0.799820, 0.063250, -0.415630, 0.214080, -0.028270, 0.345890, 0.158830, -0.636670, -0.061090, -0.026710, 

0.171960, 0.719010, 0.120350, 0.692740, 1.058840, 1.073020, 0.540310, -1.802120, -1.132070, -0.706820, 
0.260460, -0.305540, -1.182450, 0.087850, -0.286900, 0.890100, -0.395910, 0.229400, 0.351230, 0.269460, 

-1.305170, -0.052230, -0.804660, 0.125360, 0.830810, 0.089070, 0.826850, 1.455590, -0.246610, -0.612380, 
0.301350, 1.121180, 1.799440, -1.168390, -0.851130, -1.883970, 0.606530, -0.543760, 1.378700, -1.789090, 

0.222250, 0.349260, 0.707110, 1.443090, 1.307010, 0.081820, 0.246750, -2.243860, 1.021850, -0.079730, 
0.112720, 0.704390, 1.998050, 2.428000, -0.529060, -0.607810, 0.800420, -1.524150, -1.944010, 2.213780, 

0.613970, 2.055670, -0.182740, -1.646130, 0.046720, -0.271070, 0.517390, -0.022780, -0.931210, -0.542330, 
0.451990, -1.310470, -0.641150, -1.598730, -0.568420, -0.943060, 0.489660, 0.194340, -1.007050, 0.732950, 

1.011050, -0.964560, -0.374920, -2.032660, -1.219310, -0.653900, 0.515630, 0.987000, -1.553930, -0.825100, 
-0.065100, 1.529290, -1.018930, 1.074730, -0.822360, 1.348480, 0.797240, -0.288940, -0.730600, -1.280080, 

-0.713440, 1.617410, 1.239470, 0.200540, -0.605370, 0.157710, 0.480490, 0.344320, 0.173210, -0.440650, 
1.693190, -0.503250, -0.011550, 1.082670, -0.425730, 0.302960, 0.422650, -0.286130, 0.352380, -0.404880, 

-0.634830, -0.432930, -0.612850, 0.205870, -0.597810, -2.179750, 0.629720, -1.618520, 0.322190, -0.606630, 
-0.163380, -0.501010, -0.234100, -0.913250, -0.600510, 0.704350, 0.649660, -0.245570, 0.368300, -0.088670, 

1.938140, -1.102270, 2.193910, 0.349770, 0.894940, -0.018390, 0.871640, 0.384320, -0.142230, -0.829100, 
-0.226590, -0.151160, -0.241410, -1.235530, -0.820600, 1.074790, 0.888050, -0.512030, 1.144640, 1.375770, 


  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[62] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -0.321020, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -0.248210, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.742850, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.654650, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, 0.466600, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.782280, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, 0.286660, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 0.301190, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 0.028960, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, 0.467940, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 11 (noName) */
      0.0, 0.474350, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 12 (noName) */
      0.0, 0.914180, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.068330, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 14 (noName) */
      0.0, -0.273480, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 15 (noName) */
      0.0, -0.704880, 14,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 16 (noName) */
      0.0, -0.434760, 14,
       &Sources[14] , 
       &Weights[14] , 
      },
    { /* unit 17 (noName) */
      0.0, -0.388270, 14,
       &Sources[28] , 
       &Weights[28] , 
      },
    { /* unit 18 (noName) */
      0.0, -0.168670, 14,
       &Sources[42] , 
       &Weights[42] , 
      },
    { /* unit 19 (noName) */
      0.0, 0.368390, 14,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 20 (noName) */
      0.0, 0.344170, 14,
       &Sources[70] , 
       &Weights[70] , 
      },
    { /* unit 21 (noName) */
      0.0, 0.345330, 14,
       &Sources[84] , 
       &Weights[84] , 
      },
    { /* unit 22 (noName) */
      0.0, 0.712470, 14,
       &Sources[98] , 
       &Weights[98] , 
      },
    { /* unit 23 (noName) */
      0.0, 0.391010, 14,
       &Sources[112] , 
       &Weights[112] , 
      },
    { /* unit 24 (noName) */
      0.0, -0.663280, 14,
       &Sources[126] , 
       &Weights[126] , 
      },
    { /* unit 25 (noName) */
      0.0, 0.250870, 14,
       &Sources[140] , 
       &Weights[140] , 
      },
    { /* unit 26 (noName) */
      0.0, -0.490230, 14,
       &Sources[154] , 
       &Weights[154] , 
      },
    { /* unit 27 (noName) */
      0.0, -0.485170, 14,
       &Sources[168] , 
       &Weights[168] , 
      },
    { /* unit 28 (noName) */
      0.0, 0.051860, 14,
       &Sources[182] , 
       &Weights[182] , 
      },
    { /* unit 29 (noName) */
      0.0, 0.565750, 14,
       &Sources[196] , 
       &Weights[196] , 
      },
    { /* unit 30 (noName) */
      0.0, -0.060630, 14,
       &Sources[210] , 
       &Weights[210] , 
      },
    { /* unit 31 (noName) */
      0.0, -0.333070, 14,
       &Sources[224] , 
       &Weights[224] , 
      },
    { /* unit 32 (noName) */
      0.0, 0.282250, 14,
       &Sources[238] , 
       &Weights[238] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.793460, 14,
       &Sources[252] , 
       &Weights[252] , 
      },
    { /* unit 34 (noName) */
      0.0, -0.601250, 14,
       &Sources[266] , 
       &Weights[266] , 
      },
    { /* unit 35 (noName) */
      0.0, -0.088590, 20,
       &Sources[280] , 
       &Weights[280] , 
      },
    { /* unit 36 (noName) */
      0.0, 0.345060, 20,
       &Sources[300] , 
       &Weights[300] , 
      },
    { /* unit 37 (noName) */
      0.0, -0.572150, 20,
       &Sources[320] , 
       &Weights[320] , 
      },
    { /* unit 38 (noName) */
      0.0, -0.302350, 20,
       &Sources[340] , 
       &Weights[340] , 
      },
    { /* unit 39 (noName) */
      0.0, -0.305730, 20,
       &Sources[360] , 
       &Weights[360] , 
      },
    { /* unit 40 (noName) */
      0.0, 0.564710, 20,
       &Sources[380] , 
       &Weights[380] , 
      },
    { /* unit 41 (noName) */
      0.0, -0.594190, 20,
       &Sources[400] , 
       &Weights[400] , 
      },
    { /* unit 42 (noName) */
      0.0, 0.212510, 20,
       &Sources[420] , 
       &Weights[420] , 
      },
    { /* unit 43 (noName) */
      0.0, -0.291760, 20,
       &Sources[440] , 
       &Weights[440] , 
      },
    { /* unit 44 (noName) */
      0.0, 0.555220, 20,
       &Sources[460] , 
       &Weights[460] , 
      },
    { /* unit 45 (noName) */
      0.0, -0.261690, 20,
       &Sources[480] , 
       &Weights[480] , 
      },
    { /* unit 46 (noName) */
      0.0, -0.200760, 20,
       &Sources[500] , 
       &Weights[500] , 
      },
    { /* unit 47 (noName) */
      0.0, -0.385660, 20,
       &Sources[520] , 
       &Weights[520] , 
      },
    { /* unit 48 (noName) */
      0.0, -0.121080, 20,
       &Sources[540] , 
       &Weights[540] , 
      },
    { /* unit 49 (noName) */
      0.0, 0.629570, 20,
       &Sources[560] , 
       &Weights[560] , 
      },
    { /* unit 50 (noName) */
      0.0, -0.288340, 20,
       &Sources[580] , 
       &Weights[580] , 
      },
    { /* unit 51 (noName) */
      0.0, -0.620870, 20,
       &Sources[600] , 
       &Weights[600] , 
      },
    { /* unit 52 (noName) */
      0.0, 0.448320, 20,
       &Sources[620] , 
       &Weights[620] , 
      },
    { /* unit 53 (noName) */
      0.0, 0.232090, 20,
       &Sources[640] , 
       &Weights[640] , 
      },
    { /* unit 54 (noName) */
      0.0, -0.215040, 20,
       &Sources[660] , 
       &Weights[660] , 
      },
    { /* unit 55 (noName) */
      0.0, -0.936840, 20,
       &Sources[680] , 
       &Weights[680] , 
      },
    { /* unit 56 (noName) */
      0.0, -0.390430, 20,
       &Sources[700] , 
       &Weights[700] , 
      },
    { /* unit 57 (noName) */
      0.0, -0.569930, 20,
       &Sources[720] , 
       &Weights[720] , 
      },
    { /* unit 58 (noName) */
      0.0, -0.613880, 20,
       &Sources[740] , 
       &Weights[740] , 
      },
    { /* unit 59 (noName) */
      0.0, -0.524440, 20,
       &Sources[760] , 
       &Weights[760] , 
      },
    { /* unit 60 (noName) */
      0.0, -0.730800, 20,
       &Sources[780] , 
       &Weights[780] , 
      },
    { /* unit 61 (noName) */
      0.0, -0.978530, 20,
       &Sources[800] , 
       &Weights[800] , 
      }

  };



int classifyAngleAdvanced(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[14] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14}; /* members */

  static pUnit Hidden1[20] = {Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34}; /* members */

  static pUnit Hidden2[20] = {Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54}; /* members */

  static pUnit Output1[7] = {Units + 55, Units + 56, Units + 57, Units + 58, Units + 59, Units + 60, Units + 61}; /* members */

  static int Output[7] = {55, 56, 57, 58, 59, 60, 61};

  for(member = 0; member < 14; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 20; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 20; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 7; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for(member = 0; member < 7; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
