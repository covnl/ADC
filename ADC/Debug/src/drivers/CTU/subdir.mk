################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/CTU/CTU.c" \

C_SRCS += \
../src/drivers/CTU/CTU.c \

OBJS_OS_FORMAT += \
./src/drivers/CTU/CTU.o \

C_DEPS_QUOTED += \
"./src/drivers/CTU/CTU.d" \

OBJS += \
./src/drivers/CTU/CTU.o \

OBJS_QUOTED += \
"./src/drivers/CTU/CTU.o" \

C_DEPS += \
./src/drivers/CTU/CTU.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/CTU/CTU.o: ../src/drivers/CTU/CTU.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/CTU/CTU.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/CTU/CTU.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


