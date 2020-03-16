// 
// This demo performs a simple loopback using the UART interface. In order 
// to execute this demo correctly, you will need to connect your board to
// your PC using a standard serial DB9 cable. The UART connector of the board
// is J3.
// 
// Once your board is connected, you will need to setup the serial connection
// on your PC using, for example, a software like Hyperterminal.
//
// In order to match the default initialization values of the PADK UART module,
// the serial connection must be configured as follow :
//      Serial Port     - COMx (depending of your PC configuration)
//      Bits per second - 115200
//      Data bits       - 8
//      Partity         - None
//      Stop bits       - 1
//      Flow control    - None
//
// Once your PC serial connection is configured and the DSP code is running
// on the PADK, any character you type in your Hyperterminal window should
// be displayed when the host receives it back from the PADK.
//

// CSL Modules
#include <soc.h>
#include <csl_mcasp.h>
#include <csl_dmax.h>
#include <csl_chip.h>
#include <csl_intc.h>
#include <math.h>

// PADK Library
#include "PADK.h"

#include <stdio.h>
#include <stdlib.h>

#include "PADK_UART.h"

#include "DaneDSP.h"
//extern
//void fDaneDSP(StrDaneDSP *D_DSP);
void fDaneDSP(StrDaneDSP *D_DSP)
{
	D_DSP->numbParams = numbParamsConst;
	D_DSP->rozmKomunik = rozmKomunikConst;
	D_DSP->daneClassSize = sizeof(StrDaneDSP);
}

//StrDaneDSP Dane;
unDaneType Dane;

//far int UART_Write( unsigned char *data, int N, int wait );

// McASP
CSL_McaspHandle hMcasp0;
CSL_McaspObj 	mcasp0Obj;

// Dmax
CSL_DmaxObj 	dmaxUartObj;	
CSL_DmaxHandle 	hDmaxUart;

// Intc
CSL_IntcHandle           hIntc;
CSL_IntcObj              intcObj;    
CSL_IntcEventEnableState eventStat;

//
// PADK UART Module
//
UART_Params uartParams = UART_DEFAULT_PARAMS;


//
// PADK MIDI Module
//
MIDI_Params midiParams = MIDI_DEFAULT_PARAMS;

CSL_DmaxCpuintEventSetup uartEventSetup = 
{
	CSL_DMAX_EVENT28_ETYPE_CPUINT,
	CSL_DMAX_EVENT28_INT_INT11
};

CSL_DmaxHwSetup	uartDmaxHwSetup =
{
	// DMAX Priority (priority)
	CSL_DMAX_HI_PRIORITY,

	//DMAX Polarity (polarity)
    CSL_DMAX_POLARITY_RISING_EDGE,

	// DMAX Event initialization structure (eventSetup)
	&uartEventSetup
};

//
// McASP initialization structure
//
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


// 
// UART related defines
//
#define UART_WAIT       1
#define UART_NO_WAIT    0

//
// Demo Presentation String
//
unsigned char demo_pres[] = 
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r"
		"*************************************************************************\n\r"
		"*************************************************************************\n\r"
		"**                                                                     **\n\r"	
		"**                             Lyrtech Inc.                            **\n\r"	
		"**           TMS320C6727-based Pro Audio Development Kit (PADK)        **\n\r"	
		"**                                                                     **\n\r"	
		"**              RS-232 Serial Communication Loopback Example           **\n\r"	
		"**                                                                     **\n\r"	
		"*************************************************************************\n\r"	
		"*************************************************************************\n\r"
		"\n\nEvery character you send to the DSP using this Hyperterminal session \n\r"
		"will be sent back by the DSP and displayed below.\n\n\r";

unsigned char rst_cursor_pos[] = "\r";
unsigned char int2bcd[16] = {
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
	};

//
// Forward Declaration 
//
//far int UART_Write( unsigned char *data, int N, int wait );
int UART_Write( unsigned char *data, int N, int wait );
int SetupInterrupts();
interrupt void uart_isr( void );
interrupt void nmi_isr( void );
//interrupt void midi_isr( void );
int bcditer=0;
int gain=1;
int gainOld=1;
int opcja=1;
#define DATA_ROZM  33
unsigned char data[DATA_ROZM];
unsigned char data_out[DATA_ROZM];
unsigned char data_midi[DATA_ROZM];
int num;
int flaga = 0;

//
//  Main Function
//
int main( int argc, char *argv[] )
{
	/*---------------------------------------------------------------*/
    /* Chip Initialization                                           */
    /*---------------------------------------------------------------*/
	CSL_chipInit( NULL );

    /*---------------------------------------------------------------*/
    /* Set the base address of the Interrupt Vector Table            */
    /*---------------------------------------------------------------*/
	CSL_intcSetVectorPtr( 0x10000000 );    

	/*---------------------------------------------------------------*/
    /* Initialize the UART module with default values                */
    /*---------------------------------------------------------------*/
	uartParams.ier = 1;
	UART_Init( &uartParams );

	/*---------------------------------------------------------------*/
	/* Initialize the MIDI module with default values                */
    /*---------------------------------------------------------------*/
	midiParams.ier = 1;
	MIDI_Init( &midiParams );


    /*---------------------------------------------------------------*/
    /* Setup interrupt handler                                       */
    /*---------------------------------------------------------------*/   
	if ( SetupInterrupts() )
	{
		fprintf( stderr, "Failed to setup interrupts\n" );
	    return -1;
    }

	/*---------------------------------------------------------------*/
    /* Main loop waits for a character to be sent to the board       */
	/* through the serial interface and sends it back to the host    */
	/* when it receives one											 */
    /*---------------------------------------------------------------*/
	
//	UART_Write( demo_pres, strlen(demo_pres), 1 );
	fDaneDSP(&Dane.DxDSP);
//    Dane.DxDSP.daneClassSize = danClSizeConst;

	int num_of_midi_bytes = 0;
	int toggle_midi = 0;
	while(1)  {

		if (flaga == 1) {
			flaga = 0;
	     	UART_Write( data_out, 1, UART_NO_WAIT );
		}

		/*if (num_of_midi_bytes = MIDI_Read(data_midi, 1, UART_NO_WAIT)) {
			MIDI_EnableLed1(toggle_midi ^= 1);
			MIDI_EnableLed2(!toggle_midi);
			UART_Write( (unsigned char *)num_of_midi_bytes, 1, UART_NO_WAIT );
			UART_Write( data_midi, 1, UART_NO_WAIT );
			while(1);
		}*/

	}
}

interrupt void nmi_isr( void )
{
    while(1);
}


interrupt void uart_isr( void )
{
	flaga = 0;
    static int toggle = 0;
	UART_EnableLed1( toggle ^= 1 );
    UART_EnableLed2( !toggle );
    num = UART_Read( data, 1, UART_NO_WAIT );
//    num = UART_Read( Dane.Buf, Dane.DxDSP.daneClassSize, UART_NO_WAIT );
    if( num )
    {
    	gain = (int)data[0];
    	data_out[0] = data[0];
    }
    if(data_out[0] == 2) GPIO_SetBCD( int2bcd[bcditer++] );
    flaga = 1;

//	num = UART_Read( data, 32, UART_NO_WAIT );
//	if( num )
//	{
//		//data[0]=data[0]*0x0A+data[1];
//		//data[1]='\0';
//		UART_Write( data, num, UART_WAIT );
//   	UART_Write( rst_cursor_pos, strlen(rst_cursor_pos), UART_NO_WAIT );
//	}
////	if( gain != gainOld )
////	{
////		gainOld = gain;
////		data[0] = gain+48;
////		UART_Write( data, 1, UART_WAIT );
////   	UART_Write( rst_cursor_pos, strlen(rst_cursor_pos), UART_NO_WAIT );
////	}
}

int SetupInterrupts()
{
    CSL_Status                    status;   
    CSL_IntcGlobalEnableState     state;

    
    /*---------------------------------------------------------------*/
    /* INTC Module Initialization                                    */
    /*---------------------------------------------------------------*/   
	status = CSL_intcInit( NULL ); 

    /*---------------------------------------------------------------*/
    /* Hook Transfert completion Notification from DMAX (INT11)       */
    /*---------------------------------------------------------------*/   
    hIntc = CSL_intcOpen( &intcObj, CSL_INTC_EVENTID_DMAXEVTOUT4, NULL, &status );
	if( (hIntc == NULL) || (status != CSL_SOK) ) 
	{	
		return -1;
	}
    
   /*---------------------------------------------------------------*/
   /* Create CPU Interrupt Event Entry - dMax EVENT 28 corresponds  */
   /* to AMUTEIN2 (External Int 6 -> UART)                          */
   /*---------------------------------------------------------------*/

	// Reserve MCASP 0
    hMcasp0 = CSL_mcaspOpen( &mcasp0Obj, CSL_MCASP_0, (CSL_McaspParam *)NULL, &status );
	status = CSL_mcaspHwSetup( hMcasp0, &mcasp0HwCfg );
   
	//Reserve dMax
	dmaxUartObj.eventUid = CSL_DMAX_HIPRIORITY_EVENT28_UID;
	hDmaxUart = CSL_dmaxOpen( &dmaxUartObj, CSL_DMAX, (CSL_DmaxParam *)NULL, &status );
    
    // Set Dmax Event Entry 28
    status = CSL_dmaxHwSetup( hDmaxUart, &uartDmaxHwSetup );    
    if ( status != CSL_SOK ) 
    {
        fprintf( stderr, "Failed to setup the dMAX Module \n" );
	    return -1;
	}

    // Dmax Event Enable
	CSL_dmaxHwControl( hDmaxUart, CSL_DMAX_CMD_EVENTENABLE, NULL );	

    CSL_intcHookIsr( CSL_INTC_EVENTID_DMAXEVTOUT4, (Uint32)uart_isr );
    //CSL_intcHookIsr( CSL_INTC_EVENTID_DMAXEVTOUT6, (Uint32)midi_isr );
	
    CSL_intcHookIsr( CSL_INTC_EVENTID_NMI, (Uint32)nmi_isr );

    CSL_intcEventEnable( CSL_INTC_EVENTID_DMAXEVTOUT4, &eventStat );
    CSL_intcEventEnable( CSL_INTC_EVENTID_DMAXEVTOUT6, &eventStat );
	
    CSL_intcEventEnable( CSL_INTC_EVENTID_NMI, &eventStat );
    CSL_intcGlobalEnable( &state );  

	return 0;

}
