/*********************************************************
  c:\temp\v35.c
  --------------------------------------------------------
  generated at Mon Nov 02 20:19:08 2015
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
  static UnitType Units[47];
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
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 

Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
0.535100, -1.168630, -0.246110, -0.209970, -0.391220, -0.386530, 0.636580, 0.145840, 
-0.817020, 0.148240, -0.161490, 0.070300, 0.049220, 0.248200, 0.965860, -0.707020, 
-0.188250, -0.133400, -0.093000, -0.137160, -0.233720, -0.154900, -0.108860, -0.156510, 
0.311080, 0.031240, -1.012120, 0.445390, 0.578290, 0.287290, -0.496380, -0.025940, 
-0.351600, 1.090800, -0.602020, 0.336810, -0.020890, 0.307210, -0.523000, 0.335720, 
-0.895190, -0.551750, 0.901550, 0.107790, -0.312740, -0.025180, 0.839060, 0.498790, 
0.167170, -0.524430, 1.287800, -0.292500, -0.430650, -0.309150, -0.292200, 0.048150, 
0.454210, 0.558120, -0.349720, 0.305740, -0.220400, 0.272320, 0.558600, -1.215750, 
1.082230, 0.210370, 0.029810, -0.616500, -0.480940, -0.218300, -0.491470, 0.186480, 
-0.153520, 0.265820, -0.655820, 0.199270, 0.241930, 0.433280, -0.912860, -0.023130, 
-1.038760, 0.708340, 0.848490, -0.562800, 0.795940, 0.309340, -0.954600, 0.182340, 
0.201570, 0.008180, -0.242230, 0.565950, 0.605620, 0.110880, 0.085020, -0.246280, 
0.311430, -0.301040, -0.457960, -0.072530, -0.400600, -0.264610, 0.913450, -0.152570, 
-0.302950, -0.321220, -0.122920, 0.391980, 0.478450, 0.093580, 0.314200, -0.633130, 
0.348390, -0.213890, 0.717720, -0.124100, -0.013430, -0.364490, -0.259140, -0.447380, 
0.158470, 0.180030, 0.113690, 0.164620, 0.234760, 0.140680, 0.162540, 0.158290, 
-0.135130, -0.160000, -0.234910, -0.083890, -0.134780, -0.135090, -0.131030, -0.115290, 
-0.426220, 0.087880, -0.086100, 0.222860, 0.301240, -0.230520, -0.489700, 0.312980, 
-0.550660, -0.159740, -0.730180, 0.460110, -0.798850, 0.356310, 0.970790, 0.674160, 
-0.154970, -0.143550, -0.137170, -0.165960, -0.168990, -0.159580, -0.154880, -0.144750, 
-0.466010, 0.466190, -0.364560, -1.022380, -0.981320, -2.642290, 0.107560, 0.422520, 0.425620, 0.251520, 
-0.828310, -0.317240, 0.280710, -0.112450, 0.268210, 1.053640, -1.026960, -0.001140, 0.012670, -1.083970, 

-0.335050, 0.695420, 0.976570, 0.770530, 0.713780, 0.493860, -0.635230, -0.212550, 0.907100, -0.866800, 
-0.408970, -0.275680, 0.311510, 1.045020, 0.264430, -0.852390, 0.257290, -0.773280, -2.084590, 0.377890, 

0.496960, 0.337990, 0.111760, 0.228320, 0.744350, -0.344990, 0.194270, -0.256870, -0.193910, -0.156340, 
2.149990, -2.732470, 0.152330, -2.607870, 1.084700, -0.632700, 0.053560, -0.270340, 4.553410, 1.174780, 

0.648080, -0.023790, -0.110640, -0.935760, 0.268250, 0.184980, 0.560660, -0.573550, -0.854030, -0.575530, 
-0.855150, -0.292920, -0.060050, 2.215450, -0.261550, -0.838340, 0.541830, 0.461990, -0.277090, 0.982630, 

0.558980, 0.064990, 0.927430, -0.019490, -0.023830, 0.094470, 0.001010, -0.586120, 0.128080, 0.767140, 
-0.118530, -0.053710, 0.103060, -0.043950, 0.773370, -0.070000, 0.132530, 0.093130, 0.446760, 0.077150, 

-1.233260, -0.711550, 0.146430, -1.177830, 0.750610, -2.296900, -0.776440, -0.255880, 0.793290, 0.919680, 
-0.476360, -0.857520, -0.403730, -2.478650, 0.534140, -0.769370, -0.924010, -1.042210, -0.898190, 0.772730, 

-0.444630, 0.081760, 0.677360, -0.751250, -0.097530, 0.709560, -0.427570, 0.396830, -0.789910, -0.981190, 
-0.286170, -0.249590, 0.332450, -0.366400, 0.336750, -0.690910, -0.048440, 0.540190, -0.303170, 0.596670, 

0.338930, 0.401870, 1.016560, 0.242610, -1.679240, 0.824110, -0.561420, 0.612460, -1.334580, -0.552930, 
-1.805580, 0.323320, 0.558030, -0.123250, 0.131650, -0.269690, 1.233000, 0.732630, 1.604040, 0.541930, 

-0.824740, 0.535930, -0.228920, -0.990260, -0.081640, -0.342890, -0.735650, -0.699030, -0.766120, 0.993050, 
0.064440, -2.035240, -0.674540, -0.804140, -0.505340, 0.269940, -0.694910, -0.037790, 0.011230, -0.754320, 

0.894620, -0.092400, -0.682950, -0.078340, -0.107840, 0.158660, -0.256360, -1.009010, -0.161810, 0.077160, 
-2.723250, 0.518140, 1.162350, 0.529740, 1.105980, 0.525120, -0.010470, 0.127540, -3.146270, -0.377410, 

0.559820, 0.584460, 0.069740, 0.863080, 0.546130, 0.517770, 0.964420, 0.200890, -0.191890, -0.746110, 
-0.847940, -4.947510, 0.410710, 2.709520, -0.135710, -0.716420, 0.632500, -0.638860, -0.131560, -0.407390, 

0.227920, 0.384150, 0.186500, 0.485160, -0.931180, -2.455930, 0.861510, -0.938570, -0.567030, -1.028870, 
-2.071870, -0.125740, 0.029010, 0.311980, 0.920070, 1.085290, -0.439670, -0.344120, -2.217100, -1.337560, 

-0.300090, 0.246080, 0.298620, 0.098590, -0.419210, 0.585670, -0.534250, 0.551340, -0.552820, -0.680150, 
-1.508480, 0.371980, -0.204330, -0.235510, 0.941700, -0.308840, -0.086550, -0.050390, -0.312680, -0.710600, 

0.132490, 0.071480, 0.084230, 0.109640, -0.217210, 0.040070, 0.016750, -0.464340, 0.188480, 0.174970, 
0.143840, 0.021210, 0.418890, -0.156430, 0.096470, -0.107830, 0.264230, 0.128690, 0.402290, 0.002420, 

-1.195280, 5.289650, -0.372560, -0.552300, 0.723180, -0.329700, 0.328930, -0.531980, -0.541860, 1.049650, 
0.800620, -0.294920, -0.042960, -1.044070, 
0.000590, -0.504040, 3.769670, 0.248670, 0.587620, -0.602390, 0.272190, -0.406260, 0.558160, -0.162050, 
2.531840, 0.259940, -1.145080, 0.868060, 
0.392740, -2.432550, -1.196020, 2.839400, -0.200550, 1.931200, 0.218080, 2.884820, 1.375390, 0.509670, 
0.607130, 2.959280, -0.481220, 0.029190, 
-3.630430, -0.416370, -1.366250, -0.255540, 0.265230, 0.444630, 0.020600, -0.087590, -0.455690, -2.617930, 
-2.917070, -1.240750, 1.031840, 1.341080, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[47] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, 0.328170, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -0.075110, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, 0.734240, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.159030, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.627740, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, -0.867920, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -0.933290, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 0.381210, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, -0.482830, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, -0.034820, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, -0.057580, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, -0.380630, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, 0.455290, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, -0.465910, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, 0.156420, 8,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, -0.500580, 8,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 17 (noName) */
      0.0, 0.287440, 8,
       &Sources[64] , 
       &Weights[64] , 
      },
    { /* unit 18 (noName) */
      0.0, 0.049070, 8,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 19 (noName) */
      0.0, -0.815120, 8,
       &Sources[80] , 
       &Weights[80] , 
      },
    { /* unit 20 (noName) */
      0.0, -2.840450, 8,
       &Sources[88] , 
       &Weights[88] , 
      },
    { /* unit 21 (noName) */
      0.0, -0.157590, 8,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 22 (noName) */
      0.0, 0.560480, 8,
       &Sources[104] , 
       &Weights[104] , 
      },
    { /* unit 23 (noName) */
      0.0, -0.078920, 8,
       &Sources[112] , 
       &Weights[112] , 
      },
    { /* unit 24 (noName) */
      0.0, 0.081160, 8,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 25 (noName) */
      0.0, -0.048080, 8,
       &Sources[128] , 
       &Weights[128] , 
      },
    { /* unit 26 (noName) */
      0.0, -0.002980, 8,
       &Sources[136] , 
       &Weights[136] , 
      },
    { /* unit 27 (noName) */
      0.0, 0.030760, 8,
       &Sources[144] , 
       &Weights[144] , 
      },
    { /* unit 28 (noName) */
      0.0, -0.065130, 8,
       &Sources[152] , 
       &Weights[152] , 
      },
    { /* unit 29 (noName) */
      0.0, -0.122600, 20,
       &Sources[160] , 
       &Weights[160] , 
      },
    { /* unit 30 (noName) */
      0.0, -0.793010, 20,
       &Sources[180] , 
       &Weights[180] , 
      },
    { /* unit 31 (noName) */
      0.0, 0.226410, 20,
       &Sources[200] , 
       &Weights[200] , 
      },
    { /* unit 32 (noName) */
      0.0, 0.466600, 20,
       &Sources[220] , 
       &Weights[220] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.136680, 20,
       &Sources[240] , 
       &Weights[240] , 
      },
    { /* unit 34 (noName) */
      0.0, -0.535720, 20,
       &Sources[260] , 
       &Weights[260] , 
      },
    { /* unit 35 (noName) */
      0.0, -0.544720, 20,
       &Sources[280] , 
       &Weights[280] , 
      },
    { /* unit 36 (noName) */
      0.0, 0.092290, 20,
       &Sources[300] , 
       &Weights[300] , 
      },
    { /* unit 37 (noName) */
      0.0, 0.523650, 20,
       &Sources[320] , 
       &Weights[320] , 
      },
    { /* unit 38 (noName) */
      0.0, 0.029020, 20,
       &Sources[340] , 
       &Weights[340] , 
      },
    { /* unit 39 (noName) */
      0.0, 0.341840, 20,
       &Sources[360] , 
       &Weights[360] , 
      },
    { /* unit 40 (noName) */
      0.0, 0.196010, 20,
       &Sources[380] , 
       &Weights[380] , 
      },
    { /* unit 41 (noName) */
      0.0, -0.724750, 20,
       &Sources[400] , 
       &Weights[400] , 
      },
    { /* unit 42 (noName) */
      0.0, -0.061270, 20,
       &Sources[420] , 
       &Weights[420] , 
      },
    { /* unit 43 (noName) */
      0.0, 0.028500, 14,
       &Sources[440] , 
       &Weights[440] , 
      },
    { /* unit 44 (noName) */
      0.0, -0.907590, 14,
       &Sources[454] , 
       &Weights[454] , 
      },
    { /* unit 45 (noName) */
      0.0, 0.267200, 14,
       &Sources[468] , 
       &Weights[468] , 
      },
    { /* unit 46 (noName) */
      0.0, -0.750350, 14,
       &Sources[482] , 
       &Weights[482] , 
      }

  };



int classify35(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[8] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8}; /* members */

  static pUnit Hidden1[20] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28}; /* members */

  static pUnit Hidden2[14] = {Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42}; /* members */

  static pUnit Output1[4] = {Units + 43, Units + 44, Units + 45, Units + 46}; /* members */

  static int Output[4] = {43, 44, 45, 46};

  for(member = 0; member < 8; member++) {
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

  for (member = 0; member < 14; member++) {
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
