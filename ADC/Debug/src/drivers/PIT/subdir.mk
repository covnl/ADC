################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/PIT/PIT.c" \
"../src/drivers/PIT/PIT_IRQ.c" \

C_SRCS += \
../src/drivers/PIT/PIT.c \
../src/drivers/PIT/PIT_IRQ.c \

OBJS_OS_FORMAT += \
./src/drivers/PIT/PIT.o \
./src/drivers/PIT/PIT_IRQ.o \

C_DEPS_QUOTED += \
"./src/drivers/PIT/PIT.d" \
"./src/drivers/PIT/PIT_IRQ.d" \

OBJS += \
./src/drivers/PIT/PIT.o \
./src/drivers/PIT/PIT_IRQ.o \

OBJS_QUOTED += \
"./src/drivers/PIT/PIT.o" \
"./src/drivers/PIT/PIT_IRQ.o" \

C_DEPS += \
./src/drivers/PIT/PIT.d \
./src/drivers/PIT/PIT_IRQ.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/PIT/PIT.o: ../src/drivers/PIT/PIT.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/PIT/PIT.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/PIT/PIT.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/PIT/PIT_IRQ.o: ../src/drivers/PIT/PIT_IRQ.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/PIT/PIT_IRQ.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/PIT/PIT_IRQ.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


