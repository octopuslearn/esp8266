//@ -1,95 +0,0 @@
////3.26 14:47
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <FS.h>  

ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象

ESP8266WebServer esp8266_server(80);    // 建立网络服务器对象，该对象用于响应HTTP请求。监听端口（80）

void setup() {
  Serial.begin(9600);
  Serial.println("");
  
  wifiMulti.addAP("519", "88888888"); // 将需要连接的一系列WiFi ID和密码输入这里
  wifiMulti.addAP("创新实验室", "chuangxin"); // ESP8266-NodeMCU再启动后会扫描当前网络
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3"); // 环境查找是否有这里列出的WiFi ID。如果有
  Serial.println("Connecting ...");                            // 则尝试使用此处存储的密码进行连接。
  
  int i = 0;  
  while (wifiMulti.run() != WL_CONNECTED) { // 尝试进行wifi连接。
    delay(1000);
    Serial.print(i++); Serial.print(' ');
  }
  
  // WiFi连接成功后将通过串口监视器输出连接成功信息 
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // 通过串口监视器输出连接的WiFi名称
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); 
  
  if(SPIFFS.begin())//打开闪存文件系统
    Serial.println("SPIFFS Start.");
  else
    Serial.println("SPIFFS File.");
   
  esp8266_server.onNotFound(handleNotFound);
  esp8266_server.begin();//打开服务器

  Serial.println("HTTP server started");
  // put your setup code here, to run once:

}

void loop() {
  esp8266_server.handleClient();
  // put your main code here, to run repeatedly:

}

void handleNotFound()
{
  String Resource=esp8266_server.uri();//获取客户端请求的资源信息
  bool fileReadOK=getfileok(Resource);//判断闪存文件系统中有没有请求的资源
  Serial.print("Resource:");//客户端请求的资源信息
  Serial.println(Resource);
  
  if(!fileReadOK)//闪存文件系统中没有
    esp8266_server.send(404,"text/plain","404:Not Found.");
}

bool getfileok(String Resource)
{
  if(Resource.endsWith("/"))//如果请求的是首页信息
//////问题存在这里if后面有分号  if(Resource.endsWith("/"));//如果请求的是首页信息
    Resource="/index.html";//则访问根目录下的index.html

  String contentType=getcontentType(Resource);//获取请求资源类型
    
  if(SPIFFS.exists(Resource))//访问的资源在闪存文件系统中存在
  {
    File file=SPIFFS.open(Resource,"r");//读取请求的资源个文件对象file
    esp8266_server.streamFile(file,contentType);//将请求的资源按照相应的类型返回给浏览器
    file.close();
    return true;//访问的资源在闪存文件系统中存在，故而返回真
  }
  return false;
}

String getcontentType(String Resource_filename)
{
  if(Resource_filename.endsWith(".htm"))  return "text/html";
  else if(Resource_filename.endsWith(".html")) return "text/html";
  else if(Resource_filename.endsWith(".css")) return "text/css";
  else if(Resource_filename.endsWith(".js")) return "application/javascript";
  else if(Resource_filename.endsWith(".png")) return "image/png";
  else if(Resource_filename.endsWith(".gif")) return "image/gif";
  else if(Resource_filename.endsWith(".jpg")) return "image/jpeg";
  else if(Resource_filename.endsWith(".ico")) return "image/x-icon";
  else if(Resource_filename.endsWith(".xml")) return "text/xml";
  else if(Resource_filename.endsWith(".pdf")) return "application/x-pdf";
  else if(Resource_filename.endsWith(".zip")) return "application/x-zip";
  else if(Resource_filename.endsWith(".gz")) return "application/x-gzip";
  /*else*/  return "text/plain";//客户端请求资源在SPIFFS中没有时，返回"text/plain"  
}
