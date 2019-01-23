################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/ADC/ADC.c" \

C_SRCS += \
../src/drivers/ADC/ADC.c \

OBJS_OS_FORMAT += \
./src/drivers/ADC/ADC.o \

C_DEPS_QUOTED += \
"./src/drivers/ADC/ADC.d" \

OBJS += \
./src/drivers/ADC/ADC.o \

OBJS_QUOTED += \
"./src/drivers/ADC/ADC.o" \

C_DEPS += \
./src/drivers/ADC/ADC.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/ADC/ADC.o: ../src/drivers/ADC/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/ADC/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/ADC/ADC.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


