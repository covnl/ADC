################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/ucOSII/uC_LIB/lib_ascii.c" \
"../src/ucOSII/uC_LIB/lib_math.c" \
"../src/ucOSII/uC_LIB/lib_mem.c" \
"../src/ucOSII/uC_LIB/lib_str.c" \

C_SRCS += \
../src/ucOSII/uC_LIB/lib_ascii.c \
../src/ucOSII/uC_LIB/lib_math.c \
../src/ucOSII/uC_LIB/lib_mem.c \
../src/ucOSII/uC_LIB/lib_str.c \

OBJS += \
./src/ucOSII/uC_LIB/lib_ascii.o \
./src/ucOSII/uC_LIB/lib_math.o \
./src/ucOSII/uC_LIB/lib_mem.o \
./src/ucOSII/uC_LIB/lib_str.o \

C_DEPS += \
./src/ucOSII/uC_LIB/lib_ascii.d \
./src/ucOSII/uC_LIB/lib_math.d \
./src/ucOSII/uC_LIB/lib_mem.d \
./src/ucOSII/uC_LIB/lib_str.d \

OBJS_QUOTED += \
"./src/ucOSII/uC_LIB/lib_ascii.o" \
"./src/ucOSII/uC_LIB/lib_math.o" \
"./src/ucOSII/uC_LIB/lib_mem.o" \
"./src/ucOSII/uC_LIB/lib_str.o" \

OBJS_OS_FORMAT += \
./src/ucOSII/uC_LIB/lib_ascii.o \
./src/ucOSII/uC_LIB/lib_math.o \
./src/ucOSII/uC_LIB/lib_mem.o \
./src/ucOSII/uC_LIB/lib_str.o \

C_DEPS_QUOTED += \
"./src/ucOSII/uC_LIB/lib_ascii.d" \
"./src/ucOSII/uC_LIB/lib_math.d" \
"./src/ucOSII/uC_LIB/lib_mem.d" \
"./src/ucOSII/uC_LIB/lib_str.d" \


# Each subdirectory must supply rules for building sources it contributes
src/ucOSII/uC_LIB/lib_ascii.o: ../src/ucOSII/uC_LIB/lib_ascii.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/uC_LIB/lib_ascii.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/uC_LIB/lib_ascii.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/uC_LIB/lib_math.o: ../src/ucOSII/uC_LIB/lib_math.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/uC_LIB/lib_math.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/uC_LIB/lib_math.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/uC_LIB/lib_mem.o: ../src/ucOSII/uC_LIB/lib_mem.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/uC_LIB/lib_mem.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/uC_LIB/lib_mem.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/uC_LIB/lib_str.o: ../src/ucOSII/uC_LIB/lib_str.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/uC_LIB/lib_str.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/uC_LIB/lib_str.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


