//#include <ESP8266WiFi.h>
//#include <ESP8266WiFiMulti.h>
//
//ESP8266WiFiMulti wifiMulti;
//
//#define button 0
//const char* local_IP="192.168.0.147";
//const int httpPort=80;//即将连接的服务器端口
//
//int clientIntVlaue;
//bool buttonState;
//
//
//void setup()
//{
//  pinMode(button,INPUT_PULLUP);
//  
//  Serial.begin(9600);
//  
//  Serial.println("");
//
//  wifiMulti.addAP("创新实验室", "chuangxin"); // 将需要连接的一系列WiFi ID和密码输入这里
//  wifiMulti.addAP("519", "88888888"); // ESP8266-NodeMCU再启动后会扫描当前网络
////  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3"); // 环境查找是否有这里列出的WiFi ID。如果有
//  Serial.println("Connecting ...");                            // 则尝试使用此处存储的密码进行连接。
//  
//  // 尝试进行wifi连接。
//  while (wifiMulti.run() != WL_CONNECTED) { 
//    delay(250);
//    Serial.print('.');
//  }
// 
//  // WiFi连接成功后将通过串口监视器输出连接成功信息 
//  Serial.println('\n');
//  Serial.print("Connected to ");
//  Serial.println(WiFi.SSID());              // 通过串口监视器输出连接的WiFi名称
//  Serial.print("IP address:\t");
//  Serial.println(WiFi.localIP());           // 通过串口监视器输出ESP8266-NodeMCU的IP
//}
//
//void loop()
//{
//  buttonState=digitalRead(button);
//  clientIntVlaue+=2;
//  RequestReource(); 
//  Serial.println("A");////调试 
//  delay(1000);
//}
//
//void RequestReource()
//{
//  WiFiClient client;//创建对象
//  /*客户端请求信息*/
//  String url = "/update?int=" + String(clientIntVlaue) +//String（）是数据类型转换
//             "&buttons=" + String(buttonState);
//  Serial.println("B");////调试
//  /*http请求*/
//  String httpRequst = String("GET ") + url + " HTTP/1.1\r\n" +
//                      "Host: " + local_IP + "\r\n" +
//                      "Connection: close\r\n" +
//                      "\r\n";
//  Serial.println("C");////调试
//  if(client.connect(local_IP, httpPort))//连接服务器，local_IP-服务器IP，httpPort-访问端口号
//  {  Serial.println("客户端连接服务器成功");
//    Serial.println("D");////调试
//    client.print(httpRequst);//客户端发送HTTP请求
//    Serial.println("E");////调试
//    Serial.println(httpRequst);
//  }
//  else 
//    Serial.println("客户端连接服务器失败");
//
//  client.stop();//关闭客户端
//}

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

#define button 0
const char *local_IP="192.168.0.147";
const int httpPort=80;//即将连接的服务器端口

int clientIntVlaue;
bool buttonState;


void setup()
{
  pinMode(button,INPUT_PULLUP);
  
  Serial.begin(9600);
  
  Serial.println(" ");

  wifiMulti.addAP("创新实验室", "chuangxin"); // 将需要连接的一系列WiFi ID和密码输入这里
  wifiMulti.addAP("519","88888888"); // ESP8266-NodeMCU再启动后会扫描当前网络
//  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3"); // 环境查找是否有这里列出的WiFi ID。如果有
  Serial.println("Connecting ...");                            // 则尝试使用此处存储的密码进行连接。
  
  // 尝试进行wifi连接。
  while (wifiMulti.run() != WL_CONNECTED) { 
    delay(250);
    Serial.print('.');
  }
 
  // WiFi连接成功后将通过串口监视器输出连接成功信息 
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // 通过串口监视器输出连接的WiFi名称
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // 通过串口监视器输出ESP8266-NodeMCU的IP
}

void loop()
{
  buttonState=digitalRead(button);
  clientIntVlaue+=2;
  RequestReource(); 
  delay(1000);
}

void RequestReource()
{
  WiFiClient client;//创建对象
  /*客户端请求信息*/
  String url = "/update?int="+String(clientIntVlaue)+//String（）是数据类型转换
             "&buttons="+String(buttonState);
  /*http请求*/
  String httpRequst = String("GET ")+url+" HTTP/1.1\r\n"+
                      "Host:"+local_IP+"\r\n"+
                      "Connection:close\r\n"+
                      "\r\n";
  if(client.connect(local_IP, httpPort))//连接服务器，local_IP-服务器IP，httpPort-访问端口号
  {  Serial.println("客户端连接服务器成功");
    client.print(httpRequst);//客户端发送HTTP请求
    Serial.println(httpRequst);
  }
  else 
    Serial.println("客户端连接服务器失败");

  client.stop();//关闭客户端
}
