################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/INTC/INTC.c" \

C_SRCS += \
../src/drivers/INTC/INTC.c \

OBJS_OS_FORMAT += \
./src/drivers/INTC/INTC.o \

C_DEPS_QUOTED += \
"./src/drivers/INTC/INTC.d" \

OBJS += \
./src/drivers/INTC/INTC.o \

OBJS_QUOTED += \
"./src/drivers/INTC/INTC.o" \

C_DEPS += \
./src/drivers/INTC/INTC.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/INTC/INTC.o: ../src/drivers/INTC/INTC.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/INTC/INTC.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/INTC/INTC.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


