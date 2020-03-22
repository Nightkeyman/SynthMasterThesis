/*
 * var&fun.h
 *
 *  Created on: 13 cze 2019
 *      Author: Krzysztof
 */

#ifndef VAR_FUN_H_
#define VAR_FUN_H_


//
// CSL McASP 0 Module
//
CSL_McaspHandle  hMcasp0;
CSL_McaspObj 	 mcasp0Obj;

// ################## UART ##################
// McASP UART
CSL_McaspHandle hMcasp0_uart;
CSL_McaspObj 	mcasp0Obj_uart;
// for DMAX HW setup
CSL_McaspHwSetup mcasp0HwCfg = PADK_MCASP0_HWSETUP_DEFAULTS;
//
// McASP initialization structure
//
/*
CSL_McaspHwSetup mcasp0HwCfg = {
    // Value to be loaded in global control register (GLBCTL)
    {
        // Pin function register (PFUNC)
          (1<< 9)          // AXR9: GPIO (DSP_EXT_INT5)
        | (1<< 8)          // AXR8: GPIO (DSP_EXT_INT4)
        | (1<< 7),         // AXR7: GPIO (DSP_EXT_INT6)

        // Pin direction register (PDIR)
          (0<< 9)          // AXR9  : Input (DSP_EXT_INT5)
        | (0<< 8)          // AXR8  : Input (DSP_EXT_INT4)
        | (0<< 7),         // AXR7  : Input (DSP_EXT_INT6)

        // Global control register (GBLCTL)
        0x00000000,         // Everything in reset

        // Decides whether McASP operates in DIT mode (DITCTL)
        0x00000000,         // DIT mode disable

        // Digital loopback mode setup (DLBEN)
        0x00000000,         // Loopback mode disable

        // Mute control register (AMUTE)
        0x00000000,         // AMUTE pin is disabled

        // Setup serializer control register (SRCTL0-5)
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    },

    // Receiver settings
    {
		0
	},

    // Transmitter settings
    {
		0
	},

    // Power down emulation mode params - PWRDEMU
    CSL_MCASP_PWRDEMU_FREE_OFF
};
*/

#include "audioBufConst&ExtVar.h"

//
// CSL dMAX Module
//
//#define ADC_TCC 1  /* Definicja w pliku "audioBufConst&ExtVar.h" */
CSL_DmaxHandle               hDmaxAdc;
CSL_DmaxObj 				 adcDmaxObj;
CSL_DmaxHwSetup	             adcDmaxHwSetup;
CSL_DmaxGPTransferEventSetup adcGpxfrEventSetup;
CSL_DmaxGPXFRParameterSetup	 adcGpxfrParameterSetup;

//#define DAC_TCC 2  /* Definicja w pliku "audioBufConst&ExtVar.h" */
CSL_DmaxHandle               hDmaxDac;
CSL_DmaxObj                  dacDmaxObj;
CSL_DmaxHwSetup              dacDmaxHwSetup;
CSL_DmaxGPTransferEventSetup dacGpxfrEventSetup;
CSL_DmaxGPXFRParameterSetup  dacGpxfrParameterSetup;

// Dmax UART
CSL_DmaxObj 	dmaxUartObj;
CSL_DmaxHandle 	hDmaxUart;
CSL_DmaxHwSetup	uartDmaxHwSetup;

//
// CSL INTC Module
//
CSL_IntcObj              intcObj;
CSL_IntcHandle           hIntc;
CSL_IntcEventEnableState eventStat;
//

// Intc
CSL_IntcHandle           hIntc_uart;
CSL_IntcObj              intcObj_uart;
CSL_IntcEventEnableState eventStat_uart;

// PADK CLKGEN Module
//
CLKGEN_Params clkgenParams = CLKGEN_DEFAULT_PARAMS;


//
// PADK ADC Module
//
ADC_Params adcParams = ADC_DEFAULT_PARAMS;


//
// PADK DAC Module
//
DAC_Params dacParams = DAC_DEFAULT_PARAMS;


// PADK UART Module
//
UART_Params uartParams = UART_DEFAULT_PARAMS;


//
// Forward Declaration
//
int SetupInterrupts();
//interrupt void dmax_isr( void );    /* Definicja w pliku "iterrupts.c" */
//interrupt void nmi_isr( void );     /* Definicja w pliku "iterrupts.c" */

/* Definicja poni¿szych typów w pliku "audioBufConst&ExtVar.h" */
IOBufType IBuf;
IOBufType OBuf;

IOBufType2 IBuf2;
IOBufType2 OBuf2;

IOBufType3 IBuf3;
IOBufType3 OBuf3;

//
//  Audio Buffers
//
int dmaxDacBuffer[PINGPONG][STEREO][NUM_CHANNEL][FRAME_SIZE];
int dmaxAdcBuffer[PINGPONG][STEREO][NUM_CHANNEL][FRAME_SIZE];

int gain = 1;
int opcja = 1;

void *memset(void *s, int c, size_t n);


#endif /* VAR_FUN_H_ */
