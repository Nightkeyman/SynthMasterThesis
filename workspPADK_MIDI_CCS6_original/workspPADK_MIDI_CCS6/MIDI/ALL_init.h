/*
 * ALL_init.h
 *
 *  Created on: 18 cze 2019
 *      Author: Krzysztof
 */


#ifndef ALL_INIT_H_
#define VAR_FUN_H_

    CSL_Status status;
    CSL_BitMask16 mask;


    /*---------------------------------------------------------------*/
    /* Chip Initialization                                           */
    /*---------------------------------------------------------------*/
    CSL_chipInit( NULL );

    /*---------------------------------------------------------------*/
    /* Output Audio Buffer Initialization                            */
    /*---------------------------------------------------------------*/
    memset( dmaxDacBuffer, 0, sizeof(dmaxDacBuffer) );

    /*---------------------------------------------------------------*/
    /* Set the base address of the Interrupt Vector Table            */
    /*---------------------------------------------------------------*/
	CSL_intcSetVectorPtr( 0x10000000 );

    /*---------------------------------------------------------------*/
    /* Clock Generator Initilization                                 */
    /*---------------------------------------------------------------*/
    clkgenParams.osc_sel = OSC_24_576MHz;
    clkgenParams.adc_dir_clk_src = CLK_SRC_OSC;
    clkgenParams.dac_dit_clk_src = CLK_SRC_OSC;
	clkgenParams.adc_scki = CLK_SRC_OSC_1X;
	clkgenParams.dac_scki = CLK_SRC_OSC_1X;
    CLKGEN_Init( &clkgenParams );

    /*---------------------------------------------------------------*/
    /* ADC Initilization                                             */
    /*---------------------------------------------------------------*/
    adcParams.format = ADC_FMT_24B_LEFT_JUST;
    adcParams.rate = ADC_RATE_DUAL;
    ADC_Init( &adcParams );

    /*---------------------------------------------------------------*/
    /* DAC Initilization (use default values)                        */
    /*---------------------------------------------------------------*/
    dacParams.fs = DAC_FS_DUALRATE;
    dacParams.mute = DAC_MUTE_OFF;
    dacParams.format = DAC_FMT_24B_LEFT_JUST;
    dacParams.deemphasis = DAC_DEM_OFF;
    DAC_Init( &dacParams );

    /*---------------------------------------------------------------*/
	/* UART Initilization (use default values)                        */
	/*---------------------------------------------------------------*/
	uartParams.ier = 1;
	UART_Init( &uartParams );

    /*---------------------------------------------------------------*/
    /* DMAX Initilization                                            */
    /*---------------------------------------------------------------*/
    CSL_dmaxInit( NULL );

    /*---------------------------------------------------------------*/
    /* McASP Initilization                                           */
    /*---------------------------------------------------------------*/
	CSL_mcaspInit( NULL );
	printf("Correctly inited");

    /*---------------------------------------------------------------*/
    /* Opening McASP Module                                          */
	/*---------------------------------------------------------------*/
    /* Create CPU Interrupt Event Entry - dMax EVENT 28 corresponds  */
    /* to AMUTEIN2 (External Int 6 -> UART)                          */
    /*---------------------------------------------------------------*/

	// Reserve MCASP UART
    hMcasp0_uart = CSL_mcaspOpen( &mcasp0Obj_uart, CSL_MCASP_0, (CSL_McaspParam *)NULL, &status );
	status = CSL_mcaspHwSetup( hMcasp0_uart, &mcasp0HwCfg );

    //hMcasp0 = CSL_mcaspOpen( &mcasp0Obj, CSL_MCASP_0, NULL, &status );
    //if ( (hMcasp0 == NULL) || (status != CSL_SOK) )
    //{
    //    fprintf( stderr, "Failed to open the McASP Module \n" );
	//    return -1;
    //}

    /*---------------------------------------------------------------*/
    /* Opening dMAX Module                                           */
    /*---------------------------------------------------------------*/

	//Reserve dMax UART
	dmaxUartObj.eventUid = CSL_DMAX_HIPRIORITY_EVENT28_UID;
	hDmaxUart = CSL_dmaxOpen( &dmaxUartObj, CSL_DMAX, (CSL_DmaxParam *)NULL, &status );

	/*
	adcDmaxObj.eventUid = CSL_DMAX_HIPRIORITY_MCASP0RX_UID;
	adcDmaxObj.paramUid = CSL_DMAX_HIPRIORITY_PARAMETERENTRY_ANY;
	hDmaxAdc = CSL_dmaxOpen( &adcDmaxObj, CSL_DMAX, NULL ,&status );
	if ( (status != CSL_SOK) || (hDmaxAdc == (CSL_DmaxHandle)CSL_DMAX_BADHANDLE) )
	{
        fprintf( stderr, "Failed to open the dMAX Module \n" );
	    return -1;
	}

	dacDmaxObj.eventUid = CSL_DMAX_HIPRIORITY_MCASP0TX_UID;
	dacDmaxObj.paramUid = CSL_DMAX_HIPRIORITY_PARAMETERENTRY_ANY;
	hDmaxDac = CSL_dmaxOpen( &dacDmaxObj, CSL_DMAX, NULL ,&status );
	if ( (status != CSL_SOK) || (hDmaxDac == (CSL_DmaxHandle)CSL_DMAX_BADHANDLE) )
	{
        fprintf( stderr, "Failed to open the dMAX Module \n" );
	    return -1;
	}
	*/

    /*---------------------------------------------------------------*/
    /* Event Enable                                                  */
    /*---------------------------------------------------------------*/

	// Dmax Event Disable
	//CSL_dmaxHwControl( hDmaxAdc, CSL_DMAX_CMD_EVENTDISABLE, NULL );
	//CSL_dmaxHwControl( hDmaxDac, CSL_DMAX_CMD_EVENTDISABLE, NULL );

	// Clear TCC
	//CSL_dmaxHwControl( hDmaxAdc, CSL_DMAX_CMD_CLEARTCC, NULL );
	//CSL_dmaxHwControl( hDmaxDac, CSL_DMAX_CMD_CLEARTCC, NULL );

	// Dmax Event Enable
	//CSL_dmaxHwControl( hDmaxAdc, CSL_DMAX_CMD_EVENTENABLE, NULL );
    //CSL_dmaxHwControl( hDmaxDac, CSL_DMAX_CMD_EVENTENABLE, NULL );

    // Dmax Event Enable UART & NMI
	CSL_dmaxHwControl( hDmaxUart, CSL_DMAX_CMD_EVENTENABLE, NULL );

    /*---------------------------------------------------------------*/
    /* DMAX for data transfer on MCASP0RX DMA REQ - 3D Transfer      */
    /*---------------------------------------------------------------*/

    //
    // DMAX Parameter initialization structure
    //

    // Source Reload Address0
    adcGpxfrParameterSetup.srcReloadAddr0 = (Uint32)0x54000000;     // McASP0

    // Destination Reload Address0
    adcGpxfrParameterSetup.dstReloadAddr0 = (Uint32)dmaxAdcBuffer[0];

    // Source Reload Address1
    adcGpxfrParameterSetup.srcReloadAddr1 = (Uint32)0x54000000;     // McASP0

    // Destination Reload Address1
    adcGpxfrParameterSetup.dstReloadAddr1 = (Uint32)dmaxAdcBuffer[1];

    // Source Index0 Value
    adcGpxfrParameterSetup.srcIndex0 = (Int16)1;

    // Destination Index0 Value
    adcGpxfrParameterSetup.dstIndex0 = (Int16)FRAME_SIZE;

    // Source Index1 Value
    adcGpxfrParameterSetup.srcIndex1 = (Int16)-(NUM_CHANNEL-1);

    // Destination Index1 Value
    adcGpxfrParameterSetup.dstIndex1 = (Int16)FRAME_SIZE;

    // Source Index2 Value
    adcGpxfrParameterSetup.srcIndex2 = (Int16)-(NUM_CHANNEL-1);

    // Destination Index2 Value
    adcGpxfrParameterSetup.dstIndex2 = (Int16)-( (STEREO*NUM_CHANNEL-1)*FRAME_SIZE - 1),

    // Dimension 0 Count Value
    adcGpxfrParameterSetup.count0 = (Uint16)NUM_CHANNEL;

    // Dimension 1 Count Value
    adcGpxfrParameterSetup.count1 = (Uint16)STEREO;

    // Dimension 2 Count Value
    adcGpxfrParameterSetup.count2 = (Uint16)FRAME_SIZE;


    //
    // DMAX Event initialization structure
    //

    // Event Type
    adcGpxfrEventSetup.etype = CSL_DMAX_EVENT5_ETYPE_GENERALXFR;

    // Pointer to parameterSetup
    adcGpxfrEventSetup.paramSetup = &adcGpxfrParameterSetup;

    // Quantum Transfer Size Limit
    adcGpxfrEventSetup.qtsl = CSL_DMAX_EVENT5_QTSL_MOVE8_ELE;

    // Transfer Synchronization
    adcGpxfrEventSetup.sync = 0;

    // Transfer Complete Code
    adcGpxfrEventSetup.tcc = ADC_TCC;

    // Alternate Transfer Mode Interrupt
    adcGpxfrEventSetup.atcint = CSL_DMAX_EVENT5_ATCINT_DISABLE;

    // Transfer Completion Interrupt
    adcGpxfrEventSetup.tcint = CSL_DMAX_EVENT5_TCINT_ENABLE;

    // Reload
    adcGpxfrEventSetup.rload = CSL_DMAX_EVENT5_RLOAD_ENABLE;

    // Counter Configuration
    adcGpxfrEventSetup.cc = CSL_DMAX_EVENT5_CC_COUNT2_15_COUNT1_8_COUNT0_8;

    // Element Size
    adcGpxfrEventSetup.esize = CSL_DMAX_EVENT5_ESIZE_32BIT;

    // Pointer to Transfer Entry (pte)
    adcGpxfrEventSetup.pte = hDmaxAdc->paramPtr;


    //
    // DMAX initialization structure
    //

	// DMAX Priority
    //adcDmaxHwSetup.priority = CSL_DMAX_HI_PRIORITY;

	//DMAX Polarity
    //adcDmaxHwSetup.polarity = CSL_DMAX_POLARITY_RISING_EDGE;

	// DMAX Event initialization structure
    //adcDmaxHwSetup.eventSetup = &adcGpxfrEventSetup;


    // Set Dmax Event Entry 28 UART
    status = CSL_dmaxHwSetup( hDmaxUart, &uartDmaxHwSetup );
    if ( status != CSL_SOK )
    {
        //fprintf( stderr, "Failed to setup the dMAX Module \n" );
	    return -1;
	}
    //status = CSL_dmaxHwSetup( hDmaxAdc, &adcDmaxHwSetup );
    //if ( status != CSL_SOK )
    //{
    //    fprintf( stderr, "Failed to setup the dMAX Module \n" );
	//    return -1;
	//}

    /*---------------------------------------------------------------*/
    /* DMAX for data transfer on MCASP0TX DMA REQ - 3D Transfer      */
    /*---------------------------------------------------------------*/

    //
    // DMAX Parameter initialization structure
    //

    // Source Reload Address0
    dacGpxfrParameterSetup.srcReloadAddr0 = (Uint32)dmaxDacBuffer[0];

    // Destination Reload Address0
    dacGpxfrParameterSetup.dstReloadAddr0 = (Uint32)0x54000000;     // McASP0

    // Source Reload Address1
    dacGpxfrParameterSetup.srcReloadAddr1 = (Uint32)dmaxDacBuffer[1];

    // Destination Reload Address1
    dacGpxfrParameterSetup.dstReloadAddr1 = (Uint32)0x54000000;     // McASP0

    // Source Index0 Value
    dacGpxfrParameterSetup.srcIndex0 = (Int16)FRAME_SIZE;

    // Destination Index0 Value
    dacGpxfrParameterSetup.dstIndex0 = (Int16)1;

    // Source Index1 Value
    dacGpxfrParameterSetup.srcIndex1 = (Int16)FRAME_SIZE;

    // Destination Index1 Value
    dacGpxfrParameterSetup.dstIndex1 = (Int16)-(NUM_CHANNEL-1);

    // Source Index2 Value
    dacGpxfrParameterSetup.srcIndex2 = (Int16)-( (STEREO*NUM_CHANNEL-1)*FRAME_SIZE - 1);

    // Destination Index2 Value
    dacGpxfrParameterSetup.dstIndex2 = (Int16)-(NUM_CHANNEL-1);

    // Dimension 0 Count Value
    dacGpxfrParameterSetup.count0 = (Uint16)NUM_CHANNEL;

    // Dimension 1 Count Value
    dacGpxfrParameterSetup.count1 = (Uint16)STEREO;

    // Dimension 2 Count Value
    dacGpxfrParameterSetup.count2 = (Uint16)FRAME_SIZE;

    //
    // DMAX Event initialization structure
    //

    // Event Type
    dacGpxfrEventSetup.etype = CSL_DMAX_EVENT4_ETYPE_GENERALXFR;

    // Pointer to parameterSetup
    dacGpxfrEventSetup.paramSetup = &dacGpxfrParameterSetup;

    // Quantum Transfer Size Limit
    dacGpxfrEventSetup.qtsl = CSL_DMAX_EVENT4_QTSL_MOVE8_ELE;

    // Transfer Synchronization
    dacGpxfrEventSetup.sync = 0;

    // Transfer Complete Code
    dacGpxfrEventSetup.tcc = DAC_TCC;

    // Alternate Transfer Mode Interrupt
    dacGpxfrEventSetup.atcint = CSL_DMAX_EVENT4_ATCINT_DISABLE;

    // Transfer Completion Interrupt
    dacGpxfrEventSetup.tcint = CSL_DMAX_EVENT4_TCINT_ENABLE;

    // Reload
    dacGpxfrEventSetup.rload = CSL_DMAX_EVENT4_RLOAD_ENABLE;

    // Counter Configuration
    dacGpxfrEventSetup.cc = CSL_DMAX_EVENT4_CC_COUNT2_15_COUNT1_8_COUNT0_8;

    // Element Size
    dacGpxfrEventSetup.esize = CSL_DMAX_EVENT0_ESIZE_32BIT;

    // Pointer to Transfer Entry
    dacGpxfrEventSetup.pte = hDmaxDac->paramPtr;

    //
    // DMAX initialization structure
    //

	// DMAX Priority
    //dacDmaxHwSetup.priority = CSL_DMAX_HI_PRIORITY;

	//DMAX Polarity
    //dacDmaxHwSetup.polarity = CSL_DMAX_POLARITY_RISING_EDGE;

	// DMAX Event initialization structure
    //dacDmaxHwSetup.eventSetup = &dacGpxfrEventSetup;

    //status = CSL_dmaxHwSetup( hDmaxDac, &dacDmaxHwSetup );
    //if ( status != CSL_SOK )
    //{
    //    fprintf( stderr, "Failed to setup the dMAX Module \n" );
	//    return -1;
	//}

    /*---------------------------------------------------------------*/
    /* McASP0 Setup - (Default PADK values)                          */
    /*---------------------------------------------------------------*/
	// Set Mcasp clocks to 96K sample rate
    //mcasp0HwCfg.rx.clk.clkSetupClk |= ADC_96K_CLK;
    //mcasp0HwCfg.tx.clk.clkSetupClk |= DAC_96K_CLK;

    //status = CSL_mcaspHwSetup( hMcasp0, &mcasp0HwCfg );
  	//if ( status != CSL_SOK )
    //{
    //    fprintf( stderr, "Failed to setup the McASP 0\n" );
	//    return -1;
    //}

    /*---------------------------------------------------------------*/
    /* Setup interrupt handler                                       */
    /*---------------------------------------------------------------*/
	if ( SetupInterrupts() )
	{
		fprintf( stderr, "Failed to setup interrupts\n" );
	    return -1;
    }
    /*---------------------------------------------------------------*/
    /* Take receive serial clock, high frequency clock and           */
    /* serializer out of reset                                       */
    /*---------------------------------------------------------------*/
	//hMcasp0->regs->RSTAT = 0x1FFF;
    //mask =  CSL_MCASP_GBLCTL_RCLKRST_MASK   |
    //        CSL_MCASP_GBLCTL_RHCLKRST_MASK  |
    //        CSL_MCASP_GBLCTL_RSRCLR_MASK;
    //CSL_mcaspResetCtrl( hMcasp0, mask );

    /*---------------------------------------------------------------*/
    /* Take transmit serial clock, high frequency clock and          */
    /* serializer out of reset                                       */
    /*---------------------------------------------------------------*/
	//hMcasp0->regs->XSTAT = 0x1FFF;
    //mask =  CSL_MCASP_GBLCTL_XCLKRST_MASK   |
    //        CSL_MCASP_GBLCTL_XHCLKRST_MASK  |
    //        CSL_MCASP_GBLCTL_XSRCLR_MASK;
    //CSL_mcaspResetCtrl( hMcasp0, mask );

    /*---------------------------------------------------------------*/
    /* Verify all transmit buffers are serviced                      */
    /*---------------------------------------------------------------*/
    //while ( (hMcasp0->regs->XSTAT & 0x0020) == 0x0020 );

    /*---------------------------------------------------------------*/
    /* Take receive and transmit state machine out of reset          */
    /*---------------------------------------------------------------*/
    //CSL_mcaspHwControl( hMcasp0, CSL_MCASP_CMD_ACTIVATE_SM_RCV_XMT, NULL );

    /*---------------------------------------------------------------*/
    /* Take receive and transmit frame sync out of reset             */
    /*---------------------------------------------------------------*/
    //CSL_mcaspHwControl( hMcasp0, CSL_MCASP_CMD_ACTIVATE_FS_RCV_XMT, NULL );

    /*---------------------------------------------------------------*/
    /* Unmute audio outputs                                          */
    /*---------------------------------------------------------------*/
	DAC_RelayUnmute();

	/*---------------------------------------------------------------*/
	/* Analog audio initialization complete                          */
	/*---------------------------------------------------------------*/



	/*---------------------------------------------------------------*/
	/* Init GPIO Driver                                              */
	/*---------------------------------------------------------------*/
    GPIO_Reset();

	/*---------------------------------------------------------------*/
	/* Init USB Interface                                            */
	/*---------------------------------------------------------------*/
	USB_Reset();


#endif /* ALL_INIT_H_ */


