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
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Ejercicio1.3.hex \

SECONDARY_SIZE += \
Ejercicio1.3.siz \


# All Target
all: Ejercicio1.3.axf secondary-outputs

# Tool invocations
Ejercicio1.3.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "/home/carlos/ciaa-ide/workspace/Ejercicio1.3/ld/ciaa_lpc4337.ld" -Xlinker --gc-sections -L"/home/carlos/ciaa-ide/workspace/freertos_lpc43xx/Debug" -L"/home/carlos/ciaa-ide/workspace/lpcopen_lpc4337/Debug" -Wl,-Map,"Ejercicio1.3.map" --specs=nano.specs -o "Ejercicio1.3.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Ejercicio1.3.hex: Ejercicio1.3.axf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "Ejercicio1.3.axf"  "Ejercicio1.3.hex"
	@echo 'Finished building: $@'
	@echo ' '

Ejercicio1.3.siz: Ejercicio1.3.axf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "Ejercicio1.3.axf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(S_UPPER_DEPS) Ejercicio1.3.axf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
