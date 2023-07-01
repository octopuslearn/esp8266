#include <FS.h>//文件系统SPIFFS头文件

void setup() {
  String file_name="/zhangyu.txt";//字符串存储文件地址 在根目录下zhangyu.txt

  Serial.begin(9600);
/*以下为写入*/
  SPIFFS.format();//格式化SPIFFS
  if(SPIFFS.begin())//打开SPIFFS,打开后才能进行操作
    Serial.println("SPIFFS Start.");
  else 
    Serial.println("SPIFFS Filed to Start.");
  
  // put your setup code here, to run once:
  Serial.println("SPIFFS Format Succcessed.");

  File dataFile=SPIFFS.open(file_name,"w");//创建dataFile对象 创建file_name文件，并设置为写
  dataFile.println("I hate you.");//写入////创建对象后对SPIFFS操作时用对象名称dataFile
  dataFile.close();//关闭SPIFFS

  Serial.println("Finish Writing data to SPIFFS.");


/*以下为读取*/
  if(SPIFFS.begin())//打开SPIFFS,打开后才能进行操作
    Serial.println("SPIFFS Start.");
  else 
    Serial.println("SPIFFS Filed to Start.");

  if(SPIFFS.exists(file_name))//倘若（exists）存在file_name文件
    Serial.println("Found.");
  else
    Serial.println("Not Found.");

  File datafiles=SPIFFS.open(file_name,"r");//创建对象datafiles,创建file_name并设置为读
  for(int i=0;i<datafiles.size();i++)//一个个全部读出来
    Serial.print((char)datafiles.read());

  datafiles.close();//关闭文件系统
  Serial.println("Finish Reading to file_name");
}

void loop() {
  // put your main code here, to run repeatedly:

}
