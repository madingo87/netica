/*********************************************************
  c:\temp\distance1.c
  --------------------------------------------------------
  generated at Tue Apr 05 13:34:02 2016
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
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, 
Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
1.188910, -3.469460, 2.993730, 1.240090, -0.473940, 3.149800, -5.744860, 0.106780, 
-1.332580, 1.186560, 0.338350, 0.115960, -0.430530, -3.842830, 0.034980, -0.273550, 
0.947730, 1.328790, 0.552480, -0.053790, 0.931730, 1.304340, 4.097290, -0.357690, 
0.081000, -0.341500, -2.916200, -1.069890, -2.942200, 0.664100, -0.435530, 1.308100, 
0.640400, -1.255940, -1.093300, -0.241020, -0.926650, 0.988970, -0.860340, -1.022330, 
0.010990, 0.245380, 3.167560, 0.314990, 0.641450, -1.282990, -2.545800, -2.407390, 
-0.746010, 0.629490, -2.964090, -1.214510, -3.138360, 0.587000, 1.658010, 5.657360, 
-0.534160, 0.360860, 1.077490, 0.622090, 0.781200, -2.943880, -1.714790, -1.401650, 
1.304840, 0.667610, -3.335260, -1.805110, -2.021810, 0.786500, 1.492930, -2.565450, 
-1.554880, 1.518580, -1.174070, -0.701280, 0.049500, -4.312410, 1.628060, 1.606110, 
0.979930, -0.444880, -1.013680, -0.282270, -0.873240, 3.645410, 1.276490, 1.117630, 
-1.412240, -0.729340, 1.042060, 1.334290, 1.262880, -0.185280, -0.916910, 2.688840, 
-0.281170, 0.614620, 3.081140, 0.075900, 0.194250, -2.850180, -1.485640, -1.939730, 
1.388470, -0.252890, -0.349600, -0.334810, -1.139020, 1.522720, -0.529200, -2.108150, 
-1.161550, 0.442090, 0.084250, 1.301500, 1.364650, -4.874350, -0.538210, -0.005470, 
2.554490, 1.191220, -2.574300, -1.476470, -1.685430, 3.581000, 2.398740, -1.732480, 
2.069070, 0.327340, -0.195290, -1.355060, -1.040120, 0.685820, -0.574700, 0.622950, -1.904810, 0.305980, 
-0.708300, 1.542280, 0.894080, -1.290380, 1.469470, -3.614710, 
4.831740, -1.482980, -0.530360, -1.097500, 0.048930, 1.221300, -1.287510, -0.245250, -2.658320, -2.975160, 
0.544710, 1.597110, 0.451890, 0.495020, -1.920400, 0.273360, 
0.507060, 0.746920, -2.208140, 1.141390, 2.928960, 1.701380, -1.941100, 1.421230, 0.194190, -1.177870, 
-0.136330, -0.765480, 1.239520, 3.510970, -1.363280, 3.536330, 
-2.859890, 0.838310, -1.786510, 2.570860, 0.967590, -1.665520, 2.254970, 0.351420, 1.663830, 2.090060, 
-0.945740, 0.179430, -1.174730, 0.353210, 1.200740, 0.477170, 
1.569220, -0.898500, 2.078460, -1.564320, 0.014490, 0.328080, -1.709050, 0.364240, -1.241010, -0.930860, 
0.508780, 1.683880, 0.069230, 0.355160, 0.832120, 0.036880, 
0.584970, -1.340160, 0.909080, 1.761050, 1.063090, -1.747610, 3.050060, -1.535170, 2.548740, -0.318330, 
2.834570, -0.478310, -2.195800, 0.273310, -0.940630, 2.741280, 
-0.826380, 0.879390, -1.316650, 1.551640, -1.044040, -1.258980, 5.141790, -0.563890, -0.659410, 2.228950, 
0.334500, 2.136520, -0.537130, -1.577360, -0.108290, -1.428770, 
1.429860, -0.109940, -1.921310, 1.558940, 2.017540, 1.003800, -1.965720, 0.421070, 1.432170, -1.706610, 
-0.693020, -2.644790, 0.605970, 2.295480, -1.126190, 1.691480, 
0.378720, 1.372400, 0.972260, -0.247550, 0.046910, 1.413760, -1.374390, 1.225510, 2.680380, 1.216300, 
0.126700, -1.557100, 1.595620, -0.369530, 2.028510, -2.678710, 
-6.364510, 1.446910, 2.482850, -0.809970, -0.919460, -0.226210, -0.063210, 0.145750, 0.200370, 1.759730, 
-0.145790, -0.822130, 0.511560, 0.010990, 0.165960, 3.030980, 
0.839700, -3.364240, 2.984980, 0.057360, -0.356710, -2.576300, 1.772840, -2.775540, 1.389060, -2.132360, 
2.455180, -0.104700, -3.277530, -0.833830, -2.262700, 0.080510, 
1.186560, -1.521720, 1.752150, 0.373740, 0.227540, -1.465120, 2.838340, -1.975820, 0.362280, -0.900210, 
3.038700, 1.189130, -1.927080, -0.193240, -1.835080, 0.597440, 
0.936170, 1.579940, -2.083510, 1.635320, -0.085780, -0.269680, 2.017250, 0.953470, 0.517000, 1.823710, 
-1.015180, 0.388280, 0.238980, -1.134390, 1.803410, -1.921280, 
0.667030, 0.712910, 1.418700, -2.532650, -1.116670, 1.620180, -1.399050, 1.424860, -2.830520, 0.707610, 
-0.481450, 2.308300, 1.746730, -0.644060, 1.835930, -0.312790, 
0.705050, -2.194920, 2.212820, 0.966490, -0.177600, -1.079470, 1.865290, -2.372240, 1.881020, -2.328410, 
2.807960, -1.220180, -1.791740, 0.351120, -3.583010, 2.254980, 
-3.626200, -0.982960, 4.875610, -1.038800, -1.464040, -2.429660, 1.395170, -1.868440, 1.633920, 0.868310, 
1.807120, -0.533420, -2.090040, -1.532270, 0.109420, -0.134530, 
2.409970, 3.318460, -0.026440, -2.788040, 0.237010, -4.500390, -3.430390, 3.471480, -0.109980, -3.950480, 
-0.373040, -3.115560, 0.310020, -0.013990, -1.306590, -0.346740, 
1.417500, -3.430240, 2.190920, 0.998480, -0.394580, -5.508010, 3.099960, -5.130780, -0.493740, 2.749490, 
-0.361700, -3.803240, -0.275300, -0.494370, -0.584850, -3.110110, 
-5.526440, -3.417830, -0.910600, 2.080500, -1.063820, 3.736060, -4.312260, 1.970640, -0.599550, 1.567500, 
-0.918060, -5.000570, 0.677800, 2.189620, -5.573260, -1.095920, 
-0.262500, -3.887080, -0.785690, 1.006670, -0.190230, -0.837960, -5.299000, 1.337080, 1.283810, 0.604760, 
3.932280, -0.045380, -4.073970, -4.408410, -0.059810, 4.351190, 
-1.914770, 2.727120, -0.070230, 0.901880, 0.141030, 0.094290, 0.948290, 2.139430, -4.304890, -5.579150, 
2.612490, 0.174110, -1.086850, -3.675050, 0.552690, -3.819880, 
0.421330, -4.110680, -6.146900, 1.021530, -0.715820, 2.053930, -0.424430, -2.286790, -0.820470, 2.418820, 
-3.947360, 3.234440, -0.472460, -0.343060, -4.635250, 4.283130, 
-3.738850, 0.801060, 1.481610, -1.983200, -0.337230, -0.953680, 1.696350, -5.324130, -5.950970, 3.487720, 
0.893050, -0.942300, -3.536790, 2.238840, 0.191780, 2.666170, 
-3.199910, 2.367770, -1.266320, -4.608240, -0.155950, 1.064420, -3.907480, 0.555640, 0.431290, 1.241750, 
-4.817830, 2.313310, -5.170520, 1.967600, 3.063310, -4.122370, 
2.592410, 1.606080, -7.079260, -3.929580, -1.078440, -0.571780, -0.586490, -1.833880, 1.043940, -5.293040, 
4.092200, -1.215880, 0.420660, -0.116800, 3.222580, 1.870480, 
-0.368790, 1.811860, 2.357210, -1.868400, -1.349960, 3.924620, 2.027740, -6.150160, -0.307340, -5.207320, 
-5.216530, 4.076230, -0.545520, -0.285290, -4.200740, -5.774000, 
-1.299520, -2.941680, -0.872260, 0.334610, -5.634290, -0.403220, 2.514060, -0.223340, 0.475210, 0.995190, 
-4.781290, 2.273580, 2.190250, -4.575480, 3.420740, -2.742030, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[52] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, -0.962160, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, -0.006260, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, 0.805110, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.501330, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, 0.520680, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, -0.358560, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, 0.233920, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, -0.881710, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 0.325790, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, 2.258220, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, -4.972960, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, 2.196520, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, 2.538410, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.988250, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, -0.207070, 8,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, 1.855050, 8,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 17 (noName) */
      0.0, 1.502370, 8,
       &Sources[64] , 
       &Weights[64] , 
      },
    { /* unit 18 (noName) */
      0.0, 1.160980, 8,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 19 (noName) */
      0.0, -1.864550, 8,
       &Sources[80] , 
       &Weights[80] , 
      },
    { /* unit 20 (noName) */
      0.0, -1.298770, 8,
       &Sources[88] , 
       &Weights[88] , 
      },
    { /* unit 21 (noName) */
      0.0, 1.466590, 8,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 22 (noName) */
      0.0, 2.371820, 8,
       &Sources[104] , 
       &Weights[104] , 
      },
    { /* unit 23 (noName) */
      0.0, 1.369610, 8,
       &Sources[112] , 
       &Weights[112] , 
      },
    { /* unit 24 (noName) */
      0.0, 0.089440, 8,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 25 (noName) */
      0.0, 0.169820, 16,
       &Sources[128] , 
       &Weights[128] , 
      },
    { /* unit 26 (noName) */
      0.0, 0.216210, 16,
       &Sources[144] , 
       &Weights[144] , 
      },
    { /* unit 27 (noName) */
      0.0, 0.522200, 16,
       &Sources[160] , 
       &Weights[160] , 
      },
    { /* unit 28 (noName) */
      0.0, -0.857390, 16,
       &Sources[176] , 
       &Weights[176] , 
      },
    { /* unit 29 (noName) */
      0.0, 0.838010, 16,
       &Sources[192] , 
       &Weights[192] , 
      },
    { /* unit 30 (noName) */
      0.0, 0.788860, 16,
       &Sources[208] , 
       &Weights[208] , 
      },
    { /* unit 31 (noName) */
      0.0, -0.189630, 16,
       &Sources[224] , 
       &Weights[224] , 
      },
    { /* unit 32 (noName) */
      0.0, -0.517790, 16,
       &Sources[240] , 
       &Weights[240] , 
      },
    { /* unit 33 (noName) */
      0.0, 0.798550, 16,
       &Sources[256] , 
       &Weights[256] , 
      },
    { /* unit 34 (noName) */
      0.0, 0.390790, 16,
       &Sources[272] , 
       &Weights[272] , 
      },
    { /* unit 35 (noName) */
      0.0, 0.318420, 16,
       &Sources[288] , 
       &Weights[288] , 
      },
    { /* unit 36 (noName) */
      0.0, 0.952450, 16,
       &Sources[304] , 
       &Weights[304] , 
      },
    { /* unit 37 (noName) */
      0.0, -0.175140, 16,
       &Sources[320] , 
       &Weights[320] , 
      },
    { /* unit 38 (noName) */
      0.0, 0.677180, 16,
       &Sources[336] , 
       &Weights[336] , 
      },
    { /* unit 39 (noName) */
      0.0, 0.622830, 16,
       &Sources[352] , 
       &Weights[352] , 
      },
    { /* unit 40 (noName) */
      0.0, 0.205400, 16,
       &Sources[368] , 
       &Weights[368] , 
      },
    { /* unit 41 (noName) */
      0.0, -0.471240, 16,
       &Sources[384] , 
       &Weights[384] , 
      },
    { /* unit 42 (noName) */
      0.0, -0.692130, 16,
       &Sources[400] , 
       &Weights[400] , 
      },
    { /* unit 43 (noName) */
      0.0, -1.012130, 16,
       &Sources[416] , 
       &Weights[416] , 
      },
    { /* unit 44 (noName) */
      0.0, -1.033430, 16,
       &Sources[432] , 
       &Weights[432] , 
      },
    { /* unit 45 (noName) */
      0.0, -0.792920, 16,
       &Sources[448] , 
       &Weights[448] , 
      },
    { /* unit 46 (noName) */
      0.0, -1.541000, 16,
       &Sources[464] , 
       &Weights[464] , 
      },
    { /* unit 47 (noName) */
      0.0, -1.213410, 16,
       &Sources[480] , 
       &Weights[480] , 
      },
    { /* unit 48 (noName) */
      0.0, -1.329560, 16,
       &Sources[496] , 
       &Weights[496] , 
      },
    { /* unit 49 (noName) */
      0.0, -1.218170, 16,
       &Sources[512] , 
       &Weights[512] , 
      },
    { /* unit 50 (noName) */
      0.0, -1.879580, 16,
       &Sources[528] , 
       &Weights[528] , 
      },
    { /* unit 51 (noName) */
      0.0, -1.504600, 16,
       &Sources[544] , 
       &Weights[544] , 
      }

  };



int classifyDistance(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[8] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8}; /* members */

  static pUnit Hidden1[16] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24}; /* members */

  static pUnit Hidden2[16] = {Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40}; /* members */

  static pUnit Output1[11] = {Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51}; /* members */

  static int Output[11] = {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};

  for(member = 0; member < 8; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 16; member++) {
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

  for (member = 0; member < 11; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for(member = 0; member < 11; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
