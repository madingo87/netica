/*********************************************************
  c:\temp\v73.c
  --------------------------------------------------------
  generated at Fri Nov 27 16:29:04 2015
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
  static UnitType Units[59];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 

Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, 
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


  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.000960, -0.339590, -1.568260, 2.170840, 
-1.121100, 1.273200, 0.369300, -1.144920, 
1.507360, 1.445050, -1.148280, -1.247090, 
0.786010, -1.534540, 0.793280, 2.021230, 
0.692550, -1.367370, 0.632940, 1.781630, 
0.664500, 1.275530, -0.359710, -1.450160, 
-0.770940, -0.440350, -0.089550, 1.430400, 
1.106600, 0.453730, -0.995410, -0.780060, 
0.977090, 0.839130, -0.758700, -0.955630, 
-1.122640, -0.413180, 1.301500, 0.680900, 
1.065030, 0.847410, -1.019880, -0.898260, 
0.893040, -1.142110, -0.645420, 1.617580, 
-0.470300, 0.678910, 1.205960, -1.833750, 
0.095590, 0.465420, 0.734380, -1.509980, 
-1.081340, -0.163840, 1.231860, 0.445280, 
-0.993850, -0.460170, 0.635610, 0.984520, 
0.656130, 0.141440, 1.071010, -2.156670, 
0.083370, -0.524540, 0.007530, 0.883150, 
0.612660, -0.404210, -1.000070, 1.189070, 
-0.909220, 1.157370, 0.118490, -1.060430, 
-0.835450, -0.437860, 0.195190, 1.041220, 
1.177260, 0.330730, -1.206680, -0.646330, 
-1.127260, -0.418880, 0.985290, 0.820430, 
-0.603670, -0.889980, 0.366560, 1.226860, 
0.934940, 0.751020, -1.079710, -0.681680, 
-0.652680, 1.165430, 0.523770, -1.557100, 
-0.787170, 0.888140, 1.380010, -2.000090, 
-1.280990, -0.958450, 0.999890, 1.069200, 
0.362960, -0.697570, -0.153180, 0.978630, 
-0.300280, 0.614310, -0.082580, -0.906740, 
1.391430, -0.902690, -1.692280, -0.340260, 0.400390, -1.501080, 1.344290, -0.727730, -1.330850, 0.008860, 
-1.262780, 1.154230, -1.271020, -0.915930, -0.014920, 0.746170, -1.695260, 0.046580, 0.581310, -0.873610, 
0.767920, -0.556060, 0.600110, 1.252440, -1.035930, -1.131820, -1.213680, 1.372970, 0.113370, -0.814100, 

-0.075820, 0.020400, -0.330510, 0.323570, 0.326990, -0.256570, 0.276940, -0.539220, -0.379760, 0.650390, 
-0.414130, 0.046470, 0.105230, -0.042740, 0.530880, 0.446250, -0.086920, 0.178260, -0.147360, -0.072190, 
0.324870, -0.568810, 0.573450, 0.322810, -0.451780, -0.049520, 0.181050, 0.409640, 0.130770, -0.169570, 

-0.896090, 0.994150, 0.028250, -0.993380, -0.639280, 0.149670, -0.151130, -0.450820, -0.138190, 0.546620, 
-0.119720, -0.935940, 0.924270, 0.553900, 0.374550, 0.285670, 0.466670, -0.175500, -0.569410, 0.712290, 
0.005830, -0.472760, 0.322780, 0.006170, -0.215470, 0.876710, 1.055990, 0.137490, -0.326810, 0.375340, 

0.581200, -0.772500, -0.052600, 1.344020, 1.192010, -0.112730, 0.208700, -0.144330, -0.101210, 0.273440, 
-0.078240, 0.914850, -0.600260, -0.366390, 0.200910, 0.217160, -0.249530, 0.436670, 0.502640, -0.736500, 
0.192550, -0.112630, 0.239190, 0.239450, -0.122560, -0.709210, -0.690100, 0.161090, 0.595530, -0.480770, 

1.221110, -0.738180, -1.789800, -0.283330, 0.046910, -1.294950, 1.409120, -0.692830, -1.322840, 0.122800, 
-1.033470, 0.772910, -1.095050, -0.772930, 0.083520, 0.833750, -1.632850, 0.243420, 0.516260, -0.867980, 
0.909240, -0.521100, 0.541360, 1.036140, -0.989540, -1.234170, -1.160520, 1.357630, 0.356380, -0.854080, 

-0.647370, 0.728190, 1.287080, 0.359910, -0.186510, 1.153250, -0.657760, 0.498210, 0.930190, -0.391630, 
0.886760, -0.692960, 0.833400, 0.693770, -0.322240, -0.752490, 1.234890, -0.290740, -0.184710, 0.644060, 
-0.432570, 0.421670, -0.368120, -0.766320, 0.799730, 0.866850, 0.848580, -0.904240, -0.497880, 0.669530, 

-0.093280, -0.000440, -0.350940, 0.330470, 0.365390, -0.276500, 0.287550, -0.556950, -0.393420, 0.664320, 
-0.435660, 0.066020, 0.084060, -0.048580, 0.564080, 0.485430, -0.091620, 0.176080, -0.125990, -0.091880, 
0.338000, -0.600430, 0.570300, 0.335060, -0.473430, -0.077760, 0.173410, 0.443450, 0.140360, -0.176560, 

0.039840, 0.042840, 0.407490, -0.523450, -0.530750, 0.365540, -0.391070, 0.682870, 0.481290, -0.841050, 
0.527080, -0.154110, -0.064180, 0.102360, -0.707330, -0.612230, 0.141800, -0.206430, 0.132610, 0.152580, 
-0.426320, 0.723550, -0.730310, -0.432010, 0.545870, 0.141270, -0.163200, -0.566680, -0.209020, 0.257980, 

-0.879140, 0.695650, 1.363100, -0.269480, 0.405700, 1.301970, -0.998280, 0.630930, 1.040630, -0.506720, 
1.112050, -0.707170, 1.126370, 0.953840, 0.012110, -0.528360, 1.422970, -0.614410, -0.325170, 0.599650, 
-0.499370, 0.471670, -0.709610, -1.116790, 0.826340, 0.987660, 0.929330, -1.092210, -0.152510, 0.669550, 

-0.301960, 0.921650, -0.255250, -1.078870, -0.906550, -0.046570, 0.312540, -0.309910, -0.141710, 0.525430, 
-0.196750, -0.658640, 0.729950, 0.319170, 0.532500, 0.460270, 0.121330, -0.050340, -0.412060, 0.814240, 
0.371980, -0.354060, 0.519910, 0.352770, -0.170500, 0.786000, 0.887800, 0.519570, -0.221890, 0.374300, 

0.038810, 0.070410, 0.414080, -0.513410, -0.545800, 0.376190, -0.378230, 0.660770, 0.480750, -0.824060, 
0.507730, -0.168390, -0.061450, 0.102180, -0.673100, -0.604810, 0.152000, -0.268440, 0.128920, 0.160870, 
-0.418670, 0.714050, -0.725090, -0.415320, 0.548940, 0.138920, -0.143210, -0.519800, -0.236000, 0.252630, 

0.572540, -0.779910, -0.030700, 1.292740, 1.192550, -0.100240, 0.189180, -0.134550, -0.064780, 0.241480, 
-0.078390, 0.905020, -0.619980, -0.357060, 0.164940, 0.187970, -0.232580, 0.427890, 0.501420, -0.733180, 
0.170780, -0.119670, 0.204220, 0.220140, -0.086140, -0.698580, -0.679480, 0.136910, 0.561470, -0.461500, 

1.503930, -1.058680, -0.384400, 0.341960, 0.002190, -0.506660, 0.570660, 0.716880, 0.139230, -0.614460, 
0.078180, 1.467730, -1.339870, -0.712480, -0.568630, -0.407120, -1.001090, 0.317170, 1.180470, -0.785200, 
0.184790, 0.927970, -0.580860, 0.334570, 0.321090, -1.100940, -1.380160, 0.273690, 0.820920, -0.449570, 

-0.029930, 0.003600, -0.322290, 0.249090, 0.261520, -0.257800, 0.286440, -0.524870, -0.348640, 0.620010, 
-0.382200, 0.059000, 0.079620, -0.062440, 0.530510, 0.460000, -0.112690, 0.177770, -0.122780, -0.073050, 
0.340840, -0.577460, 0.545270, 0.322270, -0.426720, -0.059360, 0.159240, 0.394820, 0.113890, -0.169270, 

-0.644330, 0.827530, 0.087180, -1.448490, -1.322390, 0.122510, -0.272170, 0.205080, 0.093190, -0.373680, 
0.160220, -0.972070, 0.647320, 0.382140, -0.290720, -0.297710, 0.291590, -0.531600, -0.531170, 0.792190, 
-0.257440, 0.187810, -0.330400, -0.306350, 0.193370, 0.744640, 0.725240, -0.225290, -0.656260, 0.521650, 

-0.085590, 0.017550, -0.322360, 0.351590, 0.308340, -0.273820, 0.281840, -0.548060, -0.386320, 0.663250, 
-0.430040, 0.061960, 0.099880, -0.045120, 0.548160, 0.486810, -0.100770, 0.157150, -0.131730, -0.067470, 
0.345680, -0.584980, 0.599740, 0.327220, -0.439160, -0.067420, 0.179070, 0.427120, 0.126580, -0.181960, 

-0.443230, 0.356480, 0.840820, 0.224740, -0.124200, 0.764440, -0.525680, 0.339570, 0.557060, -0.344310, 
0.583240, -0.443160, 0.519940, 0.464610, -0.046330, -0.535830, 0.803790, -0.268850, -0.230740, 0.407710, 
-0.468910, 0.291190, -0.223220, -0.552090, 0.516060, 0.569230, 0.562110, -0.557990, -0.299770, 0.431840, 

0.023750, 0.049410, 0.408710, -0.536280, -0.526670, 0.361870, -0.395250, 0.678790, 0.465270, -0.836440, 
0.524290, -0.150460, -0.058530, 0.104840, -0.680210, -0.588430, 0.160760, -0.270670, 0.104970, 0.155150, 
-0.437530, 0.719620, -0.728780, -0.454180, 0.542040, 0.151420, -0.148680, -0.539290, -0.208160, 0.256540, 

0.720210, -0.886490, -0.033620, 0.966170, 0.803150, -0.021760, 0.070940, 0.408860, 0.112120, -0.438620, 
0.133670, 0.781190, -0.823090, -0.467650, -0.568980, -0.239290, -0.328550, 0.179050, 0.540700, -0.754060, 
-0.151370, 0.477070, -0.489980, -0.032760, 0.128240, -0.760840, -1.019680, -0.166840, 0.336590, -0.403850, 

-0.337560, 0.959030, -0.253770, -1.074610, -0.893480, -0.105760, 0.340700, -0.317110, -0.189070, 0.553420, 
-0.242290, -0.632520, 0.755780, 0.345770, 0.562850, 0.489360, 0.163000, -0.078440, -0.405060, 0.842230, 
0.400620, -0.339090, 0.548300, 0.390310, -0.287720, 0.769930, 0.893720, 0.557960, -0.209800, 0.404280, 

3.874990, 0.046980, -1.198280, -0.006680, 3.810120, -3.184650, 0.105220, -0.392750, -3.644920, -0.406890, 
-0.389700, 0.065410, 1.844910, 0.556070, -0.110880, 0.064700, -2.222880, -0.397780, 0.446580, -0.054580, 

-5.024140, 1.079270, 0.595160, 0.742600, -4.777780, 1.973020, 1.263400, -3.396580, 2.896050, -0.254580, 
-3.357150, 0.506140, -3.057220, 1.095300, -2.468820, 1.203980, 0.805780, -3.383680, -1.457140, -0.214410, 

-0.052770, -1.078890, 1.940070, -3.075980, -0.060940, -0.184150, -1.097120, 0.935070, -0.220610, 1.543390, 
0.919140, -2.971850, -2.296500, -1.027520, 2.846840, -1.079790, -0.129380, 0.929020, -2.114660, 1.491500, 

-1.241440, -1.391110, -2.862900, 1.643080, -1.225360, 0.416140, -1.408760, 0.892830, 0.464550, -3.187890, 
0.703920, 1.662760, 2.183550, -1.399450, -2.418930, -1.426760, 0.305430, 0.718530, 2.243780, -3.334750, 


  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[59] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, 0.292400, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, 0.866630, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, -0.381150, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, -0.262550, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.405280, 4,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.788760, 4,
       &Sources[4] , 
       &Weights[4] , 
      },
    { /* unit 7 (noName) */
      0.0, 0.532550, 4,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 8 (noName) */
      0.0, -0.915150, 4,
       &Sources[12] , 
       &Weights[12] , 
      },
    { /* unit 9 (noName) */
      0.0, -0.784670, 4,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 10 (noName) */
      0.0, 0.697350, 4,
       &Sources[20] , 
       &Weights[20] , 
      },
    { /* unit 11 (noName) */
      0.0, -0.864840, 4,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 12 (noName) */
      0.0, 0.279270, 4,
       &Sources[28] , 
       &Weights[28] , 
      },
    { /* unit 13 (noName) */
      0.0, 0.453340, 4,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, -0.230200, 4,
       &Sources[36] , 
       &Weights[36] , 
      },
    { /* unit 15 (noName) */
      0.0, 0.880450, 4,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 16 (noName) */
      0.0, -1.097630, 4,
       &Sources[44] , 
       &Weights[44] , 
      },
    { /* unit 17 (noName) */
      0.0, 0.588950, 4,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 18 (noName) */
      0.0, 0.319270, 4,
       &Sources[52] , 
       &Weights[52] , 
      },
    { /* unit 19 (noName) */
      0.0, -0.067580, 4,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 20 (noName) */
      0.0, -0.497180, 4,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 21 (noName) */
      0.0, 0.781550, 4,
       &Sources[64] , 
       &Weights[64] , 
      },
    { /* unit 22 (noName) */
      0.0, -0.284300, 4,
       &Sources[68] , 
       &Weights[68] , 
      },
    { /* unit 23 (noName) */
      0.0, -0.449570, 4,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 24 (noName) */
      0.0, 0.809490, 4,
       &Sources[76] , 
       &Weights[76] , 
      },
    { /* unit 25 (noName) */
      0.0, -0.182400, 4,
       &Sources[80] , 
       &Weights[80] , 
      },
    { /* unit 26 (noName) */
      0.0, 0.209350, 4,
       &Sources[84] , 
       &Weights[84] , 
      },
    { /* unit 27 (noName) */
      0.0, -0.283920, 4,
       &Sources[88] , 
       &Weights[88] , 
      },
    { /* unit 28 (noName) */
      0.0, -0.757390, 4,
       &Sources[92] , 
       &Weights[92] , 
      },
    { /* unit 29 (noName) */
      0.0, 0.720370, 4,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 30 (noName) */
      0.0, 0.762090, 4,
       &Sources[100] , 
       &Weights[100] , 
      },
    { /* unit 31 (noName) */
      0.0, 0.699290, 4,
       &Sources[104] , 
       &Weights[104] , 
      },
    { /* unit 32 (noName) */
      0.0, -0.730750, 4,
       &Sources[108] , 
       &Weights[108] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.256480, 4,
       &Sources[112] , 
       &Weights[112] , 
      },
    { /* unit 34 (noName) */
      0.0, 0.882050, 4,
       &Sources[116] , 
       &Weights[116] , 
      },
    { /* unit 35 (noName) */
      0.0, 0.279980, 30,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 36 (noName) */
      0.0, 0.013180, 30,
       &Sources[150] , 
       &Weights[150] , 
      },
    { /* unit 37 (noName) */
      0.0, 0.068210, 30,
       &Sources[180] , 
       &Weights[180] , 
      },
    { /* unit 38 (noName) */
      0.0, 0.075920, 30,
       &Sources[210] , 
       &Weights[210] , 
      },
    { /* unit 39 (noName) */
      0.0, 0.066120, 30,
       &Sources[240] , 
       &Weights[240] , 
      },
    { /* unit 40 (noName) */
      0.0, -0.053060, 30,
       &Sources[270] , 
       &Weights[270] , 
      },
    { /* unit 41 (noName) */
      0.0, 0.062750, 30,
       &Sources[300] , 
       &Weights[300] , 
      },
    { /* unit 42 (noName) */
      0.0, -0.036690, 30,
       &Sources[330] , 
       &Weights[330] , 
      },
    { /* unit 43 (noName) */
      0.0, 0.047610, 30,
       &Sources[360] , 
       &Weights[360] , 
      },
    { /* unit 44 (noName) */
      0.0, 0.216190, 30,
       &Sources[390] , 
       &Weights[390] , 
      },
    { /* unit 45 (noName) */
      0.0, -0.059200, 30,
       &Sources[420] , 
       &Weights[420] , 
      },
    { /* unit 46 (noName) */
      0.0, 0.055600, 30,
       &Sources[450] , 
       &Weights[450] , 
      },
    { /* unit 47 (noName) */
      0.0, 0.353520, 30,
       &Sources[480] , 
       &Weights[480] , 
      },
    { /* unit 48 (noName) */
      0.0, 0.021300, 30,
       &Sources[510] , 
       &Weights[510] , 
      },
    { /* unit 49 (noName) */
      0.0, -0.100710, 30,
       &Sources[540] , 
       &Weights[540] , 
      },
    { /* unit 50 (noName) */
      0.0, 0.035060, 30,
       &Sources[570] , 
       &Weights[570] , 
      },
    { /* unit 51 (noName) */
      0.0, 0.285120, 30,
       &Sources[600] , 
       &Weights[600] , 
      },
    { /* unit 52 (noName) */
      0.0, -0.034510, 30,
       &Sources[630] , 
       &Weights[630] , 
      },
    { /* unit 53 (noName) */
      0.0, -0.140710, 30,
       &Sources[660] , 
       &Weights[660] , 
      },
    { /* unit 54 (noName) */
      0.0, 0.309210, 30,
       &Sources[690] , 
       &Weights[690] , 
      },
    { /* unit 55 (noName) */
      0.0, 0.011400, 20,
       &Sources[720] , 
       &Weights[720] , 
      },
    { /* unit 56 (noName) */
      0.0, -1.118810, 20,
       &Sources[740] , 
       &Weights[740] , 
      },
    { /* unit 57 (noName) */
      0.0, -0.360160, 20,
       &Sources[760] , 
       &Weights[760] , 
      },
    { /* unit 58 (noName) */
      0.0, -0.608070, 20,
       &Sources[780] , 
       &Weights[780] , 
      }

  };



int classify73(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[4] = {Units + 1, Units + 2, Units + 3, Units + 4}; /* members */

  static pUnit Hidden1[30] = {Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34}; /* members */

  static pUnit Hidden2[20] = {Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54}; /* members */

  static pUnit Output1[4] = {Units + 55, Units + 56, Units + 57, Units + 58}; /* members */

  static int Output[4] = {55, 56, 57, 58};

  for(member = 0; member < 4; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 30; member++) {
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
