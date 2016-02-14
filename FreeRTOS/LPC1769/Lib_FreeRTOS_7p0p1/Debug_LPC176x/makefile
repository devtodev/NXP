################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include demo_code/subdir.mk
-include FreeRTOS_src/subdir.mk
-include FreeRTOS_portable/MemMang/subdir.mk
-include FreeRTOS_portable/subdir.mk
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
all: libLib_FreeRTOS_7p0p1.a

# Tool invocations
libLib_FreeRTOS_7p0p1.a: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Archiver'
	arm-none-eabi-ar -r  "libLib_FreeRTOS_7p0p1.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ARCHIVES) libLib_FreeRTOS_7p0p1.a
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size libLib_FreeRTOS_7p0p1.a ; # arm-none-eabi-objdump -h -S libLib_FreeRTOS_7p0p1.a >libLib_FreeRTOS_7p0p1.lss
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
