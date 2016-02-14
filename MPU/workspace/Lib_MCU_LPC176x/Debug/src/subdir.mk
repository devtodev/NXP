################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lpc_17xx_AIN.c \
../src/lpc_17xx_GPIO.c \
../src/lpc_17xx_PERIF.c \
../src/lpc_17xx_PIN.c \
../src/lpc_17xx_PORT.c \
../src/lpc_17xx_RTC.c \
../src/lpc_17xx_SSP.c \
../src/lpc_17xx_TIMER.c \
../src/lpc_17xx_UART.c 

OBJS += \
./src/lpc_17xx_AIN.o \
./src/lpc_17xx_GPIO.o \
./src/lpc_17xx_PERIF.o \
./src/lpc_17xx_PIN.o \
./src/lpc_17xx_PORT.o \
./src/lpc_17xx_RTC.o \
./src/lpc_17xx_SSP.o \
./src/lpc_17xx_TIMER.o \
./src/lpc_17xx_UART.o 

C_DEPS += \
./src/lpc_17xx_AIN.d \
./src/lpc_17xx_GPIO.d \
./src/lpc_17xx_PERIF.d \
./src/lpc_17xx_PIN.d \
./src/lpc_17xx_PORT.d \
./src/lpc_17xx_RTC.d \
./src/lpc_17xx_SSP.d \
./src/lpc_17xx_TIMER.d \
./src/lpc_17xx_UART.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"/home/carlos/FIUBA/MPU/workspace/CMSISv2p00_LPC17xx/inc" -I"/home/carlos/FIUBA/MPU/workspace/Lib_MCU_LPC176x/inc" -I"/home/carlos/FIUBA/MPU/workspace/Lib_Contenedores/inc" -I"/home/carlos/FIUBA/MPU/workspace/Lib_MCU_LPC176x/vendor drivers/inc" -I"/home/carlos/FIUBA/MPU/workspace/Lib_API_CAPI/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


