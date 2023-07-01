/*复习51单片机流水灯*/
/*注意事项：
1.定义用于设定方向的变量：dir
2.break是在顺或逆完成后，且方向改变后。即dir=1;break;
关于FastLED库，
*/
#include <FastLED.h>

#define button 0//按键

#define NUM_LEDS 64//led个数
#define DATA_PIN 2//控制引脚
int i;
int dir;//RGB移动方向
bool keysta;//上一次按键值
bool keydat;//当前按键值

CRGB leds[NUM_LEDS];//设置/清除led数据


void setup() {
  pinMode(button,INPUT_PULLUP);
  FastLED.addLeds<WS2812,DATA_PIN,GRB>(leds,NUM_LEDS);//指定led型号，leds数组，led个数
  // put your setup code here, to run once:

}


void loop() {
  keydat=digitalRead(button);//当前按键值
  if(keydat!=keysta)//倘若按键值发生变化
  {
    delay(100);//延时消抖
    if(digitalRead(button)==keydat)//按键值稳定，即按键状态不变
    {
      if(keysta==HIGH)//倘若上一次是高，则此次低为按下
      { 
        handleRGB();
      }
      keysta=keydat;//更新按键值
    }
  }
/*通过串口获取某个RGB灯信息，实测无用*/  //Serial.readBytes((char*)(&leds[1]),3);
/*通过串口获全部RGB灯信息，实测无用*/ //Serial.readBytes( (char*)leds, NUM_LEDS * 3);
}

void handleRGB()
{
        switch(dir)
        {
          case 0: 
          {
            for(i=0;i<NUM_LEDS;i++)
            {
//              leds[i].r=20;//经典方法1
//              leds[i].g=231;
//              leds[i].b=229;
//  leds[i].setRGB(96,34,18);//方法2：一次设置RGB三个值////注意：还有其他方法
/*向现有的led添加颜色,实测无用，可能不是这样用的*/  leds[i]+=CRGB(20,0,0);//
fill_solid(leds+1,30,CRGB::Green);
fill_solid(leds+31,3,CRGB::Blue);//第32个灯开始的3个灯设置为蓝色 
fill_solid(leds+34,30,CRGB::Black);//第35个灯开始的20个灯熄灭
              FastLED.show();////更新灯      
            }
            dir=1;
            break;
          }
          case 1:
          {
            for(i=NUM_LEDS-1;i>=0;i--)
            {
              leds[i]=CRGB::Black;
              FastLED.show();  
            } 
            dir=0;
            break;
          }
        }

/*实测没用，用法见上述*/  fill_solid(leds, 1, CRGB(242,231,229));//填充一个灯的办法
/*实测没用，用法见上述*/  //fill_rainbow( &(leds[1]), 0, 20);//填充一个灯的办法
   }
