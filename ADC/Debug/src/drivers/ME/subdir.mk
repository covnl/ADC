################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/ME/ME.c" \

C_SRCS += \
../src/drivers/ME/ME.c \

OBJS_OS_FORMAT += \
./src/drivers/ME/ME.o \

C_DEPS_QUOTED += \
"./src/drivers/ME/ME.d" \

OBJS += \
./src/drivers/ME/ME.o \

OBJS_QUOTED += \
"./src/drivers/ME/ME.o" \

C_DEPS += \
./src/drivers/ME/ME.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/ME/ME.o: ../src/drivers/ME/ME.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/ME/ME.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/ME/ME.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


