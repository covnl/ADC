################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/eTimer/eTimer.c" \

C_SRCS += \
../src/drivers/eTimer/eTimer.c \

OBJS_OS_FORMAT += \
./src/drivers/eTimer/eTimer.o \

C_DEPS_QUOTED += \
"./src/drivers/eTimer/eTimer.d" \

OBJS += \
./src/drivers/eTimer/eTimer.o \

OBJS_QUOTED += \
"./src/drivers/eTimer/eTimer.o" \

C_DEPS += \
./src/drivers/eTimer/eTimer.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/eTimer/eTimer.o: ../src/drivers/eTimer/eTimer.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/eTimer/eTimer.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/eTimer/eTimer.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


