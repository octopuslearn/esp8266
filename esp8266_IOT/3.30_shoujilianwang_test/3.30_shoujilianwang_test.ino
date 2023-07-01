

//
//#include <ESP8266WiFi.h>          
//#include <ESP8266WiFiMulti.h>   //  ESP8266WiFiMulti库
//#include <ESP8266WebServer.h>
//
//#define LED_BUILTIN 2
//
//ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象
//ESP8266WebServer esp8266_server(80); 
//
//void setup() {
//  // put your setup code here, to run once:
//  pinMode(LED_BUILTIN,OUTPUT);
//  
//  Serial.begin(9600);
//  Serial.println(" ");
//  
//  wifiMulti.addAP("519", "88888888"); // 将需要连接的一系列WiFi ID和密码输入这里
//  wifiMulti.addAP("创新实验室", "chuangxin"); // ESP8266-NodeMCU再启动后会扫描当前网络
//  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3"); // 环境查找是否有这里列出的WiFi ID。如果有
//  Serial.println("Connecting ...");                            // 则尝试使用此处存储的密码进行连接。
  
//  int i = 0;  
//  while (wifiMulti.run() != WL_CONNECTED) { // 尝试进行wifi连接。
//    delay(1000);
//    Serial.print(i++); Serial.print(' ');
//  }
//  
//  // WiFi连接成功后将通过串口监视器输出连接成功信息 
//  Serial.println('\n');
//  Serial.print("Connected to ");
//  Serial.println(WiFi.SSID());              // 通过串口监视器输出连接的WiFi名称
//  Serial.print("IP address:\t");
//  Serial.println(WiFi.localIP()); 
//
//  esp8266_server.begin();//打开服务器
//////错误：记错  esp8266_server.on(200,"/",handleled);
//  esp8266_server.on("/",HTTP_GET,handleRoot);
//  esp8266_server.on("/led",HTTP_POST,handleled);
//  esp8266_server.onNotFound(hanleNotFound);
//}
//
//void loop() {
//  esp8266_server.handleClient();
//  // put your main code here, to run repeatedly:
//
//}
//
//void handleRoot()
//{
//////错误：请求首页时建立了按钮  esp8266_server.send(200,"text/plain","successful");
//  esp8266_server.send(200, "text/html", "<form action=\"/led\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
//}
//
//void handleled()
//{
//  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
//  esp8266_server.sendHeader("Location","/");//跳转回根目录，即首页
//  esp8266_server.send(303);
//}
//
//void hanleNotFound()
//{
//  esp8266_server.send(404,"text/plain","404:Not Found!");
//}




//
//#include <ESP8266WiFi.h>        // 本程序使用 ESP8266WiFi库
//#include <ESP8266WiFiMulti.h>   //  ESP8266WiFiMulti库
//#include <ESP8266WebServer.h>   //  ESP8266WebServer库
//#include <WiFiManager.h>
//
//
//#define LED_BUILTIN 2
//WiFiManager wiFiManager;
//ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是 'wifiMulti'
// 
//ESP8266WebServer esp8266_server(80);// 建立网络服务器对象，该对象用于响应HTTP请求。监听端口（80）
// 
//void setup(void){
//  Serial.begin(9600);   // 启动串口通讯
// 
//  pinMode(LED_BUILTIN, OUTPUT); //设置内置LED引脚为输出模式以便控制LED
//  
//  wifiMulti.addAP("519", "88888888"); // 将需要连接的一系列WiFi ID和密码输入这里
////  wifiMulti.addAP("创新实验室", "chuangxin"); // ESP8266-NodeMCU再启动后会扫描当前网络
//  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3"); // 环境查找是否有这里列出的WiFi ID。如果有
//  Serial.println("Connecting ...");                            // 则尝试使用此处存储的密码进行连接。
//  
//  int i = 0;                                 
//  while (wifiMulti.run() != WL_CONNECTED) {  // 此处的wifiMulti.run()是重点。通过wifiMulti.run()，NodeMCU将会在当前
//    delay(1000);                             // 环境中搜索addAP函数所存储的WiFi。如果搜到多个存储的WiFi那么NodeMCU
//    Serial.print(i++); Serial.print(' ');    // 将会连接信号最强的那一个WiFi信号。
//  }                                          // 一旦连接WiFI成功，wifiMulti.run()将会返回“WL_CONNECTED”。这也是
//                                             // 此处while循环判断是否跳出循环的条件。
//  
//  // WiFi连接成功后将通过串口监视器输出连接成功信息
//  wiFiManager.autoConnect("AutoConnectAP");
//   
//  Serial.println('\n');
//  Serial.print("Connected to ");
//  Serial.println(WiFi.SSID());              // 通过串口监视器输出连接的WiFi名称
//  Serial.print("IP address:\t");
//  Serial.println(WiFi.localIP());           // 通过串口监视器输出ESP8266-NodeMCU的IP
// 
//  esp8266_server.begin();                           // 启动网站服务
//  esp8266_server.on("/", HTTP_GET, handleRoot);     // 设置服务器根目录即'/'的函数'handleRoot'
//  esp8266_server.on("/LED", HTTP_POST, handleLED);  // 设置处理LED控制请求的函数'handleLED'
//  esp8266_server.onNotFound(handleNotFound);        // 设置处理404情况的函数'handleNotFound'
// 
//  Serial.println("HTTP esp8266_server started");//  告知用户ESP8266网络服务功能已经启动
//}
//
//void loop(void){
//  esp8266_server.handleClient();                     // 检查http服务器访问
//}
// 
///*设置服务器根目录即'/'的函数'handleRoot'
//  该函数的作用是每当有客户端访问NodeMCU服务器根目录时，
//  NodeMCU都会向访问设备发送 HTTP 状态 200 (Ok) 这是send函数的第一个参数。
//  同时NodeMCU还会向浏览器发送HTML代码，以下示例中send函数中第三个参数，
//  也就是双引号中的内容就是NodeMCU发送的HTML代码。该代码可在网页中产生LED控制按钮。 
//  当用户按下按钮时，浏览器将会向NodeMCU的/LED页面发送HTTP请求，请求方式为POST。
//  NodeMCU接收到此请求后将会执行handleLED函数内容*/
//void handleRoot() {       
//  esp8266_server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
//}
// 
////处理LED控制请求的函数'handleLED'
//void handleLED() {                          
//  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));// 改变LED的点亮或者熄灭状态
//  esp8266_server.sendHeader("Location","/");          // 跳转回页面根目录
//  esp8266_server.send(303);                           // 发送Http相应代码303 跳转  
//}
// 
//// 设置处理404情况的函数'handleNotFound'
//void handleNotFound(){
//  esp8266_server.send(404, "text/plain", "404: Not found"); // 发送 HTTP 状态 404 (未找到页面) 并向浏览器发送文字 "404: Not found"
//}

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
         
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#include <WiFiClient.h>

WiFiClient wiFiClient;

 
// 测试HTTP请求用的URL。注意网址前面必须添加"http://"
#define URL "http://www.example.com"
 
void setup() {
  //初始化串口设置
  Serial.begin(9600);
 
  // 建立WiFiManager对象
  WiFiManager wifiManager;
  
  // 自动连接WiFi。以下语句的参数是连接ESP8266时的WiFi名称
  wifiManager.autoConnect("AutoConnectAP");
  
  Serial.print("WiFi Connected!");
  
  httpClientRequest();  
}
 
void loop() {}
 
// 发送HTTP请求并且将服务器响应通过串口输出
void httpClientRequest(){
 
  //重点1 创建 HTTPClient 对象
  HTTPClient httpClient;
 
  //重点2 通过begin函数配置请求地址。此处也可以不使用端口号和PATH而单纯的
  httpClient.begin(wiFiClient,URL); 
  Serial.print("URL: "); Serial.println(URL);
 
  //重点3 通过GET函数启动连接并发送HTTP请求
  int httpCode = httpClient.GET();
  Serial.print("Send GET request to URL: ");
  Serial.println(URL);
  
  //重点4. 如果服务器响应HTTP_CODE_OK(200)则从服务器获取响应体信息并通过串口输出
  //如果服务器不响应HTTP_CODE_OK(200)则将服务器响应状态码通过串口输出
  if (httpCode == HTTP_CODE_OK) {
    // 使用getString函数获取服务器响应体内容
    String responsePayload = httpClient.getString();
    Serial.println("Server Response Payload: ");
    Serial.println(responsePayload);
  } else {
    Serial.println("Server Respose Code：");
    Serial.println(httpCode);
  }
 
  //重点5. 关闭ESP8266与服务器连接
  httpClient.end();
}
//
//#include <ESP8266WiFi.h>          
//#include <DNSServer.h>
//#include <ESP8266WebServer.h>
//#include <WiFiManager.h>         
// 
//void setup() {
//  Serial.begin(9600);       
//  // 建立WiFiManager对象
//  WiFiManager wifiManager;
//  
//  // 清除ESP8266所存储的WiFi连接信息以便测试WiFiManager工作效果
//  wifiManager.resetSettings();
//  Serial.println("ESP8266 WiFi Settings Cleared");
//}
// 
//void loop() {}
