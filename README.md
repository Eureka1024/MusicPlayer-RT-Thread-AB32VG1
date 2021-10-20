# MusicPlayer-RT-Thread-AB32VG1
A music player based on RT-thread and AB32VG1.

## 一、概述

本项目是基于实时操作系统 RT-Thread 和 AB32VG1的核心板实现的音乐播放器模块，下面是目前规划的系统框图：

![image-20211010155216979](https://gitee.com/Eureka1024/my-image-hosting-service/raw/master/img/202110101552470.png)

下面是实现的功能（其中打勾的为已经实现的功能）：

- [x] 音乐播放
- [x] SD 卡音乐读取
- [x] OLED 屏幕菜单显示
- [x] 按键控制
- [ ] 三色LED灯效果
- [ ] 手势识别控制

## 二、引脚连接关系

- OLED12864 模块（IIC 协议）
  - SDA --  PA1
  - SCL --  PA0

- 按键模块（GPIO）
  - S2 -- PA2
  - S3 -- PF0
  - S4 -- PF1

- SD 卡模块（SDIO协议）

  SD_CMD -- PB0

  SD_CLK -- PB1

  SD_DAT -- PB2

  SD_DET -- PE5

  
