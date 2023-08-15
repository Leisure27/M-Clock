#include <TFT_eSPI.h>
#include "KaiTi_26.h"

TFT_eSPI tft = TFT_eSPI(); // 创建TFT对象

#define BLK 5 // 亮度控制引脚
void TFT_Init()
{
  tft.init();                // 初始化
  tft.fillScreen(TFT_BLACK); // 设置屏幕背景颜色
  analogWrite(BLK, 150);     // 调节屏幕亮度，0最亮，255最暗
}

void TFT_Display()
{
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // 参数1：字体颜色，参数2：背景色

  tft.setTextFont(2); // 字体大小16*16
  tft.println("Hello,world");
  tft.drawString("I want to eat something", 0, 50, 2);

  tft.setTextFont(4); // 字体大小26*26
  tft.drawNumber(1234, 0, 70);
  tft.drawFloat(3.14159, 5, 0, 90);

  // 自定义字库测试
  tft.loadFont(KaiTi_26); // 加载自定义字体
  tft.setCursor(0, 150);
  tft.println("中文");
  tft.drawString("汉字测试", 0, 177);
  tft.unloadFont(); // 释放字库
}

void setup()
{
  TFT_Init();
  TFT_Display();
}

void loop() {}