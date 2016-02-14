################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../aciones.c \
../cr_startup_lpc17.c \
../globales.c \
../main.c 

OBJS += \
./aciones.o \
./cr_startup_lpc17.o \
./globales.o \
./main.o 

C_DEPS += \
./aciones.d \
./cr_startup_lpc17.d \
./globales.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"/home/carlos/workspace RTOS TP/tp_rtos_2014/CMSIS/CMSISv2p00_LPC17xx/inc" -I"/home/carlos/workspace RTOS TP/tp_rtos_2014/CAPI/Lib_Contenedores/inc" -I"/home/carlos/workspace RTOS TP/tp_rtos_2014/CAPI/Lib_API_CAPI/inc" -I"/home/carlos/workspace RTOS TP/tp_rtos_2014/CAPI/Lib_MCU_LPC176x/inc" -I"/home/carlos/workspace RTOS TP/tp_rtos_2014/FreeRTOS/Lib_FreeRTOS_7p0p1/FreeRTOS_include" -I"/home/carlos/workspace RTOS TP/tp_rtos_2014/FreeRTOS/Lib_FreeRTOS_7p0p1/FreeRTOS_portable" -I"/home/carlos/workspace RTOS TP/tp_rtos_2014/Librerias/Lib_EaBaseBoard/inc" -I"/home/carlos/workspace RTOS TP/tp_rtos_2014/ControlBici" -I"/home/carlos/workspace RTOS TP/tp_rtos_2014/ControlBici/Framework" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


