################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/SWG/SWG.c" \

C_SRCS += \
../src/drivers/SWG/SWG.c \

OBJS_OS_FORMAT += \
./src/drivers/SWG/SWG.o \

C_DEPS_QUOTED += \
"./src/drivers/SWG/SWG.d" \

OBJS += \
./src/drivers/SWG/SWG.o \

OBJS_QUOTED += \
"./src/drivers/SWG/SWG.o" \

C_DEPS += \
./src/drivers/SWG/SWG.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/SWG/SWG.o: ../src/drivers/SWG/SWG.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/SWG/SWG.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/SWG/SWG.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


