/*
 *   通过和风天气API获取天气信息
 */
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

String location = "101200101";                   // 城市ID，武汉市
String key = "9a15fc50a5414cb4b1615d49d390030a"; // 个人私钥

// 请求实时天气信息
void qweather()
{
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;

    String URL = "https://devapi.qweather.com/v7/weather/now?location=" + location + "&key=" + key + "&gzip=n";
    Serial.print("请求实时天气URL：");
    Serial.println(URL);

    if (https.begin(*client, URL))
    {
        // start connection and send HTTP header
        int httpCode = https.GET();
        // httpCode will be negative on error
        if (httpCode > 0)
        {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            {
                String payload = https.getString();
                Serial.println(payload);
                // 开始JSON数据解析
            }
        }
        else
        {
            Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
        https.end();
    }
    else
    {
        Serial.printf("[HTTPS] Unable to connect\n");
    }
}