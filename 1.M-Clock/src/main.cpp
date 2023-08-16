#include <Arduino.h>
#include <TFT_eSPI.h>
#include "M_Config.h"
#include <NTP.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ESP32
#include <WiFi.h>
#endif

/*全局变量声明区*/
#define BLK 5         // 屏幕亮度控制引脚
#define TFT_Light 150 // 调节屏幕亮度，0最亮，255最暗
TIME Current_Time;    // 结构体，存储当前NTP时间

/*实例化对象区*/
TFT_eSPI tft = TFT_eSPI(); // 创建TFT对象
TFT_eSprite clk = TFT_eSprite(&tft);

/*函数声明区*/
String num2str(uint16_t num);

/*自定义函数区*/
void Connect_Wifi()
{
  WiFi.hostname(DeviceName);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int flag = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    flag++;
    Serial.print(flag);
    if (flag > 10)
    {
      ESP.restart(); //  重启
    }
  }

  Serial.println(F(""));
  Serial.println(F("WiFi Connected!"));
  Serial.print("IP:");
  Serial.println(WiFi.localIP());
}

void TFT_Init()
{
  tft.init();                // 初始化
  tft.fillScreen(TFT_BLACK); // 设置屏幕背景颜色
  analogWrite(BLK, TFT_Light);
}

// 数字转化为字符串
String num2str(uint16_t num)
{
  String s = "";
  if (num < 10)
  {
    s = s + "0";
  }
  s = s + num;
  return s;
}

// 将时分秒组成字符串
String Time_s()
{
  String s = num2str(Current_Time.hour) + ":" + num2str(Current_Time.minute) + ":" + num2str(Current_Time.second);
  return s;
}

void NTP_Time()
{

  Current_Time = NTPGetTime();
  Serial.print("Current time: ");
  Serial.print(Current_Time.year);
  Serial.print("/");
  Serial.print(Current_Time.month);
  Serial.print("/");
  Serial.print(Current_Time.day);
  Serial.print(" ");
  Serial.print(Current_Time.hour);
  Serial.print(":");
  Serial.print(Current_Time.minute);
  Serial.print(":");
  Serial.println(Current_Time.second);

  // 显示当前时间
  clk.setColorDepth(8);
  clk.createSprite(220, 48);   // 创建一个画布，画布大小x*y
  clk.fillSprite(TFT_BLACK);   // 画布颜色
  clk.setTextColor(TFT_WHITE); // 字体颜色
  clk.setTextFont(7);          // 字体类型Font 7，字体大小：48*48
  clk.setTextDatum(TL_DATUM);  // 设置文本显示基准：左上对齐(默认对齐方式)
  clk.drawString(Time_s(), 0, 0);

  clk.pushSprite(2, 2); // 把画布推送到屏幕的(x,y)位置进行显示
  clk.unloadFont();     // 卸载字体
  clk.deleteSprite();   // 删除画布

  // 显示日期
}

void setup()
{
  Serial.begin(115200);
  TFT_Init();
  Connect_Wifi();
  NTP_Init();
}

void loop()
{
  NTP_Time();
}