################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/SIUL/SIUL.c" \

C_SRCS += \
../src/drivers/SIUL/SIUL.c \

OBJS_OS_FORMAT += \
./src/drivers/SIUL/SIUL.o \

C_DEPS_QUOTED += \
"./src/drivers/SIUL/SIUL.d" \

OBJS += \
./src/drivers/SIUL/SIUL.o \

OBJS_QUOTED += \
"./src/drivers/SIUL/SIUL.o" \

C_DEPS += \
./src/drivers/SIUL/SIUL.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/SIUL/SIUL.o: ../src/drivers/SIUL/SIUL.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/SIUL/SIUL.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/SIUL/SIUL.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


