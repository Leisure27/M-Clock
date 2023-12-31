/*
 * NTP授时
 */
#include "NTP/NTP.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

const long utcOffsetInSeconds = 28800; // 时区偏移量（以秒为单位），3600*8，偏移8个小时
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// 启动NTP服务器
void NTP_Init()
{
    timeClient.begin();
}

// 获取当前时间
void GetCurrentTime(TIME &time)
{
    static unsigned long previousMillis;
    unsigned long CurrentMillis = millis();
    if (CurrentMillis - previousMillis >= 500) // 0.5s更新一次时间
    {
        previousMillis = millis();
        timeClient.update(); // 更新NTP时间
    }
    uint64_t epochTime = timeClient.getEpochTime(); // 获取当前NTP时间
    struct tm *currentTime = gmtime((time_t *)&epochTime);

    time.year = currentTime->tm_year + 1900; // 存储的是自 1900 年以来经过的年数，因此需要加上 1900 才能得到当前年份
    time.month = currentTime->tm_mon + 1;    // 由于 tm_mon 变量存储的是从 0 开始计数的月份数，因此需要加上 1 才能得到当前月份。
    time.day = currentTime->tm_mday;         // 日
    time.hour = currentTime->tm_hour;        // 时
    time.minute = currentTime->tm_min;       // 分
    time.second = currentTime->tm_sec;       // 秒
}
