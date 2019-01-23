################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/UART/uart.c" \
"../src/drivers/UART/uart_console_io.c" \
"../src/drivers/UART/uart_init.c" \
"../src/drivers/UART/uart_irq.c" \

C_SRCS += \
../src/drivers/UART/uart.c \
../src/drivers/UART/uart_console_io.c \
../src/drivers/UART/uart_init.c \
../src/drivers/UART/uart_irq.c \

OBJS_OS_FORMAT += \
./src/drivers/UART/uart.o \
./src/drivers/UART/uart_console_io.o \
./src/drivers/UART/uart_init.o \
./src/drivers/UART/uart_irq.o \

C_DEPS_QUOTED += \
"./src/drivers/UART/uart.d" \
"./src/drivers/UART/uart_console_io.d" \
"./src/drivers/UART/uart_init.d" \
"./src/drivers/UART/uart_irq.d" \

OBJS += \
./src/drivers/UART/uart.o \
./src/drivers/UART/uart_console_io.o \
./src/drivers/UART/uart_init.o \
./src/drivers/UART/uart_irq.o \

OBJS_QUOTED += \
"./src/drivers/UART/uart.o" \
"./src/drivers/UART/uart_console_io.o" \
"./src/drivers/UART/uart_init.o" \
"./src/drivers/UART/uart_irq.o" \

C_DEPS += \
./src/drivers/UART/uart.d \
./src/drivers/UART/uart_console_io.d \
./src/drivers/UART/uart_init.d \
./src/drivers/UART/uart_irq.d \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/UART/uart.o: ../src/drivers/UART/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/UART/uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/UART/uart.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/UART/uart_console_io.o: ../src/drivers/UART/uart_console_io.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/UART/uart_console_io.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/UART/uart_console_io.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/UART/uart_init.o: ../src/drivers/UART/uart_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/UART/uart_init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/UART/uart_init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/UART/uart_irq.o: ../src/drivers/UART/uart_irq.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/drivers/UART/uart_irq.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "src/drivers/UART/uart_irq.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


