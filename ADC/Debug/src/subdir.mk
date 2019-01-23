################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS_QUOTED += \
"../src/intc_sw_handlers.S" \

C_SRCS_QUOTED += \
"../src/ADC-demo.c" \
"../src/MPC57xx__Interrupt_Init.c" \
"../src/Vector.c" \
"../src/flashrchw.c" \
"../src/intc_SW_mode_isr_vectors_MPC5744P.c" \

S_UPPER_SRCS += \
../src/intc_sw_handlers.S \

C_SRCS += \
../src/ADC-demo.c \
../src/MPC57xx__Interrupt_Init.c \
../src/Vector.c \
../src/flashrchw.c \
../src/intc_SW_mode_isr_vectors_MPC5744P.c \

OBJS_OS_FORMAT += \
./src/ADC-demo.o \
./src/MPC57xx__Interrupt_Init.o \
./src/Vector.o \
./src/flashrchw.o \
./src/intc_SW_mode_isr_vectors_MPC5744P.o \
./src/intc_sw_handlers.o \

C_DEPS_QUOTED += \
"./src/ADC-demo.d" \
"./src/MPC57xx__Interrupt_Init.d" \
"./src/Vector.d" \
"./src/flashrchw.d" \
"./src/intc_SW_mode_isr_vectors_MPC5744P.d" \

OBJS += \
./src/ADC-demo.o \
./src/MPC57xx__Interrupt_Init.o \
./src/Vector.o \
./src/flashrchw.o \
./src/intc_SW_mode_isr_vectors_MPC5744P.o \
./src/intc_sw_handlers.o \

OBJS_QUOTED += \
"./src/ADC-demo.o" \
"./src/MPC57xx__Interrupt_Init.o" \
"./src/Vector.o" \
"./src/flashrchw.o" \
"./src/intc_SW_mode_isr_vectors_MPC5744P.o" \
"./src/intc_sw_handlers.o" \

C_DEPS += \
./src/ADC-demo.d \
./src/MPC57xx__Interrupt_Init.d \
./src/Vector.d \
./src/flashrchw.d \
./src/intc_SW_mode_isr_vectors_MPC5744P.d \


# Each subdirectory must supply rules for building sources it contributes
src/ADC-demo.o: ../src/ADC-demo.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/ADC-demo.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/ADC-demo.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/MPC57xx__Interrupt_Init.o: ../src/MPC57xx__Interrupt_Init.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/MPC57xx__Interrupt_Init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/MPC57xx__Interrupt_Init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Vector.o: ../src/Vector.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/Vector.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/Vector.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/flashrchw.o: ../src/flashrchw.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/flashrchw.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/flashrchw.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/intc_SW_mode_isr_vectors_MPC5744P.o: ../src/intc_SW_mode_isr_vectors_MPC5744P.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/intc_SW_mode_isr_vectors_MPC5744P.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/intc_SW_mode_isr_vectors_MPC5744P.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/intc_sw_handlers.o: ../src/intc_sw_handlers.S
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	powerpc-eabivle-gcc "@src/intc_sw_handlers.args" -c -o "src/intc_sw_handlers.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


