/*
 * 功能：心知天气API请求
 */
#include <ESP8266WiFi.h>

const char *host = "api.seniverse.com"; // 将要连接的服务器地址
const int httpPort = 80;                // 将要连接的服务器端口

// 心知天气HTTP请求所需信息
String reqUserKey = "SkybHM6Aah0aqwb4_"; // 私钥
String reqLocation = "Wuhan";            // 城市
String reqUnit = "c";                    // 摄氏/华氏

// 建立心知天气API当前天气请求资源地址
String URL()
{
    String reqRes = "/v3/weather/now.json?key=" + reqUserKey +
                    +"&location=" + reqLocation +
                    "&language=en&unit=" + reqUnit;
    return reqRes;
}

// 向心知天气服务器服务器请求信息并对信息进行解析
void httpRequest()
{
    WiFiClient client;
    // 建立http请求信息
    String httpRequest = String("GET ") + URL() + " HTTP/1.1\r\n" +
                         "Host: " + host + "\r\n" +
                         "Connection: close\r\n\r\n";
    Serial.println("");
    Serial.print("Connecting to ");
    Serial.print(host);

    // 尝试连接服务器
    if (client.connect(host, 80))
    {
        Serial.println(" Success!");

        // 向服务器发送http请求信息
        client.print(httpRequest);
        Serial.println("Sending request: ");
        Serial.println(httpRequest);

        // 获取并显示服务器响应状态行
        String status_response = client.readStringUntil('\n');
        Serial.print("status_response: ");
        Serial.println(status_response);

        // 使用find跳过HTTP响应头
        if (client.find("\r\n\r\n"))
        {
            Serial.println("Found Header End. Start Parsing.");
        }

        // 利用ArduinoJson库解析心知天气响应信息
        String serverJson = client.readString();
        Serial.println(serverJson);
        // parseInfo(client);
    }
    else
    {
        Serial.println(" connection failed!");
    }
    // 断开客户端与服务器连接工作
    client.stop();
}