/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2021-09-15     Eureka1024       the first version
 */
#include <rtthread.h>
#include <dfs_posix.h> /* 当需要使用文件操作时，需要包含这个头文件 */

int music_num_get(void)
{
    int num = 0;
    DIR *dirp = RT_NULL;
    struct dirent *d;

    /* 打开 / dir_test 目录 */
    while(dirp == RT_NULL)
    {
        dirp = opendir("/music");
        rt_thread_mdelay(500);
    };

    if (dirp == RT_NULL)
    {
        rt_kprintf("open directory error!\n");
    }
    else
    {
        /* 读取目录 */
        while ((d = readdir(dirp)) != RT_NULL)
        {
            rt_kprintf("found %s\n", d->d_name);
            num++;
        }
        /* 关闭目录 */
        closedir(dirp);
    }
    rt_kprintf("i = %d\n",num);

    return num;
}
