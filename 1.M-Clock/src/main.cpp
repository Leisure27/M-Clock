#include <Arduino.h>

#include "M_Config.h"
#include "NTP/NTP.h"
#include "HeFeng/HeFengAPI.h"
#include "XinZhi/XinZhiAPI.h"
#include "LCD/Lcd.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ESP32
#include <WiFi.h>
#endif

/*全局变量声明区*/

/*实例化对象区*/

/*函数声明区*/

/*自定义函数区*/
void Connect_Wifi()
{
  WiFi.hostname(DeviceName);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int flag = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    flag++;
    Serial.print(flag);
    if (flag > 10)
    {
      Serial.println("WiFi Connection Failed");
      ESP.restart(); //  重启
    }
  }

  Serial.println(F(""));
  Serial.println(F("WiFi Connected!"));
  Serial.print("IP:");
  Serial.println(WiFi.localIP());
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
  // NTP_Time();
  Update_Current_Time();
  // XinZhi_test();
  // delay(3000);
}