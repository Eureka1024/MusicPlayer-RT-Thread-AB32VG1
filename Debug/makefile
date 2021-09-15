################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include rt-thread/src/subdir.mk
-include rt-thread/components/libc/compilers/newlib/subdir.mk
-include rt-thread/components/libc/compilers/common/subdir.mk
-include rt-thread/components/finsh/subdir.mk
-include rt-thread/components/drivers/src/subdir.mk
-include rt-thread/components/drivers/serial/subdir.mk
-include rt-thread/components/drivers/sdio/subdir.mk
-include rt-thread/components/drivers/misc/subdir.mk
-include rt-thread/components/drivers/audio/subdir.mk
-include rt-thread/components/dfs/src/subdir.mk
-include rt-thread/components/dfs/filesystems/elmfat/subdir.mk
-include rt-thread/components/dfs/filesystems/devfs/subdir.mk
-include packages/wavplayer-latest/src/subdir.mk
-include packages/optparse-latest/subdir.mk
-include packages/MultiButton-v1.1.0/subdir.mk
-include libraries/hal_libraries/bmsis/source/subdir.mk
-include libraries/hal_libraries/ab32vg1_hal/source/subdir.mk
-include libraries/hal_drivers/subdir.mk
-include libcpu/cpu/subdir.mk
-include board/ports/audio/subdir.mk
-include board/subdir.mk
-include applications/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
rtthread.bin \

SECONDARY_LIST += \
rtthread.lst \

SECONDARY_SIZE += \
rtthread.siz \


# 所有目标
all: rtthread.elf secondary-outputs

# 工具调用
rtthread.elf: $(OBJS) $(USER_OBJS)
	riscv64-unknown-elf-gcc -T "D:\music_player_AB32VG1\AB32VG1MusicPlayer\link.lds" -nostartfiles -L"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_libraries\ab32vg1_hal" -Wl,-Map,"rtthread.map" -mcmodel=medany -march=rv32imc -mabi=ilp32 -msave-restore -nostartfiles -Wl,-cref,-u,_start -o "rtthread.elf" $(OBJS) $(USER_OBJS) $(LIBS)

rtthread.bin: rtthread.elf
	riscv64-unknown-elf-objcopy -O binary "rtthread.elf"  "rtthread.bin"

rtthread.lst: rtthread.elf
	riscv64-unknown-elf-objdump --source --all-headers --demangle --line-numbers --wide "rtthread.elf" > "rtthread.lst"

rtthread.siz: rtthread.elf
	riscv64-unknown-elf-size --format=berkeley "rtthread.elf"

# 其他目标
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) rtthread.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
