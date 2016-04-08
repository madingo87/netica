/*********************************************************
  c:\temp\orient1.c
  --------------------------------------------------------
  generated at Tue Apr 05 16:37:53 2016
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
  static UnitType Units[56];
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
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, 
Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 
Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, 
Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.074230, -0.820290, 0.293750, -0.309680, -0.908580, 0.741890, 0.221870, -0.511750, -0.720720, -0.065800, 
-0.053590, 0.316800, 
0.433540, -0.258350, -0.047840, 0.196250, -0.074080, -0.439780, 0.361850, -0.579370, 0.083700, 0.239460, 
-0.315760, 0.140770, 
-0.000350, 0.755100, 0.195520, 0.161390, -0.071290, -0.878690, -0.255800, 0.487130, -0.470290, 0.370900, 
-0.104490, 0.304280, 
-0.029380, 0.162740, 0.757180, -0.425210, 0.292830, -0.281050, -0.119020, -0.457000, -1.295390, -0.042670, 
0.272940, -0.270190, 
0.088060, 0.152500, -0.126100, -0.287090, -0.454520, -0.833270, 0.038570, -0.308480, -0.737820, 0.258860, 
0.007570, 0.392800, 
0.233680, -0.130190, 0.283550, 0.197790, 0.103660, -0.051900, 0.224090, -0.105430, -0.185740, 0.109500, 
0.065270, -0.062880, 
-0.058490, -0.129350, 1.032820, -0.222990, 0.038330, 0.536310, -0.034760, 0.012840, -0.897520, -0.174390, 
0.432730, 0.461220, 
-0.221550, -0.159450, 0.075810, -0.059320, -0.426480, 0.304990, -0.148240, -0.521740, -0.426940, 0.227590, 
-0.950130, -0.557650, 
-0.194740, 0.311720, 0.688430, 0.123490, -0.587850, 0.057360, -0.212610, 0.798460, -0.546030, 0.237920, 
0.147600, 0.839610, 
-0.235000, 0.131210, -0.283470, -0.199190, -0.104670, 0.048110, -0.224810, 0.104930, 0.182030, -0.109870, 
-0.066330, 0.063820, 
0.393320, -0.273440, -0.517310, -0.010590, 0.167200, -0.077530, 0.526590, -0.027220, 0.595370, -0.169650, 
0.408210, 0.457030, 
-0.220460, 0.293830, 0.236900, -0.115330, 0.102080, 0.434750, -0.379420, -0.006270, -0.265870, -0.047380, 
-0.118020, -0.976610, 
0.129250, 0.342720, 0.322270, 0.532280, -0.989440, -0.104320, -0.040340, 0.981650, -0.235900, 0.505680, 
-0.102970, 0.254510, 
0.064130, 0.659610, 0.406680, 0.196260, 0.974470, 0.368000, 0.116800, 1.035670, 0.056560, -0.233540, 
0.312280, 0.114190, 
-0.225310, -0.142450, 0.286980, 0.071640, -0.534780, 0.971480, -0.249170, 0.544310, 0.103030, -0.170840, 
0.287750, -0.077090, 
-0.039810, -0.950940, -0.632020, 0.236970, -0.739150, -0.254590, -0.002220, -0.926230, 0.869360, 0.167420, 
-0.434780, -0.198630, 
-0.093190, 0.339720, 0.719330, 0.743120, 0.909550, -0.231940, 0.160120, 0.340250, -0.115420, 0.238010, 
-0.121570, -0.114030, -0.529470, -0.121690, -0.855590, -0.333090, 
0.887520, -0.580080, 0.099030, -0.282910, 0.604200, -0.074590, -0.309100, 1.034220, 0.445220, 0.085880, 
-0.016760, -0.666110, 0.311250, 0.247460, -0.386630, -0.796570, 
0.147180, -0.053580, -0.545560, -0.623430, -0.406470, 0.458260, -0.229520, -0.101730, -0.410920, -0.460970, 
0.605920, -0.394520, -0.097400, 0.815440, -0.272950, -0.864100, 
-0.010770, -0.270780, 0.066660, -0.168380, 0.179530, -0.486130, -0.204150, 0.020100, 0.037580, 0.486940, 
0.032460, 0.015950, -0.207790, -0.073440, 0.098540, -0.084860, 
1.124350, 0.031390, -0.521100, 0.072080, 0.356930, -0.315160, 0.398700, 0.172790, 0.048000, 0.317250, 
0.256210, -0.406240, -0.379450, -0.992130, 0.328160, 0.716740, 
-0.440750, -0.001370, -0.137190, -0.142350, 0.415320, -0.177290, -0.980090, -0.220980, -0.963200, 0.177210, 
0.450840, -0.170090, -0.501840, -0.475040, -0.555820, 0.587860, 
0.777460, 0.353890, -0.291260, 0.103740, 0.221760, 0.405580, -0.131850, 0.293410, 0.285290, -0.402440, 
0.307330, -0.489160, 0.761270, -0.219860, 0.109500, 0.464200, 
0.577790, 0.770150, -0.352260, 0.099240, 0.074820, 0.406910, 0.127560, 0.663050, -0.252850, -0.406740, 
0.159360, -0.271200, 0.078060, 0.023870, -0.385260, 0.084090, 
-0.052710, -0.388220, -0.100540, 0.962080, -0.133300, 0.099150, 0.658410, 0.103360, -0.142820, -0.090320, 
-0.682200, 0.522270, -0.788110, -0.528450, 0.213670, 0.896960, 
-0.099920, 0.041690, -0.391300, -0.257270, -0.123220, -0.288220, -0.842770, 0.526040, -0.882020, 0.288090, 
-0.245900, 0.746080, 0.036140, -0.736280, 0.260810, 0.436420, 
0.688820, -0.235950, 0.273940, 0.955100, 0.602840, 0.258420, 0.268950, -0.249680, 0.645780, -0.263330, 
-0.048420, -0.109690, 0.780950, -0.811480, 0.492020, 0.391040, 
0.452760, -0.152890, -0.170410, -0.572810, -0.132920, -0.489580, 0.040520, -0.241910, 0.561530, 0.490620, 
0.333810, -0.216220, 0.077960, -0.068000, 0.748620, 0.040240, 
-0.146260, -0.096290, -0.405810, -0.267580, -0.299770, -0.240340, 0.095390, -0.753750, -0.149520, 0.239510, 
0.498260, -0.214860, -0.683400, 0.051450, 0.256540, 0.516020, 
0.676020, 0.124770, -0.900850, 0.386850, -0.223070, -0.167130, 0.576630, 0.349240, -0.698470, 0.162960, 
0.059100, 0.319370, -1.027850, 0.042390, 0.107670, -0.139300, 
0.733330, -0.536280, -0.335350, -0.108940, 0.069330, -0.447000, -0.136500, 0.613170, 0.224810, 0.447110, 
0.015360, 0.013670, -0.120460, 0.411530, 0.389470, -0.582240, 
0.300790, -0.094530, 0.131390, 0.573420, 0.707830, -0.402080, 0.266670, -0.677170, 0.042250, 0.401390, 
0.599890, -0.347920, -0.397240, 0.066410, -0.152320, -0.600810, 
1.188750, 0.721510, 0.184180, 0.811670, -1.137250, -0.789700, 0.042400, -0.271210, -1.747290, 0.316620, 
0.105470, 0.439800, -0.456560, -0.549850, 0.493760, 2.357580, 
1.216330, -0.534830, -1.494290, 0.794880, -1.311410, 1.500580, -0.076720, -0.494170, 0.495220, 1.612540, 
0.185740, 0.678640, -0.022930, -0.753590, 0.669120, 0.260700, 
0.828620, -0.164300, 0.182930, 0.589130, 1.079140, 1.328670, -0.189650, -0.563280, 0.802870, -0.319700, 
0.362990, 0.247720, 1.256300, 1.178950, 0.502210, 1.635840, 
-0.383340, 1.798100, 0.766290, 0.671890, 1.056010, 1.412120, -0.546380, -0.598840, -1.173430, 1.697140, 
0.079820, 0.169650, -0.594750, 0.015640, 0.368040, 0.323710, 
-0.269110, -0.068160, 0.062940, 0.698980, 1.047850, -1.024190, -0.241460, -0.287420, -0.875500, -0.178990, 
0.286520, 2.494080, 1.151950, -0.206460, 0.573740, 0.023050, 
1.402760, 0.093920, 0.084150, 0.677570, -0.151990, -0.623490, -1.616490, 0.172580, -0.003360, 0.380670, 
-2.196680, 0.582760, -0.227930, 1.257710, 0.034290, -0.168100, 
-1.007570, -0.770310, -1.764960, 0.816490, 1.276380, -0.881010, -0.227760, -0.632950, 0.394120, 1.634390, 
-0.325620, 0.334740, 0.082520, 1.477330, 0.279960, 0.483790, 
1.265710, 1.883240, -1.795910, 0.777110, 1.481130, -0.437900, -0.447140, -0.612250, 0.550560, -1.046290, 
-0.518790, 0.388820, 0.122180, -0.769300, 0.363380, -0.102530, 
-0.648080, 1.537500, 0.061310, 0.674650, -0.863680, -0.069090, 0.414220, -0.088490, 0.306160, -0.435940, 
0.043240, 0.599450, 0.215030, 1.100570, 2.466320, 0.168570, 
-0.899350, -0.270310, -0.342530, 0.649710, -0.127040, -0.059870, -1.631510, -2.488510, 0.468420, -0.081170, 
0.288390, 0.064100, -0.038510, -0.928340, 0.150010, 0.463640, 
-0.766330, -0.018320, -0.297060, 0.761150, -1.156760, 1.335910, -0.012460, -0.486130, -1.057010, -0.142300, 
-2.063820, -0.180200, 1.275830, -0.434440, 0.669900, 0.269600, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[56] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, 0.482470, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, 0.318830, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, 0.028290, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.711660, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, -0.176980, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.214640, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, -0.767270, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 0.489060, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 0.119050, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, -0.960450, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 11 (noName) */
      0.0, -0.174230, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 12 (noName) */
      0.0, 0.885250, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.351250, 12,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 14 (noName) */
      0.0, 0.309930, 12,
       &Sources[12] , 
       &Weights[12] , 
      },
    { /* unit 15 (noName) */
      0.0, 0.018580, 12,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 16 (noName) */
      0.0, 0.106020, 12,
       &Sources[36] , 
       &Weights[36] , 
      },
    { /* unit 17 (noName) */
      0.0, -0.579170, 12,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 18 (noName) */
      0.0, 0.712430, 12,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 19 (noName) */
      0.0, 0.151630, 12,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 20 (noName) */
      0.0, -0.199690, 12,
       &Sources[84] , 
       &Weights[84] , 
      },
    { /* unit 21 (noName) */
      0.0, 0.020620, 12,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 22 (noName) */
      0.0, -0.713260, 12,
       &Sources[108] , 
       &Weights[108] , 
      },
    { /* unit 23 (noName) */
      0.0, -0.131920, 12,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 24 (noName) */
      0.0, 0.129720, 12,
       &Sources[132] , 
       &Weights[132] , 
      },
    { /* unit 25 (noName) */
      0.0, 0.572760, 12,
       &Sources[144] , 
       &Weights[144] , 
      },
    { /* unit 26 (noName) */
      0.0, 0.466900, 12,
       &Sources[156] , 
       &Weights[156] , 
      },
    { /* unit 27 (noName) */
      0.0, 0.013890, 12,
       &Sources[168] , 
       &Weights[168] , 
      },
    { /* unit 28 (noName) */
      0.0, 0.054060, 12,
       &Sources[180] , 
       &Weights[180] , 
      },
    { /* unit 29 (noName) */
      0.0, -0.367940, 16,
       &Sources[192] , 
       &Weights[192] , 
      },
    { /* unit 30 (noName) */
      0.0, -0.132450, 16,
       &Sources[208] , 
       &Weights[208] , 
      },
    { /* unit 31 (noName) */
      0.0, 0.562810, 16,
       &Sources[224] , 
       &Weights[224] , 
      },
    { /* unit 32 (noName) */
      0.0, -0.582910, 16,
       &Sources[240] , 
       &Weights[240] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.403260, 16,
       &Sources[256] , 
       &Weights[256] , 
      },
    { /* unit 34 (noName) */
      0.0, -0.209590, 16,
       &Sources[272] , 
       &Weights[272] , 
      },
    { /* unit 35 (noName) */
      0.0, 0.455400, 16,
       &Sources[288] , 
       &Weights[288] , 
      },
    { /* unit 36 (noName) */
      0.0, 0.419930, 16,
       &Sources[304] , 
       &Weights[304] , 
      },
    { /* unit 37 (noName) */
      0.0, 0.117500, 16,
       &Sources[320] , 
       &Weights[320] , 
      },
    { /* unit 38 (noName) */
      0.0, -0.314310, 16,
       &Sources[336] , 
       &Weights[336] , 
      },
    { /* unit 39 (noName) */
      0.0, 0.324830, 16,
       &Sources[352] , 
       &Weights[352] , 
      },
    { /* unit 40 (noName) */
      0.0, -0.566940, 16,
       &Sources[368] , 
       &Weights[368] , 
      },
    { /* unit 41 (noName) */
      0.0, -0.276570, 16,
       &Sources[384] , 
       &Weights[384] , 
      },
    { /* unit 42 (noName) */
      0.0, -0.257420, 16,
       &Sources[400] , 
       &Weights[400] , 
      },
    { /* unit 43 (noName) */
      0.0, -0.559200, 16,
       &Sources[416] , 
       &Weights[416] , 
      },
    { /* unit 44 (noName) */
      0.0, -0.553960, 16,
       &Sources[432] , 
       &Weights[432] , 
      },
    { /* unit 45 (noName) */
      0.0, -0.874460, 16,
       &Sources[448] , 
       &Weights[448] , 
      },
    { /* unit 46 (noName) */
      0.0, -0.814090, 16,
       &Sources[464] , 
       &Weights[464] , 
      },
    { /* unit 47 (noName) */
      0.0, -0.616640, 16,
       &Sources[480] , 
       &Weights[480] , 
      },
    { /* unit 48 (noName) */
      0.0, -0.674280, 16,
       &Sources[496] , 
       &Weights[496] , 
      },
    { /* unit 49 (noName) */
      0.0, -0.738960, 16,
       &Sources[512] , 
       &Weights[512] , 
      },
    { /* unit 50 (noName) */
      0.0, -0.731740, 16,
       &Sources[528] , 
       &Weights[528] , 
      },
    { /* unit 51 (noName) */
      0.0, -0.888920, 16,
       &Sources[544] , 
       &Weights[544] , 
      },
    { /* unit 52 (noName) */
      0.0, -0.824950, 16,
       &Sources[560] , 
       &Weights[560] , 
      },
    { /* unit 53 (noName) */
      0.0, -0.706890, 16,
       &Sources[576] , 
       &Weights[576] , 
      },
    { /* unit 54 (noName) */
      0.0, -0.647620, 16,
       &Sources[592] , 
       &Weights[592] , 
      },
    { /* unit 55 (noName) */
      0.0, -0.785610, 16,
       &Sources[608] , 
       &Weights[608] , 
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

  static pUnit Hidden1[16] = {Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28}; /* members */

  static pUnit Hidden2[16] = {Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44}; /* members */

  static pUnit Output1[11] = {Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, Units + 55}; /* members */

  static int Output[11] = {45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55};

  for(member = 0; member < 12; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 16; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 16; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 11; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for(member = 0; member < 11; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
