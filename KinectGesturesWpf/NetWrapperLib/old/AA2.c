/*********************************************************
  c:\temp\AA2.c
  --------------------------------------------------------
  generated at Mon Oct 12 16:43:13 2015
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
  static UnitType Units[52];
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

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 

Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 


  };

  /* Weigths definition section */
  static float Weights[] =  {
3.542310, 1.106330, 4.165580, -3.027380, -2.151860, 0.567930, 2.870720, 1.652800, 5.002200, -1.296840, 
-3.591050, -1.770900, -1.543750, 0.607240, 
1.608150, -1.251460, 3.102270, -0.603960, 1.858080, -2.023520, -2.738610, -2.853050, -1.514060, -2.008520, 
0.627080, -2.373640, -0.360470, 0.984870, 
-0.193930, 0.489900, 0.603070, -0.662280, -0.070890, -0.347530, -0.442240, 0.129450, 0.041830, -0.874680, 
-1.106650, -0.113120, -0.465920, -0.227860, 
-1.460390, 0.865650, -5.106730, -0.412030, -0.272070, -1.508230, 1.814140, 2.929430, -0.078760, 1.398280, 
-3.920550, 0.144160, -1.967440, 3.304420, 
1.141340, 0.743090, 3.228200, -2.954550, -3.532880, 0.561290, -2.411250, 0.024320, 0.047460, -2.009940, 
-2.367250, 1.953090, -1.225760, -0.238460, 
-0.000910, 0.148880, 0.225350, -0.022710, -0.016200, 0.024670, 0.036210, -0.089880, 0.039690, -0.164700, 
-0.109330, 0.016010, -0.020310, -0.345120, 
1.880250, 1.917440, -2.977220, 4.021620, -0.183770, 0.111980, -0.188110, 2.837660, 1.406580, -0.515050, 
2.197630, -1.870580, -1.595020, -0.858680, 
-1.300050, -2.026730, 0.278220, 2.680990, 0.787490, 1.077520, 1.098830, -1.729120, -3.386750, 3.894630, 
1.995280, 0.382870, -0.625290, -2.759960, 
-0.405570, 0.554090, -0.047670, -0.301730, 0.964750, 0.004900, -0.188540, -1.497560, 1.080270, -3.931960, 
1.302870, -1.479480, 1.278650, 0.386160, 
-2.129290, -4.250860, -4.490050, 0.035950, 1.402080, 1.153860, 0.390100, 3.021290, 1.559230, 3.230780, 
-1.343490, 3.270280, 3.122240, 1.863540, 
0.247820, -0.417560, 1.256910, -0.023570, 0.438260, -0.110470, -0.010670, -0.446960, 0.625960, 1.594910, 
0.771160, 0.988900, 0.353540, -1.153240, 
1.074500, 2.177510, -0.341820, 1.159990, -2.924370, 1.021320, -0.131140, 1.353310, -2.676510, -0.556770, 
-1.124270, -3.158000, 0.180720, 4.260180, 
0.016430, -0.076440, -0.223310, 0.003430, -0.009120, 0.482460, 0.144210, 0.000340, 0.079540, 0.004340, 
-0.003840, 0.011800, -0.004500, 0.076680, 
0.545370, -1.973180, 1.988130, -0.403310, 0.713270, -1.005170, -2.086630, -1.749350, -0.104790, 0.436180, 
0.418020, -0.224200, 0.933790, 0.048390, 
1.340110, 0.261590, 2.457640, -1.972620, 2.457350, -4.016060, 0.147060, 1.909680, -3.459830, 2.327350, 
-3.264570, 0.073110, -0.616870, 2.563450, 
-1.541330, 3.274750, -1.921200, 0.683590, -2.849420, 0.088310, 2.340800, 1.854600, 1.545370, -2.006050, 
-3.372770, -3.482760, 1.462970, -2.392140, 
0.463070, -0.228720, -1.083880, 0.809510, -0.908070, -0.185850, 0.706420, 0.399520, -0.150780, 0.374760, 
-0.159550, 0.209310, -1.063800, -0.120400, 
0.634670, -0.493140, -0.469080, 0.322360, -1.249600, -0.807600, 0.214800, 0.700170, -0.159780, 0.396400, 
0.174420, 0.627590, 0.559170, -0.493380, 
-1.001190, -4.481410, 0.816500, 4.552440, 2.456310, 4.498960, 1.474480, -3.026460, -1.512460, -4.352010, 
5.796180, -4.194140, -2.772070, 1.610430, 
1.868140, -0.473560, 0.358660, 1.090310, -0.455210, 0.977070, 2.148830, -2.095480, 3.915510, -1.630370, 
0.871350, -0.072540, 1.649370, -2.413090, 
-5.335290, -1.837480, -1.129430, 1.997080, -3.817200, -0.528370, 1.853290, 2.334230, -2.087720, 2.884500, 
0.327560, 1.415680, 2.273060, -1.361920, 2.715690, -3.584980, 2.610600, 1.581890, 0.913550, -1.382780, 

2.227140, 1.515470, 0.216580, -1.449960, 3.207420, 0.005780, -3.055780, -2.063970, 0.635000, -3.087290, 
-0.038850, 0.804920, 1.305180, 0.651540, 1.461050, 0.684990, 0.559120, 1.095140, -3.286080, 0.430860, 

0.285330, -3.630260, -0.393990, 2.286770, -0.774000, 0.000220, 3.370580, -0.175540, -0.913450, -0.025340, 
-1.247820, 0.999490, 0.999030, -1.519290, -3.628780, 2.306380, 0.872260, 1.160100, -0.320640, 1.119590, 

-2.381360, -0.338670, 0.094690, 2.152570, -1.073730, 0.033880, 1.718300, 1.125890, -0.551150, 0.764340, 
-0.150460, 2.848940, 0.429530, -1.084940, 0.169760, -1.691650, 0.351610, 0.089950, 0.253680, -2.424230, 

0.233240, 3.409070, 0.461720, -1.361510, 0.501180, 0.009990, -2.749740, 0.025310, -0.130390, 0.325480, 
0.475360, -1.227920, 0.546020, 1.715870, 3.397150, -2.698450, -1.035820, -0.349490, 0.300790, -0.282660, 

1.017990, 2.493660, -0.330440, -0.664540, -2.728870, 0.005230, 0.532030, -0.036780, 1.763880, -1.588270, 
-0.005780, 0.733330, -0.724360, 1.287820, -1.181560, 0.013380, -0.647940, -2.751620, 6.629040, 1.598700, 

0.341540, 0.119550, 0.245510, 0.339950, 0.363420, 0.258290, 0.276990, 0.212920, 0.279900, 0.291300, 
0.270120, 0.041660, 0.468110, 0.201700, 0.178580, 0.455660, 0.335080, 0.400180, 0.029670, 0.310170, 

-1.377660, -0.532660, -0.881570, -4.094230, -0.657050, 0.000670, -0.409690, 3.197320, 0.313660, 1.308290, 
1.823390, -4.745390, 0.493460, 0.877080, -1.669720, -1.815890, 0.073930, 0.248240, 2.946950, 2.511820, 

3.022490, -0.417880, 0.208830, 0.909550, 1.492040, -0.031090, 0.872750, -4.191060, 0.772920, -2.055680, 
-2.147460, 2.154750, 1.684260, -1.493560, -1.000250, 3.782450, 0.396590, -0.381790, 1.654910, 0.281870, 

-0.947760, -1.145020, -0.034890, 1.083040, 0.383890, 0.022240, -0.518550, -0.219950, -2.913300, 3.502820, 
-0.368040, -3.198730, 0.302450, 0.720160, 4.492400, -0.332850, 0.242210, 1.510590, -6.237470, -1.350040, 

-7.340070, 1.273630, -6.458380, -5.706540, 2.646880, 5.013330, -2.381610, 6.337970, 0.435320, -6.858670, 

-6.278330, 4.954790, 6.054590, -2.684420, -6.076320, -3.228520, -1.277700, -2.360220, 0.961100, -5.581910, 

3.433360, -4.363010, 2.126140, 3.211640, -4.002620, -4.526780, -2.105260, -4.972470, -0.638880, 4.254720, 

2.519820, -8.081580, 2.694880, -0.287950, -4.490480, 5.857870, -1.775000, 3.808910, -1.048910, -6.641800, 

-5.314650, 0.872310, -4.829450, -2.652940, 3.169260, -3.887810, -1.633520, -6.359290, 1.976020, 5.373500, 

3.466730, 0.478010, -4.489090, 4.560350, 1.886440, 3.668860, -1.883550, -7.822300, -0.594230, -5.712990, 

5.014850, 0.106170, -2.783160, -0.487810, 1.711870, -4.039360, -2.015750, 4.650660, -9.872040, 2.877220, 


  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[52] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -0.318770, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, 4.229710, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, 4.802850, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, -0.807060, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -3.601640, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 2.535020, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -0.779900, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 3.817100, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 1.259350, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, 4.663990, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 11 (noName) */
      0.0, 3.969700, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 12 (noName) */
      0.0, 2.351910, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 13 (noName) */
      0.0, -1.269110, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 14 (noName) */
      0.0, -1.258430, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 15 (noName) */
      0.0, -4.730090, 14,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 16 (noName) */
      0.0, 3.492550, 14,
       &Sources[14] , 
       &Weights[14] , 
      },
    { /* unit 17 (noName) */
      0.0, 1.128390, 14,
       &Sources[28] , 
       &Weights[28] , 
      },
    { /* unit 18 (noName) */
      0.0, 2.338380, 14,
       &Sources[42] , 
       &Weights[42] , 
      },
    { /* unit 19 (noName) */
      0.0, 2.867660, 14,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 20 (noName) */
      0.0, -0.063240, 14,
       &Sources[70] , 
       &Weights[70] , 
      },
    { /* unit 21 (noName) */
      0.0, -3.229400, 14,
       &Sources[84] , 
       &Weights[84] , 
      },
    { /* unit 22 (noName) */
      0.0, 0.999820, 14,
       &Sources[98] , 
       &Weights[98] , 
      },
    { /* unit 23 (noName) */
      0.0, 0.848100, 14,
       &Sources[112] , 
       &Weights[112] , 
      },
    { /* unit 24 (noName) */
      0.0, -2.124910, 14,
       &Sources[126] , 
       &Weights[126] , 
      },
    { /* unit 25 (noName) */
      0.0, -1.582380, 14,
       &Sources[140] , 
       &Weights[140] , 
      },
    { /* unit 26 (noName) */
      0.0, -0.997670, 14,
       &Sources[154] , 
       &Weights[154] , 
      },
    { /* unit 27 (noName) */
      0.0, 1.289990, 14,
       &Sources[168] , 
       &Weights[168] , 
      },
    { /* unit 28 (noName) */
      0.0, 1.280010, 14,
       &Sources[182] , 
       &Weights[182] , 
      },
    { /* unit 29 (noName) */
      0.0, -0.177420, 14,
       &Sources[196] , 
       &Weights[196] , 
      },
    { /* unit 30 (noName) */
      0.0, 2.387780, 14,
       &Sources[210] , 
       &Weights[210] , 
      },
    { /* unit 31 (noName) */
      0.0, 0.826290, 14,
       &Sources[224] , 
       &Weights[224] , 
      },
    { /* unit 32 (noName) */
      0.0, 0.722210, 14,
       &Sources[238] , 
       &Weights[238] , 
      },
    { /* unit 33 (noName) */
      0.0, 0.604160, 14,
       &Sources[252] , 
       &Weights[252] , 
      },
    { /* unit 34 (noName) */
      0.0, -3.171520, 14,
       &Sources[266] , 
       &Weights[266] , 
      },
    { /* unit 35 (noName) */
      0.0, -0.277220, 20,
       &Sources[280] , 
       &Weights[280] , 
      },
    { /* unit 36 (noName) */
      0.0, -0.640730, 20,
       &Sources[300] , 
       &Weights[300] , 
      },
    { /* unit 37 (noName) */
      0.0, -0.831810, 20,
       &Sources[320] , 
       &Weights[320] , 
      },
    { /* unit 38 (noName) */
      0.0, 0.073380, 20,
       &Sources[340] , 
       &Weights[340] , 
      },
    { /* unit 39 (noName) */
      0.0, -0.900260, 20,
       &Sources[360] , 
       &Weights[360] , 
      },
    { /* unit 40 (noName) */
      0.0, -2.101030, 20,
       &Sources[380] , 
       &Weights[380] , 
      },
    { /* unit 41 (noName) */
      0.0, 0.515040, 20,
       &Sources[400] , 
       &Weights[400] , 
      },
    { /* unit 42 (noName) */
      0.0, 0.627810, 20,
       &Sources[420] , 
       &Weights[420] , 
      },
    { /* unit 43 (noName) */
      0.0, -0.930440, 20,
       &Sources[440] , 
       &Weights[440] , 
      },
    { /* unit 44 (noName) */
      0.0, 0.795180, 20,
       &Sources[460] , 
       &Weights[460] , 
      },
    { /* unit 45 (noName) */
      0.0, -1.271820, 10,
       &Sources[480] , 
       &Weights[480] , 
      },
    { /* unit 46 (noName) */
      0.0, 0.140370, 10,
       &Sources[490] , 
       &Weights[490] , 
      },
    { /* unit 47 (noName) */
      0.0, -1.371440, 10,
       &Sources[500] , 
       &Weights[500] , 
      },
    { /* unit 48 (noName) */
      0.0, -1.692360, 10,
       &Sources[510] , 
       &Weights[510] , 
      },
    { /* unit 49 (noName) */
      0.0, -1.031520, 10,
       &Sources[520] , 
       &Weights[520] , 
      },
    { /* unit 50 (noName) */
      0.0, -2.718340, 10,
       &Sources[530] , 
       &Weights[530] , 
      },
    { /* unit 51 (noName) */
      0.0, -0.886970, 10,
       &Sources[540] , 
       &Weights[540] , 
      }

  };



int classifyAngleAdvanced2(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[14] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14}; /* members */

  static pUnit Hidden1[20] = {Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34}; /* members */

  static pUnit Hidden2[10] = {Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44}; /* members */

  static pUnit Output1[7] = {Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51}; /* members */

  static int Output[7] = {45, 46, 47, 48, 49, 50, 51};

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
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 10; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 7; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for(member = 0; member < 7; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
