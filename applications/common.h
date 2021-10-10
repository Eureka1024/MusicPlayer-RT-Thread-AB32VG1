/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-15     Eureka1024       the first version
 */
#ifndef APPLICATIONS_COMMON_H_
#define APPLICATIONS_COMMON_H_

#include "oled_iic.h"
#include <wavplayer.h>
#include <dfs_posix.h> /* 当需要使用文件操作时，需要包含这个头文件 */
#include <rthw.h>
#include "paj7620.h"

/* 功能控制事件 */
#define UP_FLAG     (1 << 0)
#define ENTRY_FLAG  (1 << 1)
#define RETURN_FLAG (1 << 2)
#define DOWN_FLAG   (1 << 3)

extern struct rt_event control_event; //功能控制事件


struct SONG_INFO
{
    uint8_t songs_num;
    char music_table[3][20];
};

extern  unsigned char music_bmp[];
extern  unsigned char setting_bmp[];
extern unsigned char loading_bmp[];
extern struct SONG_INFO song_info;

int music_num_get(void);
#endif /* APPLICATIONS_COMMON_H_ */
