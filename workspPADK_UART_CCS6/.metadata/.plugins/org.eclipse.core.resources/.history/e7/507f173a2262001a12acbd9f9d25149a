################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/instalki/ti/ccsv6/tools/compiler/c6000_7.4.14

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./DaneDSP.obj" \
"./main.obj" \
"../padk.cmd" \
$(GEN_CMDS__FLAG) \
-l"rts67plus.lib" \
-lcsl_c6727_CCS6d.lib \
-lcsl_C672x_intc.lib \
-lPADK6d.lib \
-lc672xSystemPatchV2_00_00.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
UART.out \

EXE_OUTPUTS__QUOTED += \
"UART.out" \

BIN_OUTPUTS += \
UART.hex \

BIN_OUTPUTS__QUOTED += \
"UART.hex" \


# All Target
all: UART.out

# Tool invocations
UART.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"D:/instalki/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/cl6x" -mv67p --abi=coffabi -Ooff -g --define=c6727 --display_error_number --diag_suppress=16002 --diag_warning=225 --diag_wrap=off --mem_model:data=far --wchar_t=16 -z --stack_size=0x800 -m"UART.map" --heap_size=0x800 -i"D:/instalki/ti/ccsv6/tools/compiler/c6000_7.4.14/lib" -i"D:/instalki/ti/ccsv6/tools/compiler/c6000_7.4.14/C672x/lib" -i"D:/instalki/ti/ccsv6/tools/compiler/c6000_7.4.14/PADK/dsp/lib" -i"D:/instalki/ti/ccsv6/tools/compiler/c6000_7.4.14/PADK/patchdsprom" --reread_libs --warn_sections --display_error_number --diag_suppress=225 --diag_wrap=off --xml_link_info="UART_linkInfo.xml" --rom_model -o "UART.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

UART.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C6000 Hex Utility'
	"D:/instalki/ti/ccsv6/tools/compiler/c6000_7.4.14/bin/hex6x"  -o "UART.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "DaneDSP.pp" 
	-$(RM) "main.pp" 
	-$(RM) "DaneDSP.obj" "main.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

