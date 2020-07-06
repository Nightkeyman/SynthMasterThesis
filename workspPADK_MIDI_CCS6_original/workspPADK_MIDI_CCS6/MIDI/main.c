// CSL Modules
#include <soc.h>
#include <csl_chip.h>
#include <csl_intc.h>
#include <csl_dmax.h>
#include <csl_mcasp.h>
#include <math.h>
// PADK Library
//#include "api/PADK.h"
#include "PADK.h"
#include <stdio.h>
#include <stdlib.h>

#include "PADK_UART.h"
#include "midi_fifo.h"
#include "filters.h"
#include "waveforms.h"
#include "var&fun.h"
//#include "myfft.h"


#define M_PI 3.14159
#define Fs 96000
#define F_sq 440
#define F_sqq 10000
#define N 2048
 short  table[64];
#pragma DATA_ALIGN(v, 8)
 float  v[2*N];
#pragma DATA_ALIGN(w, 8)
 float  w[N];

float waveform[2*N];
//float waveform2[2*N];
double s = 0;
double sig_amp = 10000000;
//float hann[1024] = {0,9.4308e-06,3.7723e-05,8.4875e-05,0.00015089,0.00023575,0.00033947,0.00046204,0.00060345,0.0007637,0.00094278,0.0011407,0.0013574,0.001593,0.0018473,0.0021204,0.0024123,0.002723,0.0030525,0.0034007,0.0037676,0.0041532,0.0045576,0.0049806,0.0054223,0.0058827,0.0063617,0.0068593,0.0073755,0.0079104,0.0084637,0.0090357,0.0096261,0.010235,0.010862,0.011508,0.012173,0.012855,0.013556,0.014276,0.015014,0.01577,0.016544,0.017336,0.018147,0.018976,0.019823,0.020688,0.021572,0.022473,0.023392,0.02433,0.025285,0.026258,0.027249,0.028258,0.029285,0.030329,0.031391,0.032471,0.033568,0.034683,0.035816,0.036966,0.038134,0.039319,0.040521,0.041741,0.042978,0.044232,0.045503,0.046792,0.048098,0.04942,0.05076,0.052117,0.05349,0.054881,0.056288,0.057712,0.059153,0.06061,0.062084,0.063574,0.065081,0.066604,0.068143,0.069699,0.071271,0.07286,0.074464,0.076084,0.077721,0.079373,0.081041,0.082725,0.084425,0.086141,0.087872,0.089618,0.09138,0.093158,0.094951,0.096759,0.098582,0.10042,0.10227,0.10414,0.10603,0.10792,0.10984,0.11177,0.11371,0.11567,0.11764,0.11962,0.12162,0.12364,0.12567,0.12771,0.12977,0.13184,0.13392,0.13602,0.13813,0.14026,0.1424,0.14455,0.14672,0.1489,0.15109,0.1533,0.15552,0.15775,0.15999,0.16225,0.16452,0.16681,0.1691,0.17141,0.17373,0.17606,0.17841,0.18077,0.18314,0.18552,0.18791,0.19032,0.19273,0.19516,0.1976,0.20005,0.20252,0.20499,0.20748,0.20997,0.21248,0.215,0.21752,0.22006,0.22261,0.22517,0.22774,0.23033,0.23292,0.23552,0.23813,0.24075,0.24338,0.24602,0.24867,0.25133,0.254,0.25668,0.25937,0.26206,0.26477,0.26748,0.2702,0.27294,0.27568,0.27843,0.28118,0.28395,0.28672,0.2895,0.29229,0.29509,0.29789,0.30071,0.30353,0.30636,0.30919,0.31203,0.31488,0.31774,0.3206,0.32347,0.32635,0.32923,0.33212,0.33502,0.33792,0.34083,0.34374,0.34666,0.34959,0.35252,0.35545,0.3584,0.36135,0.3643,0.36726,0.37022,0.37319,0.37616,0.37914,0.38212,0.38511,0.3881,0.39109,0.39409,0.3971,0.4001,0.40311,0.40613,0.40915,0.41217,0.41519,0.41822,0.42125,0.42429,0.42732,0.43036,0.43341,0.43645,0.4395,0.44255,0.4456,0.44865,0.45171,0.45477,0.45782,0.46089,0.46395,0.46701,0.47008,0.47314,0.47621,0.47928,0.48235,0.48542,0.48848,0.49156,0.49463,0.4977,0.50077,0.50384,0.50691,0.50998,0.51305,0.51612,0.51919,0.52226,0.52532,0.52839,0.53146,0.53452,0.53758,0.54065,0.54371,0.54676,0.54982,0.55288,0.55593,0.55898,0.56203,0.56507,0.56812,0.57116,0.5742,0.57723,0.58026,0.58329,0.58632,0.58934,0.59236,0.59538,0.59839,0.6014,0.60441,0.60741,0.6104,0.6134,0.61639,0.61937,0.62235,0.62533,0.6283,0.63126,0.63422,0.63718,0.64013,0.64307,0.64601,0.64895,0.65188,0.6548,0.65772,0.66063,0.66353,0.66643,0.66933,0.67221,0.67509,0.67796,0.68083,0.68369,0.68654,0.68939,0.69223,0.69506,0.69788,0.7007,0.70351,0.70631,0.7091,0.71189,0.71467,0.71744,0.7202,0.72295,0.72569,0.72843,0.73116,0.73388,0.73659,0.73929,0.74198,0.74466,0.74734,0.75,0.75265,0.7553,0.75794,0.76056,0.76318,0.76578,0.76838,0.77097,0.77354,0.77611,0.77866,0.78121,0.78374,0.78626,0.78878,0.79128,0.79377,0.79625,0.79872,0.80117,0.80362,0.80605,0.80848,0.81089,0.81329,0.81567,0.81805,0.82041,0.82276,0.8251,0.82743,0.82975,0.83205,0.83434,0.83661,0.83888,0.84113,0.84337,0.84559,0.84781,0.85001,0.85219,0.85437,0.85653,0.85867,0.86081,0.86292,0.86503,0.86712,0.8692,0.87126,0.87331,0.87535,0.87737,0.87938,0.88137,0.88335,0.88532,0.88727,0.8892,0.89112,0.89303,0.89492,0.89679,0.89865,0.9005,0.90233,0.90415,0.90595,0.90773,0.9095,0.91126,0.913,0.91472,0.91643,0.91812,0.91979,0.92145,0.9231,0.92473,0.92634,0.92794,0.92952,0.93108,0.93263,0.93416,0.93567,0.93717,0.93866,0.94012,0.94157,0.943,0.94442,0.94582,0.9472,0.94856,0.94991,0.95124,0.95256,0.95385,0.95513,0.9564,0.95764,0.95887,0.96008,0.96128,0.96245,0.96361,0.96475,0.96588,0.96698,0.96807,0.96914,0.9702,0.97123,0.97225,0.97325,0.97423,0.9752,0.97614,0.97707,0.97798,0.97887,0.97975,0.9806,0.98144,0.98226,0.98306,0.98385,0.98461,0.98536,0.98609,0.9868,0.98749,0.98816,0.98882,0.98945,0.99007,0.99067,0.99125,0.99182,0.99236,0.99288,0.99339,0.99388,0.99435,0.9948,0.99523,0.99565,0.99604,0.99642,0.99678,0.99711,0.99743,0.99774,0.99802,0.99828,0.99853,0.99875,0.99896,0.99915,0.99932,0.99947,0.9996,0.99971,0.99981,0.99988,0.99994,0.99998,1,1,0.99998,0.99994,0.99988,0.99981,0.99971,0.9996,0.99947,0.99932,0.99915,0.99896,0.99875,0.99853,0.99828,0.99802,0.99774,0.99743,0.99711,0.99678,0.99642,0.99604,0.99565,0.99523,0.9948,0.99435,0.99388,0.99339,0.99288,0.99236,0.99182,0.99125,0.99067,0.99007,0.98945,0.98882,0.98816,0.98749,0.9868,0.98609,0.98536,0.98461,0.98385,0.98306,0.98226,0.98144,0.9806,0.97975,0.97887,0.97798,0.97707,0.97614,0.9752,0.97423,0.97325,0.97225,0.97123,0.9702,0.96914,0.96807,0.96698,0.96588,0.96475,0.96361,0.96245,0.96128,0.96008,0.95887,0.95764,0.9564,0.95513,0.95385,0.95256,0.95124,0.94991,0.94856,0.9472,0.94582,0.94442,0.943,0.94157,0.94012,0.93866,0.93717,0.93567,0.93416,0.93263,0.93108,0.92952,0.92794,0.92634,0.92473,0.9231,0.92145,0.91979,0.91812,0.91643,0.91472,0.913,0.91126,0.9095,0.90773,0.90595,0.90415,0.90233,0.9005,0.89865,0.89679,0.89492,0.89303,0.89112,0.8892,0.88727,0.88532,0.88335,0.88137,0.87938,0.87737,0.87535,0.87331,0.87126,0.8692,0.86712,0.86503,0.86292,0.86081,0.85867,0.85653,0.85437,0.85219,0.85001,0.84781,0.84559,0.84337,0.84113,0.83888,0.83661,0.83434,0.83205,0.82975,0.82743,0.8251,0.82276,0.82041,0.81805,0.81567,0.81329,0.81089,0.80848,0.80605,0.80362,0.80117,0.79872,0.79625,0.79377,0.79128,0.78878,0.78626,0.78374,0.78121,0.77866,0.77611,0.77354,0.77097,0.76838,0.76578,0.76318,0.76056,0.75794,0.7553,0.75265,0.75,0.74734,0.74466,0.74198,0.73929,0.73659,0.73388,0.73116,0.72843,0.72569,0.72295,0.7202,0.71744,0.71467,0.71189,0.7091,0.70631,0.70351,0.7007,0.69788,0.69506,0.69223,0.68939,0.68654,0.68369,0.68083,0.67796,0.67509,0.67221,0.66933,0.66643,0.66353,0.66063,0.65772,0.6548,0.65188,0.64895,0.64601,0.64307,0.64013,0.63718,0.63422,0.63126,0.6283,0.62533,0.62235,0.61937,0.61639,0.6134,0.6104,0.60741,0.60441,0.6014,0.59839,0.59538,0.59236,0.58934,0.58632,0.58329,0.58026,0.57723,0.5742,0.57116,0.56812,0.56507,0.56203,0.55898,0.55593,0.55288,0.54982,0.54676,0.54371,0.54065,0.53758,0.53452,0.53146,0.52839,0.52532,0.52226,0.51919,0.51612,0.51305,0.50998,0.50691,0.50384,0.50077,0.4977,0.49463,0.49156,0.48848,0.48542,0.48235,0.47928,0.47621,0.47314,0.47008,0.46701,0.46395,0.46089,0.45782,0.45477,0.45171,0.44865,0.4456,0.44255,0.4395,0.43645,0.43341,0.43036,0.42732,0.42429,0.42125,0.41822,0.41519,0.41217,0.40915,0.40613,0.40311,0.4001,0.3971,0.39409,0.39109,0.3881,0.38511,0.38212,0.37914,0.37616,0.37319,0.37022,0.36726,0.3643,0.36135,0.3584,0.35545,0.35252,0.34959,0.34666,0.34374,0.34083,0.33792,0.33502,0.33212,0.32923,0.32635,0.32347,0.3206,0.31774,0.31488,0.31203,0.30919,0.30636,0.30353,0.30071,0.29789,0.29509,0.29229,0.2895,0.28672,0.28395,0.28118,0.27843,0.27568,0.27294,0.2702,0.26748,0.26477,0.26206,0.25937,0.25668,0.254,0.25133,0.24867,0.24602,0.24338,0.24075,0.23813,0.23552,0.23292,0.23033,0.22774,0.22517,0.22261,0.22006,0.21752,0.215,0.21248,0.20997,0.20748,0.20499,0.20252,0.20005,0.1976,0.19516,0.19273,0.19032,0.18791,0.18552,0.18314,0.18077,0.17841,0.17606,0.17373,0.17141,0.1691,0.16681,0.16452,0.16225,0.15999,0.15775,0.15552,0.1533,0.15109,0.1489,0.14672,0.14455,0.1424,0.14026,0.13813,0.13602,0.13392,0.13184,0.12977,0.12771,0.12567,0.12364,0.12162,0.11962,0.11764,0.11567,0.11371,0.11177,0.10984,0.10792,0.10603,0.10414,0.10227,0.10042,0.098582,0.096759,0.094951,0.093158,0.09138,0.089618,0.087872,0.086141,0.084425,0.082725,0.081041,0.079373,0.077721,0.076084,0.074464,0.07286,0.071271,0.069699,0.068143,0.066604,0.065081,0.063574,0.062084,0.06061,0.059153,0.057712,0.056288,0.054881,0.05349,0.052117,0.05076,0.04942,0.048098,0.046792,0.045503,0.044232,0.042978,0.041741,0.040521,0.039319,0.038134,0.036966,0.035816,0.034683,0.033568,0.032471,0.031391,0.030329,0.029285,0.028258,0.027249,0.026258,0.025285,0.02433,0.023392,0.022473,0.021572,0.020688,0.019823,0.018976,0.018147,0.017336,0.016544,0.01577,0.015014,0.014276,0.013556,0.012855,0.012173,0.011508,0.010862,0.010235,0.0096261,0.0090357,0.0084637,0.0079104,0.0073755,0.0068593,0.0063617,0.0058827,0.0054223,0.0049806,0.0045576,0.0041532,0.0037676,0.0034007,0.0030525,0.002723,0.0024123,0.0021204,0.0018473,0.001593,0.0013574,0.0011407,0.00094278,0.0007637,0.00060345,0.00046204,0.00033947,0.00023575,0.00015089,8.4875e-05,3.7723e-05,9.4308e-06,0};
float hann[2048] = {0,2.3554e-06,9.4216e-06,2.1198e-05,3.7686e-05,5.8884e-05,8.4792e-05,0.00011541,0.00015074,0.00019077,0.00023552,0.00028498,0.00033914,0.00039801,0.00046159,0.00052987,0.00060286,0.00068056,0.00076295,0.00085006,0.00094186,0.0010384,0.0011396,0.0012455,0.0013561,0.0014714,0.0015914,0.0017161,0.0018455,0.0019796,0.0021184,0.0022618,0.00241,0.0025628,0.0027204,0.0028826,0.0030495,0.0032211,0.0033973,0.0035783,0.0037639,0.0039542,0.0041492,0.0043488,0.0045531,0.0047621,0.0049757,0.0051941,0.005417,0.0056447,0.0058769,0.0061139,0.0063555,0.0066017,0.0068526,0.0071082,0.0073684,0.0076332,0.0079026,0.0081768,0.0084555,0.0087389,0.0090269,0.0093195,0.0096167,0.0099186,0.010225,0.010536,0.010852,0.011172,0.011497,0.011827,0.012161,0.012499,0.012843,0.013191,0.013543,0.0139,0.014262,0.014628,0.014999,0.015374,0.015754,0.016139,0.016528,0.016921,0.01732,0.017722,0.01813,0.018541,0.018958,0.019379,0.019804,0.020234,0.020668,0.021107,0.021551,0.021999,0.022451,0.022908,0.02337,0.023836,0.024306,0.024781,0.02526,0.025744,0.026233,0.026725,0.027223,0.027724,0.028231,0.028741,0.029256,0.029776,0.0303,0.030828,0.031361,0.031898,0.03244,0.032986,0.033536,0.034091,0.03465,0.035214,0.035781,0.036354,0.03693,0.037512,0.038097,0.038687,0.039281,0.039879,0.040482,0.041089,0.041701,0.042316,0.042936,0.043561,0.044189,0.044822,0.04546,0.046101,0.046747,0.047397,0.048052,0.04871,0.049373,0.05004,0.050711,0.051387,0.052067,0.052751,0.053439,0.054132,0.054828,0.055529,0.056234,0.056943,0.057657,0.058374,0.059096,0.059822,0.060552,0.061286,0.062024,0.062767,0.063513,0.064264,0.065019,0.065777,0.06654,0.067307,0.068078,0.068854,0.069633,0.070416,0.071204,0.071995,0.07279,0.07359,0.074393,0.075201,0.076012,0.076828,0.077647,0.07847,0.079298,0.080129,0.080964,0.081804,0.082647,0.083494,0.084345,0.0852,0.086059,0.086922,0.087788,0.088659,0.089533,0.090412,0.091294,0.09218,0.09307,0.093963,0.094861,0.095762,0.096667,0.097576,0.098489,0.099406,0.10033,0.10125,0.10218,0.10311,0.10404,0.10498,0.10593,0.10687,0.10782,0.10878,0.10973,0.1107,0.11166,0.11263,0.1136,0.11458,0.11556,0.11654,0.11753,0.11852,0.11951,0.12051,0.12151,0.12251,0.12352,0.12453,0.12555,0.12657,0.12759,0.12862,0.12965,0.13068,0.13171,0.13275,0.1338,0.13484,0.13589,0.13695,0.138,0.13907,0.14013,0.1412,0.14227,0.14334,0.14442,0.1455,0.14658,0.14767,0.14876,0.14985,0.15095,0.15205,0.15316,0.15426,0.15537,0.15649,0.1576,0.15872,0.15985,0.16097,0.1621,0.16324,0.16437,0.16551,0.16665,0.1678,0.16895,0.1701,0.17125,0.17241,0.17357,0.17474,0.1759,0.17707,0.17825,0.17942,0.1806,0.18178,0.18297,0.18416,0.18535,0.18654,0.18774,0.18894,0.19014,0.19135,0.19256,0.19377,0.19499,0.1962,0.19742,0.19865,0.19987,0.2011,0.20233,0.20357,0.20481,0.20605,0.20729,0.20853,0.20978,0.21103,0.21229,0.21354,0.2148,0.21606,0.21733,0.2186,0.21987,0.22114,0.22241,0.22369,0.22497,0.22626,0.22754,0.22883,0.23012,0.23141,0.23271,0.23401,0.23531,0.23661,0.23792,0.23923,0.24054,0.24185,0.24316,0.24448,0.2458,0.24713,0.24845,0.24978,0.25111,0.25244,0.25378,0.25511,0.25645,0.25779,0.25914,0.26048,0.26183,0.26318,0.26453,0.26589,0.26725,0.26861,0.26997,0.27133,0.2727,0.27407,0.27544,0.27681,0.27818,0.27956,0.28094,0.28232,0.2837,0.28509,0.28647,0.28786,0.28925,0.29064,0.29204,0.29344,0.29483,0.29623,0.29764,0.29904,0.30045,0.30186,0.30327,0.30468,0.30609,0.30751,0.30892,0.31034,0.31176,0.31319,0.31461,0.31604,0.31747,0.3189,0.32033,0.32176,0.32319,0.32463,0.32607,0.32751,0.32895,0.33039,0.33184,0.33328,0.33473,0.33618,0.33763,0.33908,0.34054,0.34199,0.34345,0.34491,0.34637,0.34783,0.34929,0.35076,0.35222,0.35369,0.35516,0.35663,0.3581,0.35957,0.36104,0.36252,0.36399,0.36547,0.36695,0.36843,0.36991,0.37139,0.37288,0.37436,0.37585,0.37734,0.37882,0.38031,0.3818,0.3833,0.38479,0.38628,0.38778,0.38927,0.39077,0.39227,0.39377,0.39527,0.39677,0.39827,0.39978,0.40128,0.40278,0.40429,0.4058,0.4073,0.40881,0.41032,0.41183,0.41334,0.41486,0.41637,0.41788,0.4194,0.42091,0.42243,0.42394,0.42546,0.42698,0.4285,0.43002,0.43154,0.43306,0.43458,0.4361,0.43762,0.43915,0.44067,0.44219,0.44372,0.44524,0.44677,0.4483,0.44982,0.45135,0.45288,0.45441,0.45593,0.45746,0.45899,0.46052,0.46205,0.46358,0.46511,0.46664,0.46818,0.46971,0.47124,0.47277,0.4743,0.47584,0.47737,0.4789,0.48044,0.48197,0.4835,0.48504,0.48657,0.48811,0.48964,0.49118,0.49271,0.49424,0.49578,0.49731,0.49885,0.50038,0.50192,0.50345,0.50499,0.50652,0.50806,0.50959,0.51113,0.51266,0.51419,0.51573,0.51726,0.5188,0.52033,0.52186,0.5234,0.52493,0.52646,0.52799,0.52953,0.53106,0.53259,0.53412,0.53565,0.53718,0.53871,0.54024,0.54177,0.5433,0.54483,0.54636,0.54789,0.54941,0.55094,0.55247,0.55399,0.55552,0.55704,0.55857,0.56009,0.56162,0.56314,0.56466,0.56618,0.5677,0.56922,0.57074,0.57226,0.57378,0.5753,0.57681,0.57833,0.57985,0.58136,0.58287,0.58439,0.5859,0.58741,0.58892,0.59043,0.59194,0.59345,0.59496,0.59646,0.59797,0.59947,0.60098,0.60248,0.60398,0.60548,0.60698,0.60848,0.60998,0.61147,0.61297,0.61446,0.61596,0.61745,0.61894,0.62043,0.62192,0.62341,0.62489,0.62638,0.62786,0.62935,0.63083,0.63231,0.63379,0.63527,0.63674,0.63822,0.63969,0.64117,0.64264,0.64411,0.64558,0.64705,0.64851,0.64998,0.65144,0.6529,0.65436,0.65582,0.65728,0.65874,0.66019,0.66164,0.66309,0.66454,0.66599,0.66744,0.66889,0.67033,0.67177,0.67321,0.67465,0.67609,0.67752,0.67896,0.68039,0.68182,0.68325,0.68468,0.6861,0.68752,0.68895,0.69037,0.69178,0.6932,0.69462,0.69603,0.69744,0.69885,0.70026,0.70166,0.70306,0.70447,0.70587,0.70726,0.70866,0.71005,0.71144,0.71283,0.71422,0.71561,0.71699,0.71837,0.71975,0.72113,0.72251,0.72388,0.72525,0.72662,0.72799,0.72935,0.73071,0.73207,0.73343,0.73479,0.73614,0.73749,0.73884,0.74019,0.74154,0.74288,0.74422,0.74556,0.74689,0.74823,0.74956,0.75089,0.75221,0.75354,0.75486,0.75618,0.75749,0.75881,0.76012,0.76143,0.76274,0.76404,0.76534,0.76664,0.76794,0.76923,0.77053,0.77182,0.7731,0.77439,0.77567,0.77695,0.77822,0.7795,0.78077,0.78204,0.7833,0.78457,0.78583,0.78708,0.78834,0.78959,0.79084,0.79209,0.79333,0.79458,0.79581,0.79705,0.79828,0.79951,0.80074,0.80197,0.80319,0.80441,0.80562,0.80684,0.80805,0.80925,0.81046,0.81166,0.81286,0.81405,0.81525,0.81644,0.81762,0.81881,0.81999,0.82117,0.82234,0.82351,0.82468,0.82585,0.82701,0.82817,0.82932,0.83048,0.83163,0.83277,0.83392,0.83506,0.8362,0.83733,0.83846,0.83959,0.84072,0.84184,0.84296,0.84407,0.84518,0.84629,0.8474,0.8485,0.8496,0.85069,0.85179,0.85287,0.85396,0.85504,0.85612,0.8572,0.85827,0.85934,0.8604,0.86147,0.86252,0.86358,0.86463,0.86568,0.86672,0.86777,0.8688,0.86984,0.87087,0.8719,0.87292,0.87394,0.87496,0.87597,0.87698,0.87799,0.87899,0.87999,0.88099,0.88198,0.88297,0.88395,0.88493,0.88591,0.88689,0.88786,0.88882,0.88979,0.89074,0.8917,0.89265,0.8936,0.89455,0.89549,0.89642,0.89736,0.89829,0.89921,0.90013,0.90105,0.90197,0.90288,0.90379,0.90469,0.90559,0.90648,0.90738,0.90826,0.90915,0.91003,0.9109,0.91178,0.91265,0.91351,0.91437,0.91523,0.91608,0.91693,0.91778,0.91862,0.91945,0.92029,0.92112,0.92194,0.92276,0.92358,0.92439,0.9252,0.92601,0.92681,0.92761,0.9284,0.92919,0.92998,0.93076,0.93153,0.93231,0.93308,0.93384,0.9346,0.93536,0.93611,0.93686,0.93761,0.93835,0.93908,0.93981,0.94054,0.94127,0.94199,0.9427,0.94341,0.94412,0.94482,0.94552,0.94622,0.94691,0.94759,0.94827,0.94895,0.94962,0.95029,0.95096,0.95162,0.95228,0.95293,0.95358,0.95422,0.95486,0.95549,0.95613,0.95675,0.95737,0.95799,0.95861,0.95921,0.95982,0.96042,0.96102,0.96161,0.9622,0.96278,0.96336,0.96393,0.9645,0.96507,0.96563,0.96619,0.96674,0.96729,0.96783,0.96837,0.96891,0.96944,0.96996,0.97048,0.971,0.97151,0.97202,0.97253,0.97303,0.97352,0.97401,0.9745,0.97498,0.97546,0.97593,0.9764,0.97686,0.97732,0.97778,0.97823,0.97867,0.97911,0.97955,0.97998,0.98041,0.98083,0.98125,0.98167,0.98207,0.98248,0.98288,0.98328,0.98367,0.98405,0.98444,0.98481,0.98519,0.98556,0.98592,0.98628,0.98663,0.98698,0.98733,0.98767,0.98801,0.98834,0.98867,0.98899,0.98931,0.98962,0.98993,0.99023,0.99053,0.99083,0.99112,0.9914,0.99168,0.99196,0.99223,0.9925,0.99276,0.99302,0.99327,0.99352,0.99377,0.99401,0.99424,0.99447,0.9947,0.99492,0.99513,0.99534,0.99555,0.99575,0.99595,0.99614,0.99633,0.99651,0.99669,0.99687,0.99703,0.9972,0.99736,0.99751,0.99766,0.99781,0.99795,0.99809,0.99822,0.99835,0.99847,0.99859,0.9987,0.99881,0.99891,0.99901,0.9991,0.99919,0.99928,0.99936,0.99943,0.9995,0.99957,0.99963,0.99969,0.99974,0.99979,0.99983,0.99987,0.9999,0.99993,0.99995,0.99997,0.99999,0.99999,1,1,0.99999,0.99999,0.99997,0.99995,0.99993,0.9999,0.99987,0.99983,0.99979,0.99974,0.99969,0.99963,0.99957,0.9995,0.99943,0.99936,0.99928,0.99919,0.9991,0.99901,0.99891,0.99881,0.9987,0.99859,0.99847,0.99835,0.99822,0.99809,0.99795,0.99781,0.99766,0.99751,0.99736,0.9972,0.99703,0.99687,0.99669,0.99651,0.99633,0.99614,0.99595,0.99575,0.99555,0.99534,0.99513,0.99492,0.9947,0.99447,0.99424,0.99401,0.99377,0.99352,0.99327,0.99302,0.99276,0.9925,0.99223,0.99196,0.99168,0.9914,0.99112,0.99083,0.99053,0.99023,0.98993,0.98962,0.98931,0.98899,0.98867,0.98834,0.98801,0.98767,0.98733,0.98698,0.98663,0.98628,0.98592,0.98556,0.98519,0.98481,0.98444,0.98405,0.98367,0.98328,0.98288,0.98248,0.98207,0.98167,0.98125,0.98083,0.98041,0.97998,0.97955,0.97911,0.97867,0.97823,0.97778,0.97732,0.97686,0.9764,0.97593,0.97546,0.97498,0.9745,0.97401,0.97352,0.97303,0.97253,0.97202,0.97151,0.971,0.97048,0.96996,0.96944,0.96891,0.96837,0.96783,0.96729,0.96674,0.96619,0.96563,0.96507,0.9645,0.96393,0.96336,0.96278,0.9622,0.96161,0.96102,0.96042,0.95982,0.95921,0.95861,0.95799,0.95737,0.95675,0.95613,0.95549,0.95486,0.95422,0.95358,0.95293,0.95228,0.95162,0.95096,0.95029,0.94962,0.94895,0.94827,0.94759,0.94691,0.94622,0.94552,0.94482,0.94412,0.94341,0.9427,0.94199,0.94127,0.94054,0.93981,0.93908,0.93835,0.93761,0.93686,0.93611,0.93536,0.9346,0.93384,0.93308,0.93231,0.93153,0.93076,0.92998,0.92919,0.9284,0.92761,0.92681,0.92601,0.9252,0.92439,0.92358,0.92276,0.92194,0.92112,0.92029,0.91945,0.91862,0.91778,0.91693,0.91608,0.91523,0.91437,0.91351,0.91265,0.91178,0.9109,0.91003,0.90915,0.90826,0.90738,0.90648,0.90559,0.90469,0.90379,0.90288,0.90197,0.90105,0.90013,0.89921,0.89829,0.89736,0.89642,0.89549,0.89455,0.8936,0.89265,0.8917,0.89074,0.88979,0.88882,0.88786,0.88689,0.88591,0.88493,0.88395,0.88297,0.88198,0.88099,0.87999,0.87899,0.87799,0.87698,0.87597,0.87496,0.87394,0.87292,0.8719,0.87087,0.86984,0.8688,0.86777,0.86672,0.86568,0.86463,0.86358,0.86252,0.86147,0.8604,0.85934,0.85827,0.8572,0.85612,0.85504,0.85396,0.85287,0.85179,0.85069,0.8496,0.8485,0.8474,0.84629,0.84518,0.84407,0.84296,0.84184,0.84072,0.83959,0.83846,0.83733,0.8362,0.83506,0.83392,0.83277,0.83163,0.83048,0.82932,0.82817,0.82701,0.82585,0.82468,0.82351,0.82234,0.82117,0.81999,0.81881,0.81762,0.81644,0.81525,0.81405,0.81286,0.81166,0.81046,0.80925,0.80805,0.80684,0.80562,0.80441,0.80319,0.80197,0.80074,0.79951,0.79828,0.79705,0.79581,0.79458,0.79333,0.79209,0.79084,0.78959,0.78834,0.78708,0.78583,0.78457,0.7833,0.78204,0.78077,0.7795,0.77822,0.77695,0.77567,0.77439,0.7731,0.77182,0.77053,0.76923,0.76794,0.76664,0.76534,0.76404,0.76274,0.76143,0.76012,0.75881,0.75749,0.75618,0.75486,0.75354,0.75221,0.75089,0.74956,0.74823,0.74689,0.74556,0.74422,0.74288,0.74154,0.74019,0.73884,0.73749,0.73614,0.73479,0.73343,0.73207,0.73071,0.72935,0.72799,0.72662,0.72525,0.72388,0.72251,0.72113,0.71975,0.71837,0.71699,0.71561,0.71422,0.71283,0.71144,0.71005,0.70866,0.70726,0.70587,0.70447,0.70306,0.70166,0.70026,0.69885,0.69744,0.69603,0.69462,0.6932,0.69178,0.69037,0.68895,0.68752,0.6861,0.68468,0.68325,0.68182,0.68039,0.67896,0.67752,0.67609,0.67465,0.67321,0.67177,0.67033,0.66889,0.66744,0.66599,0.66454,0.66309,0.66164,0.66019,0.65874,0.65728,0.65582,0.65436,0.6529,0.65144,0.64998,0.64851,0.64705,0.64558,0.64411,0.64264,0.64117,0.63969,0.63822,0.63674,0.63527,0.63379,0.63231,0.63083,0.62935,0.62786,0.62638,0.62489,0.62341,0.62192,0.62043,0.61894,0.61745,0.61596,0.61446,0.61297,0.61147,0.60998,0.60848,0.60698,0.60548,0.60398,0.60248,0.60098,0.59947,0.59797,0.59646,0.59496,0.59345,0.59194,0.59043,0.58892,0.58741,0.5859,0.58439,0.58287,0.58136,0.57985,0.57833,0.57681,0.5753,0.57378,0.57226,0.57074,0.56922,0.5677,0.56618,0.56466,0.56314,0.56162,0.56009,0.55857,0.55704,0.55552,0.55399,0.55247,0.55094,0.54941,0.54789,0.54636,0.54483,0.5433,0.54177,0.54024,0.53871,0.53718,0.53565,0.53412,0.53259,0.53106,0.52953,0.52799,0.52646,0.52493,0.5234,0.52186,0.52033,0.5188,0.51726,0.51573,0.51419,0.51266,0.51113,0.50959,0.50806,0.50652,0.50499,0.50345,0.50192,0.50038,0.49885,0.49731,0.49578,0.49424,0.49271,0.49118,0.48964,0.48811,0.48657,0.48504,0.4835,0.48197,0.48044,0.4789,0.47737,0.47584,0.4743,0.47277,0.47124,0.46971,0.46818,0.46664,0.46511,0.46358,0.46205,0.46052,0.45899,0.45746,0.45593,0.45441,0.45288,0.45135,0.44982,0.4483,0.44677,0.44524,0.44372,0.44219,0.44067,0.43915,0.43762,0.4361,0.43458,0.43306,0.43154,0.43002,0.4285,0.42698,0.42546,0.42394,0.42243,0.42091,0.4194,0.41788,0.41637,0.41486,0.41334,0.41183,0.41032,0.40881,0.4073,0.4058,0.40429,0.40278,0.40128,0.39978,0.39827,0.39677,0.39527,0.39377,0.39227,0.39077,0.38927,0.38778,0.38628,0.38479,0.3833,0.3818,0.38031,0.37882,0.37734,0.37585,0.37436,0.37288,0.37139,0.36991,0.36843,0.36695,0.36547,0.36399,0.36252,0.36104,0.35957,0.3581,0.35663,0.35516,0.35369,0.35222,0.35076,0.34929,0.34783,0.34637,0.34491,0.34345,0.34199,0.34054,0.33908,0.33763,0.33618,0.33473,0.33328,0.33184,0.33039,0.32895,0.32751,0.32607,0.32463,0.32319,0.32176,0.32033,0.3189,0.31747,0.31604,0.31461,0.31319,0.31176,0.31034,0.30892,0.30751,0.30609,0.30468,0.30327,0.30186,0.30045,0.29904,0.29764,0.29623,0.29483,0.29344,0.29204,0.29064,0.28925,0.28786,0.28647,0.28509,0.2837,0.28232,0.28094,0.27956,0.27818,0.27681,0.27544,0.27407,0.2727,0.27133,0.26997,0.26861,0.26725,0.26589,0.26453,0.26318,0.26183,0.26048,0.25914,0.25779,0.25645,0.25511,0.25378,0.25244,0.25111,0.24978,0.24845,0.24713,0.2458,0.24448,0.24316,0.24185,0.24054,0.23923,0.23792,0.23661,0.23531,0.23401,0.23271,0.23141,0.23012,0.22883,0.22754,0.22626,0.22497,0.22369,0.22241,0.22114,0.21987,0.2186,0.21733,0.21606,0.2148,0.21354,0.21229,0.21103,0.20978,0.20853,0.20729,0.20605,0.20481,0.20357,0.20233,0.2011,0.19987,0.19865,0.19742,0.1962,0.19499,0.19377,0.19256,0.19135,0.19014,0.18894,0.18774,0.18654,0.18535,0.18416,0.18297,0.18178,0.1806,0.17942,0.17825,0.17707,0.1759,0.17474,0.17357,0.17241,0.17125,0.1701,0.16895,0.1678,0.16665,0.16551,0.16437,0.16324,0.1621,0.16097,0.15985,0.15872,0.1576,0.15649,0.15537,0.15426,0.15316,0.15205,0.15095,0.14985,0.14876,0.14767,0.14658,0.1455,0.14442,0.14334,0.14227,0.1412,0.14013,0.13907,0.138,0.13695,0.13589,0.13484,0.1338,0.13275,0.13171,0.13068,0.12965,0.12862,0.12759,0.12657,0.12555,0.12453,0.12352,0.12251,0.12151,0.12051,0.11951,0.11852,0.11753,0.11654,0.11556,0.11458,0.1136,0.11263,0.11166,0.1107,0.10973,0.10878,0.10782,0.10687,0.10593,0.10498,0.10404,0.10311,0.10218,0.10125,0.10033,0.099406,0.098489,0.097576,0.096667,0.095762,0.094861,0.093963,0.09307,0.09218,0.091294,0.090412,0.089533,0.088659,0.087788,0.086922,0.086059,0.0852,0.084345,0.083494,0.082647,0.081804,0.080964,0.080129,0.079298,0.07847,0.077647,0.076828,0.076012,0.075201,0.074393,0.07359,0.07279,0.071995,0.071204,0.070416,0.069633,0.068854,0.068078,0.067307,0.06654,0.065777,0.065019,0.064264,0.063513,0.062767,0.062024,0.061286,0.060552,0.059822,0.059096,0.058374,0.057657,0.056943,0.056234,0.055529,0.054828,0.054132,0.053439,0.052751,0.052067,0.051387,0.050711,0.05004,0.049373,0.04871,0.048052,0.047397,0.046747,0.046101,0.04546,0.044822,0.044189,0.043561,0.042936,0.042316,0.041701,0.041089,0.040482,0.039879,0.039281,0.038687,0.038097,0.037512,0.03693,0.036354,0.035781,0.035214,0.03465,0.034091,0.033536,0.032986,0.03244,0.031898,0.031361,0.030828,0.0303,0.029776,0.029256,0.028741,0.028231,0.027724,0.027223,0.026725,0.026233,0.025744,0.02526,0.024781,0.024306,0.023836,0.02337,0.022908,0.022451,0.021999,0.021551,0.021107,0.020668,0.020234,0.019804,0.019379,0.018958,0.018541,0.01813,0.017722,0.01732,0.016921,0.016528,0.016139,0.015754,0.015374,0.014999,0.014628,0.014262,0.0139,0.013543,0.013191,0.012843,0.012499,0.012161,0.011827,0.011497,0.011172,0.010852,0.010536,0.010225,0.0099186,0.0096167,0.0093195,0.0090269,0.0087389,0.0084555,0.0081768,0.0079026,0.0076332,0.0073684,0.0071082,0.0068526,0.0066017,0.0063555,0.0061139,0.0058769,0.0056447,0.005417,0.0051941,0.0049757,0.0047621,0.0045531,0.0043488,0.0041492,0.0039542,0.0037639,0.0035783,0.0033973,0.0032211,0.0030495,0.0028826,0.0027204,0.0025628,0.00241,0.0022618,0.0021184,0.0019796,0.0018455,0.0017161,0.0015914,0.0014714,0.0013561,0.0012455,0.0011396,0.0010384,0.00094186,0.00085006,0.00076295,0.00068056,0.00060286,0.00052987,0.00046159,0.00039801,0.00033914,0.00028498,0.00023552,0.00019077,0.00015074,0.00011541,8.4792e-05,5.8884e-05,3.7686e-05,2.1198e-05,9.4216e-06,2.3554e-06,0};
unsigned char data_midi[1];
int notes[128];
extern volatile unsigned PP;

float sinusek[2000];
float mySin(int counter, float freq)
{
	return sinusek[(int)((float)counter*freq*(0.02083333333))%2000]; //2000/96000
}
float mySqr(int counter, float freq)
{
	if(sinusek[(int)((float)counter*freq*(0.02083333333))%2000] >= 0) {
		return sig_amp;
	} else {
		return -1*sig_amp;
	}
}
//
//  Main Function
//
#define SIN(counter, freq) sinusek[(int)((float)counter*freq*(0.02083333333))%2000]
int main( int argc, char *argv[] ) {

	#include "ALL_init.h"

	// INITIALIZE VARIABLES
	int i = 0, j = 0;
	int freq_wav = 0;
	int mono = 0;
	for(i = 0; i < 128; i++)
		notes[i] = 0;

	sin_wave(440, sig_amp);
	// HANNING TIME WINDOW
	for(i = 0; i < 2*N; i+=2) {
		//v[i] = v[i]*hann[i/2];
		waveform[i] = waveform[i]*hann[i/2];
		waveform[i+1] = waveform[i+1]*hann[i/2];
	}

	// FFT
	fft_full();

	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		v[i] = v[i]/(float)N;		// Skalowanie do najwyzszej probki --> moze to zrobic jakos lepiej ze znalezieniem najwiekszej wartosci?
		v[i+1] = v[i+1]/(float)N;
	}

	// Filtering
	highPassFilter(220);

	// Inverse FFT
	ifft_full();

	/*---------------------------------------------------------------*/
	/*							 MAIN LOOP 		                     */
	/*---------------------------------------------------------------*/
	for (i = 0; i < 2000; i++){
		sinusek[i] = sig_amp*sin(2.0*M_PI*(i/2000.0));
	}
	for(i = 0; i < 80; i++) {
		dmaxDacBuffer[0][0][0][i] = 1*sig_amp;
		dmaxDacBuffer[1][0][0][i] = -1*sig_amp;
	}


	int k = 0;
    while(1)  {
    	if(PP == 0 || PP == 1) {
    		for(i = 0; i < FRAME_SIZE; i++) {
    			dmaxDacBuffer[PP][0][0][i] = 0.8*mySin(k+i, 220) + 0.9*mySin(k+i, 440) + 0.8*mySin(k+i, 660) +
    					+ 0.8*mySin(k+i, 880) + 0.8*mySin(k+i, 1320)
						+ 0.8*mySin(k+i, 1760) + 0.8*mySin(k+i, 2200)
						+ 0.8*mySin(k+i, 2640) + 0.8*mySin(k+i, 3520);
    			//dmaxDacBuffer[PP][0][0][i] = 0.5*mySqr(k+i, 220) + 0.9*mySqr(k+i, 440) + 0.8*mySqr(k+i, 660)
    			//+ 0.8*mySqr(k+i, 880) + 0.8*mySqr(k+i, 1320);
    		}
    		k += FRAME_SIZE;
        	PP = 3;
    	}

    	// MONOPHONIC KEYBOARD
    	/*
    	if(mono == 1) {
    		for(i = 0; i < 128; i++) {
				if(notes[i] == 1) {
					freq_wav = 261*pow(1.059463,i - 48);
					for(j = 0; j < 2*N; j++) {
						waveform[j] = sig_amp*(sin((double)(j)*2.0*M_PI*freq_wav*(1.0/Fs)));
						waveform[j] = waveform[j]*hann[j/2];
					}
				}
				while(notes[i] == 1);
				for(j = 0; j < 2*N; j++);
					waveform[j] = 0;
    		}
    	// POLYPHONIC KEYBOARD
    	} else {
    		for(j = 0; j < 2*N; j++)
				waveform2[j] = 0;
			for(i = 0; i < 128; i++) {
				if(notes[i] == 1) {
					freq_wav = 261*pow(1.059463,i - 48);
					for(j = 0; j < 2*N; j++) {
						s = sig_amp*(sin((double)(j)*2.0*M_PI*freq_wav*(1.0/Fs)));
						waveform2[j] += s*hann[j/2];
					}
				}
				for(j = 0; j < 2*N; j++)
					waveform[j] = waveform2[j];
			}
    	}*/
    }
}
