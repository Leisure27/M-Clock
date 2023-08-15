#pragma once
#include <Arduino.h>

void NTP_Init();
void NTPGetTime();

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} TIME;
extern TIME Current_Time;
