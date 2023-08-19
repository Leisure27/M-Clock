#include <TFT_eSPI.h>
#include "NTP/NTP.h"
#include "KaiTI_30.h" // 自定义字体

#define BLK 5         // 屏幕亮度控制引脚
#define TFT_Light 150 // 调节屏幕亮度，0最亮，255最暗
TIME Current_Time;    // 结构体，存储当前NTP时间

TFT_eSPI tft = TFT_eSPI(); // 创建TFT对象
TFT_eSprite clk = TFT_eSprite(&tft);

String num2str(uint16_t num);
uint8_t Zeller_Week();
void Update_Current_Time();

void TFT_Init()
{
    tft.init();                // 初始化
    tft.fillScreen(TFT_BLACK); // 设置屏幕背景颜色
    analogWrite(BLK, TFT_Light);
}

// 数字转化为字符串，将时间以两位数显示
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
String Time_str()
{
    String s = num2str(Current_Time.hour) + ":" + num2str(Current_Time.minute) + ":" + num2str(Current_Time.second);
    return s;
}

String Week_str()
{
    uint8_t w = Zeller_Week();
    String week[7] = {"日", "一", "二", "三", "四", "五", "六"};
    String s = "周" + week[w];
    return s;
}

// 蔡勒(Zeller)公式：快速将任意日期转换为星期数
uint8_t Zeller_Week()
{
    uint16_t year = Current_Time.year;
    uint8_t month = Current_Time.month;
    uint8_t day = Current_Time.day;
    if (month < 3)
    {
        year--;
        month += 12;
    }
    int c = int(year / 100), y = year - 100 * c;
    int w = int(c / 4) - 2 * c + y + int(y / 4) + (26 * (month + 1) / 10) + day - 1;
    w = (w % 7 + 7) % 7; // 0：Sunday，1:Monday
    return w;
}

void Display_NTP_Time()
{
    clk.setColorDepth(8);

    // 显示当前时间
    clk.createSprite(220, 48);   // 创建一个画布，画布大小x*y
    clk.fillSprite(TFT_BLACK);   // 画布颜色
    clk.setTextColor(TFT_WHITE); // 字体颜色
    clk.setTextFont(7);          // 字体类型Font 7，字体大小：48*48
    clk.setTextDatum(TL_DATUM);  // 设置文本显示基准：左上对齐(默认对齐方式)
    clk.drawString(Time_str(), 0, 0);
    clk.pushSprite(2, 38); // 把画布推送到屏幕的(x,y)位置进行显示
    clk.unloadFont();      // 卸载字体
    clk.deleteSprite();    // 删除画布

    // 显示日期
    clk.createSprite(120, 32);   // 创建一个画布，画布大小x*y
    clk.fillSprite(TFT_BLACK);   // 画布颜色
    clk.setTextColor(TFT_WHITE); // 字体颜色
    clk.loadFont(KaiTI_30);      // 加载字体
    clk.setTextDatum(TL_DATUM);  // 设置文本显示基准：左上对齐(默认对齐方式)
    clk.print(Current_Time.month);
    clk.print("月");
    clk.print(Current_Time.day);
    clk.print("日");
    clk.pushSprite(2, 7); // 把画布推送到屏幕的(x,y)位置进行显示
    clk.deleteSprite();   // 删除画布

    // 显示星期
    clk.createSprite(68, 32);    // 创建一个画布，画布大小x*y
    clk.fillSprite(TFT_BLACK);   // 画布颜色
    clk.setTextColor(TFT_WHITE); // 字体颜色
    // clk.loadFont(KaiTI_30);
    clk.setTextDatum(TL_DATUM); // 设置文本显示基准：左上对齐(默认对齐方式)
    clk.print(Week_str());
    clk.pushSprite(173, 7); // 把画布推送到屏幕的(x,y)位置进行显示
    clk.unloadFont();       // 卸载字体
    clk.deleteSprite();     // 删除画布
}

void Update_Current_Time()
{
    GetCurrentTime(Current_Time);
    Display_NTP_Time();
}