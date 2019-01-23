################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 36
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include src/subdir.mk
-include src/drivers/ADC/subdir.mk
-include src/drivers/CTU/subdir.mk
-include src/drivers/DSPI/subdir.mk
-include src/drivers/FCCU/subdir.mk
-include src/drivers/FlexCAN/subdir.mk
-include src/drivers/FlexPWM/subdir.mk
-include src/drivers/FreeMASTER/subdir.mk
-include src/drivers/INTC/subdir.mk
-include src/drivers/LINFlex/subdir.mk
-include src/drivers/LLD_INIT/subdir.mk
-include src/drivers/ME/subdir.mk
-include src/drivers/PIT/subdir.mk
-include src/drivers/SIUL/subdir.mk
-include src/drivers/SWG/subdir.mk
-include src/drivers/UART/subdir.mk
-include src/drivers/eTimer/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MPC5744P.elf \

EXECUTABLES_QUOTED += \
"MPC5744P.elf" \

EXECUTABLES_OS_FORMAT += \
MPC5744P.elf \


# All Target
all: warning-messages explicit-dependencies MPC5744P.elf secondary-outputs

# Tool invocations
MPC5744P.elf: $(OBJS) C:/Users/ZHL/Desktop/MPC5744P/MPC5744P-drivers-17.3.26/ADC/Project_Settings/Linker_Files/mem.ld C:/Users/ZHL/Desktop/MPC5744P/MPC5744P-drivers-17.3.26/ADC/Project_Settings/Linker_Files/sections.ld C:/Users/ZHL/Desktop/MPC5744P/MPC5744P-drivers-17.3.26/ADC/Project_Settings/Linker_Files/libs.ld $(OSPT) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #37 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	powerpc-eabivle-gcc -o "MPC5744P.elf" "@MPC5744P.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) $(OSPT)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*/*/*.d ./*/*.d  ./*/*/*/*.o ./*/*.o ./*/*/*.o  $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

