#include <Arduino.h>
#include "M_Config.h"
#include <NTP.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ESP32
#include <WiFi.h>
#endif

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

void setup()
{
  Serial.begin(115200);
  Connect_Wifi();
  NTP_Init();
}
void loop()
{
  TIME Current_Time = NTPGetTime();

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
  delay(1000);
}