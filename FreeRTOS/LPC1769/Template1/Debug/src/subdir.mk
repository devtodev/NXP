################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc17.c \
../src/main.c 

OBJS += \
./src/cr_startup_lpc17.o \
./src/main.o 

C_DEPS += \
./src/cr_startup_lpc17.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"/home/carlos/workspace fiuba/wsRTO/CMSISv2p00_LPC17xx/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_FreeRTOS_7p0p1/demo_code" -I"/home/carlos/workspace fiuba/wsRTO/Lib_API_CAPI/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_Contenedores/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_MCU_LPC176x/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_FreeRTOS_7p0p1/FreeRTOS_include" -I"/home/carlos/workspace fiuba/wsRTO/Lib_FreeRTOS_7p0p1/FreeRTOS_portable" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


