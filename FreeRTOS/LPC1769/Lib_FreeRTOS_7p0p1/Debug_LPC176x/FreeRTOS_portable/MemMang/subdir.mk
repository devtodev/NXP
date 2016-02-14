################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS_portable/MemMang/heap_2.c 

OBJS += \
./FreeRTOS_portable/MemMang/heap_2.o 

C_DEPS += \
./FreeRTOS_portable/MemMang/heap_2.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_portable/MemMang/%.o: ../FreeRTOS_portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DLIB_MCU_LPC134x=134 -DLIB_MCU_LPC176x=176 -D__TARGET_PORT=LIB_MCU_LPC176x -I"/home/carlos/workspace fiuba/wsRTO/CMSISv2p00_LPC17xx/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_FreeRTOS_7p0p1/FreeRTOS_portable" -I"/home/carlos/workspace fiuba/wsRTO/Lib_FreeRTOS_7p0p1/FreeRTOS_include" -I"/home/carlos/workspace fiuba/wsRTO/Lib_API_CAPI/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_MCU_LPC176x/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_Contenedores/inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -I"/home/carlos/workspace fiuba/wsRTO/CMSISv2p00_LPC17xx/inc"  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


