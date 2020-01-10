################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
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
all:
	$(MAKE) --no-print-directory pre-build
	$(MAKE) --no-print-directory main-build

# Main-build Target
main-build: 02.Blink-Fast.axf

# Tool invocations
02.Blink-Fast.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="02.Blink-Fast.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m0plus -mthumb -T "02_Blink-Fast_Debug.ld" -o "02.Blink-Fast.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) 02.Blink-Fast.axf
	-@echo ' '

pre-build:
	-arm-none-eabi-objcopy -v -O binary "02.Blink-Fast.axf" "02.Blink-Fast.bin"
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "02.Blink-Fast.axf"; # arm-none-eabi-objcopy -v -O binary "02.Blink-Fast.axf" "02.Blink-Fast.bin" ; # checksum -p MKL25Z128xxx4 -d "02.Blink-Fast.bin";
	-@echo ' '

.PHONY: all clean dependents main-build pre-build post-build

-include ../makefile.targets
