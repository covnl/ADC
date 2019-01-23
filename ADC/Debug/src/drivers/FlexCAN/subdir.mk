################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/FlexCAN/CAN.c" \

C_SRCS += \
../src/drivers/FlexCAN/CAN.c \

OBJS_OS_FORMAT += \
./src/drivers/FlexCAN/CAN.o \

C_DEPS_QUOTED += \
"./src/drivers/FlexCAN/CAN.d" \

OBJS += \
./src/drivers/FlexCAN/CAN.o \

OBJS_QUOTED += \
"./src/drivers/FlexCAN/CAN.o" \

C_DEPS += \
./src/drivers/FlexCAN/CAN.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/FlexCAN/CAN.o: ../src/drivers/FlexCAN/CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FlexCAN/CAN.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FlexCAN/CAN.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


