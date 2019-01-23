################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/ucOSII/Ports/CPU/cpu_core.c" \

C_SRCS += \
../src/ucOSII/Ports/CPU/cpu_core.c \

S_SRCS += \
../src/ucOSII/Ports/CPU/cpu_a.s \

S_SRCS_QUOTED += \
"../src/ucOSII/Ports/CPU/cpu_a.s" \

OBJS += \
./src/ucOSII/Ports/CPU/cpu_a.o \
./src/ucOSII/Ports/CPU/cpu_core.o \

C_DEPS += \
./src/ucOSII/Ports/CPU/cpu_core.d \

OBJS_QUOTED += \
"./src/ucOSII/Ports/CPU/cpu_a.o" \
"./src/ucOSII/Ports/CPU/cpu_core.o" \

OBJS_OS_FORMAT += \
./src/ucOSII/Ports/CPU/cpu_a.o \
./src/ucOSII/Ports/CPU/cpu_core.o \

C_DEPS_QUOTED += \
"./src/ucOSII/Ports/CPU/cpu_core.d" \


# Each subdirectory must supply rules for building sources it contributes
src/ucOSII/Ports/CPU/cpu_a.o: ../src/ucOSII/Ports/CPU/cpu_a.s
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	powerpc-eabivle-gcc "@src/ucOSII/Ports/CPU/cpu_a.args" -c -o "src/ucOSII/Ports/CPU/cpu_a.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Ports/CPU/cpu_core.o: ../src/ucOSII/Ports/CPU/cpu_core.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Ports/CPU/cpu_core.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Ports/CPU/cpu_core.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


