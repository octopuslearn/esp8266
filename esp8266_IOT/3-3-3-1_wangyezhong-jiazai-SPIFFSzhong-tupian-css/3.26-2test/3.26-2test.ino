#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>//联网
#include <ESP8266WiFiMulti.h>//存储多个wifi信息，multi-多
#include <FS.h>//SPIFFS，即闪存文件系统

ESP8266WebServer  WebServer(80);
ESP8266WiFiMulti  WiFiMulti;

const char *ssid="创新实验室"; const char *password="chuangxin";

void setup() {
  Serial.begin(9600);
  
  WiFiMulti.addAP("ssid","password");

  Serial.println("Connecting to");
  int i=0;
  while(WiFiMulti.run()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print(i++);  Serial.print(' ');
  }
  Serial.println("Connected to:");
  Serial.print(WiFi.SSID());
  Serial.println("IP:");
  Serial.print(WiFi.localIP());


  SPIFFS.begin();
  WebServer.begin();
  WebServer.onNotFound(handleUserRequst);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  WebServer.handleClient();
}

void handleUserRequst()
{
  String RequstResource=WebServer.uri();
  bool fileReadOK=getfileReadOK(RequstResource);

  if(!fileReadOK)
    WebServer.send(404,"text/plain","Not Found!");
}

bool getfileReadOK(String path)
////形参和实参的名字不能相同bool getfileReadOK(String RequstResource)////形参和实参的名字不能相同
{ 
  String contentType=getycontentType(path);
  if(SPIFFS.exists(path))
  {
    File file=SPIFFS.open(path,"r");
    WebServer.streamFile(file,contentType);
    return true;
  }
  return false;

  if(path.endsWith("/"))
    path="/index.html";
}

String getycontentType(String filename)
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
