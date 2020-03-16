
#define  numbParamsConst  10
#define rozmKomunikConst 256
#define danClSizeConst 337

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
	unsigned char Buf[danClSizeConst];
} unDaneType;


//void fDaneDSP(StrDaneDSP *D_DSP);

