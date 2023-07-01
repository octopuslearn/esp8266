#include <FS.h>//文件系统SPIFFS头文件

void setup() {
  String file_name="/weidade/buse/zhangyu.txt";//字符串存储文件地址 在根目录下创建weidade文件夹 zhangyu.txt
  String file_name1="/weidade/data.txt";//第二个txt文件
  String folder_name="/weidade";//字符串存储目录，即要读取的文件夹
  String folder_name1="/weidade";//第二个目录

  Serial.begin(9600);
/*以下为写入*/
  SPIFFS.format();//格式化SPIFFS
  if(SPIFFS.begin())//打开SPIFFS,打开后才能进行操作
    Serial.println("SPIFFS Start.");
  else 
    Serial.println("SPIFFS Filed to Start.");
  
  // put your setup code here, to run once:
  Serial.println("SPIFFS Format Succcessed.");

  File dataFile_w=SPIFFS.open(file_name,"w");//创建dataFile对象 创建file_name文件，并设置为写
  File dataFile_w1=SPIFFS.open(file_name1,"w");//第二个txt文件

  dataFile_w.print("I hate you.");//写入////创建对象后对SPIFFS操作时用对象名称dataFile
  dataFile_w1.print("No!No!");//第二个txt文件
  dataFile_w.close();//关闭SPIFFS

  Serial.println("Finish Writing data to SPIFFS.");




  if(SPIFFS.begin())//打开SPIFFS,打开后才能进行操作
    Serial.println("SPIFFS Start.");
  else 
    Serial.println("SPIFFS Filed to Start.");

  if(SPIFFS.exists(file_name))//倘若（exists）存在file_name文件
    Serial.println("Found file_name.");
  else
    Serial.println("Not Found file_name.");
  if(SPIFFS.exists(file_name1))//倘若（exists）存在file_name文件//第二个txt文件
    Serial.println("Found file_name1.");
  else
    Serial.println("Not Found file_name1.");
/*以下为向文件系统添加信息,////添加信息不会覆盖*/
  File datafile_a=SPIFFS.open(file_name,"a");//向file_name中添加信息
  datafile_a.println("Nobody likes you!");
  Serial.println("Finish adding.");
////???/*以下为从SPIFFS中删除文件，此处删除第二个目录*/  ////???不能删除目录，问如何删除目录
  if(SPIFFS.remove(folder_name1))
    Serial.println("folder_name1 remove success");
  else
    Serial.println("folder_name1 remove file");

/*以下为读取目录内容*/
  Dir dir=SPIFFS.openDir(folder_name);//建立目录对象dir，创建目录folder_name
  while(dir.next())//查找目录中是否有下一个文件，会将/weidade中的所有文件名全部弄出来////不断的重复dir.next()，即将指针不断指向下一个，故而文件一个个的输出了文件名
    Serial.println(dir.fileName());//有的话输出文件名

/*以下为从SPIFFS中删除文件，此处删除第二个文件*/
  if(SPIFFS.remove(file_name1))
    Serial.println("file_name1 remove success");
  else
    Serial.println("file_name1 remove file");

/*以下为读取信息*/
  File datafile_r=SPIFFS.open(file_name,"r");//创建对象datafiles,创建file_name并设置为读
  File datafile_r1=SPIFFS.open(file_name1,"r");//第二个txt文件
  
  for(int i=0;i<datafile_r.size();i++)//一个个全部读出来
    Serial.print((char)datafile_r.read());
  for(int i=0;i<datafile_r1.size();i++)//一个个全部读出来//第二个txt文件
    Serial.print((char)datafile_r1.read());

  datafile_r.close();//关闭文件系统
  Serial.println("Finish Reading to file_name");
}

void loop() {
  // put your main code here, to run repeatedly:

}
