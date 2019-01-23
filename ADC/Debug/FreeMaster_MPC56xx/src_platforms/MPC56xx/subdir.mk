################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"C:/Freescale/S32_Power_v1.1/S32DS/FreeMASTER_Serial_Communication_Driver_V1_9/src_platforms/MPC56xx/freemaster_MPC56xx.c" \

C_SRCS += \
C:/Freescale/S32_Power_v1.1/S32DS/FreeMASTER_Serial_Communication_Driver_V1_9/src_platforms/MPC56xx/freemaster_MPC56xx.c \

OBJS += \
./FreeMaster_MPC56xx/src_platforms/MPC56xx/freemaster_MPC56xx.o \

C_DEPS += \
./FreeMaster_MPC56xx/src_platforms/MPC56xx/freemaster_MPC56xx.d \

OBJS_QUOTED += \
"./FreeMaster_MPC56xx/src_platforms/MPC56xx/freemaster_MPC56xx.o" \

OBJS_OS_FORMAT += \
./FreeMaster_MPC56xx/src_platforms/MPC56xx/freemaster_MPC56xx.o \

C_DEPS_QUOTED += \
"./FreeMaster_MPC56xx/src_platforms/MPC56xx/freemaster_MPC56xx.d" \


# Each subdirectory must supply rules for building sources it contributes
FreeMaster_MPC56xx/src_platforms/MPC56xx/freemaster_MPC56xx.o: C:/Freescale/S32_Power_v1.1/S32DS/FreeMASTER_Serial_Communication_Driver_V1_9/src_platforms/MPC56xx/freemaster_MPC56xx.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@FreeMaster_MPC56xx/src_platforms/MPC56xx/freemaster_MPC56xx.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "FreeMaster_MPC56xx/src_platforms/MPC56xx/freemaster_MPC56xx.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


