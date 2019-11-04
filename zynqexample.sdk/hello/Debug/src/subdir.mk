################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/main.c \
../src/memtest_controller.c \
../src/menu_controller.c \
../src/platform.c \
../src/uart_controller.c 

OBJS += \
./src/main.o \
./src/memtest_controller.o \
./src/menu_controller.o \
./src/platform.o \
./src/uart_controller.o 

C_DEPS += \
./src/main.d \
./src/memtest_controller.d \
./src/menu_controller.d \
./src/platform.d \
./src/uart_controller.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../standalone_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

