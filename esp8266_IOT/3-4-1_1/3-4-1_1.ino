#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wiFiClient;//////注意：与教程库不同 为解决库版本不同eSP8266HTTPClient.begin(wiFiClient,URL);

const char *ssid1="创新实验室"; const char *password1="chuangxin";
////const char *URL="http://www.example.com";
#define URL "http://www.example.com"

void setup() {
  Serial.begin(9600);
  
  WiFi.mode(WIFI_STA);//无线终端模式 返回值true false ESP8266WiFiGeneric库
  Serial.println(WiFi.mode(WIFI_STA));
  
  WiFi.begin(ssid1,password1);//ESP8266WiFiSTA库 连接wifi

  int i=0;
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print(i++);  Serial.print(' ');
  }
   Serial.println("Wifi Connected!");
  // put your setup code here, to run once:

  httpClientRequst();
}

void loop() {}

void httpClientRequst()
{
////    ESP8266HTTPClient  eSP8266HTTPClient;
    HTTPClient  eSP8266HTTPClient;
    eSP8266HTTPClient.begin(wiFiClient,URL);//////注意此处与教程库不同
    Serial.print("URL:"); Serial.println(URL);    
    
    int httpcode=eSP8266HTTPClient.GET();//向服务器发送GET请求
    Serial.print("Send GET requst to URL:"); Serial.println(URL);
    if(httpcode==HTTP_CODE_OK)
    {     
      String responsePayload=eSP8266HTTPClient.getString();//responsePayload-response-响应Payload-有效负载
      Serial.print("Server Response Payload:"); Serial.println(responsePayload);
    }
    Serial.println(httpcode);

  eSP8266HTTPClient.end();//关闭与服务器连接
}
