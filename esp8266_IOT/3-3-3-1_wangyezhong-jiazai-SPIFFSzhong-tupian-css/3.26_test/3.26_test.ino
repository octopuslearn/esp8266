#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>//联网
#include <ESP8266WiFiMulti.h>//存储多个wifi信息，multi-多
#include <FS.h>//SPIFFS，即闪存文件系统

ESP8266WebServer WebServer(80);//创建对象webserver，监视端口80,端口80即首页
ESP8266WiFiMulti  WiFiMulti;

const char *ssid1="创新实验室"; const char *password1="chuangxin";
//const char *ssid2="";  const char *password2="";
//const char *ssid3="";  const char *password3="";

void setup() {

  Serial.begin(9600);
  
  WiFiMulti.addAP("ssid1","password1");//添加wifi连接
//  WiFiMulti.addAP("ssid2","password2");
//  WiFiMulti.addAP("ssid3","password3");

  Serial.println("Connecting to ");
  int i=0;
  while(WiFiMulti.run()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print(i++);  Serial.print('\t');
  }
  Serial.print("Connected to:");
  Serial.println(WiFi.SSID());////记住是WiFi
  Serial.print("IPAdress:");
  Serial.println(WiFi.localIP());
  
  SPIFFS.begin();//打开SPIFFS
  WebServer.begin();//打开网络服务器

  WebServer.onNotFound(handleUserRequest);//处理客户请求，handle-处理，request-请求
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  WebServer.handleClient();//处理客户请求，client-请求
}

void handleUserRequest()
{
  String RequestResource=WebServer.uri();//1.获取用户请求资源
  bool fileReadOK=handleFileRead(RequestResource);//2.判断请求的资源是否存在

  if(!fileReadOK)
    WebServer.send(404,"text/plain","404:Not Found!");
}

bool handleFileRead(String path)
{  
  if(path.endsWith("/"))//如果客户端请求中存在首页
    path="/index.html";

  String contentType=getContentType(path);//3.分析请求资源的文件类型
  
  if(SPIFFS.exists(path))//4.判断请求的文件类型是否存在
  {
    File file=SPIFFS.open(path,"r");//5.读取请求的文件类型的内容 创建文件对象，并设置为读////注意对SPIFFS的操作时open   
    WebServer.streamFile(file,contentType);//6.发送请求的文件 使用文件内容发送响应stream,即发送相应体，file-存储与响应信息的闪存文件对象，contentType-响应信息类型
    file.close();//关闭SPIFFS
    return true;//2.1请求存在返回真
  }
  return false;
  
}

String getContentType(String filename)
{
  if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";  
  else 
    return "text/plain";
}
