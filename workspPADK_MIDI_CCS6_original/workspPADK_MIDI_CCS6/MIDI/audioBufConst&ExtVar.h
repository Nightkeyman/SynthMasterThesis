#ifndef AUDIOBUFCONSTEXTVAR_H_
#define AUDIOBUFCONSTEXTVAR_H_

#endif /*AUDIOBUFCONSTEXTVAR_H_*/

#define ADC_TCC 1             
extern CSL_DmaxHandle               hDmaxAdc;

#define DAC_TCC 2
extern CSL_DmaxHandle               hDmaxDac;

extern CSL_IntcObj              intcObj; 
extern CSL_IntcHandle           hIntc;
extern CSL_IntcEventEnableState eventStat;

extern CSL_IntcObj              intcObj_uart;
extern CSL_IntcHandle           hIntc_uart;
extern CSL_IntcEventEnableState eventStat_uart;

extern CSL_IntcHandle           hIntc_midi;
extern CSL_IntcObj              intcObj_midi;
extern CSL_IntcEventEnableState eventStat_midi;

//
//  Audio Buffers const
//
//#define FRAME_SIZE  80
#define FRAME_SIZE  128
#define NUM_CHANNEL 4
#define STEREO      2
#define PINGPONG    2
typedef struct {
	int w1_L;
	int w2_L;
	int w3_L;
	int w4_L;
	int w1_R;
	int w2_R;
	int w3_R;
	int w4_R;
} IOStruct;

//int tab0[5][3];  //-> tablicz dwuwymiarowa
//int (*ptab)[3];  //-> wskaŸnik do tablicy dwuwymiarowej o drugim wymiarze = 3, pierwszy jest nieistotny
//ptab = tab0;
//ptab[1][2]=25; jest to¿same z -> tab0[1][2]=25; 

//#ifndef AUDIOBUFSRUCTS_
//#define AUDIOBUFSRUCTS_
//#else
//#endif /*AUDIOBUFSRUCTS_*/

typedef union {
	int *pBuf;
    IOStruct *pIO;
} IOBufType;
extern IOBufType IBuf;
extern IOBufType OBuf;

typedef union {
	int *pBuf;
    int (*ptab)[NUM_CHANNEL];  //-> wskaŸnik do tablicy dwuwymiarowej
} IOBufType2;
extern IOBufType2 IBuf2;
extern IOBufType2 OBuf2;

typedef union {
	int *pBuf;
    int (*ptab)[NUM_CHANNEL][FRAME_SIZE];  //-> wskaŸnik do tablicy trójwymiarowej
} IOBufType3;
extern IOBufType3 IBuf3;
extern IOBufType3 OBuf3;

extern int dmaxDacBuffer[PINGPONG][STEREO][NUM_CHANNEL][FRAME_SIZE];
extern int dmaxAdcBuffer[PINGPONG][STEREO][NUM_CHANNEL][1];

extern int gain;
extern int opcja;


