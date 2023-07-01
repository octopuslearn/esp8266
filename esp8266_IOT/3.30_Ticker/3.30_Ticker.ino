#include <Ticker.h>

Ticker ticker1;
Ticker ticker2;

#define led 2

int i=0,o=0;//测试用 

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  // put your setup code here, to run once:
  ticker1.attach(1,print_test);
  ticker2.attach_ms(1000,handleled,3);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void print_test()
{
  Serial.println(i++);
}

void handleled(int count)
{ 
  o++;
  if(o>=count)
    ticker2.detach();//关闭多任务处理，即定时器 
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
  digitalWrite(led,HIGH);
}
