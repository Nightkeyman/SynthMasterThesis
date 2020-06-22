################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
filters.obj: ../filters.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/cl6x" -mv67p --abi=coffabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/C672x/inc" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/PADK/dsp/inc" --define=c6727 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="filters.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

interrupts.obj: ../interrupts.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/cl6x" -mv67p --abi=coffabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/C672x/inc" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/PADK/dsp/inc" --define=c6727 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="interrupts.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/cl6x" -mv67p --abi=coffabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/C672x/inc" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/PADK/dsp/inc" --define=c6727 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

midi_fifo.obj: ../midi_fifo.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/cl6x" -mv67p --abi=coffabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/C672x/inc" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/PADK/dsp/inc" --define=c6727 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="midi_fifo.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

myfft.obj: ../myfft.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/cl6x" -mv67p --abi=coffabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/C672x/inc" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/PADK/dsp/inc" --define=c6727 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="myfft.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

waveforms.obj: ../waveforms.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/cl6x" -mv67p --abi=coffabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/C672x/inc" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/include" --include_path="C:/ti/ccsv6/tools/compiler/c6000_7.4.14/PADK/dsp/inc" --define=c6727 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="waveforms.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


