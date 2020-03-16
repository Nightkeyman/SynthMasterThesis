// stdafx.cpp : source file that includes just the standard includes
// Projekt_0.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

void fDaneDSP(unDaneType *D_DSP)
{
	D_DSP->DxDSP.numbParams = numbParamsConst;
	D_DSP->DxDSP.rozmKomunik = rozmKomunikConst;
	D_DSP->DxDSP.daneClassSize = sizeof(StrDaneDSP);
}


char tab_zn[SIZE_TAB_ZN] = {"abcdefgh01234567efghijkl98765432"};
char tab_zn_input[SIZE_TAB_ZN];
