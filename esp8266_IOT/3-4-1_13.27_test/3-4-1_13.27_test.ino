#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

HTTPClient hTTPClient;
WiFiClient wiFiClient;
//#define URL "http://www.taichi-maker.com"
#define URL ""

const char *ssid1="创新实验室"; const char *password1="chuangxin";

void setup() {
  Serial.begin(9600);
  
  WiFi.mode(WIFI_STA);//无线终端模式
  WiFi.begin(ssid1,password1);//打开客户端，wifi名和密码

  int i=0;
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print(i++);  Serial.print(' ');
  }
  Serial.print("WiFi Connected!");
  
  handleClient();//处理请求
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void handleClient()
{
  hTTPClient.begin(wiFiClient,URL);//请求网站，wifilclient是新的库
  int httpcode=hTTPClient.GET();
  if(httpcode==HTTP_CODE_OK)
  {
    String httpContent=hTTPClient.getString();//获取响应体
    Serial.print("URL:"); Serial.println(URL);
    Serial.println(httpContent);
  }
   Serial.println(httpcode);

   hTTPClient.end();
}
