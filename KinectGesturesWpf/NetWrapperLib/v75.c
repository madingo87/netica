/*********************************************************
  c:\temp\v75.c
  --------------------------------------------------------
  generated at Fri Nov 27 17:21:39 2015
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
  static UnitType Units[55];
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
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 

Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 

Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 

Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 

Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 

Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, 


  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.072580, 1.184820, -0.717970, -1.014310, -0.804030, -0.042650, -0.909810, 0.154440, 
1.288350, -0.459640, -0.536690, -0.117570, -1.318270, -1.342780, 0.442380, 0.678560, 
0.251730, -0.193530, -1.380610, -2.182440, -0.788200, 0.839960, 0.320790, 0.745240, 
1.048770, 1.038990, -2.438970, -2.731080, 2.322110, -0.789970, -0.806330, 0.484580, 
1.253600, -0.778150, -1.092390, 0.100600, -2.245690, 0.205530, 2.291440, 0.608740, 
0.810550, 0.137270, -0.432830, 0.267610, 1.657880, -1.819790, -1.031130, -0.360040, 
0.071810, -0.485760, -0.418100, -1.036210, 2.554010, -0.832270, -0.663610, 1.364580, 
0.267780, -0.009400, 0.802050, 0.698730, -0.262990, -1.874790, -0.871650, 0.871200, 
-1.061060, -0.930610, 0.280990, -0.459150, -0.743950, 1.750450, 0.620040, 1.666670, 
1.616180, 0.880270, -0.359050, 0.703310, -2.824270, -1.470420, -0.773940, -1.962740, 
0.458220, 0.509500, -0.209770, -1.748270, -1.128880, -2.454610, 0.408600, 1.772300, 
-1.247790, 0.900670, 0.746750, -0.817080, 2.040020, -1.314020, -0.676920, 0.209440, 
1.089730, -0.727570, -0.335970, -0.317210, -1.256160, 0.277700, 1.752840, 0.325980, 
0.879500, -0.273160, -0.166650, 0.347670, -2.759590, 1.620590, 0.722170, -0.428110, 
-1.287630, -0.470420, 0.358820, -0.165900, 1.452610, 1.348000, 0.338470, 1.026570, 
-0.707510, 0.564830, 0.287320, -0.332200, 2.003930, 1.097860, 0.691950, -2.300940, 
1.476670, 0.254050, 0.343520, -0.733130, -2.377130, 0.054360, 0.035620, -0.630890, 
1.668260, -0.617030, -0.233430, 0.019810, 0.453250, 0.192360, 0.656010, -2.053730, 
-0.706510, 0.632120, 0.875680, 1.389760, 0.312880, -0.824660, -0.365200, -0.264600, 
-0.846280, -0.128700, 0.060480, 0.643090, 2.035320, -0.551760, -0.938760, -0.425530, 
-0.255580, 0.213870, 0.077050, -0.047710, 0.409020, 0.156240, 0.388350, 0.212450, 0.219900, -0.192230, 
0.083180, 0.058450, 0.290570, 0.143420, 0.334070, -0.014930, -0.005570, 0.056170, 0.135890, 0.108740, 

0.139650, -1.402770, -0.693760, -0.866610, -1.202820, -0.030490, 0.272350, 0.299020, 0.710210, -0.651400, 
-0.456260, 1.583440, -0.729280, -0.876930, 1.578250, 1.278140, -0.966560, -0.300820, 1.277570, 1.143230, 

-1.494290, 1.267880, -1.643860, -2.151940, 1.239910, 0.053750, -0.216630, 1.406660, 0.066750, 0.696970, 
1.472160, -0.711740, 0.717550, 0.047930, -1.035400, -2.031210, -0.175590, -1.138340, 0.308670, -1.277280, 

-0.400190, -0.191870, -1.285350, -0.807440, 0.248690, 0.635440, -0.310450, 0.675330, -0.533810, 0.463680, 
-0.242950, 0.502070, 0.255950, -0.034750, -0.239240, 0.623760, -0.177910, 0.696240, 1.279980, 0.335070, 

0.814050, 0.219560, -0.174910, -0.660210, -0.567680, 0.271010, -1.276370, 0.287390, -0.583010, 2.435320, 
-0.003600, -0.364390, -0.281060, 0.447050, -1.825370, -0.489020, 1.339550, 0.535350, 0.067410, -0.180610, 

-1.541340, -0.806910, -0.525470, 2.077210, 0.727020, 0.414350, 0.652020, -1.143960, -1.183730, -3.105510, 
-2.084170, -0.339740, 0.736110, -0.843220, 0.487240, 2.461850, -1.303650, 1.630330, -0.111140, 0.693600, 

0.801280, 0.329030, 0.979690, 1.155740, -0.419770, 0.804130, 0.402400, 0.146160, -0.627700, 0.537960, 
0.016820, -0.100930, -0.613730, 0.109740, -0.492060, -0.061300, 0.839700, 0.290810, -0.646370, 0.431860, 

0.548430, 0.219340, 1.047390, 1.184900, -1.027430, 0.777620, -1.043720, -0.696800, -0.307210, 0.425080, 
-1.802020, -0.794630, 0.447480, 1.542100, -0.647750, 1.878010, 1.551230, 2.046830, -1.001610, 0.789090, 

-0.565830, 0.925310, 0.166930, -0.982730, 1.321260, -0.232390, 0.036930, 0.400300, 0.339060, 0.517150, 
0.962370, -1.102260, 0.573150, 0.680770, -0.779350, -1.798990, 0.377470, -0.503320, -0.048220, -1.147230, 

1.708100, -0.176940, 1.537620, 1.686030, -1.686550, 0.465100, 0.782650, -0.115040, 0.071010, 0.020940, 
0.061520, 0.714440, -1.506070, -0.492470, 0.428710, 0.469580, 0.113860, 0.242050, -0.629630, 1.112010, 

0.259440, -1.023550, -0.175420, 0.563170, -0.869930, 0.196650, -0.466130, -0.734720, -0.077810, -0.934840, 
-1.459840, 0.324280, -0.187110, -0.552060, 0.735050, 2.244570, -0.159060, 1.141990, 0.036900, 1.021890, 

1.402470, -0.573090, 0.986310, 0.704860, -2.021110, 0.296950, 1.187190, 0.316700, 0.590760, -0.358120, 
0.786300, 1.715700, -1.276320, -0.908290, 0.775120, 0.032630, -0.251930, -1.020630, 0.115710, 1.324690, 

-0.482210, -0.238360, 0.469520, -0.823730, 0.682930, -1.562920, 0.108520, -0.711890, 1.964090, -0.835040, 
-0.119010, -0.572610, 0.611220, 0.758150, 1.168300, -0.573780, -0.383290, -1.216340, -0.414270, -0.604060, 

-0.143330, -0.094830, -1.042310, -2.332690, 0.974250, -0.697930, -1.474310, 0.433040, 0.822120, 2.379920, 
-0.025960, -0.376710, 0.316620, 0.917580, -0.603310, -0.151280, 0.627070, -0.022170, 0.804830, -0.613530, 

-1.074320, 0.009810, -1.319890, 0.103510, 0.285140, 0.772960, 2.132000, 0.965770, -0.834060, -2.480290, 
1.213560, 1.369280, -0.121500, -2.572320, 0.580910, -0.323350, -2.456940, -1.212070, 0.368060, -0.054320, 

0.898450, 0.522090, 0.989880, 1.442280, -1.184350, 1.179540, 0.480340, 0.389990, -1.048150, 0.687480, 
0.159710, 0.100470, -0.756990, -0.071180, -0.795760, 0.070420, 0.960780, 0.885720, -0.627360, 0.640800, 

0.408840, 0.372560, -0.048850, -0.033300, -0.659570, 0.804610, 0.977010, 1.389040, -0.204840, 0.702000, 
1.471830, 0.993830, -0.538400, -1.054930, -0.890900, -1.167740, 0.034720, -0.847290, 0.641040, 0.196820, 

-0.164430, -0.042160, 0.448200, 0.969560, -0.551430, 0.404830, 2.409480, 0.709040, 0.313730, -2.194140, 
1.507030, 0.995500, -0.288760, -1.609060, 1.055230, -0.919170, -1.311740, -1.417380, -0.496960, 0.800490, 

0.108990, -0.393520, 1.365280, 0.539590, 0.541450, -1.266500, -0.581080, -1.427860, 1.133680, -0.700740, 
-1.225960, -0.997020, 0.205370, 1.250470, 0.595700, 0.641760, 0.447090, 0.517280, -0.771340, -0.312270, 

-1.097370, 0.756270, 0.088990, -1.225720, 1.863270, -1.085330, -0.736620, 0.034450, 1.033730, 0.187550, 
-0.232740, -1.673330, 1.083210, 1.769680, -0.043720, -0.795240, 0.602560, -0.110100, -0.324540, -1.151450, 

-0.420220, 1.144560, 2.924240, -0.395660, -1.298050, -2.437640, -2.411870, -5.447830, 1.008660, -2.325160, 
-2.478600, 0.239270, 1.450560, 0.546890, 3.722580, -3.165520, 0.991020, 2.545980, -2.086430, 0.181810, 

-0.675580, 1.331780, -1.465280, -0.148350, -1.365040, 3.021780, -1.871080, 1.893260, -1.219610, -1.771440, 
2.143930, -2.191700, 1.358270, 0.355740, -2.284240, -2.572090, -3.860260, -3.138270, 2.384520, 1.503070, 

-1.428960, 2.316620, -3.401340, -0.959790, 3.703610, -4.415190, 0.021990, -0.214910, -3.204460, 1.826100, 
1.083080, 2.734840, -0.501090, 1.858670, -4.365090, -0.683190, -0.215940, -3.930310, -0.507220, -4.099390, 

-0.763140, -0.977310, -1.980560, -0.341470, -3.061350, 4.524840, 0.085520, -0.402910, -1.982080, 0.753270, 
0.546300, 0.158480, -3.392210, -4.275950, 4.068560, 0.687380, -0.185460, 2.470000, -1.761040, -3.304950, 

-0.428530, -2.888660, -1.894140, -3.875810, -1.368670, -1.912230, 0.929960, 0.185140, 0.751160, 1.716460, 
-1.741360, 0.972650, 1.983550, -2.789170, -2.103560, 0.800940, -0.671340, 1.480470, 2.557900, 0.644210, 

-0.658560, -3.765480, 3.016350, 0.321830, 2.197910, -0.850920, -0.039130, 0.403030, 1.807920, -2.727770, 
-2.192540, -3.915370, -2.533700, 0.423150, -1.119990, 1.035600, -0.085090, -2.065750, -1.546300, 1.847960, 


  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[55] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -0.332260, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -0.036650, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, 0.131140, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.380840, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, 0.621510, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.183510, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -0.113320, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 0.885920, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 1.125050, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, -0.511710, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, 0.384890, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, 0.079050, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.865740, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.659720, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, 0.424400, 8,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, -0.654450, 8,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 17 (noName) */
      0.0, -0.268350, 8,
       &Sources[64] , 
       &Weights[64] , 
      },
    { /* unit 18 (noName) */
      0.0, 0.441970, 8,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 19 (noName) */
      0.0, -0.371600, 8,
       &Sources[80] , 
       &Weights[80] , 
      },
    { /* unit 20 (noName) */
      0.0, 0.152790, 8,
       &Sources[88] , 
       &Weights[88] , 
      },
    { /* unit 21 (noName) */
      0.0, -0.718000, 8,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 22 (noName) */
      0.0, -0.372640, 8,
       &Sources[104] , 
       &Weights[104] , 
      },
    { /* unit 23 (noName) */
      0.0, 0.272120, 8,
       &Sources[112] , 
       &Weights[112] , 
      },
    { /* unit 24 (noName) */
      0.0, -0.045550, 8,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 25 (noName) */
      0.0, 0.198290, 8,
       &Sources[128] , 
       &Weights[128] , 
      },
    { /* unit 26 (noName) */
      0.0, 1.348770, 8,
       &Sources[136] , 
       &Weights[136] , 
      },
    { /* unit 27 (noName) */
      0.0, -0.382400, 8,
       &Sources[144] , 
       &Weights[144] , 
      },
    { /* unit 28 (noName) */
      0.0, 1.236410, 8,
       &Sources[152] , 
       &Weights[152] , 
      },
    { /* unit 29 (noName) */
      0.0, 0.257900, 20,
       &Sources[160] , 
       &Weights[160] , 
      },
    { /* unit 30 (noName) */
      0.0, 0.727540, 20,
       &Sources[180] , 
       &Weights[180] , 
      },
    { /* unit 31 (noName) */
      0.0, -0.430170, 20,
       &Sources[200] , 
       &Weights[200] , 
      },
    { /* unit 32 (noName) */
      0.0, 0.153400, 20,
       &Sources[220] , 
       &Weights[220] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.309580, 20,
       &Sources[240] , 
       &Weights[240] , 
      },
    { /* unit 34 (noName) */
      0.0, -0.011290, 20,
       &Sources[260] , 
       &Weights[260] , 
      },
    { /* unit 35 (noName) */
      0.0, -0.025410, 20,
       &Sources[280] , 
       &Weights[280] , 
      },
    { /* unit 36 (noName) */
      0.0, 0.868190, 20,
       &Sources[300] , 
       &Weights[300] , 
      },
    { /* unit 37 (noName) */
      0.0, -0.718040, 20,
       &Sources[320] , 
       &Weights[320] , 
      },
    { /* unit 38 (noName) */
      0.0, -0.134350, 20,
       &Sources[340] , 
       &Weights[340] , 
      },
    { /* unit 39 (noName) */
      0.0, 0.582430, 20,
       &Sources[360] , 
       &Weights[360] , 
      },
    { /* unit 40 (noName) */
      0.0, 0.579920, 20,
       &Sources[380] , 
       &Weights[380] , 
      },
    { /* unit 41 (noName) */
      0.0, 0.228390, 20,
       &Sources[400] , 
       &Weights[400] , 
      },
    { /* unit 42 (noName) */
      0.0, 0.177740, 20,
       &Sources[420] , 
       &Weights[420] , 
      },
    { /* unit 43 (noName) */
      0.0, -0.248460, 20,
       &Sources[440] , 
       &Weights[440] , 
      },
    { /* unit 44 (noName) */
      0.0, 0.173990, 20,
       &Sources[460] , 
       &Weights[460] , 
      },
    { /* unit 45 (noName) */
      0.0, 0.240750, 20,
       &Sources[480] , 
       &Weights[480] , 
      },
    { /* unit 46 (noName) */
      0.0, -0.567160, 20,
       &Sources[500] , 
       &Weights[500] , 
      },
    { /* unit 47 (noName) */
      0.0, -0.289600, 20,
       &Sources[520] , 
       &Weights[520] , 
      },
    { /* unit 48 (noName) */
      0.0, -0.217640, 20,
       &Sources[540] , 
       &Weights[540] , 
      },
    { /* unit 49 (noName) */
      0.0, -0.189930, 20,
       &Sources[560] , 
       &Weights[560] , 
      },
    { /* unit 50 (noName) */
      0.0, -0.109040, 20,
       &Sources[580] , 
       &Weights[580] , 
      },
    { /* unit 51 (noName) */
      0.0, -0.883130, 20,
       &Sources[600] , 
       &Weights[600] , 
      },
    { /* unit 52 (noName) */
      0.0, -0.585130, 20,
       &Sources[620] , 
       &Weights[620] , 
      },
    { /* unit 53 (noName) */
      0.0, -0.681860, 20,
       &Sources[640] , 
       &Weights[640] , 
      },
    { /* unit 54 (noName) */
      0.0, -0.486130, 20,
       &Sources[660] , 
       &Weights[660] , 
      }

  };



int classify75(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[8] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8}; /* members */

  static pUnit Hidden1[20] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28}; /* members */

  static pUnit Hidden2[20] = {Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48}; /* members */

  static pUnit Output1[6] = {Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54}; /* members */

  static int Output[6] = {49, 50, 51, 52, 53, 54};

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
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 20; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 6; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for(member = 0; member < 6; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
