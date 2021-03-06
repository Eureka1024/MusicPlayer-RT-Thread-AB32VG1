/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-15     Eureka1024       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include <multi_button.h>
#include "wavplayer.h"
#include "common.h"

#define UP_BUTTON_PIN    rt_pin_get("PA.2")
#define ENTRY_BUTTON_PIN rt_pin_get("PF.0")
#define DOWN_BUTTON_PIN  rt_pin_get("PF.1")

static struct button btn_0;
static struct button btn_1;
static struct button btn_2;

void saia_channels_set(uint8_t channels);
void saia_volume_set(rt_uint8_t volume);
uint8_t saia_volume_get(void);

static uint8_t button_read_pin_0(void)
{
    return rt_pin_read(UP_BUTTON_PIN);
}

static uint8_t button_read_pin_1(void)
{
    return rt_pin_read(ENTRY_BUTTON_PIN);
}

static uint8_t button_read_pin_2(void)
{
    return rt_pin_read(DOWN_BUTTON_PIN);
}

static void button_0_callback(void *btn) //pre
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct button *)btn);

    switch(btn_event_val)
    {
        case SINGLE_CLICK:
            rt_event_send(&control_event, UP_FLAG);
            break;

        case DOUBLE_CLICK:
            break;

        default:
            break;
    }
}

static void button_1_callback(void *btn)//entry
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct button *)btn);

    switch(btn_event_val)
    {
        case SINGLE_CLICK:
            rt_event_send(&control_event, ENTRY_FLAG);
            break;

        case DOUBLE_CLICK:
            rt_event_send(&control_event, RETURN_FLAG);
            break;

        default:
            break;
    }
}


static void button_2_callback(void *btn)//next
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct button *)btn);

    switch(btn_event_val)
    {
        case SINGLE_CLICK:
            rt_event_send(&control_event, DOWN_FLAG);
            break;

        case DOUBLE_CLICK:
            break;

        default:
            break;
    }
}

static void btn_thread_entry(void* p)
{
    while(1)
    {
        /* 5ms */
        rt_thread_delay(RT_TICK_PER_SECOND/200);
        button_ticks();

        //??????????????????????????????????????????wavplayer????????????????????????????????????????????????????????????????????????bug,????????????
        //wavplayer_volume_set(wavplayer_volume_get());
    }
}

static int multi_button_ctrl(void)
{
    rt_thread_t thread = RT_NULL;

    /* Create background ticks thread */
    thread = rt_thread_create("btn", btn_thread_entry, RT_NULL, 512, 20, 10);
    if(thread == RT_NULL)
    {
        return RT_ERROR;
    }
    rt_thread_startup(thread);

    /* low level drive */
    rt_pin_mode  (UP_BUTTON_PIN, PIN_MODE_INPUT_PULLUP);
    button_init  (&btn_0, button_read_pin_0, PIN_LOW);
    button_attach(&btn_0, SINGLE_CLICK,     button_0_callback);
    button_attach(&btn_0, DOUBLE_CLICK,     button_0_callback);
    button_start (&btn_0);

    rt_pin_mode  (ENTRY_BUTTON_PIN, PIN_MODE_INPUT_PULLUP);
    button_init  (&btn_1, button_read_pin_1, PIN_LOW);
    button_attach(&btn_1, SINGLE_CLICK,     button_1_callback);
    button_attach(&btn_1, DOUBLE_CLICK,     button_1_callback);
    button_start (&btn_1);

    rt_pin_mode  (DOWN_BUTTON_PIN, PIN_MODE_INPUT_PULLUP);
    button_init  (&btn_2, button_read_pin_2, PIN_LOW);
    button_attach(&btn_2, SINGLE_CLICK,     button_2_callback);
    button_attach(&btn_2, DOUBLE_CLICK,     button_2_callback);
    button_start (&btn_2);

    return RT_EOK;
}
INIT_APP_EXPORT(multi_button_ctrl);
