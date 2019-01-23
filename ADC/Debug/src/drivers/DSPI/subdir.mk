################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/DSPI/DSPI.c" \

C_SRCS += \
../src/drivers/DSPI/DSPI.c \

OBJS_OS_FORMAT += \
./src/drivers/DSPI/DSPI.o \

C_DEPS_QUOTED += \
"./src/drivers/DSPI/DSPI.d" \

OBJS += \
./src/drivers/DSPI/DSPI.o \

OBJS_QUOTED += \
"./src/drivers/DSPI/DSPI.o" \

C_DEPS += \
./src/drivers/DSPI/DSPI.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/DSPI/DSPI.o: ../src/drivers/DSPI/DSPI.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/DSPI/DSPI.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/DSPI/DSPI.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


