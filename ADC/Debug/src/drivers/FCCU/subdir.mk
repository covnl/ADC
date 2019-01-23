################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/FCCU/FCCU.c" \

C_SRCS += \
../src/drivers/FCCU/FCCU.c \

OBJS_OS_FORMAT += \
./src/drivers/FCCU/FCCU.o \

C_DEPS_QUOTED += \
"./src/drivers/FCCU/FCCU.d" \

OBJS += \
./src/drivers/FCCU/FCCU.o \

OBJS_QUOTED += \
"./src/drivers/FCCU/FCCU.o" \

C_DEPS += \
./src/drivers/FCCU/FCCU.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/FCCU/FCCU.o: ../src/drivers/FCCU/FCCU.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FCCU/FCCU.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FCCU/FCCU.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


