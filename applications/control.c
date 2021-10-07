/*
 * Copyright (c) 2021, Eureka1024 <eureka1024@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-07     Eureka1024    the first version
 */
#include "common.h"

//控制事件控制块
struct rt_event control_event;

int control_event_init(void)
{
    rt_event_init(&control_event, "control_event", RT_IPC_FLAG_FIFO);
}
INIT_APP_EXPORT(control_event_init);
