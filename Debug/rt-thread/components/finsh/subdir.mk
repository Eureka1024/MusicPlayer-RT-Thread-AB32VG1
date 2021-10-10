################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/components/finsh/cmd.c \
../rt-thread/components/finsh/finsh_compiler.c \
../rt-thread/components/finsh/finsh_error.c \
../rt-thread/components/finsh/finsh_heap.c \
../rt-thread/components/finsh/finsh_init.c \
../rt-thread/components/finsh/finsh_node.c \
../rt-thread/components/finsh/finsh_ops.c \
../rt-thread/components/finsh/finsh_parser.c \
../rt-thread/components/finsh/finsh_token.c \
../rt-thread/components/finsh/finsh_var.c \
../rt-thread/components/finsh/finsh_vm.c \
../rt-thread/components/finsh/msh.c \
../rt-thread/components/finsh/msh_file.c \
../rt-thread/components/finsh/shell.c 

OBJS += \
./rt-thread/components/finsh/cmd.o \
./rt-thread/components/finsh/finsh_compiler.o \
./rt-thread/components/finsh/finsh_error.o \
./rt-thread/components/finsh/finsh_heap.o \
./rt-thread/components/finsh/finsh_init.o \
./rt-thread/components/finsh/finsh_node.o \
./rt-thread/components/finsh/finsh_ops.o \
./rt-thread/components/finsh/finsh_parser.o \
./rt-thread/components/finsh/finsh_token.o \
./rt-thread/components/finsh/finsh_var.o \
./rt-thread/components/finsh/finsh_vm.o \
./rt-thread/components/finsh/msh.o \
./rt-thread/components/finsh/msh_file.o \
./rt-thread/components/finsh/shell.o 

C_DEPS += \
./rt-thread/components/finsh/cmd.d \
./rt-thread/components/finsh/finsh_compiler.d \
./rt-thread/components/finsh/finsh_error.d \
./rt-thread/components/finsh/finsh_heap.d \
./rt-thread/components/finsh/finsh_init.d \
./rt-thread/components/finsh/finsh_node.d \
./rt-thread/components/finsh/finsh_ops.d \
./rt-thread/components/finsh/finsh_parser.d \
./rt-thread/components/finsh/finsh_token.d \
./rt-thread/components/finsh/finsh_var.d \
./rt-thread/components/finsh/finsh_vm.d \
./rt-thread/components/finsh/msh.d \
./rt-thread/components/finsh/msh_file.d \
./rt-thread/components/finsh/shell.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/components/finsh/%.o: ../rt-thread/components/finsh/%.c
	riscv64-unknown-elf-gcc  -DDEBUG -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\include\libc" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\applications" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\board" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libcpu\cpu" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_drivers\config" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_drivers" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_libraries\ab32vg1_hal\include" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_libraries\ab32vg1_hal" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_libraries\bmsis\include" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_libraries\bmsis" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\MultiButton-v1.1.0" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\PAJ7620-latest\src" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\PAJ7620-latest" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\optparse-latest" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\wavplayer-latest\inc" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\wavplayer-latest" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\dfs\filesystems\devfs" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\dfs\filesystems\elmfat" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\dfs\include" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\drivers\audio" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\drivers\include" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\finsh" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\libc\compilers\common" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\libc\compilers\newlib" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\include" -isystem"D:\music_player_AB32VG1\AB32VG1MusicPlayer" -include"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rtconfig_preinc.h" -std=gnu11 -c -mcmodel=medany -march=rv32imc -mabi=ilp32 -msave-restore -Os -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

