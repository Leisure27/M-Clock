// #include <TFT_eSPI.h>
// #include <ESP8266WiFi.h>
// #define BLK 5

// uint8_t loadNum = 6; // 开机启动进度条的起始位置
// const char *ssid = "613专属";
// const char *pwd = "613613613";

// TFT_eSPI tft = TFT_eSPI(); // 创建TFT对象
// TFT_eSprite clk = TFT_eSprite(&tft);

// // 开机联网动画
// void PowerOn_Loading(uint8_t delayTime) // 开机联网显示的进度条，输入延时时间
// {
//     clk.setColorDepth(8);
//     clk.createSprite(200, 50); // 创建Sprite
//     clk.fillSprite(0x0000);    // 填充颜色

//     clk.drawRoundRect(0, 0, 200, 16, 8, 0xFFFF);      // 画一个圆角矩形
//     clk.fillRoundRect(3, 3, loadNum, 10, 5, 0xFFFF);  // 画一个填充的圆角矩形
//     clk.setTextDatum(CC_DATUM);                       // 显示对齐方式
//     clk.setTextColor(TFT_GREEN, 0x0000);              // 文本的前景色和背景色
//     clk.drawString("Connecting to WiFi", 100, 40, 2); // 显示文本
//     clk.pushSprite(20, 110);                          // Sprite中内容一次推向屏幕
//     clk.deleteSprite();                               // 删除Sprite
//     loadNum += 1;                                     // 进度条位置变化，直到加载完成
//     if (loadNum >= 194)
//     {
//         loadNum = 194;
//     }
//     delay(delayTime);
// }

// void ConnectWifi()
// {
//     WiFi.mode(WIFI_STA);
//     WiFi.begin(ssid, pwd); // 用固定的账号密码连接网络

//     while (WiFi.status() != WL_CONNECTED)
//     { // 未连接上的话
//         for (uint8_t n = 0; n < 10; n++)
//         { // 每500毫秒检测一次状态
//             PowerOn_Loading(50);
//         }
//     }
//     while (loadNum < 194)
//     {                       // 让动画走完
//         PowerOn_Loading(1); // 加载动画，加载完后串口输出wifi信息
//     }

//     Serial.print("\nWiFi connected to: ");
//     Serial.println(ssid);
//     Serial.print("IP:   ");
//     Serial.println(WiFi.localIP()); // 得到IP地址
// }
// void setup()
// {
//     Serial.begin(115200);
//     pinMode(BLK, OUTPUT);
//     analogWrite(BLK, 150); // 调节屏幕亮度，0最亮，255最暗

//     tft.init();
//     tft.fillScreen(0x0000);
//     ConnectWifi();
// }
// void loop()
// {
// }
