################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/ucOSII/Source/os_core.c" \
"../src/ucOSII/Source/os_flag.c" \
"../src/ucOSII/Source/os_mbox.c" \
"../src/ucOSII/Source/os_mem.c" \
"../src/ucOSII/Source/os_mutex.c" \
"../src/ucOSII/Source/os_q.c" \
"../src/ucOSII/Source/os_sem.c" \
"../src/ucOSII/Source/os_task.c" \
"../src/ucOSII/Source/os_time.c" \
"../src/ucOSII/Source/os_tmr.c" \

C_SRCS += \
../src/ucOSII/Source/os_core.c \
../src/ucOSII/Source/os_flag.c \
../src/ucOSII/Source/os_mbox.c \
../src/ucOSII/Source/os_mem.c \
../src/ucOSII/Source/os_mutex.c \
../src/ucOSII/Source/os_q.c \
../src/ucOSII/Source/os_sem.c \
../src/ucOSII/Source/os_task.c \
../src/ucOSII/Source/os_time.c \
../src/ucOSII/Source/os_tmr.c \

OBJS += \
./src/ucOSII/Source/os_core.o \
./src/ucOSII/Source/os_flag.o \
./src/ucOSII/Source/os_mbox.o \
./src/ucOSII/Source/os_mem.o \
./src/ucOSII/Source/os_mutex.o \
./src/ucOSII/Source/os_q.o \
./src/ucOSII/Source/os_sem.o \
./src/ucOSII/Source/os_task.o \
./src/ucOSII/Source/os_time.o \
./src/ucOSII/Source/os_tmr.o \

C_DEPS += \
./src/ucOSII/Source/os_core.d \
./src/ucOSII/Source/os_flag.d \
./src/ucOSII/Source/os_mbox.d \
./src/ucOSII/Source/os_mem.d \
./src/ucOSII/Source/os_mutex.d \
./src/ucOSII/Source/os_q.d \
./src/ucOSII/Source/os_sem.d \
./src/ucOSII/Source/os_task.d \
./src/ucOSII/Source/os_time.d \
./src/ucOSII/Source/os_tmr.d \

OBJS_QUOTED += \
"./src/ucOSII/Source/os_core.o" \
"./src/ucOSII/Source/os_flag.o" \
"./src/ucOSII/Source/os_mbox.o" \
"./src/ucOSII/Source/os_mem.o" \
"./src/ucOSII/Source/os_mutex.o" \
"./src/ucOSII/Source/os_q.o" \
"./src/ucOSII/Source/os_sem.o" \
"./src/ucOSII/Source/os_task.o" \
"./src/ucOSII/Source/os_time.o" \
"./src/ucOSII/Source/os_tmr.o" \

OBJS_OS_FORMAT += \
./src/ucOSII/Source/os_core.o \
./src/ucOSII/Source/os_flag.o \
./src/ucOSII/Source/os_mbox.o \
./src/ucOSII/Source/os_mem.o \
./src/ucOSII/Source/os_mutex.o \
./src/ucOSII/Source/os_q.o \
./src/ucOSII/Source/os_sem.o \
./src/ucOSII/Source/os_task.o \
./src/ucOSII/Source/os_time.o \
./src/ucOSII/Source/os_tmr.o \

C_DEPS_QUOTED += \
"./src/ucOSII/Source/os_core.d" \
"./src/ucOSII/Source/os_flag.d" \
"./src/ucOSII/Source/os_mbox.d" \
"./src/ucOSII/Source/os_mem.d" \
"./src/ucOSII/Source/os_mutex.d" \
"./src/ucOSII/Source/os_q.d" \
"./src/ucOSII/Source/os_sem.d" \
"./src/ucOSII/Source/os_task.d" \
"./src/ucOSII/Source/os_time.d" \
"./src/ucOSII/Source/os_tmr.d" \


# Each subdirectory must supply rules for building sources it contributes
src/ucOSII/Source/os_core.o: ../src/ucOSII/Source/os_core.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_core.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_core.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Source/os_flag.o: ../src/ucOSII/Source/os_flag.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_flag.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_flag.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Source/os_mbox.o: ../src/ucOSII/Source/os_mbox.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_mbox.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_mbox.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Source/os_mem.o: ../src/ucOSII/Source/os_mem.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_mem.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_mem.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Source/os_mutex.o: ../src/ucOSII/Source/os_mutex.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_mutex.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_mutex.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Source/os_q.o: ../src/ucOSII/Source/os_q.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_q.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_q.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Source/os_sem.o: ../src/ucOSII/Source/os_sem.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_sem.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_sem.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Source/os_task.o: ../src/ucOSII/Source/os_task.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_task.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_task.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Source/os_time.o: ../src/ucOSII/Source/os_time.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_time.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_time.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ucOSII/Source/os_tmr.o: ../src/ucOSII/Source/os_tmr.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ucOSII/Source/os_tmr.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ucOSII/Source/os_tmr.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


