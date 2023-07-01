#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   // 使用WiFiMulti库 
#include <ESP8266WebServer.h>   // 使用WebServer库

#define led 2

ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是 'wifiMulti'
 
ESP8266WebServer server(80); 

IPAddress local_IP(192, 168, 1, 147);
IPAddress getway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress DNS(192, 168, 1, 1);

void setup() {
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  
  Serial.begin(9600);          // 启动串口通讯
  Serial.println("");

  if(!WiFi.config(local_IP, getway, subnet))//第一步：此处设置esp8266网络环境，ESP8266连接后的IP地址，路由器IP，子网掩码
    Serial.println("ESP8266网络环境配置成功");
  wifiMulti.addAP("创新实验室", "chuangxin"); // 将需要连接的一系列WiFi ID和密码输入这里
//  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2"); // ESP8266-NodeMCU再启动后会扫描当前网络
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

  Serial.println("1");////调试
  server.on("/update",hanleClientWiFi);//处理/update请求
  Serial.println("2");////调试
  
  server.begin();//打开网络服务器
  
  Serial.println("ESP8266网络服务器打开成功");
  
  
  // put your setup code here, to run once:

}

void loop() {
  Serial.println("3");////调试
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void hanleClientWiFi()
{
  Serial.println("4");////调试
  int buttonValue=server.arg("button").toInt();//第二步：获取特定的客户端的信息////注意后面有括号
  int intValue=server.arg("int").toInt();

  Serial.println("5");////调试
  server.send(200,"text/plain","获取信息成功");//第三步：获取信息成功后，发送成功

  buttonValue==0 ? digitalWrite(led,LOW) : digitalWrite(led,HIGH);
    // 通过串口监视器输出获取到的变量数值 
  Serial.println("6");////调试
  Serial.print("intValue = ");  Serial.println(intValue); 
  Serial.print("buttonValue = ");  Serial.println(buttonValue);   
  Serial.println("================="); 
}
