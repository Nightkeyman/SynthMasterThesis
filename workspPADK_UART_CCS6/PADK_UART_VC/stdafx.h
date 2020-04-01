// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

// TODO: reference additional headers your program requires here


#define  numbParamsConst  10
#define rozmKomunikConst 256
//#define danClSizeConst 337

typedef struct {
	int daneClassSize;
	short option;
	short minOption;
	short maxOption;
	short gain;
	short minGain;
	short maxGain;
	short numbParams;
	short paramsTab[numbParamsConst];
	short minParamsTab[numbParamsConst];
	short maxParamsTab[numbParamsConst];
	short rozmKomunik;
	char Komunikat[rozmKomunikConst];
	unsigned char wysw7Segm;
} StrDaneDSP;

typedef union {
	StrDaneDSP DxDSP;
	unsigned char Buf[sizeof(StrDaneDSP)];
} unDaneType;

#define SIZE_TAB_ZN		33
extern  char tab_zn[SIZE_TAB_ZN];
extern  char tab_zn_input[SIZE_TAB_ZN];

void fDaneDSP(unDaneType *D_DSP);
