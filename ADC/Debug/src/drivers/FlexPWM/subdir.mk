################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/FlexPWM/flexpwm.c" \

C_SRCS += \
../src/drivers/FlexPWM/flexpwm.c \

OBJS_OS_FORMAT += \
./src/drivers/FlexPWM/flexpwm.o \

C_DEPS_QUOTED += \
"./src/drivers/FlexPWM/flexpwm.d" \

OBJS += \
./src/drivers/FlexPWM/flexpwm.o \

OBJS_QUOTED += \
"./src/drivers/FlexPWM/flexpwm.o" \

C_DEPS += \
./src/drivers/FlexPWM/flexpwm.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/FlexPWM/flexpwm.o: ../src/drivers/FlexPWM/flexpwm.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FlexPWM/flexpwm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FlexPWM/flexpwm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


