#pragma once
#include <Arduino.h>

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} TIME;

void NTP_Init();
void GetCurrentTime(TIME &time); // 通过NTP服务器获取当前时间
