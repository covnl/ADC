################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/LLD_INIT/MPC5744P_LLD.c" \

C_SRCS += \
../src/drivers/LLD_INIT/MPC5744P_LLD.c \

OBJS_OS_FORMAT += \
./src/drivers/LLD_INIT/MPC5744P_LLD.o \

C_DEPS_QUOTED += \
"./src/drivers/LLD_INIT/MPC5744P_LLD.d" \

OBJS += \
./src/drivers/LLD_INIT/MPC5744P_LLD.o \

OBJS_QUOTED += \
"./src/drivers/LLD_INIT/MPC5744P_LLD.o" \

C_DEPS += \
./src/drivers/LLD_INIT/MPC5744P_LLD.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/LLD_INIT/MPC5744P_LLD.o: ../src/drivers/LLD_INIT/MPC5744P_LLD.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/LLD_INIT/MPC5744P_LLD.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/LLD_INIT/MPC5744P_LLD.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


