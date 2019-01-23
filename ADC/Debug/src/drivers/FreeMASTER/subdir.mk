################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/FreeMASTER/freemaster_MPC56xx.c" \
"../src/drivers/FreeMASTER/freemaster_appcmd.c" \
"../src/drivers/FreeMASTER/freemaster_bdm.c" \
"../src/drivers/FreeMASTER/freemaster_can.c" \
"../src/drivers/FreeMASTER/freemaster_protocol.c" \
"../src/drivers/FreeMASTER/freemaster_rec.c" \
"../src/drivers/FreeMASTER/freemaster_scope.c" \
"../src/drivers/FreeMASTER/freemaster_serial.c" \
"../src/drivers/FreeMASTER/freemaster_sfio.c" \
"../src/drivers/FreeMASTER/freemaster_tsa.c" \

C_SRCS += \
../src/drivers/FreeMASTER/freemaster_MPC56xx.c \
../src/drivers/FreeMASTER/freemaster_appcmd.c \
../src/drivers/FreeMASTER/freemaster_bdm.c \
../src/drivers/FreeMASTER/freemaster_can.c \
../src/drivers/FreeMASTER/freemaster_protocol.c \
../src/drivers/FreeMASTER/freemaster_rec.c \
../src/drivers/FreeMASTER/freemaster_scope.c \
../src/drivers/FreeMASTER/freemaster_serial.c \
../src/drivers/FreeMASTER/freemaster_sfio.c \
../src/drivers/FreeMASTER/freemaster_tsa.c \

OBJS_OS_FORMAT += \
./src/drivers/FreeMASTER/freemaster_MPC56xx.o \
./src/drivers/FreeMASTER/freemaster_appcmd.o \
./src/drivers/FreeMASTER/freemaster_bdm.o \
./src/drivers/FreeMASTER/freemaster_can.o \
./src/drivers/FreeMASTER/freemaster_protocol.o \
./src/drivers/FreeMASTER/freemaster_rec.o \
./src/drivers/FreeMASTER/freemaster_scope.o \
./src/drivers/FreeMASTER/freemaster_serial.o \
./src/drivers/FreeMASTER/freemaster_sfio.o \
./src/drivers/FreeMASTER/freemaster_tsa.o \

C_DEPS_QUOTED += \
"./src/drivers/FreeMASTER/freemaster_MPC56xx.d" \
"./src/drivers/FreeMASTER/freemaster_appcmd.d" \
"./src/drivers/FreeMASTER/freemaster_bdm.d" \
"./src/drivers/FreeMASTER/freemaster_can.d" \
"./src/drivers/FreeMASTER/freemaster_protocol.d" \
"./src/drivers/FreeMASTER/freemaster_rec.d" \
"./src/drivers/FreeMASTER/freemaster_scope.d" \
"./src/drivers/FreeMASTER/freemaster_serial.d" \
"./src/drivers/FreeMASTER/freemaster_sfio.d" \
"./src/drivers/FreeMASTER/freemaster_tsa.d" \

OBJS += \
./src/drivers/FreeMASTER/freemaster_MPC56xx.o \
./src/drivers/FreeMASTER/freemaster_appcmd.o \
./src/drivers/FreeMASTER/freemaster_bdm.o \
./src/drivers/FreeMASTER/freemaster_can.o \
./src/drivers/FreeMASTER/freemaster_protocol.o \
./src/drivers/FreeMASTER/freemaster_rec.o \
./src/drivers/FreeMASTER/freemaster_scope.o \
./src/drivers/FreeMASTER/freemaster_serial.o \
./src/drivers/FreeMASTER/freemaster_sfio.o \
./src/drivers/FreeMASTER/freemaster_tsa.o \

OBJS_QUOTED += \
"./src/drivers/FreeMASTER/freemaster_MPC56xx.o" \
"./src/drivers/FreeMASTER/freemaster_appcmd.o" \
"./src/drivers/FreeMASTER/freemaster_bdm.o" \
"./src/drivers/FreeMASTER/freemaster_can.o" \
"./src/drivers/FreeMASTER/freemaster_protocol.o" \
"./src/drivers/FreeMASTER/freemaster_rec.o" \
"./src/drivers/FreeMASTER/freemaster_scope.o" \
"./src/drivers/FreeMASTER/freemaster_serial.o" \
"./src/drivers/FreeMASTER/freemaster_sfio.o" \
"./src/drivers/FreeMASTER/freemaster_tsa.o" \

C_DEPS += \
./src/drivers/FreeMASTER/freemaster_MPC56xx.d \
./src/drivers/FreeMASTER/freemaster_appcmd.d \
./src/drivers/FreeMASTER/freemaster_bdm.d \
./src/drivers/FreeMASTER/freemaster_can.d \
./src/drivers/FreeMASTER/freemaster_protocol.d \
./src/drivers/FreeMASTER/freemaster_rec.d \
./src/drivers/FreeMASTER/freemaster_scope.d \
./src/drivers/FreeMASTER/freemaster_serial.d \
./src/drivers/FreeMASTER/freemaster_sfio.d \
./src/drivers/FreeMASTER/freemaster_tsa.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/FreeMASTER/freemaster_MPC56xx.o: ../src/drivers/FreeMASTER/freemaster_MPC56xx.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_MPC56xx.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_MPC56xx.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/FreeMASTER/freemaster_appcmd.o: ../src/drivers/FreeMASTER/freemaster_appcmd.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_appcmd.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_appcmd.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/FreeMASTER/freemaster_bdm.o: ../src/drivers/FreeMASTER/freemaster_bdm.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_bdm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_bdm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/FreeMASTER/freemaster_can.o: ../src/drivers/FreeMASTER/freemaster_can.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_can.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_can.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/FreeMASTER/freemaster_protocol.o: ../src/drivers/FreeMASTER/freemaster_protocol.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_protocol.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_protocol.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/FreeMASTER/freemaster_rec.o: ../src/drivers/FreeMASTER/freemaster_rec.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_rec.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_rec.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/FreeMASTER/freemaster_scope.o: ../src/drivers/FreeMASTER/freemaster_scope.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_scope.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_scope.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/FreeMASTER/freemaster_serial.o: ../src/drivers/FreeMASTER/freemaster_serial.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_serial.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_serial.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/FreeMASTER/freemaster_sfio.o: ../src/drivers/FreeMASTER/freemaster_sfio.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_sfio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_sfio.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/FreeMASTER/freemaster_tsa.o: ../src/drivers/FreeMASTER/freemaster_tsa.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/FreeMASTER/freemaster_tsa.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/FreeMASTER/freemaster_tsa.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


