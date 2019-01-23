################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/LINFlex/LINFLEX.c" \

C_SRCS += \
../src/drivers/LINFlex/LINFLEX.c \

OBJS_OS_FORMAT += \
./src/drivers/LINFlex/LINFLEX.o \

C_DEPS_QUOTED += \
"./src/drivers/LINFlex/LINFLEX.d" \

OBJS += \
./src/drivers/LINFlex/LINFLEX.o \

OBJS_QUOTED += \
"./src/drivers/LINFlex/LINFLEX.o" \

C_DEPS += \
./src/drivers/LINFlex/LINFLEX.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/LINFlex/LINFLEX.o: ../src/drivers/LINFlex/LINFLEX.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/LINFlex/LINFLEX.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/LINFlex/LINFLEX.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


