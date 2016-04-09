/*********************************************************
  c:\temp\dist.c
  --------------------------------------------------------
  generated at Sat Apr 09 14:20:00 2016
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
  static UnitType Units[58];
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
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, 
Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 
Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, 
Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.124340, 1.053050, -4.484370, -0.852530, -2.964440, 2.964010, 1.031290, 2.851450, 
-0.447880, -0.807450, -0.964700, 0.296730, 1.531040, 0.189080, -1.584920, -0.320580, 
-0.483300, 0.627240, 0.224150, -0.077860, -0.136810, 1.322360, 1.449700, 0.028800, 
2.888540, 1.726910, 2.238170, -0.455510, 0.577190, -2.637720, -3.081800, 1.727480, 
-0.015330, 0.334480, 1.985420, 0.021760, 1.115190, -0.474380, -0.357200, -1.761560, 
-1.000510, 0.261620, -0.797880, 0.694370, 1.427470, 0.608270, -1.016660, 0.789340, 
1.520710, 3.000730, -1.834550, 0.361340, -4.726240, 0.145230, 3.961700, -18.108351, 
2.102920, 4.463600, 0.674290, -0.457170, -0.779940, -1.904780, -2.746080, 0.403520, 
-0.152090, -0.646710, 0.589520, 0.150590, 1.039100, -0.112110, 0.205590, 5.577000, 
0.592380, 0.048580, -0.107900, 0.514540, -0.357390, -0.407620, 0.909890, 3.705900, 
0.282420, 0.197900, 0.120220, 0.142220, -0.218720, 0.307190, -0.116970, 1.286380, 
-0.598890, 0.147680, 0.549530, -0.205190, 2.075900, -1.277920, -1.137080, -0.623590, 
-0.318310, 0.641460, 0.429200, -0.553450, -1.247070, 0.608750, -1.210890, -1.977080, 
-0.545830, -0.728970, 2.280150, -1.205000, -0.182730, -0.652990, 0.652140, 0.362950, 
0.666450, 4.606670, 1.273390, -3.611720, -0.122870, -0.031070, 2.576910, -1.582150, 
-0.540270, -5.553100, 0.065760, 2.717240, 1.183090, 0.645640, -2.249930, 1.404660, 
-3.076030, 0.081100, -0.343920, 2.910430, 1.992390, -0.495600, -3.400330, 2.777250, 
2.180050, -0.045870, 1.999050, -0.538690, -0.200680, 0.856980, -1.966540, -0.826470, 
-1.956010, -21.052469, -0.188530, 0.976440, 0.269270, -0.476830, 1.874810, 11.826070, -0.359440, 0.477720, 
1.014290, 0.088170, 9.047800, -0.381610, 0.381850, 6.350690, 0.811140, -0.252010, 
-2.524680, -2.541080, 0.120650, 0.912660, -1.118190, 0.818070, 11.399210, -0.304150, 2.060510, 0.971960, 
-0.381050, -0.676320, -1.936930, 0.032070, 0.448690, -0.210640, 0.061760, -0.684800, 
-7.372330, 1.077680, -1.469360, 2.208910, 0.555490, -1.667840, -2.744860, 20.709419, -0.371860, -1.056990, 
-0.812450, 3.508010, -4.273670, -0.281490, 0.852300, -7.206900, 0.185180, -6.464970, 
1.039660, 1.177500, 0.551280, 1.014060, -1.562350, -0.291860, 2.302270, 0.710810, 1.317470, -0.454830, 
0.704670, 1.373470, -2.910520, -1.116580, -1.435470, -0.271020, 0.980830, -2.640680, 
11.333590, 0.471660, -0.099140, 0.653280, -0.225030, -0.942240, -0.535100, -0.189720, -0.008600, 0.705660, 
-0.761250, -0.274950, 0.115200, 0.841660, 0.108170, -9.753200, 0.296570, 0.320330, 
16.296600, -2.506190, 0.503450, 0.017360, -1.644240, 0.190940, -0.942110, -0.812820, 1.376770, -0.688070, 
0.371870, -2.941670, -2.791430, -1.137510, -0.365380, 5.561270, -0.812140, 2.969320, 
-4.705720, -0.441590, -0.759080, 2.752550, -0.060320, -0.551320, -10.861460, 2.734090, 1.869320, 0.239690, 
0.556630, -1.028930, -1.378090, 1.016330, 0.001640, 3.804740, -0.782160, 0.575710, 
-29.752230, 7.968770, -0.308580, -0.302460, 0.179080, 0.147600, -1.530360, 2.956560, 0.617470, 0.602080, 
0.123580, 5.346570, 6.947150, 0.302610, 0.073140, 20.575020, 5.293720, 0.955880, 
-2.389240, -1.445270, 0.220600, -0.363810, 14.310590, -0.311020, -12.381110, -0.448640, -1.619230, -0.483740, 
-0.258830, 2.265020, -0.012000, 0.735080, 1.759190, -6.114060, 1.698960, -0.921620, 
-1.486990, 1.647900, -1.143360, -1.369940, 3.357630, -0.502440, -6.812980, -2.724650, -0.225390, -1.090400, 
-0.783280, 5.436580, 12.394000, -0.624140, -0.510830, -1.258160, -1.019950, 9.932220, 
6.375230, 2.545550, -0.173490, -0.696220, 0.159940, 0.401690, -1.901150, 0.588640, -1.372570, -1.096390, 
-0.422010, 0.752420, 1.934860, -1.766080, -2.040210, 4.969420, 1.962360, -0.134800, 
0.454780, -1.601970, 0.172600, -0.719720, 3.984960, -2.133160, -2.799470, -0.056500, -3.238810, 1.688610, 
-1.026510, -1.195860, 9.199640, 1.017630, -0.014210, -3.519160, -2.348250, 3.933870, 
-12.999700, -0.335570, -0.352430, 0.484650, -0.393360, -0.231540, 16.154819, 3.173630, 0.859890, 0.755850, 
0.108010, -0.380230, 3.643080, -0.664810, 0.506230, 1.633690, -1.235430, 0.899740, 
1.949130, -0.013970, -0.634360, -0.920480, -0.820340, 2.100890, 14.034280, -19.839161, 0.252430, 0.249970, 
0.600970, -0.233590, 0.143010, 0.289870, 0.607930, 30.942520, 11.399590, 0.639740, 
1.033570, 0.168310, -0.894620, -0.148980, -1.653230, 0.899850, 4.120760, 0.065590, -0.000630, -0.098750, 
0.270660, -0.817140, -0.174060, -0.262940, -0.218530, 5.985340, -0.185190, -0.001710, 
3.540620, -0.560730, 0.738790, -0.422390, -0.107990, 3.113760, 2.438590, -8.479950, 0.736000, 0.618090, 
-0.185140, 0.226690, -1.698250, 0.531210, 1.791340, -0.342830, 1.929410, -0.172720, 
-0.269270, -5.746340, -0.655670, -4.014500, -5.055410, -7.712660, 2.345710, 0.057950, 0.096340, 0.587640, 
4.053210, 5.976760, 5.390520, -1.659630, 0.594870, -5.372340, 
0.581060, 7.410780, -0.839290, 5.577680, 2.285120, -7.250930, 0.726080, -1.006580, 1.341240, -0.071510, 
-9.052390, -7.729210, -0.437910, 0.596590, -4.216140, 1.376560, 
0.576200, -0.989640, 0.080640, -0.427180, -0.871010, 1.130340, -42.717731, 39.017990, 2.756090, -0.188300, 
13.484380, 1.241420, -26.927401, -22.372709, -4.818280, 8.514630, 
-7.142550, -3.310320, 9.572110, 0.385430, -0.579590, 0.305980, 0.558790, -7.823160, 6.699350, -4.358250, 
0.147120, -7.762120, -4.746240, 3.282310, -5.909550, 0.630770, 
-3.088210, -7.145530, -0.600600, -0.660390, 3.255380, 12.166430, 0.659220, 3.353520, 1.484620, 0.824810, 
0.374780, -12.549520, 0.216010, 0.460400, -4.948150, -17.630819, 
-3.304010, 6.923730, -7.622410, -3.212160, -0.971040, -1.646080, -5.284930, -1.163170, -1.968970, -1.162310, 
-0.633450, 5.215930, -0.299030, 3.274750, -2.454030, 3.420780, 
-3.599750, -12.847440, -4.603440, -1.247260, 2.120390, -1.020170, -2.349270, -4.171200, -6.697490, 7.111920, 
4.743030, -6.018130, -0.908060, 3.598010, 2.129900, -4.559500, 
-7.563940, -0.688060, 16.887039, 0.314370, -15.818990, 2.751090, 2.207380, 2.845800, 1.568610, -17.008730, 
-12.676720, -0.023990, -2.595970, 5.952170, -0.727110, 3.831690, 
-5.195080, 3.307230, -8.670230, -0.109390, 11.395380, 0.509280, 5.654150, 1.892200, 6.548130, -16.564831, 
-7.113520, -0.982210, -2.010820, -0.695760, -1.318740, -1.140050, 
-0.356680, 0.044260, 0.082130, -1.189910, 0.793090, 1.136200, 24.051920, -32.393108, 1.293630, 8.307600, 
-20.862711, 3.310160, 14.549350, -45.928890, -7.370800, -0.509400, 
15.191320, -0.206310, -12.254420, -0.276740, -9.155740, 0.212080, 4.751920, -1.003400, -6.876470, -14.211970, 
-8.178570, -0.011260, -1.187310, 0.240240, 4.890160, 0.043680, 
-17.581619, -0.131900, -5.653470, -1.071800, -14.078170, -3.382710, 0.625780, 5.977460, 0.790960, 13.184370, 
1.187750, -0.165440, 2.202430, -0.101390, 0.714050, -0.264200, 
4.605990, -3.148050, 11.417960, 0.023250, 7.447280, -0.020390, 1.173360, -0.442390, -11.063740, -8.321540, 
-5.784680, -4.610310, -8.769770, 2.070360, -1.728510, -5.201560, 
2.337360, 1.929060, 4.872490, 0.937410, -0.996380, -0.413380, -3.791970, -3.221770, -6.309650, -0.671700, 
-1.902530, -0.554830, 3.072220, -2.788900, 2.335940, -5.599450, 
0.508870, -8.740890, 10.135430, -1.225310, -10.371260, 0.071020, -0.781050, -0.103550, -11.659660, 6.370870, 
8.141850, -4.687350, -4.863270, 0.866870, 0.340290, -12.598640, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[58] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (noName) */
      0.0, 0.611800, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (noName) */
      0.0, 0.003690, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (noName) */
      0.0, 0.604720, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (noName) */
      0.0, 0.540640, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (noName) */
      0.0, 0.307720, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (noName) */
      0.0, 0.906190, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (noName) */
      0.0, 0.539780, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (noName) */
      0.0, 0.968440, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (noName) */
      0.0, 0.441250, 8,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (noName) */
      0.0, 0.934150, 8,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 11 (noName) */
      0.0, -0.280340, 8,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 12 (noName) */
      0.0, 0.133730, 8,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 13 (noName) */
      0.0, -0.650450, 8,
       &Sources[32] , 
       &Weights[32] , 
      },
    { /* unit 14 (noName) */
      0.0, -0.590500, 8,
       &Sources[40] , 
       &Weights[40] , 
      },
    { /* unit 15 (noName) */
      0.0, 0.185510, 8,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (noName) */
      0.0, 0.472440, 8,
       &Sources[56] , 
       &Weights[56] , 
      },
    { /* unit 17 (noName) */
      0.0, -1.897450, 8,
       &Sources[64] , 
       &Weights[64] , 
      },
    { /* unit 18 (noName) */
      0.0, -0.256010, 8,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 19 (noName) */
      0.0, -0.366070, 8,
       &Sources[80] , 
       &Weights[80] , 
      },
    { /* unit 20 (noName) */
      0.0, 0.615750, 8,
       &Sources[88] , 
       &Weights[88] , 
      },
    { /* unit 21 (noName) */
      0.0, 0.020320, 8,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 22 (noName) */
      0.0, 0.524650, 8,
       &Sources[104] , 
       &Weights[104] , 
      },
    { /* unit 23 (noName) */
      0.0, -0.504070, 8,
       &Sources[112] , 
       &Weights[112] , 
      },
    { /* unit 24 (noName) */
      0.0, -0.537930, 8,
       &Sources[120] , 
       &Weights[120] , 
      },
    { /* unit 25 (noName) */
      0.0, 0.989640, 8,
       &Sources[128] , 
       &Weights[128] , 
      },
    { /* unit 26 (noName) */
      0.0, -0.744180, 8,
       &Sources[136] , 
       &Weights[136] , 
      },
    { /* unit 27 (noName) */
      0.0, -0.633590, 18,
       &Sources[144] , 
       &Weights[144] , 
      },
    { /* unit 28 (noName) */
      0.0, -0.294290, 18,
       &Sources[162] , 
       &Weights[162] , 
      },
    { /* unit 29 (noName) */
      0.0, -0.741720, 18,
       &Sources[180] , 
       &Weights[180] , 
      },
    { /* unit 30 (noName) */
      0.0, -0.372150, 18,
       &Sources[198] , 
       &Weights[198] , 
      },
    { /* unit 31 (noName) */
      0.0, -0.102650, 18,
       &Sources[216] , 
       &Weights[216] , 
      },
    { /* unit 32 (noName) */
      0.0, -0.598050, 18,
       &Sources[234] , 
       &Weights[234] , 
      },
    { /* unit 33 (noName) */
      0.0, -0.363850, 18,
       &Sources[252] , 
       &Weights[252] , 
      },
    { /* unit 34 (noName) */
      0.0, 1.232010, 18,
       &Sources[270] , 
       &Weights[270] , 
      },
    { /* unit 35 (noName) */
      0.0, -1.123000, 18,
       &Sources[288] , 
       &Weights[288] , 
      },
    { /* unit 36 (noName) */
      0.0, 0.515500, 18,
       &Sources[306] , 
       &Weights[306] , 
      },
    { /* unit 37 (noName) */
      0.0, -0.220140, 18,
       &Sources[324] , 
       &Weights[324] , 
      },
    { /* unit 38 (noName) */
      0.0, -0.636250, 18,
       &Sources[342] , 
       &Weights[342] , 
      },
    { /* unit 39 (noName) */
      0.0, -0.204570, 18,
       &Sources[360] , 
       &Weights[360] , 
      },
    { /* unit 40 (noName) */
      0.0, -0.097360, 18,
       &Sources[378] , 
       &Weights[378] , 
      },
    { /* unit 41 (noName) */
      0.0, 0.062650, 18,
       &Sources[396] , 
       &Weights[396] , 
      },
    { /* unit 42 (noName) */
      0.0, -0.772400, 18,
       &Sources[414] , 
       &Weights[414] , 
      },
    { /* unit 43 (noName) */
      0.0, 0.354930, 16,
       &Sources[432] , 
       &Weights[432] , 
      },
    { /* unit 44 (noName) */
      0.0, -0.233440, 16,
       &Sources[448] , 
       &Weights[448] , 
      },
    { /* unit 45 (noName) */
      0.0, 0.576090, 16,
       &Sources[464] , 
       &Weights[464] , 
      },
    { /* unit 46 (noName) */
      0.0, -2.033460, 16,
       &Sources[480] , 
       &Weights[480] , 
      },
    { /* unit 47 (noName) */
      0.0, -1.200340, 16,
       &Sources[496] , 
       &Weights[496] , 
      },
    { /* unit 48 (noName) */
      0.0, -1.727020, 16,
       &Sources[512] , 
       &Weights[512] , 
      },
    { /* unit 49 (noName) */
      0.0, 0.476990, 16,
       &Sources[528] , 
       &Weights[528] , 
      },
    { /* unit 50 (noName) */
      0.0, -0.462650, 16,
       &Sources[544] , 
       &Weights[544] , 
      },
    { /* unit 51 (noName) */
      0.0, 0.495010, 16,
       &Sources[560] , 
       &Weights[560] , 
      },
    { /* unit 52 (noName) */
      0.0, -1.040330, 16,
       &Sources[576] , 
       &Weights[576] , 
      },
    { /* unit 53 (noName) */
      0.0, 0.530530, 16,
       &Sources[592] , 
       &Weights[592] , 
      },
    { /* unit 54 (noName) */
      0.0, -0.512280, 16,
       &Sources[608] , 
       &Weights[608] , 
      },
    { /* unit 55 (noName) */
      0.0, -0.299510, 16,
       &Sources[624] , 
       &Weights[624] , 
      },
    { /* unit 56 (noName) */
      0.0, -1.489210, 16,
       &Sources[640] , 
       &Weights[640] , 
      },
    { /* unit 57 (noName) */
      0.0, -0.525440, 16,
       &Sources[656] , 
       &Weights[656] , 
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

  static pUnit Hidden1[18] = {Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26}; /* members */

  static pUnit Hidden2[16] = {Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42}; /* members */

  static pUnit Output1[15] = {Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52, Units + 53, Units + 54, Units + 55, Units + 56, Units + 57}; /* members */

  static int Output[15] = {43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57};

  for(member = 0; member < 8; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 18; member++) {
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

  for (member = 0; member < 15; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for(member = 0; member < 15; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
