################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/ucOSII/Application/app_hooks.c" \
"../src/ucOSII/Application/app_main.c" \

C_SRCS += \
../src/ucOSII/Application/app_hooks.c \
../src/ucOSII/Application/app_main.c \

OBJS += \
./src/ucOSII/Application/app_hooks.o \
./src/ucOSII/Application/app_main.o \

C_DEPS += \
./src/ucOSII/Application/app_hooks.d \
./src/ucOSII/Application/app_main.d \

OBJS_QUOTED += \
"./src/ucOSII/Application/app_hooks.o" \
"./src/ucOSII/Application/app_main.o" \

OBJS_OS_FORMAT += \
./src/ucOSII/Application/app_hooks.o \
./src/ucOSII/Application/app_main.o \

C_DEPS_QUOTED += \
"./src/ucOSII/Application/app_hooks.d" \
"./src/ucOSII/Application/app_main.d" \


# Each subdirectory must supply rules for building sources it contributes
src/ucOSII/Application/app_hooks.o: ../src/ucOSII/Application/app_hooks.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Application/app_hooks.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Application/app_hooks.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Application/app_main.o: ../src/ucOSII/Application/app_main.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Application/app_main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Application/app_main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


