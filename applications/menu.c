/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-9-13     Eureka1024    the first version
 */

#include <rtthread.h>
#include "common.h"

void load_menu(int8_t* state_addr);
void main_menu(int8_t* state_addr);

void playlists(int8_t* state_addr);
void settings_list(int8_t* state_addr);

void music_play(int8_t* state_addr);
void volume_control(int8_t* state_addr);
void language_setting(int8_t* state_addr);
void brightness_setting(int8_t* state_addr);

uint8_t songs_num_get(void);

struct SONG_INFO song_info; //存放歌曲信息

typedef struct
{
    uint8_t coordinate;      //当前状态索引号
    uint8_t back;            //返回（双击确定键）
    void (*enter_operation)(int8_t*);     //当前状态执行的操作

    //当 entry键按下时  sub_base_addr提供子状态的基地址索引，sub_offset_addr提供偏移量，两者相加，得到下一个状态
    uint8_t sub_base_addr;   //子状态基地址
    uint8_t sub_offset_addr; //子状态偏移地址 （用于记录下一步要跳转到的子状态）

    uint8_t leaf_node_flag;  //标志是否为叶子节点（最底层的状态），方便在该状态下按确定可以实现返回功能
} Menu_table;


//针对下表，一些想法：其实可以增加一个变量来实现树的收缩的（解决音乐播放时，点击任意一首歌进入的是同一个状态，目前是enter事件给特殊，如果还有，就思考了）
Menu_table  table[]=
{   //索引   - back -  function(当前)  - 子状态基地址(固定)  - 子状态偏移地址   - 标志是否为叶子节点
    {  0,    0,      (*load_menu),       1,             0,           0},   //0加载界面

    {  1,    1,      (*main_menu),       2,             0,           0},   //1主菜单界面

    {  2,    1,      (*playlists),       4,             0,           0},   //歌单
    {  3,    1,    (*settings_list),     5,             0,           0},   //设置

    //播放的子菜单
    {  4,    2,      (*music_play),      0,             0,           0},   //音乐播放控制：（2-1）

    //设置菜单的子菜单
    {  5,    3,      (*volume_control),  0,             1,           1},   //音量控制
    {  6,    3,    (*language_setting),  0,             1,           1},   //语言设置
    {  7,    3,  (*brightness_setting),  0,             1,           1},   //亮度设置
};


void (*current_operation_index)(void);   //当前状态操作函数
uint8_t  func_index = 0;                 //当前状态

/* 超时函数 */
static void menu_thread_entry(void *parameter)
{
    rt_uint32_t e;
    int8_t k;

    while(1)
    {
        if (rt_event_recv(&control_event,
                           (UP_FLAG | ENTRY_FLAG | RETURN_FLAG | DOWN_FLAG),
                           RT_EVENT_FLAG_OR,
                           RT_WAITING_FOREVER, &e) == RT_EOK)
        {
            //按键 PRE
            if (rt_event_recv(&control_event,
                               UP_FLAG,
                               RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                               RT_WAITING_NO, &e) == RT_EOK)
            {
                table[func_index].sub_offset_addr -= 1;
                table[func_index].enter_operation(&table[func_index].sub_offset_addr);
            }

            //按键 ENTRY
            if (rt_event_recv(&control_event,
                               ENTRY_FLAG,
                               RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                               RT_WAITING_NO, &e) == RT_EOK)
            {
                if(table[func_index].leaf_node_flag)
                {
                    func_index = table[func_index].back; //返回上一级菜单位置
                    table[func_index].enter_operation(&table[func_index].sub_offset_addr);
                }
                else if(func_index == 2)  //音乐播放则特殊点(所有音乐进入同一个状态)
                {
                    k = table[func_index].sub_offset_addr;
                    func_index = 4;
                    table[func_index].sub_offset_addr = k;
                    table[func_index].enter_operation(&table[func_index].sub_offset_addr);
                }
                else
                {
                    func_index = table[func_index].sub_base_addr + table[func_index].sub_offset_addr;
                    table[func_index].enter_operation(&table[func_index].sub_offset_addr);
                }
            }

             //按键 ENTRY double click
             if (rt_event_recv(&control_event,
                                RETURN_FLAG,
                                RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                                RT_WAITING_NO, &e) == RT_EOK)
             {
                 func_index = table[func_index].back;
                 table[func_index].enter_operation(&table[func_index].sub_offset_addr);
             }


            //按键 NEXT
            if (rt_event_recv(&control_event,
                               DOWN_FLAG,
                               RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                               RT_WAITING_NO, &e) == RT_EOK)
            {
                table[func_index].sub_offset_addr += 1;
                table[func_index].enter_operation(&table[func_index].sub_offset_addr);
            }
        }
    }
}

#define THREAD_PRIORITY         26
#define THREAD_STACK_SIZE       2048
#define THREAD_TIMESLICE        10
static rt_thread_t menu_tid = RT_NULL;
int menuGUI_thread_init(void)
{
    int8_t i = 0;
    OLED_Init();            //初始化OLED
    OLED_Clear();
    load_menu(&i);

    //song_info.songs_num = music_num_get();
    song_info.songs_num = 16;

    menu_tid = rt_thread_create("menu_thread",
                            menu_thread_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY,
                            THREAD_TIMESLICE);

    if (menu_tid != RT_NULL)
        rt_thread_startup(menu_tid);

//    wavplayer_volume_set(3); //初始化音量
    return RT_EOK;
}
INIT_APP_EXPORT(menuGUI_thread_init);


void load_menu(int8_t* state_addr)
{
    rt_uint32_t e;
    OLED_ShowString(30,0,"Loading...", 16);
    OLED_DrawBMP(0,2,128,8,loading_bmp); //RT-Thread图标

    rt_thread_delay(2000);

    //切换到主菜单
    func_index = table[func_index].sub_base_addr + table[func_index].sub_offset_addr;
    table[func_index].enter_operation(&table[func_index].sub_offset_addr);
}

void main_menu(int8_t* state_addr)
{
    int8_t i=20;
    OLED_Clear();

    if(*state_addr < 0)  *state_addr = 1;
    if(*state_addr >= 2)    *state_addr = 0;

    switch(*state_addr)
    {
        case 0:
            OLED_ShowCHinese(i,0,0);   //音
            OLED_ShowCHinese(i+18,0,1);//乐
            OLED_ShowCHinese(i+36,0,2);//播
            OLED_ShowCHinese(i+54,0,3);//放
            OLED_ShowCHinese(i+72,0,4);//器
            OLED_DrawBMP(40,2,40+48,8,music_bmp);//音乐图标

            break;

        case 1:
            OLED_ShowCHinese(46,0,5);//设
            OLED_ShowCHinese(64,0,6);//置
            OLED_DrawBMP(40,2,40+48,8,setting_bmp);//设置图标
            break;

        default:
            break;
    }
}


DIR *dirp = RT_NULL;
struct dirent *d = RT_NULL;
void playlists(int8_t* state_addr)
{
    int8_t   i = 0;
    uint8_t  j = 0;
    uint8_t  k = 2;

    if(*state_addr < 0)  *state_addr = song_info.songs_num-1; //第一首往上按到达末尾
    if(*state_addr >= song_info.songs_num)  *state_addr = 0;  //最后一首往下按到第一首

    OLED_Clear();
    OLED_ShowString(30,0,"PlayList", 16);

    //更新歌曲显示
    if(*state_addr%3 == 0)
    {
        dirp = opendir("/music"); // 打开 /music目录
        if (dirp == RT_NULL)
        {
            rt_kprintf("open directory error!\n");
        }
        else
        {
            i = *state_addr/3;
            while(i--)
            {
                for(j=0; j<3; ++j) //过三首
                {
                    d = readdir(dirp);
                }
            }

            for(j=0; j<3; ++j) //获取三首歌曲的名字
            {
                d = readdir(dirp);
                rt_strncpy(song_info.music_table[j],d->d_name,20);
            }
        }

        closedir(dirp); //关闭目录
    }


    for(i=0; i<=2; ++i)
    {
        OLED_ShowString(18,k,(uint8_t*)song_info.music_table[i], 16);
        k+=2;
    }

    //移动指示光标
    OLED_ShowString(0,2+(*state_addr%3)*2,"->", 16);
}


void settings_list(int8_t* state_addr)
{
    int8_t i=0,k=2;
    if(*state_addr < 0)  *state_addr = 1;
    if(*state_addr >= 3)  *state_addr = 0;
    OLED_Clear();
    OLED_ShowString(10,0,"Settings List", 16);
    OLED_ShowString(18,k,"volume", 16);
    OLED_ShowString(18,k+2,"language", 16);
    OLED_ShowString(18,k+4,"brightness", 16);

    //移动指示光标
    OLED_ShowString(0,2+(*state_addr%3)*2,"->", 16);
}

char  current_music_file_path[30];
void music_play(int8_t* state_addr)
{
    static int8_t pre_play_state = 0xFF; //默认该值不可能达到

    if(pre_play_state == *state_addr) //重复点击
    {
        pre_play_state = 0XFF;
        wavplayer_pause(); //使用wavplayer_play 会重新播放
    }
    else
    {
        pre_play_state = *state_addr; //记录当前播放位置

        rt_memcpy(current_music_file_path, "music/", 6);
        rt_strncpy(&current_music_file_path[6],song_info.music_table[*state_addr%3],20);
        rt_kprintf("play : %s\n",current_music_file_path);

        wavplayer_play(current_music_file_path); //播放
        rt_kprintf("volume = %d\n",wavplayer_volume_get());
    }

    //返回上一个状态
    func_index = table[func_index].back;
    table[func_index].enter_operation(&table[func_index].sub_offset_addr);
}


void volume_control(int8_t* state_addr)
{
    if(*state_addr > 9) *state_addr = 9;
    if(*state_addr < 0)   *state_addr = 0;

    wavplayer_volume_set(*state_addr*5);
    rt_kprintf("volume = %d\n",wavplayer_volume_get());
    OLED_Clear();
    OLED_ShowNum(30,0,*state_addr*10,2,16);
}

void language_setting(int8_t* state_addr)
{
    OLED_Clear();
    OLED_ShowString(0,2,"sorry", 16);
    OLED_ShowString(0,4,"you not is vip", 16);
    rt_thread_delay(2000);

    //返回上一个状态
    func_index = table[func_index].back;
    table[func_index].enter_operation(&table[func_index].sub_offset_addr);
}


void brightness_setting(int8_t* state_addr)
{
    OLED_Clear();
    OLED_ShowString(0,2,"sorry", 16);
    OLED_ShowString(0,4,"you not is vip", 16);
    rt_thread_delay(2000);

    //返回上一个状态
    func_index = table[func_index].back;
    table[func_index].enter_operation(&table[func_index].sub_offset_addr);
}

//获取歌曲数量
uint8_t songs_num_get(void)
{
    int num = 0;
    rt_uint32_t level;
    rt_thread_delay(1000);

    dirp = opendir("/music"); // 打开 /music目录
    while (dirp == RT_NULL)
    {
        dirp = opendir("/music"); // 打开 /music目录
        rt_kprintf("songs_num_get:open directory error!\n");
        rt_thread_delay(1000);
    }

    // 读取目录
    while ((d = readdir(dirp)) != RT_NULL)
    {
        num++;
    }

    return num;
}
