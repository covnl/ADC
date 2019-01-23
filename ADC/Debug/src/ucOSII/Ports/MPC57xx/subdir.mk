################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/ucOSII/Ports/MPC57xx/os_cpu_c.c" \
"../src/ucOSII/Ports/MPC57xx/os_dbg.c" \

C_SRCS += \
../src/ucOSII/Ports/MPC57xx/os_cpu_c.c \
../src/ucOSII/Ports/MPC57xx/os_dbg.c \

S_SRCS += \
../src/ucOSII/Ports/MPC57xx/os_cpu_a.s \

S_SRCS_QUOTED += \
"../src/ucOSII/Ports/MPC57xx/os_cpu_a.s" \

OBJS += \
./src/ucOSII/Ports/MPC57xx/os_cpu_a.o \
./src/ucOSII/Ports/MPC57xx/os_cpu_c.o \
./src/ucOSII/Ports/MPC57xx/os_dbg.o \

C_DEPS += \
./src/ucOSII/Ports/MPC57xx/os_cpu_c.d \
./src/ucOSII/Ports/MPC57xx/os_dbg.d \

OBJS_QUOTED += \
"./src/ucOSII/Ports/MPC57xx/os_cpu_a.o" \
"./src/ucOSII/Ports/MPC57xx/os_cpu_c.o" \
"./src/ucOSII/Ports/MPC57xx/os_dbg.o" \

OBJS_OS_FORMAT += \
./src/ucOSII/Ports/MPC57xx/os_cpu_a.o \
./src/ucOSII/Ports/MPC57xx/os_cpu_c.o \
./src/ucOSII/Ports/MPC57xx/os_dbg.o \

C_DEPS_QUOTED += \
"./src/ucOSII/Ports/MPC57xx/os_cpu_c.d" \
"./src/ucOSII/Ports/MPC57xx/os_dbg.d" \


# Each subdirectory must supply rules for building sources it contributes
src/ucOSII/Ports/MPC57xx/os_cpu_a.o: ../src/ucOSII/Ports/MPC57xx/os_cpu_a.s
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	powerpc-eabivle-gcc "@src/ucOSII/Ports/MPC57xx/os_cpu_a.args" -c -o "src/ucOSII/Ports/MPC57xx/os_cpu_a.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Ports/MPC57xx/os_cpu_c.o: ../src/ucOSII/Ports/MPC57xx/os_cpu_c.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Ports/MPC57xx/os_cpu_c.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Ports/MPC57xx/os_cpu_c.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Ports/MPC57xx/os_dbg.o: ../src/ucOSII/Ports/MPC57xx/os_dbg.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Ports/MPC57xx/os_dbg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Ports/MPC57xx/os_dbg.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


