################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/MPC5744P_LLD.c" \

C_SRCS += \
../src/drivers/MPC5744P_LLD.c \

OBJS += \
./src/drivers/MPC5744P_LLD.o \

C_DEPS += \
./src/drivers/MPC5744P_LLD.d \

OBJS_QUOTED += \
"./src/drivers/MPC5744P_LLD.o" \

OBJS_OS_FORMAT += \
./src/drivers/MPC5744P_LLD.o \

C_DEPS_QUOTED += \
"./src/drivers/MPC5744P_LLD.d" \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/MPC5744P_LLD.o: ../src/drivers/MPC5744P_LLD.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/MPC5744P_LLD.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/drivers/MPC5744P_LLD.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


