/*********************************************************
  c:\temp\v5.c
  --------------------------------------------------------
  generated at Wed Mar 23 12:43:21 2016
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
  static UnitType Units[50];
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
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, 

Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 43, Units + 44, 
Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 43, Units + 44, 
Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 43, Units + 44, 
Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 43, Units + 44, 
Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 43, Units + 44, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.189870, 0.014140, 0.159680, 0.042290, 0.153770, 0.300270, -0.196450, 0.028600, -0.102850, -0.000320, 
0.291550, -0.068380, 
-0.026930, -0.260150, 0.359120, -0.019470, 0.038520, 0.685700, 0.038740, 0.434450, -0.292610, -0.214630, 
0.356140, -0.060340, 
-0.060780, -0.531830, -0.374500, 0.102100, -0.618200, 0.640280, -0.067160, -0.117100, 0.138000, 0.070990, 
-0.603860, 0.081650, 
-0.003590, -0.143190, -0.110010, -0.051700, -0.215670, -0.189070, 0.100710, 0.260410, 0.171070, -0.402980, 
0.139920, 0.671020, 
-0.155620, -0.024830, -0.225270, -0.093610, 0.084370, 0.107420, -0.130370, 0.046990, 0.156950, -0.088950, 
0.138260, 0.057100, 
-0.114500, 0.020650, 0.000170, 0.031020, 0.199500, 0.014360, -0.115230, 0.095150, 0.092190, -0.002330, 
0.163110, -0.090010, 
-0.003680, -0.158980, 0.180070, 0.069230, -0.462030, 0.386210, 0.001190, -0.245710, 0.479920, 0.002380, 
-0.500320, -0.384810, 
-0.097240, -0.132150, 0.209180, 0.202910, 0.003910, 0.579880, -0.180810, -0.083450, -0.269340, 0.155690, 
-0.077690, -0.558310, 
-0.112260, -0.342790, -0.396810, -0.020780, -0.363020, -0.161190, 0.041360, -0.054020, 0.385480, -0.043170, 
-0.268140, 0.602880, 
-0.136050, -0.360110, 0.351040, 0.280490, -0.333850, 0.612290, -0.205970, -0.257960, -0.243250, 0.303060, 
-0.202540, -0.714380, 
0.165380, -0.072270, 0.021240, 0.053150, -0.107110, -0.100720, 0.128910, -0.043130, -0.229180, -0.007130, 
-0.083680, 0.061620, 
0.125040, 0.456650, 0.061360, -0.048220, 0.212800, -0.477680, 0.051670, -0.108750, 0.052540, -0.004200, 
0.169150, -0.281480, 
0.043570, -0.058430, 0.072480, 0.038100, -0.095790, 0.028630, 0.061810, -0.128360, -0.088300, 0.029190, 
-0.002690, 0.174440, 
-0.132760, 0.027140, 0.039250, 0.101740, -0.005640, 0.520990, -0.158780, 0.043970, -0.411860, 0.034640, 
-0.189160, -0.381040, 
-0.026620, -0.121890, 0.247450, 0.054020, 0.254990, 0.824820, -0.194250, 0.240140, -0.356880, -0.130660, 
0.237280, -0.134340, 
0.047130, -0.220610, -0.067040, 0.160160, -0.149040, 0.420940, 0.071290, 0.146800, -0.325380, -0.170480, 
0.281710, 0.830470, 
0.071820, 0.123500, 0.191710, -0.324140, 0.005870, -0.120400, 0.166450, -0.115000, -0.095200, 0.082860, 
-0.037700, 0.173970, 
0.102020, 0.167570, -0.059040, -0.033790, 0.054320, -0.389100, 0.064030, -0.038160, 0.139160, -0.050390, 
-0.182280, -0.102500, 
-0.088280, 0.394160, 0.296920, -0.143140, 0.577700, 0.022760, -0.061110, 0.488910, -0.319400, -0.222560, 
0.622900, 0.362660, 
0.092490, -0.086720, -0.363100, -0.095300, -0.442110, -0.230400, 0.265440, 0.371690, 0.384060, -0.166250, 
0.115370, 0.838590, 
-0.053140, 0.149230, 0.751060, 0.143270, -0.031310, -0.146770, 0.207790, -0.012050, 0.317990, -0.125490, 
0.063800, -0.414930, 0.102140, 0.121910, 0.150110, 0.279320, -0.147310, -0.104640, -0.428680, 0.322680, 

-0.061660, -0.028040, -0.100270, 0.290530, 0.204880, 0.147980, -0.176910, -0.630500, 0.076040, -0.894380, 
-0.123790, 0.200910, -0.103640, -0.132690, -0.136070, 0.032670, -0.155610, 0.108260, 0.386470, 0.419540, 

0.210070, -0.017830, -0.012600, -0.124150, 0.259800, 0.194130, 0.021600, -0.105580, 0.137180, -0.055710, 
-0.263300, 0.035500, -0.163500, 0.137000, -0.012310, -0.119950, -0.227940, -0.073190, 0.092440, -0.139630, 

0.055490, -0.027670, 0.143520, -0.314420, -0.211360, -0.074170, 0.135250, 0.580940, -0.173180, 0.843400, 
0.162570, -0.245330, 0.061320, 0.179360, 0.106890, -0.191050, 0.321810, -0.091690, -0.330490, -0.422180, 

0.016780, 0.297820, -0.394390, -0.313390, -0.352540, -0.004730, -0.237570, 0.168500, -0.729720, -0.067590, 
0.228790, 0.256220, -0.045270, 0.073250, 0.379940, -0.102440, -0.188480, 0.029440, 0.053370, -0.451780, 

0.112030, -0.339290, 0.368090, 0.239140, 0.267180, -0.008210, 0.119850, -0.126060, 0.747100, 0.025050, 
-0.033910, -0.179470, 0.088110, -0.184680, -0.330790, 0.104100, -0.187260, -0.021960, -0.274440, 0.470910, 

-0.032530, 0.155320, 0.563120, -0.462320, 0.047400, -0.117260, 0.558380, 0.273540, -0.264060, -0.299330, 
-0.325810, 0.013580, -0.118180, 0.393850, 0.351060, -0.392500, -0.330390, -0.061040, -0.592580, -0.346120, 

0.118630, 0.122430, 0.250850, -0.157980, 0.240710, 0.042310, 0.297630, 0.070270, -0.043670, -0.081970, 
-0.112930, -0.038040, -0.219480, 0.368640, 0.216970, -0.169040, -0.325780, -0.134880, -0.285470, -0.208280, 

-0.199460, -0.531140, -0.171240, -0.262810, 0.011270, 0.116390, 0.129170, -0.316270, 0.025880, 0.066920, 
-0.216280, 0.294080, -0.059350, -0.164790, -0.486770, -0.526170, -0.029900, 0.228290, -0.288760, -0.223760, 

-0.022590, -0.599290, -0.397960, -0.411500, 0.139700, 0.153470, 0.120910, -0.008800, -0.213360, 0.018790, 
-0.060200, 0.498380, -0.139270, -0.122320, -0.590350, -0.899720, -0.231870, 0.256990, -0.165500, -0.627530, 

-0.029860, -0.412730, -0.579180, 0.357670, -0.331400, -0.141220, -0.487930, -0.022420, 0.135360, 0.297360, 
0.198720, 0.108910, 0.221210, -0.505150, -0.274450, 0.353800, 0.407440, 0.138410, 0.527230, 0.294670, 

0.641260, 0.372710, -0.540870, -0.188050, 0.416410, 0.358310, -0.345180, 0.725760, 0.540370, 0.763590, 
-0.665480, 0.104360, -0.207580, 0.242910, 0.386430, 0.146700, -0.394700, -0.249110, 0.957190, -0.407900, 

-0.792880, -0.524450, 0.792230, 0.311170, -0.094580, 0.282180, -0.505850, 0.415600, -0.668450, -0.187630, 
0.123870, 3.833390, 
0.853290, -0.147120, 0.362120, -0.293050, 0.301340, -0.424140, 2.040140, 1.116570, -0.290410, 0.048230, 
-1.892400, -0.451960, 
-1.105630, -0.271220, 0.696590, 0.213150, 0.229050, -0.036230, 0.189890, 0.460020, 1.729550, 2.898680, 
0.011560, -0.461900, 
-0.428050, 2.453070, 0.346820, -2.217830, -0.064600, -0.133790, -0.230530, 0.387740, -0.140610, -0.301220, 
-0.082720, -0.439530, 
1.111780, -0.163410, 0.526830, -0.092400, -1.977870, 1.959850, -0.517870, -0.013350, 0.452900, -0.290770, 
0.445110, 0.111070, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[50] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -0.277500, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -0.270490, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.125890, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.528310, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.452860, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, -0.189060, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -0.735590, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 0.551320, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, -0.396890, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, -0.853210, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 11 (noName) */
      0.0, -0.890990, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 12 (noName) */
      0.0, 0.371200, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.467970, 12,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.163840, 12,
       &Sources[12] , 
       &Weights[12] , 
      },
    { /* unit 15 (noName) */
      0.0, -0.459900, 12,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 16 (noName) */
      0.0, 0.523770, 12,
       &Sources[36] , 
       &Weights[36] , 
      },
    { /* unit 17 (noName) */
      0.0, -0.534990, 12,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 18 (noName) */
      0.0, -0.274020, 12,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 19 (noName) */
      0.0, -0.700730, 12,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 20 (noName) */
      0.0, 0.069790, 12,
       &Sources[84] , 
       &Weights[84] , 
      },
    { /* unit 21 (noName) */
      0.0, -0.514470, 12,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 22 (noName) */
      0.0, 0.275840, 12,
       &Sources[108] , 
       &Weights[108] , 
      },
    { /* unit 23 (noName) */
      0.0, 0.487200, 12,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 24 (noName) */
      0.0, -0.077440, 12,
       &Sources[132] , 
       &Weights[132] , 
      },
    { /* unit 25 (noName) */
      0.0, 0.354610, 12,
       &Sources[144] , 
       &Weights[144] , 
      },
    { /* unit 26 (noName) */
      0.0, -0.536350, 12,
       &Sources[156] , 
       &Weights[156] , 
      },
    { /* unit 27 (noName) */
      0.0, 0.152550, 12,
       &Sources[168] , 
       &Weights[168] , 
      },
    { /* unit 28 (noName) */
      0.0, 0.557550, 12,
       &Sources[180] , 
       &Weights[180] , 
      },
    { /* unit 29 (noName) */
      0.0, 0.586660, 12,
       &Sources[192] , 
       &Weights[192] , 
      },
    { /* unit 30 (noName) */
      0.0, 0.083450, 12,
       &Sources[204] , 
       &Weights[204] , 
      },
    { /* unit 31 (noName) */
      0.0, 0.375390, 12,
       &Sources[216] , 
       &Weights[216] , 
      },
    { /* unit 32 (noName) */
      0.0, 0.296080, 12,
       &Sources[228] , 
       &Weights[228] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.012010, 20,
       &Sources[240] , 
       &Weights[240] , 
      },
    { /* unit 34 (noName) */
      0.0, -0.211880, 20,
       &Sources[260] , 
       &Weights[260] , 
      },
    { /* unit 35 (noName) */
      0.0, -0.329720, 20,
       &Sources[280] , 
       &Weights[280] , 
      },
    { /* unit 36 (noName) */
      0.0, 0.203010, 20,
       &Sources[300] , 
       &Weights[300] , 
      },
    { /* unit 37 (noName) */
      0.0, 0.333980, 20,
       &Sources[320] , 
       &Weights[320] , 
      },
    { /* unit 38 (noName) */
      0.0, -0.374130, 20,
       &Sources[340] , 
       &Weights[340] , 
      },
    { /* unit 39 (noName) */
      0.0, -0.527560, 20,
       &Sources[360] , 
       &Weights[360] , 
      },
    { /* unit 40 (noName) */
      0.0, -0.271030, 20,
       &Sources[380] , 
       &Weights[380] , 
      },
    { /* unit 41 (noName) */
      0.0, 0.045660, 20,
       &Sources[400] , 
       &Weights[400] , 
      },
    { /* unit 42 (noName) */
      0.0, -0.334450, 20,
       &Sources[420] , 
       &Weights[420] , 
      },
    { /* unit 43 (noName) */
      0.0, -0.049810, 20,
       &Sources[440] , 
       &Weights[440] , 
      },
    { /* unit 44 (noName) */
      0.0, -0.484630, 20,
       &Sources[460] , 
       &Weights[460] , 
      },
    { /* unit 45 (noName) */
      0.0, -0.767550, 12,
       &Sources[480] , 
       &Weights[480] , 
      },
    { /* unit 46 (noName) */
      0.0, -0.362720, 12,
       &Sources[492] , 
       &Weights[492] , 
      },
    { /* unit 47 (noName) */
      0.0, -0.715610, 12,
       &Sources[504] , 
       &Weights[504] , 
      },
    { /* unit 48 (noName) */
      0.0, -0.309480, 12,
       &Sources[516] , 
       &Weights[516] , 
      },
    { /* unit 49 (noName) */
      0.0, -0.681870, 12,
       &Sources[528] , 
       &Weights[528] , 
      }

  };



int classify5(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[12] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12}; /* members */

  static pUnit Hidden1[20] = {Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32}; /* members */

  static pUnit Hidden2[12] = {Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44}; /* members */

  static pUnit Output1[5] = {Units + 45, Units + 46, Units + 47, Units + 48, Units + 49}; /* members */

  static int Output[5] = {45, 46, 47, 48, 49};

  for(member = 0; member < 12; member++) {
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

  for (member = 0; member < 12; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 5; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for(member = 0; member < 5; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
