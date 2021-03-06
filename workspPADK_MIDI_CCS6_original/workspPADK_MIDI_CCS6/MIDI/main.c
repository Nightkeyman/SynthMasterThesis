// CSL Modules
#include <soc.h>
#include <csl_chip.h>
#include <csl_intc.h>
#include <csl_dmax.h>
#include <csl_mcasp.h>
#include <math.h>
#include "PADK.h"
#include <stdio.h>
#include <stdlib.h>

#include "PADK_UART.h"
#include "midi_fifo.h"
#include "filters.h"
#include "waveforms.h"
#include "var&fun.h"
#include "myfft.h"
#include "additive.h"
#include "woodwind.h"

#define OVERLAP 128
#define MIDI_TONE_RANGE 128
#define MIDI_POLY_MAX 12
#define M_PI 3.14159
#define Fs 48000
#define F_sq 440
#define F_sqq 10000
#define SIG_AMP 100000
#define ADD_SIG_AMP 100000000

#define N 1024
 short  table[64];
#pragma DATA_ALIGN(v, 8)
 float  v[2*N];
#pragma DATA_ALIGN(w, 8)
 float  w[N];
int waveform0[N];
int waveform1[N];

volatile int whichwaveform = 0;
const float overlaptable[128] = {0.008, 0.016, 0.023, 0.031, 0.039, 0.047, 0.055, 0.063, 0.070, 0.078, 0.086, 0.094, 0.102, 0.109, 0.117, 0.125, 0.133, 0.141, 0.148, 0.156, 0.164, 0.172, 0.180, 0.188, 0.195, 0.203, 0.211, 0.219, 0.227, 0.234, 0.242, 0.250, 0.258, 0.266, 0.273, 0.281, 0.289, 0.297, 0.305, 0.313, 0.320, 0.328, 0.336, 0.344, 0.352, 0.359, 0.367, 0.375, 0.383, 0.391, 0.398, 0.406, 0.414, 0.422, 0.430, 0.438, 0.445, 0.453, 0.461, 0.469, 0.477, 0.484, 0.492, 0.500, 0.508, 0.516, 0.523, 0.531, 0.539, 0.547, 0.555, 0.563, 0.570, 0.578, 0.586, 0.594, 0.602, 0.609, 0.617, 0.625, 0.633, 0.641, 0.648, 0.656, 0.664, 0.672, 0.680, 0.688, 0.695, 0.703, 0.711, 0.719, 0.727, 0.734, 0.742, 0.750, 0.758, 0.766, 0.773, 0.781, 0.789, 0.797, 0.805, 0.813, 0.820, 0.828, 0.836, 0.844, 0.852, 0.859, 0.867, 0.875, 0.883, 0.891, 0.898, 0.906, 0.914, 0.922, 0.930, 0.938, 0.945, 0.953, 0.961, 0.969, 0.977, 0.984, 0.992, 1.000};

double s = 0;
float free_tab[N];// = {0,2.3554e-06,9.4216e-06,2.1198e-05,3.7686e-05,5.8884e-05,8.4792e-05,0.00011541,0.00015074,0.00019077,0.00023552,0.00028498,0.00033914,0.00039801,0.00046159,0.00052987,0.00060286,0.00068056,0.00076295,0.00085006,0.00094186,0.0010384,0.0011396,0.0012455,0.0013561,0.0014714,0.0015914,0.0017161,0.0018455,0.0019796,0.0021184,0.0022618,0.00241,0.0025628,0.0027204,0.0028826,0.0030495,0.0032211,0.0033973,0.0035783,0.0037639,0.0039542,0.0041492,0.0043488,0.0045531,0.0047621,0.0049757,0.0051941,0.005417,0.0056447,0.0058769,0.0061139,0.0063555,0.0066017,0.0068526,0.0071082,0.0073684,0.0076332,0.0079026,0.0081768,0.0084555,0.0087389,0.0090269,0.0093195,0.0096167,0.0099186,0.010225,0.010536,0.010852,0.011172,0.011497,0.011827,0.012161,0.012499,0.012843,0.013191,0.013543,0.0139,0.014262,0.014628,0.014999,0.015374,0.015754,0.016139,0.016528,0.016921,0.01732,0.017722,0.01813,0.018541,0.018958,0.019379,0.019804,0.020234,0.020668,0.021107,0.021551,0.021999,0.022451,0.022908,0.02337,0.023836,0.024306,0.024781,0.02526,0.025744,0.026233,0.026725,0.027223,0.027724,0.028231,0.028741,0.029256,0.029776,0.0303,0.030828,0.031361,0.031898,0.03244,0.032986,0.033536,0.034091,0.03465,0.035214,0.035781,0.036354,0.03693,0.037512,0.038097,0.038687,0.039281,0.039879,0.040482,0.041089,0.041701,0.042316,0.042936,0.043561,0.044189,0.044822,0.04546,0.046101,0.046747,0.047397,0.048052,0.04871,0.049373,0.05004,0.050711,0.051387,0.052067,0.052751,0.053439,0.054132,0.054828,0.055529,0.056234,0.056943,0.057657,0.058374,0.059096,0.059822,0.060552,0.061286,0.062024,0.062767,0.063513,0.064264,0.065019,0.065777,0.06654,0.067307,0.068078,0.068854,0.069633,0.070416,0.071204,0.071995,0.07279,0.07359,0.074393,0.075201,0.076012,0.076828,0.077647,0.07847,0.079298,0.080129,0.080964,0.081804,0.082647,0.083494,0.084345,0.0852,0.086059,0.086922,0.087788,0.088659,0.089533,0.090412,0.091294,0.09218,0.09307,0.093963,0.094861,0.095762,0.096667,0.097576,0.098489,0.099406,0.10033,0.10125,0.10218,0.10311,0.10404,0.10498,0.10593,0.10687,0.10782,0.10878,0.10973,0.1107,0.11166,0.11263,0.1136,0.11458,0.11556,0.11654,0.11753,0.11852,0.11951,0.12051,0.12151,0.12251,0.12352,0.12453,0.12555,0.12657,0.12759,0.12862,0.12965,0.13068,0.13171,0.13275,0.1338,0.13484,0.13589,0.13695,0.138,0.13907,0.14013,0.1412,0.14227,0.14334,0.14442,0.1455,0.14658,0.14767,0.14876,0.14985,0.15095,0.15205,0.15316,0.15426,0.15537,0.15649,0.1576,0.15872,0.15985,0.16097,0.1621,0.16324,0.16437,0.16551,0.16665,0.1678,0.16895,0.1701,0.17125,0.17241,0.17357,0.17474,0.1759,0.17707,0.17825,0.17942,0.1806,0.18178,0.18297,0.18416,0.18535,0.18654,0.18774,0.18894,0.19014,0.19135,0.19256,0.19377,0.19499,0.1962,0.19742,0.19865,0.19987,0.2011,0.20233,0.20357,0.20481,0.20605,0.20729,0.20853,0.20978,0.21103,0.21229,0.21354,0.2148,0.21606,0.21733,0.2186,0.21987,0.22114,0.22241,0.22369,0.22497,0.22626,0.22754,0.22883,0.23012,0.23141,0.23271,0.23401,0.23531,0.23661,0.23792,0.23923,0.24054,0.24185,0.24316,0.24448,0.2458,0.24713,0.24845,0.24978,0.25111,0.25244,0.25378,0.25511,0.25645,0.25779,0.25914,0.26048,0.26183,0.26318,0.26453,0.26589,0.26725,0.26861,0.26997,0.27133,0.2727,0.27407,0.27544,0.27681,0.27818,0.27956,0.28094,0.28232,0.2837,0.28509,0.28647,0.28786,0.28925,0.29064,0.29204,0.29344,0.29483,0.29623,0.29764,0.29904,0.30045,0.30186,0.30327,0.30468,0.30609,0.30751,0.30892,0.31034,0.31176,0.31319,0.31461,0.31604,0.31747,0.3189,0.32033,0.32176,0.32319,0.32463,0.32607,0.32751,0.32895,0.33039,0.33184,0.33328,0.33473,0.33618,0.33763,0.33908,0.34054,0.34199,0.34345,0.34491,0.34637,0.34783,0.34929,0.35076,0.35222,0.35369,0.35516,0.35663,0.3581,0.35957,0.36104,0.36252,0.36399,0.36547,0.36695,0.36843,0.36991,0.37139,0.37288,0.37436,0.37585,0.37734,0.37882,0.38031,0.3818,0.3833,0.38479,0.38628,0.38778,0.38927,0.39077,0.39227,0.39377,0.39527,0.39677,0.39827,0.39978,0.40128,0.40278,0.40429,0.4058,0.4073,0.40881,0.41032,0.41183,0.41334,0.41486,0.41637,0.41788,0.4194,0.42091,0.42243,0.42394,0.42546,0.42698,0.4285,0.43002,0.43154,0.43306,0.43458,0.4361,0.43762,0.43915,0.44067,0.44219,0.44372,0.44524,0.44677,0.4483,0.44982,0.45135,0.45288,0.45441,0.45593,0.45746,0.45899,0.46052,0.46205,0.46358,0.46511,0.46664,0.46818,0.46971,0.47124,0.47277,0.4743,0.47584,0.47737,0.4789,0.48044,0.48197,0.4835,0.48504,0.48657,0.48811,0.48964,0.49118,0.49271,0.49424,0.49578,0.49731,0.49885,0.50038,0.50192,0.50345,0.50499,0.50652,0.50806,0.50959,0.51113,0.51266,0.51419,0.51573,0.51726,0.5188,0.52033,0.52186,0.5234,0.52493,0.52646,0.52799,0.52953,0.53106,0.53259,0.53412,0.53565,0.53718,0.53871,0.54024,0.54177,0.5433,0.54483,0.54636,0.54789,0.54941,0.55094,0.55247,0.55399,0.55552,0.55704,0.55857,0.56009,0.56162,0.56314,0.56466,0.56618,0.5677,0.56922,0.57074,0.57226,0.57378,0.5753,0.57681,0.57833,0.57985,0.58136,0.58287,0.58439,0.5859,0.58741,0.58892,0.59043,0.59194,0.59345,0.59496,0.59646,0.59797,0.59947,0.60098,0.60248,0.60398,0.60548,0.60698,0.60848,0.60998,0.61147,0.61297,0.61446,0.61596,0.61745,0.61894,0.62043,0.62192,0.62341,0.62489,0.62638,0.62786,0.62935,0.63083,0.63231,0.63379,0.63527,0.63674,0.63822,0.63969,0.64117,0.64264,0.64411,0.64558,0.64705,0.64851,0.64998,0.65144,0.6529,0.65436,0.65582,0.65728,0.65874,0.66019,0.66164,0.66309,0.66454,0.66599,0.66744,0.66889,0.67033,0.67177,0.67321,0.67465,0.67609,0.67752,0.67896,0.68039,0.68182,0.68325,0.68468,0.6861,0.68752,0.68895,0.69037,0.69178,0.6932,0.69462,0.69603,0.69744,0.69885,0.70026,0.70166,0.70306,0.70447,0.70587,0.70726,0.70866,0.71005,0.71144,0.71283,0.71422,0.71561,0.71699,0.71837,0.71975,0.72113,0.72251,0.72388,0.72525,0.72662,0.72799,0.72935,0.73071,0.73207,0.73343,0.73479,0.73614,0.73749,0.73884,0.74019,0.74154,0.74288,0.74422,0.74556,0.74689,0.74823,0.74956,0.75089,0.75221,0.75354,0.75486,0.75618,0.75749,0.75881,0.76012,0.76143,0.76274,0.76404,0.76534,0.76664,0.76794,0.76923,0.77053,0.77182,0.7731,0.77439,0.77567,0.77695,0.77822,0.7795,0.78077,0.78204,0.7833,0.78457,0.78583,0.78708,0.78834,0.78959,0.79084,0.79209,0.79333,0.79458,0.79581,0.79705,0.79828,0.79951,0.80074,0.80197,0.80319,0.80441,0.80562,0.80684,0.80805,0.80925,0.81046,0.81166,0.81286,0.81405,0.81525,0.81644,0.81762,0.81881,0.81999,0.82117,0.82234,0.82351,0.82468,0.82585,0.82701,0.82817,0.82932,0.83048,0.83163,0.83277,0.83392,0.83506,0.8362,0.83733,0.83846,0.83959,0.84072,0.84184,0.84296,0.84407,0.84518,0.84629,0.8474,0.8485,0.8496,0.85069,0.85179,0.85287,0.85396,0.85504,0.85612,0.8572,0.85827,0.85934,0.8604,0.86147,0.86252,0.86358,0.86463,0.86568,0.86672,0.86777,0.8688,0.86984,0.87087,0.8719,0.87292,0.87394,0.87496,0.87597,0.87698,0.87799,0.87899,0.87999,0.88099,0.88198,0.88297,0.88395,0.88493,0.88591,0.88689,0.88786,0.88882,0.88979,0.89074,0.8917,0.89265,0.8936,0.89455,0.89549,0.89642,0.89736,0.89829,0.89921,0.90013,0.90105,0.90197,0.90288,0.90379,0.90469,0.90559,0.90648,0.90738,0.90826,0.90915,0.91003,0.9109,0.91178,0.91265,0.91351,0.91437,0.91523,0.91608,0.91693,0.91778,0.91862,0.91945,0.92029,0.92112,0.92194,0.92276,0.92358,0.92439,0.9252,0.92601,0.92681,0.92761,0.9284,0.92919,0.92998,0.93076,0.93153,0.93231,0.93308,0.93384,0.9346,0.93536,0.93611,0.93686,0.93761,0.93835,0.93908,0.93981,0.94054,0.94127,0.94199,0.9427,0.94341,0.94412,0.94482,0.94552,0.94622,0.94691,0.94759,0.94827,0.94895,0.94962,0.95029,0.95096,0.95162,0.95228,0.95293,0.95358,0.95422,0.95486,0.95549,0.95613,0.95675,0.95737,0.95799,0.95861,0.95921,0.95982,0.96042,0.96102,0.96161,0.9622,0.96278,0.96336,0.96393,0.9645,0.96507,0.96563,0.96619,0.96674,0.96729,0.96783,0.96837,0.96891,0.96944,0.96996,0.97048,0.971,0.97151,0.97202,0.97253,0.97303,0.97352,0.97401,0.9745,0.97498,0.97546,0.97593,0.9764,0.97686,0.97732,0.97778,0.97823,0.97867,0.97911,0.97955,0.97998,0.98041,0.98083,0.98125,0.98167,0.98207,0.98248,0.98288,0.98328,0.98367,0.98405,0.98444,0.98481,0.98519,0.98556,0.98592,0.98628,0.98663,0.98698,0.98733,0.98767,0.98801,0.98834,0.98867,0.98899,0.98931,0.98962,0.98993,0.99023,0.99053,0.99083,0.99112,0.9914,0.99168,0.99196,0.99223,0.9925,0.99276,0.99302,0.99327,0.99352,0.99377,0.99401,0.99424,0.99447,0.9947,0.99492,0.99513,0.99534,0.99555,0.99575,0.99595,0.99614,0.99633,0.99651,0.99669,0.99687,0.99703,0.9972,0.99736,0.99751,0.99766,0.99781,0.99795,0.99809,0.99822,0.99835,0.99847,0.99859,0.9987,0.99881,0.99891,0.99901,0.9991,0.99919,0.99928,0.99936,0.99943,0.9995,0.99957,0.99963,0.99969,0.99974,0.99979,0.99983,0.99987,0.9999,0.99993,0.99995,0.99997,0.99999,0.99999,1,1,0.99999,0.99999,0.99997,0.99995,0.99993,0.9999,0.99987,0.99983,0.99979,0.99974,0.99969,0.99963,0.99957,0.9995,0.99943,0.99936,0.99928,0.99919,0.9991,0.99901,0.99891,0.99881,0.9987,0.99859,0.99847,0.99835,0.99822,0.99809,0.99795,0.99781,0.99766,0.99751,0.99736,0.9972,0.99703,0.99687,0.99669,0.99651,0.99633,0.99614,0.99595,0.99575,0.99555,0.99534,0.99513,0.99492,0.9947,0.99447,0.99424,0.99401,0.99377,0.99352,0.99327,0.99302,0.99276,0.9925,0.99223,0.99196,0.99168,0.9914,0.99112,0.99083,0.99053,0.99023,0.98993,0.98962,0.98931,0.98899,0.98867,0.98834,0.98801,0.98767,0.98733,0.98698,0.98663,0.98628,0.98592,0.98556,0.98519,0.98481,0.98444,0.98405,0.98367,0.98328,0.98288,0.98248,0.98207,0.98167,0.98125,0.98083,0.98041,0.97998,0.97955,0.97911,0.97867,0.97823,0.97778,0.97732,0.97686,0.9764,0.97593,0.97546,0.97498,0.9745,0.97401,0.97352,0.97303,0.97253,0.97202,0.97151,0.971,0.97048,0.96996,0.96944,0.96891,0.96837,0.96783,0.96729,0.96674,0.96619,0.96563,0.96507,0.9645,0.96393,0.96336,0.96278,0.9622,0.96161,0.96102,0.96042,0.95982,0.95921,0.95861,0.95799,0.95737,0.95675,0.95613,0.95549,0.95486,0.95422,0.95358,0.95293,0.95228,0.95162,0.95096,0.95029,0.94962,0.94895,0.94827,0.94759,0.94691,0.94622,0.94552,0.94482,0.94412,0.94341,0.9427,0.94199,0.94127,0.94054,0.93981,0.93908,0.93835,0.93761,0.93686,0.93611,0.93536,0.9346,0.93384,0.93308,0.93231,0.93153,0.93076,0.92998,0.92919,0.9284,0.92761,0.92681,0.92601,0.9252,0.92439,0.92358,0.92276,0.92194,0.92112,0.92029,0.91945,0.91862,0.91778,0.91693,0.91608,0.91523,0.91437,0.91351,0.91265,0.91178,0.9109,0.91003,0.90915,0.90826,0.90738,0.90648,0.90559,0.90469,0.90379,0.90288,0.90197,0.90105,0.90013,0.89921,0.89829,0.89736,0.89642,0.89549,0.89455,0.8936,0.89265,0.8917,0.89074,0.88979,0.88882,0.88786,0.88689,0.88591,0.88493,0.88395,0.88297,0.88198,0.88099,0.87999,0.87899,0.87799,0.87698,0.87597,0.87496,0.87394,0.87292,0.8719,0.87087,0.86984,0.8688,0.86777,0.86672,0.86568,0.86463,0.86358,0.86252,0.86147,0.8604,0.85934,0.85827,0.8572,0.85612,0.85504,0.85396,0.85287,0.85179,0.85069,0.8496,0.8485,0.8474,0.84629,0.84518,0.84407,0.84296,0.84184,0.84072,0.83959,0.83846,0.83733,0.8362,0.83506,0.83392,0.83277,0.83163,0.83048,0.82932,0.82817,0.82701,0.82585,0.82468,0.82351,0.82234,0.82117,0.81999,0.81881,0.81762,0.81644,0.81525,0.81405,0.81286,0.81166,0.81046,0.80925,0.80805,0.80684,0.80562,0.80441,0.80319,0.80197,0.80074,0.79951,0.79828,0.79705,0.79581,0.79458,0.79333,0.79209,0.79084,0.78959,0.78834,0.78708,0.78583,0.78457,0.7833,0.78204,0.78077,0.7795,0.77822,0.77695,0.77567,0.77439,0.7731,0.77182,0.77053,0.76923,0.76794,0.76664,0.76534,0.76404,0.76274,0.76143,0.76012,0.75881,0.75749,0.75618,0.75486,0.75354,0.75221,0.75089,0.74956,0.74823,0.74689,0.74556,0.74422,0.74288,0.74154,0.74019,0.73884,0.73749,0.73614,0.73479,0.73343,0.73207,0.73071,0.72935,0.72799,0.72662,0.72525,0.72388,0.72251,0.72113,0.71975,0.71837,0.71699,0.71561,0.71422,0.71283,0.71144,0.71005,0.70866,0.70726,0.70587,0.70447,0.70306,0.70166,0.70026,0.69885,0.69744,0.69603,0.69462,0.6932,0.69178,0.69037,0.68895,0.68752,0.6861,0.68468,0.68325,0.68182,0.68039,0.67896,0.67752,0.67609,0.67465,0.67321,0.67177,0.67033,0.66889,0.66744,0.66599,0.66454,0.66309,0.66164,0.66019,0.65874,0.65728,0.65582,0.65436,0.6529,0.65144,0.64998,0.64851,0.64705,0.64558,0.64411,0.64264,0.64117,0.63969,0.63822,0.63674,0.63527,0.63379,0.63231,0.63083,0.62935,0.62786,0.62638,0.62489,0.62341,0.62192,0.62043,0.61894,0.61745,0.61596,0.61446,0.61297,0.61147,0.60998,0.60848,0.60698,0.60548,0.60398,0.60248,0.60098,0.59947,0.59797,0.59646,0.59496,0.59345,0.59194,0.59043,0.58892,0.58741,0.5859,0.58439,0.58287,0.58136,0.57985,0.57833,0.57681,0.5753,0.57378,0.57226,0.57074,0.56922,0.5677,0.56618,0.56466,0.56314,0.56162,0.56009,0.55857,0.55704,0.55552,0.55399,0.55247,0.55094,0.54941,0.54789,0.54636,0.54483,0.5433,0.54177,0.54024,0.53871,0.53718,0.53565,0.53412,0.53259,0.53106,0.52953,0.52799,0.52646,0.52493,0.5234,0.52186,0.52033,0.5188,0.51726,0.51573,0.51419,0.51266,0.51113,0.50959,0.50806,0.50652,0.50499,0.50345,0.50192,0.50038,0.49885,0.49731,0.49578,0.49424,0.49271,0.49118,0.48964,0.48811,0.48657,0.48504,0.4835,0.48197,0.48044,0.4789,0.47737,0.47584,0.4743,0.47277,0.47124,0.46971,0.46818,0.46664,0.46511,0.46358,0.46205,0.46052,0.45899,0.45746,0.45593,0.45441,0.45288,0.45135,0.44982,0.4483,0.44677,0.44524,0.44372,0.44219,0.44067,0.43915,0.43762,0.4361,0.43458,0.43306,0.43154,0.43002,0.4285,0.42698,0.42546,0.42394,0.42243,0.42091,0.4194,0.41788,0.41637,0.41486,0.41334,0.41183,0.41032,0.40881,0.4073,0.4058,0.40429,0.40278,0.40128,0.39978,0.39827,0.39677,0.39527,0.39377,0.39227,0.39077,0.38927,0.38778,0.38628,0.38479,0.3833,0.3818,0.38031,0.37882,0.37734,0.37585,0.37436,0.37288,0.37139,0.36991,0.36843,0.36695,0.36547,0.36399,0.36252,0.36104,0.35957,0.3581,0.35663,0.35516,0.35369,0.35222,0.35076,0.34929,0.34783,0.34637,0.34491,0.34345,0.34199,0.34054,0.33908,0.33763,0.33618,0.33473,0.33328,0.33184,0.33039,0.32895,0.32751,0.32607,0.32463,0.32319,0.32176,0.32033,0.3189,0.31747,0.31604,0.31461,0.31319,0.31176,0.31034,0.30892,0.30751,0.30609,0.30468,0.30327,0.30186,0.30045,0.29904,0.29764,0.29623,0.29483,0.29344,0.29204,0.29064,0.28925,0.28786,0.28647,0.28509,0.2837,0.28232,0.28094,0.27956,0.27818,0.27681,0.27544,0.27407,0.2727,0.27133,0.26997,0.26861,0.26725,0.26589,0.26453,0.26318,0.26183,0.26048,0.25914,0.25779,0.25645,0.25511,0.25378,0.25244,0.25111,0.24978,0.24845,0.24713,0.2458,0.24448,0.24316,0.24185,0.24054,0.23923,0.23792,0.23661,0.23531,0.23401,0.23271,0.23141,0.23012,0.22883,0.22754,0.22626,0.22497,0.22369,0.22241,0.22114,0.21987,0.2186,0.21733,0.21606,0.2148,0.21354,0.21229,0.21103,0.20978,0.20853,0.20729,0.20605,0.20481,0.20357,0.20233,0.2011,0.19987,0.19865,0.19742,0.1962,0.19499,0.19377,0.19256,0.19135,0.19014,0.18894,0.18774,0.18654,0.18535,0.18416,0.18297,0.18178,0.1806,0.17942,0.17825,0.17707,0.1759,0.17474,0.17357,0.17241,0.17125,0.1701,0.16895,0.1678,0.16665,0.16551,0.16437,0.16324,0.1621,0.16097,0.15985,0.15872,0.1576,0.15649,0.15537,0.15426,0.15316,0.15205,0.15095,0.14985,0.14876,0.14767,0.14658,0.1455,0.14442,0.14334,0.14227,0.1412,0.14013,0.13907,0.138,0.13695,0.13589,0.13484,0.1338,0.13275,0.13171,0.13068,0.12965,0.12862,0.12759,0.12657,0.12555,0.12453,0.12352,0.12251,0.12151,0.12051,0.11951,0.11852,0.11753,0.11654,0.11556,0.11458,0.1136,0.11263,0.11166,0.1107,0.10973,0.10878,0.10782,0.10687,0.10593,0.10498,0.10404,0.10311,0.10218,0.10125,0.10033,0.099406,0.098489,0.097576,0.096667,0.095762,0.094861,0.093963,0.09307,0.09218,0.091294,0.090412,0.089533,0.088659,0.087788,0.086922,0.086059,0.0852,0.084345,0.083494,0.082647,0.081804,0.080964,0.080129,0.079298,0.07847,0.077647,0.076828,0.076012,0.075201,0.074393,0.07359,0.07279,0.071995,0.071204,0.070416,0.069633,0.068854,0.068078,0.067307,0.06654,0.065777,0.065019,0.064264,0.063513,0.062767,0.062024,0.061286,0.060552,0.059822,0.059096,0.058374,0.057657,0.056943,0.056234,0.055529,0.054828,0.054132,0.053439,0.052751,0.052067,0.051387,0.050711,0.05004,0.049373,0.04871,0.048052,0.047397,0.046747,0.046101,0.04546,0.044822,0.044189,0.043561,0.042936,0.042316,0.041701,0.041089,0.040482,0.039879,0.039281,0.038687,0.038097,0.037512,0.03693,0.036354,0.035781,0.035214,0.03465,0.034091,0.033536,0.032986,0.03244,0.031898,0.031361,0.030828,0.0303,0.029776,0.029256,0.028741,0.028231,0.027724,0.027223,0.026725,0.026233,0.025744,0.02526,0.024781,0.024306,0.023836,0.02337,0.022908,0.022451,0.021999,0.021551,0.021107,0.020668,0.020234,0.019804,0.019379,0.018958,0.018541,0.01813,0.017722,0.01732,0.016921,0.016528,0.016139,0.015754,0.015374,0.014999,0.014628,0.014262,0.0139,0.013543,0.013191,0.012843,0.012499,0.012161,0.011827,0.011497,0.011172,0.010852,0.010536,0.010225,0.0099186,0.0096167,0.0093195,0.0090269,0.0087389,0.0084555,0.0081768,0.0079026,0.0076332,0.0073684,0.0071082,0.0068526,0.0066017,0.0063555,0.0061139,0.0058769,0.0056447,0.005417,0.0051941,0.0049757,0.0047621,0.0045531,0.0043488,0.0041492,0.0039542,0.0037639,0.0035783,0.0033973,0.0032211,0.0030495,0.0028826,0.0027204,0.0025628,0.00241,0.0022618,0.0021184,0.0019796,0.0018455,0.0017161,0.0015914,0.0014714,0.0013561,0.0012455,0.0011396,0.0010384,0.00094186,0.00085006,0.00076295,0.00068056,0.00060286,0.00052987,0.00046159,0.00039801,0.00033914,0.00028498,0.00023552,0.00019077,0.00015074,0.00011541,8.4792e-05,5.8884e-05,3.7686e-05,2.1198e-05,9.4216e-06,2.3554e-06,0};
unsigned char data_midi[1];
float freqs[MIDI_POLY_MAX];
int pressedkeys = 0;
extern volatile unsigned PP;
extern volatile unsigned sem_dac;
extern int sem_new_note; // 0 - 128

enum methodtype{subtractive, additive, fm, fm_bell, flute, violin};
enum methodtype method = additive;
// SUBTRACTIVE GLOBALS
enum waveformtype{square, triangle, sawtooth};
enum waveformtype waveformSet = square;
enum filtertype{lowpass, highpass, bandpass, bandstop};
enum filtertype filterSet = lowpass;
int sub_lowfreq = 0;
int sub_highfreq = Fs;

// FM GLOBALS
int fm_modfreq = 1;
int fm_modamp = 10;
double bell_adsr_coefficient = 1.0;

// ADSR GLOBALS
float adsr[MIDI_POLY_MAX];
int adsr_state[MIDI_POLY_MAX];
float attack_rate = 0.5;
float attack_level = 1.0;
float decay_rate = 0.1;
float sustain_level = 1.0;
float release_rate = 0.5;

// ADDITIVE GLOBALS
float phase = 0;
float add_knobAmp[HAMMOND_KNOBS];

// WOODWIND GLOBALS
double x[N]; // x - input data - noise
int f_sin = 440;
double dt = 1.0/Fs;
float amp_noise = 0.02; //0.005
double fbk_scl1 = 0.2;
double fbk_scl2 = 0.33;
double filt_b = -0.1;
double filt_a = 0.7;
const unsigned int env_del = 50000;
unsigned int kenvibr_del = 12*N;
unsigned int kenv1_del = 24;
int flag_flute = 0;
double kenv1[N];
double wave[N];
double kenvibr[N];
double avalue[N+1];
double asum2_del[EMB_DELAY_MAX];
double avalue_del[BORE_DELAY_MAX];
double apoly;
double asum3;
double aflute1;

// VIOLIN GLOBALS
double maxVelocity = 0.25;
double lowestFrequency = 140;
int nDelays;
int bowDown = 1;
double betaRatio = 0.127236;
double baseDelay;
// vibrato
double vibrato_gain = 0.005;
double vibrato_freq = 6.12723;
#define vibrato_TABLE_SIZE 256
double vibrato_time = 0.0;
double vibrato_alpha = 0.0;
double vibrato_table[vibrato_TABLE_SIZE];
double vibrato_rate;
// neck delay line
double neckDelay[343];
double neck_delay;
int neck_inPoint = 0;
double neck_gain = 1;
double neck_outPointer;
int neck_outPoint;
double neck_alpha;
double neck_omAlpha;
int neck_doNextOut = 1;
// bridge delay line
double bridgeDelay[343];
double bridge_delay;
int bridge_inPoint = 0;
double bridge_gain = 1;
double bridge_outPointer;
int bridge_outPoint;
double bridge_alpha;
double bridge_omAlpha;
int bridge_doNextOut = 1;
// bow table function
double bowtable_offset = 0.001;
double bowtable_slope = 3.0;
double bowtable_minOutput = 0.01;
double bowtable_maxOutput = 0.98;
// string one pole filter
double stringfilter_pole = 0.55 - (0.2*Fs/(double)Fs);
double stringfilter_gain = 0.95;
double stringfilter_b;
double stringfilter_a;
double stringfilter;

int flag_violin = 0;

// Static waveform arrays
float sinusek[N];

//
//  Main Function
//
int main( int argc, char *argv[] ) {

	#include "ALL_init.h"

	// INITIALIZE VARIABLES
	int i = 0, j = 0, m = 0;
	int freq_wav = 0;
	int mono = 1; // 0 - mono, 1 - poly
	int clear_v = 1;
	int k = 0; // phase shift variable
	float *p; // pointer for additive array
	double aflute1_del = 0.0, asum2 = 0.0, ax = 0.0;
	int emb_delay = 0, bore_delay = 0;
	double wave_period = 0.0;
	sem_dac = 1;
	whichwaveform = 1;
	for (i = 0 ; i < MIDI_POLY_MAX; i++){
		adsr[i] = 0.0;
		adsr_state[i] = 0;
	}
	for(i = 0; i < MIDI_POLY_MAX; i++)
		freqs[i] = 0;

	for(i = 0; i < HAMMOND_KNOBS; i++)
		add_knobAmp[i] = 0;

	for(i = 0; i < 2*N; i+=2) {
		waveform0[i] = 0;
		waveform0[i+1] = 0;
		waveform1[i] = 0;
		waveform1[i+1] = 0;
	}

	apoly = 0.0;
	asum3 = 0.0;
	aflute1 = 0.0;
	for(i = 0; i <= N; i++) {
		avalue[i] = 0;
	}
	for(i = 0; i < EMB_DELAY_MAX; i++) {
		asum2_del[i] = 0;
	}
	for(i = 0; i < BORE_DELAY_MAX; i++) {
		avalue_del[i] = 0;
	}

	sin_wave(440, SIG_AMP, 0);
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

	// Prepare static waveform tables
	for (i = 0; i < N; i++) {
		sinusek[i] = sinf(2.0*M_PI*((float)i/(N*1.0)));
	}

	// Prepare violin
	stringfilter = 0;
	maxVelocity = 0.25;
	lowestFrequency = 140;
	nDelays = Fs/lowestFrequency;
	bowDown = 1;
	betaRatio = 0.127236;

	//vibrato
	vibrato_gain = 0.005;
	vibrato_freq = 6.12723;
	vibrato_time = 0.0;
	vibrato_alpha = 0.0;
	vibrato_rate = vibrato_TABLE_SIZE*vibrato_freq/(double)Fs;

	// bow table function
	bowtable_offset = 0.001;
	bowtable_slope = 3.0;
	bowtable_minOutput = 0.01;
	bowtable_maxOutput = 0.98;
	// string one pole filter
	stringfilter_pole = 0.55 - (0.2*(Fs/2)/(double)Fs);
	stringfilter_gain = 0.95;
	stringfilter_b;
	stringfilter_a;
	if (stringfilter_pole > 0.0)
		stringfilter_b = 1.0 - stringfilter_pole;
	else
		stringfilter_b = 1.0 + stringfilter_pole;

	stringfilter_a = -stringfilter_pole;


 	/*---------------------------------------------------------------*/
	/*							 MAIN LOOP 		                     */
	/*---------------------------------------------------------------*/
    while(1)  {
    	///// ADDITIVE /////
		if(method == additive) {
    		if(pressedkeys < 1) {
    			for(j = 0; j < N; j++) {
					waveform0[j] = 0;
					waveform1[j] = 0;
				}
    		} else {
				clear_v = 1;
				for(i = 0; i < MIDI_POLY_MAX; i++) {
					if(freqs[i] > 0 || adsr_state[i] > 0) {
						hammond_wave(freqs[i], k, clear_v, i);
						if (clear_v == 1)
							clear_v = 0;
					}
				}
				while(sem_dac == 0);
				for(j = 0; j < N; j++) {
					if (j < OVERLAP) {
						if (whichwaveform == 1) {
							waveform0[j] = overlaptable[j]*ADD_SIG_AMP*v[j*2];
						} else {
							waveform1[j] = overlaptable[j]*ADD_SIG_AMP*v[j*2];
						}
					} else if (j >= N - OVERLAP) {
						if (whichwaveform) {
							waveform0[j] = overlaptable[N-j-1]*ADD_SIG_AMP*v[j*2];
						} else {
							waveform1[j] = overlaptable[N-j-1]*ADD_SIG_AMP*v[j*2];
						}
					} else {
						if (whichwaveform) {
							waveform0[j] = ADD_SIG_AMP*v[j*2];
						} else {
							waveform1[j] = ADD_SIG_AMP*v[j*2];
						}
					}
				}
				sem_dac = 0;
				k += N - OVERLAP;
    		}
		///// WOODWIND /////
		} else if (method == flute) {
			if(pressedkeys < 1) {
				for(j = 0; j < N; j++) {
					waveform0[j] = 0.0;
					waveform1[j] = 0.0;
				}
			} else {
				clear_v = 1;
				for(i = 0; i < MIDI_POLY_MAX; i++) {
					if(freqs[i] > 0 || adsr_state[i] > 0) {
						if (clear_v == 1){
							clear_v = 0;
							ADSR(i);
							for(j = 0; j < OVERLAP; j++){
									v[j*2] = v[(N-OVERLAP+j)*2];
							}
							if(flag_flute == 1) {
								flag_flute = 0;
								wave_period = Fs/440.0;//floor(Fs/(double)freqs[i]);
								emb_delay = floor(wave_period/6);
								bore_delay = floor(wave_period/3);
								aflute1 = 0.0;
								for(m = 0; m < EMB_DELAY_MAX; m++) {
									asum2_del[m] = 0;
									avalue_del[m] = 0;
								}
								for(m = 0; m < N; m++) {
									kenv1[m] = 0.0;
									wave[m] = 0.0;
									avalue[m] = 0.0;
								}
								avalue[N] = 0.0;
								k = 0;
							}

							genNoise_full();
							// kenv1 creation
							for(j = 0; j < N - OVERLAP; j++) {
								if(env_del > (j + k)/env_del) {
									kenv1[j] = 20.0;//(j + k)/env_del;
								} else {
									kenv1[j] = 1.0;
								}
								kenv1[j] = (1.0*x[j])/10.0; // 10.0 to wspolczynnik dobrego wyniku
								wave[j] = sin((double)(j+k)*2.0*M_PI*freqs[i]/Fs); // 10.0 to wspolczynnik dobrego wyniku

								// KENVIBR creation
								if(kenvibr_del > (j + k)) {
									kenvibr[j] = (double)(j + k)/(kenvibr_del);
								} else {
									kenvibr[j] = 1.0;
								}
								kenvibr[j] = wave[j]*kenvibr[j];
								kenv1[j] = kenv1[j]*kenvibr[j];
								// ASUM1 creation
								kenv1[j] = amp_noise*kenv1[j] + kenvibr[j];
								avalue[0] = avalue[N-OVERLAP];
							}

							  // FEEDBACK LOOP
							for(j = 0; j < N - OVERLAP; j++) {
								aflute1_del = aflute1;
								asum2 = kenv1[j] + aflute1_del;
								asum2_del[emb_delay] = asum2;
								ax = asum2_del[0];
								apoly = ax - ax*ax*ax;
								asum3 = aflute1_del + apoly;
								avalue[j+1] = filt_b*asum3 - filt_a*avalue[j];
								avalue_del[bore_delay] = avalue[j+1];
								aflute1 = avalue_del[0];
								// REWRITE TO DELAYED TABLES
								for(m = 0; m < emb_delay; m++) {
								  asum2_del[m] = asum2_del[m+1];
								}

								for(m = 0; m < bore_delay; m++) {
								  avalue_del[m] = avalue_del[m+1];
								}

								v[(j+OVERLAP)*2] = avalue[j]*100000.0*adsr[i];
							}
						}
					}
				}
				while(sem_dac == 0);
				for(j = 0; j < N; j++) {
					if (j < OVERLAP) {
						if (whichwaveform == 1) {
							waveform0[j] = overlaptable[j]*SIG_AMP*v[j*2]; // tu by bylo przepisywanie z myWav
						} else {
							waveform1[j] = overlaptable[j]*SIG_AMP*v[j*2];
						}
					} else if (j >= N - OVERLAP) {
						if (whichwaveform) {
							waveform0[j] = overlaptable[N-j-1]*SIG_AMP*v[j*2];
						} else {
							waveform1[j] = overlaptable[N-j-1]*SIG_AMP*v[j*2];
						}
					} else {
						if (whichwaveform) {
							waveform0[j] = SIG_AMP*v[j*2];
						} else {
							waveform1[j] = SIG_AMP*v[j*2];
						}
					}
				}
				sem_dac = 0;
				k += N - OVERLAP;
			}
    	///// SUBTRACTIVE /////
		} else if (method == subtractive) {
			if(pressedkeys < 1) {
				for(j = 0; j < N; j++) {
					waveform0[j] = 0;
					waveform1[j] = 0;
				}
			} else {
				clear_v = 1;
				for(i = 0; i < MIDI_POLY_MAX; i++) {
					if(freqs[i] > 0 || adsr_state[i] > 0) {
						if (waveformSet == 1)
							square_wave(freqs[i], SIG_AMP, k, clear_v, i);
						else if (waveformSet == 2)
							triangle_wave(freqs[i], SIG_AMP, k, clear_v, i);
						else if (waveformSet == 3)
							sawtooth_wave(freqs[i], SIG_AMP, k, clear_v, i);

						if (clear_v == 1)
							clear_v = 0;
					}
				}
				fft_full();
				if (filterSet == lowpass)
					lowPassFilter(sub_lowfreq);
				else if (filterSet == highpass)
					highPassFilter(sub_highfreq);
				else if (filterSet == bandpass)
					bandPassFilter(sub_lowfreq, sub_highfreq);
				else if (filterSet == bandstop)
					bandStopFilter(sub_lowfreq, sub_highfreq);
				ifft_full();
				while(sem_dac == 0);
				for(j = 0; j < N; j++) {
					if (j < OVERLAP) {
						if (whichwaveform == 1) {
							waveform0[j] = overlaptable[j]*SIG_AMP*v[j*2]; // tu by bylo przepisywanie z myWav
						} else {
							waveform1[j] = overlaptable[j]*SIG_AMP*v[j*2];
						}
					} else if (j >= N - OVERLAP) {
						if (whichwaveform) {
							waveform0[j] = overlaptable[N-j-1]*SIG_AMP*v[j*2];
						} else {
							waveform1[j] = overlaptable[N-j-1]*SIG_AMP*v[j*2];
						}
					} else {
						if (whichwaveform) {
							waveform0[j] = SIG_AMP*v[j*2];
						} else {
							waveform1[j] = SIG_AMP*v[j*2];
						}
					}
				}
				sem_dac = 0;
				k += N - OVERLAP;
			}
		// FM
    	} else if (method == fm){
    		if(pressedkeys < 1) {
				for(j = 0; j < N; j++) {
					waveform0[j] = 0;
					waveform1[j] = 0;
					k = 0;
				}
			} else {
				clear_v = 1;
				for(i = 0; i < MIDI_POLY_MAX; i++) {
					if(freqs[i] > 0 || adsr_state[i] > 0) {
						ADSR(i);
						if (clear_v == 1){
							for(j = 0; j < N; j++) {
								v[j*2] = adsr[i]*sinf((float)(j+k)*2.0*M_PI*freqs[i]*(1.0/Fs) + (float)fm_modamp*sinf((float)(j+k)*2.0*M_PI*(float)fm_modfreq*(1.0/Fs)));
							}
							clear_v = 0;
						} else {
							for(j = 0; j < N; j++) {
								v[j*2] += adsr[i]*sinf((float)(j+k)*2.0*M_PI*freqs[i]*(1.0/Fs) + (float)fm_modamp*sinf((float)(j+k)*2.0*M_PI*(float)fm_modfreq*(1.0/Fs)));
							}
						}
					}
				}
				while(sem_dac == 0);
				for(j = 0; j < N; j++) {
					if (j < OVERLAP) {
						if (whichwaveform == 1) {
							waveform0[j] = overlaptable[j]*v[j*2]*SIG_AMP*1000;
						} else {
							waveform1[j] = overlaptable[j]*v[j*2]*SIG_AMP*1000;
						}
					} else if (j >= N - OVERLAP) {
						if (whichwaveform) {
							waveform0[j] = overlaptable[N-j-1]*v[j*2]*SIG_AMP*1000;
						} else {
							waveform1[j] = overlaptable[N-j-1]*v[j*2]*SIG_AMP*1000;
						}
					} else {
						if (whichwaveform) {
							waveform0[j] = v[j*2]*SIG_AMP*1000;
						} else {
							waveform1[j] = v[j*2]*SIG_AMP*1000;
						}
					}
				}
				sem_dac = 0;
				k += N - OVERLAP;
			}
    	} else if (method == fm_bell){
			if(pressedkeys < 1) {
				for(j = 0; j < N; j++) {
					waveform0[j] = 0;
					waveform1[j] = 0;
					k = 0;
				}
			} else {
				clear_v = 1;
				for(i = 0; i < MIDI_POLY_MAX; i++) {
					if(freqs[i] > 0 || adsr_state[i] > 0) {
						float bell_adsr = exp(-adsr[i]*bell_adsr_coefficient);;
						adsr[i] += (float)N/Fs;
						float mod_freq = 1.4*freqs[i];
						if (clear_v == 1) {
							for(j = 0; j < N; j++) {
								v[j*2] = bell_adsr*sinf((float)(j+k)*2.0*M_PI*freqs[i]*(1.0/Fs) + (float)fm_modamp*sinf((float)(j+k)*2.0*M_PI*(float)mod_freq*(1.0/Fs)));
							}
							clear_v = 0;
						} else {
							for(j = 0; j < N; j++) {
								v[j*2] += bell_adsr*sinf((float)(j+k)*2.0*M_PI*freqs[i]*(1.0/Fs) + (float)fm_modamp*sinf((float)(j+k)*2.0*M_PI*(float)mod_freq*(1.0/Fs)));
							}
						}
						if (bell_adsr < 0.1) {
							adsr_state[i] = 0;
							adsr[i] = 0.0;
							freqs[i] = 0.0;
							pressedkeys--;
						}
					}
				}
				while(sem_dac == 0);
				for(j = 0; j < N; j++) {
					if (j < OVERLAP) {
						if (whichwaveform == 1) {
							waveform0[j] = overlaptable[j]*v[j*2]*SIG_AMP*1000;
						} else {
							waveform1[j] = overlaptable[j]*v[j*2]*SIG_AMP*1000;
						}
					} else if (j >= N - OVERLAP) {
						if (whichwaveform) {
							waveform0[j] = overlaptable[N-j-1]*v[j*2]*SIG_AMP*1000;
						} else {
							waveform1[j] = overlaptable[N-j-1]*v[j*2]*SIG_AMP*1000;
						}
					} else {
						if (whichwaveform) {
							waveform0[j] = v[j*2]*SIG_AMP*1000;
						} else {
							waveform1[j] = v[j*2]*SIG_AMP*1000;
						}
					}
				}
				sem_dac = 0;
				k += N - OVERLAP;
			}
		// violin
		} else if (method == violin){
			if(pressedkeys < 1) {
				for(j = 0; j < N; j++) {
					waveform0[j] = 0;
					waveform1[j] = 0;
					k = 0;
				}
			} else {
				clear_v = 1;
				for(i = 0; i < MIDI_POLY_MAX; i++) {
					if(freqs[i] > 0 || adsr_state[i] > 0) {
						ADSR(i);
						if (clear_v == 1){
							if(flag_violin == 1) { // this is executed when the key is pressed
								flag_violin = 0;
								if(freqs[i] > -0.1 && freqs[i] < 0.1)
									continue;
								baseDelay = Fs/freqs[i] - 4.0;
								if (baseDelay <= 0.0) baseDelay = 0.3;
								// neck delay line
								neck_delay = baseDelay*(1.0-betaRatio);
								neck_inPoint = 0;
								neck_gain = 1;
								neck_outPointer = (double)neck_inPoint - neck_delay;
								while (neck_outPointer < 0)
									neck_outPointer = neck_outPointer + nDelays+1;

								neck_outPoint = neck_outPointer;
								neck_alpha = neck_outPointer - (double)neck_outPoint;
								neck_omAlpha = 1.0 - neck_alpha;
								if (neck_outPoint == nDelays+1)
									neck_outPoint = 0;

								neck_doNextOut = 1;

								// bridge delay line
								bridge_delay = baseDelay*betaRatio;
								bridge_inPoint = 0;
								bridge_gain = 1;
								bridge_outPointer = (double)bridge_inPoint - bridge_delay;
								while (bridge_outPointer < 0)
									bridge_outPointer = bridge_outPointer + nDelays+1;
								bridge_outPoint = bridge_outPointer;
								bridge_alpha = bridge_outPointer - (double)bridge_outPoint;
								bridge_omAlpha = 1.0 - bridge_alpha;
								if (bridge_outPoint == nDelays+1)
									bridge_outPoint = 0;
								for(i = 0; i < 343; i++) {
									bridgeDelay[i] = 0.0;
									neckDelay[i] = 0.0;
								}
								vibrato_rate = vibrato_TABLE_SIZE*vibrato_freq/(double)Fs; // vibrato can be changed via user interface, so it needs to be reinitialized
								for (i = 0; i <  vibrato_TABLE_SIZE; i++){
									vibrato_table[i] = sin((double)i*2.0*M_PI/(double)vibrato_TABLE_SIZE);
								}
							}
							for(j = 0; j < OVERLAP; j++){  // to avoid overlapping despite not turning it off, the last OVERLAP samples are rewritten to the beggining of next data frame
									v[j*2] = v[(N-OVERLAP+j)*2];
							}
							for(j = OVERLAP; j < N; j++) { // the rest N-OVERLAP samples are generated
								double bowVelocity = maxVelocity*adsr[i];
								stringfilter = stringfilter_b*stringfilter_gain*bridgeDelay[0] - stringfilter_a*stringfilter;

								double bridgeReflection = -stringfilter;
								double nutReflection = -neckDelay[0];
								double stringVelocity = bridgeReflection + nutReflection;
								double deltaV = bowVelocity - stringVelocity;

								// bowtable
								double newVelocity = 0.0;
								if (bowDown){
									double sample = deltaV + bowtable_offset;
									sample = pow(fabs(sample*bowtable_slope) + 0.75, -4);
									if (sample < bowtable_minOutput) sample = bowtable_minOutput;
									if (sample > bowtable_maxOutput) sample = bowtable_maxOutput;
									newVelocity = deltaV*sample;
								}

								// neck delay line tick
								double input = bridgeReflection + newVelocity;
								neckDelay[neck_inPoint] = input*neck_gain;
								neck_inPoint++;
								if (neck_inPoint == nDelays+1)
									neck_inPoint = 0;

								double neck_nextOutput = 0;
								if (neck_doNextOut) {
									neck_nextOutput = neckDelay[neck_outPoint]*neck_omAlpha;
									if (neck_outPoint+1 < nDelays+1)
										neck_nextOutput = neck_nextOutput + neckDelay[neck_outPoint+1]*neck_alpha;
									else
										neck_nextOutput = neck_nextOutput + neckDelay[0]*neck_alpha;
									neck_doNextOut = 0;
								}
								neckDelay[0] = neck_nextOutput;

								neck_doNextOut = 1;
								neck_outPoint++;
								if (neck_outPoint == nDelays+1)
									neck_outPoint = 0;

								// bridge delay line tick
								input = nutReflection + newVelocity;
								bridgeDelay[bridge_inPoint] = input*bridge_gain;
								bridge_inPoint++;
								if (bridge_inPoint == nDelays+1)
									bridge_inPoint = 0;
								double bridge_nextOutput = 0;
								if (bridge_doNextOut){
									bridge_nextOutput = bridgeDelay[bridge_outPoint]*bridge_omAlpha;
									if (bridge_outPoint+1 < nDelays+1)
										bridge_nextOutput = bridge_nextOutput + bridgeDelay[bridge_outPoint+1]*bridge_alpha;
									else
										bridge_nextOutput = bridge_nextOutput + bridgeDelay[0]*bridge_alpha;

									 bridge_doNextOut = 0;
								}
								bridgeDelay[0] = bridge_nextOutput;
								bridge_doNextOut = 1;
								bridge_outPoint++;
								if (bridge_outPoint == nDelays+1)
									bridge_outPoint = 0;

								// vibrato
								if (vibrato_gain > 0.0) {
									while (vibrato_time < 0.0)
										vibrato_time += vibrato_TABLE_SIZE;
									while (vibrato_time >= vibrato_TABLE_SIZE)
										vibrato_time -= vibrato_TABLE_SIZE;
									int vibrato_iIndex = vibrato_time;
									vibrato_alpha = vibrato_time - vibrato_iIndex;
									double tmp = vibrato_table[vibrato_iIndex+1];
									tmp += (vibrato_alpha*(vibrato_table[vibrato_iIndex+1] - tmp));
									vibrato_time += vibrato_rate;

									double newdel = baseDelay*(1.0-betaRatio) + baseDelay*vibrato_gain*tmp;
									neck_delay = newdel;
									neck_outPointer = (double)neck_inPoint - neck_delay;
									while (neck_outPointer < 0)
										neck_outPointer += nDelays+1;
									neck_outPoint = neck_outPointer;
									neck_alpha = neck_outPointer - (double)neck_outPoint;
									neck_omAlpha = 1.0 - neck_alpha;
									if (neck_outPoint == nDelays+1)
										neck_outPoint = 0;
									neck_doNextOut = 1;
								}

								v[j*2] = bridgeDelay[0];
							}
							clear_v = 0;
						} else {
							for(j = 0; j < N; j++) {
								v[j*2] += 0; // No polyphony in violin synthesis
							}
						}
					}
				}
				while(sem_dac == 0);
				for(j = 0; j < N; j++) {
					if (j < OVERLAP) {
						if (whichwaveform == 1) {
							waveform0[j] = overlaptable[j]*v[j*2]*SIG_AMP*10000;
						} else {
							waveform1[j] = overlaptable[j]*v[j*2]*SIG_AMP*10000;
						}
					} else if (j >= N - OVERLAP) {
						if (whichwaveform) {
							waveform0[j] = overlaptable[N-j-1]*v[j*2]*SIG_AMP*10000;
						} else {
							waveform1[j] = overlaptable[N-j-1]*v[j*2]*SIG_AMP*10000;
						}
					} else {
						if (whichwaveform) {
							waveform0[j] = v[j*2]*SIG_AMP*10000;
						} else {
							waveform1[j] = v[j*2]*SIG_AMP*10000;
						}
					}
				}
				sem_dac = 0;
				k += N;
			}
		}
    }
}

