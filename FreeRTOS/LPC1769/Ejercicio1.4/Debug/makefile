################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: Ejercicio1.4.axf

# Tool invocations
Ejercicio1.4.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\wsRTO\Lib_FreeRTOS_7p0p1\Debug_LPC176x" -L"C:\wsRTO\CMSISv2p00_LPC17xx\Debug" -L"C:\wsRTO\Lib_API_CAPI\Debug" -L"C:\wsRTO\Lib_Contenedores\Debug" -L"C:\wsRTO\Lib_MCU_LPC176x\Debug" -Xlinker -Map="Ejercicio1.4.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Ejercicio1_4_Debug.ld" -o "Ejercicio1.4.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Ejercicio1.4.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Ejercicio1.4.axf"; # arm-none-eabi-objcopy -O binary "Ejercicio1.4.axf" "Ejercicio1.4.bin" ; checksum -p LPC1769 -d "Ejercicio1.4.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
