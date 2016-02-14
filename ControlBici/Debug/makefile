################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Salud/subdir.mk
-include Robo/subdir.mk
-include MaquinaEstado/subdir.mk
-include Framework/subdir.mk
-include Estadisticas/subdir.mk
-include Drivers/Interrupcion/subdir.mk
-include Drivers/InterfazHumana/subdir.mk
-include Drivers/CuentaVueltas/subdir.mk
-include Drivers/Alarma/subdir.mk
-include Drivers/Acelerometro/subdir.mk
-include Drivers/subdir.mk
-include Configuracion/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ControlBici.axf

# Tool invocations
ControlBici.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/carlos/workspace RTOS TP/tp_rtos_2014/CMSIS/CMSISv2p00_LPC17xx/Debug" -L"/home/carlos/workspace RTOS TP/tp_rtos_2014/CAPI/Lib_Contenedores/Debug" -L"/home/carlos/workspace RTOS TP/tp_rtos_2014/CAPI/Lib_MCU_LPC176x/Debug" -L"/home/carlos/workspace RTOS TP/tp_rtos_2014/CAPI/Lib_API_CAPI/Debug" -L"/home/carlos/workspace RTOS TP/tp_rtos_2014/Librerias/Lib_EaBaseBoard/Debug" -L"/home/carlos/workspace RTOS TP/tp_rtos_2014/FreeRTOS/Lib_FreeRTOS_7p0p1/Debug_LPC176x" -Xlinker --gc-sections -Xlinker -Map=ControlBici.map -mcpu=cortex-m3 -mthumb -T "ControlBici_Debug.ld" -o "ControlBici.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) ControlBici.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size ControlBici.axf; # arm-none-eabi-objcopy -O ihex ControlBici.axf ControlBici.hex ;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
