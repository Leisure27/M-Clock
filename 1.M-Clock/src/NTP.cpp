/*
 * NTP授时
 */
#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

const long utcOffsetInSeconds = 28800; // 时区偏移量（以秒为单位），3600*8，偏移8个小时
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} TIME;
// 启动NTP服务器
void NTP_Init()
{
    timeClient.begin();
}

// NTP授时
TIME NTPGetTime()
{
    timeClient.update(); // 更新NTP时间

    uint64_t epochTime = timeClient.getEpochTime(); // 获取当前时间
    struct tm *currentTime = gmtime((time_t *)&epochTime);
    TIME Current_Time;                               // 创建一个结构体对象存储当前时间
    Current_Time.year = currentTime->tm_year + 1900; // 存储的是自 1900 年以来经过的年数，因此需要加上 1900 才能得到当前年份
    Current_Time.month = currentTime->tm_mon + 1;    // 由于 tm_mon 变量存储的是从 0 开始计数的月份数，因此需要加上 1 才能得到当前月份。
    Current_Time.day = currentTime->tm_mday;         // 日
    Current_Time.hour = currentTime->tm_hour;        // 时
    Current_Time.minute = currentTime->tm_min;       // 分
    Current_Time.second = currentTime->tm_sec;       // 秒

    return Current_Time;
}