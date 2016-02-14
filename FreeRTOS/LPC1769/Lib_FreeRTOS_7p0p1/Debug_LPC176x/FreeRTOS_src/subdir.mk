################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS_src/list.c \
../FreeRTOS_src/queue.c \
../FreeRTOS_src/tasks.c \
../FreeRTOS_src/timers.c \
../FreeRTOS_src/trace.c 

OBJS += \
./FreeRTOS_src/list.o \
./FreeRTOS_src/queue.o \
./FreeRTOS_src/tasks.o \
./FreeRTOS_src/timers.o \
./FreeRTOS_src/trace.o 

C_DEPS += \
./FreeRTOS_src/list.d \
./FreeRTOS_src/queue.d \
./FreeRTOS_src/tasks.d \
./FreeRTOS_src/timers.d \
./FreeRTOS_src/trace.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_src/%.o: ../FreeRTOS_src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DLIB_MCU_LPC134x=134 -DLIB_MCU_LPC176x=176 -D__TARGET_PORT=LIB_MCU_LPC176x -I"/home/carlos/workspace fiuba/wsRTO/CMSISv2p00_LPC17xx/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_FreeRTOS_7p0p1/FreeRTOS_portable" -I"/home/carlos/workspace fiuba/wsRTO/Lib_FreeRTOS_7p0p1/FreeRTOS_include" -I"/home/carlos/workspace fiuba/wsRTO/Lib_API_CAPI/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_MCU_LPC176x/inc" -I"/home/carlos/workspace fiuba/wsRTO/Lib_Contenedores/inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -I"/home/carlos/workspace fiuba/wsRTO/CMSISv2p00_LPC17xx/inc"  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


