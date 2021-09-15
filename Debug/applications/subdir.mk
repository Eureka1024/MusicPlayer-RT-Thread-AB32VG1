################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../applications/button.c \
../applications/main.c \
../applications/menu.c \
../applications/mnt.c \
../applications/music.c \
../applications/oled_iic.c \
../applications/test.c 

OBJS += \
./applications/button.o \
./applications/main.o \
./applications/menu.o \
./applications/mnt.o \
./applications/music.o \
./applications/oled_iic.o \
./applications/test.o 

C_DEPS += \
./applications/button.d \
./applications/main.d \
./applications/menu.d \
./applications/mnt.d \
./applications/music.d \
./applications/oled_iic.d \
./applications/test.d 


# Each subdirectory must supply rules for building sources it contributes
applications/%.o: ../applications/%.c
	riscv64-unknown-elf-gcc  -DDEBUG -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\include\libc" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\applications" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\board" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libcpu\cpu" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_drivers\config" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_drivers" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_libraries\ab32vg1_hal\include" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_libraries\ab32vg1_hal" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_libraries\bmsis\include" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\libraries\hal_libraries\bmsis" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\MultiButton-v1.1.0" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\optparse-latest" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\wavplayer-latest\inc" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\packages\wavplayer-latest" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\dfs\filesystems\devfs" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\dfs\filesystems\elmfat" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\dfs\include" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\drivers\audio" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\drivers\include" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\finsh" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\libc\compilers\common" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\components\libc\compilers\newlib" -I"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rt-thread\include" -isystem"D:\music_player_AB32VG1\AB32VG1MusicPlayer" -include"D:\music_player_AB32VG1\AB32VG1MusicPlayer\rtconfig_preinc.h" -std=gnu11 -c -mcmodel=medany -march=rv32imc -mabi=ilp32 -msave-restore -Os -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

