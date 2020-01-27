#include<SD.h>
#include<Keyboard.h>
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  
//SCL-3 SDA-2
//tf 卡接口 CS-10 MOSI-16 SCK-15 MISO-14


File myFile;

int buff; //asc2码容器


const String vision = String("Daids 0.3"); //版本号

void setup()
{
  Serial.begin(9600);
////init_OLED///// ////////////////////////////
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
  u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
  u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
  u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
  u8g.setHiColorByRGB(255,255,255);
  }
  draw("OLED INITED");
  delay(100);

////init tf///////////////////////////////////
  pinMode(4,OUTPUT);//CS
  if(!SD.begin(4))
  {
    Serial.println("初始化失败");
    draw("SD_Init Error!");
    delay(100);
    return;
  }

  myFile = SD.open("KEYCODE.TXT");

  if(myFile)
  {
    myFile.close(); 
  }
  else
  { 
    while(1){
    Serial.println("打开文件失败");
    draw("Failed KCODE!");
    }
  }

  Serial.println("初始化完成");
  draw("SD_Init_Done!");
  delay(100);
  draw("Ready!");


////press bottom///////////////////////////
  pinMode(7,INPUT_PULLUP);
  while(digitalRead(7));
    draw("go");
       
    
}



void loop()
{
myFile = SD.open("KEYCODE.TXT");
if(myFile)
      {
  //Serial.print("写入SD");
        Serial.print("读入SD");
  //draw("Write_SD!");
        draw("Strat Loop!");
        while(myFile.available())
        {
          // Serial.write(myFile.read());//每次读取1B数据
        //////今后我们在这个区域填充我们判断代码Start///////
         if(myFile.read()==33)//读出感叹号
         {
           Serial.println("START");
           buff = myFile.read();

            ////////读出A,按下////////
            ///默认格式  !A89;  
            if (buff==65) 
            {         
               draw("AN");
               Serial.println("按下");

               String key="";
               buff=myFile.read();
               while(buff != 59)
               {
                  key += char(buff);
                  buff=myFile.read();
               }
               // draw(key);
               Serial.println(key);
               Keyboard.write(key.toInt());
               delay(random(0,20));
               // Keyboard.press(key.toInt());
               // delay(100);
               // Keyboard.release(key.toInt());
            }
            

            ////////读出N,按住////////
            ///默认格式  !N89&1000; 
            else if(buff==78)

            {
               Serial.println("按住");
               draw("Press");

               String key="";
               buff=myFile.read();

               while(buff != 38)
               {
                  key += char(buff);
                  buff=myFile.read();
               }
               Keyboard.press(key.toInt());

               String times="";
               buff=myFile.read();
               while(buff != 59)
               {
                  times += char(buff);
                  buff=myFile.read();
               }
               // draw(times);
               delay(times.toInt());
               delay(random(0,60));
               Serial.println(times);
               Keyboard.releaseAll();
            }
            ////////读出J,随机按下////////
            else if(buff==74)
            {
               Serial.println("随机按下");
               draw("SJD");

               String key="";
               buff=myFile.read();
               while(buff != 59)
               {
                  key += char(buff);
                  buff=myFile.read();
               }
               if(random(0,10)>5){
                   Keyboard.press(key.toInt());
                   delay(220);
                   delay(random(0,60));
                   Keyboard.release(key.toInt());
               }
               delay(10);

            }

            ////////读出D,等待////////
            else if(buff==68)
            {
               Serial.println("等待");
               draw("DEN");

               String times="";
               buff=myFile.read();
               while(buff != 59)
               {
                  times += char(buff);
                  buff=myFile.read();
               }
               // draw(times);
               delay(times.toInt());
               delay(random(0,60));
             }
            
            ////////读出P,随机等待////////
            else if(buff==80)
            {
               Serial.println("随机等待");
               draw("DEN");

               String times="";
               buff=myFile.read();
               while(buff != 59)
               {
                  times += char(buff);
                  buff=myFile.read();
               }
               // draw(times);
               delay(random(0,times.toInt()));
             }

            ////////读出E,停止////////
            else if(buff==69)
            {
               Serial.println("停止");
               draw("STOP");
               while (1);


             }

               // //读出E,结束
               // case 69:

               // //读出L,循环
               // case 76:
           }

         }
        //////今后我们在这个区域填充我们判断代码End/////// 
          
      
// myFile.println("Hello_KEYCODE!");//16 字节 [4.00 KB (4,096 字节)]
/////////
        myFile.close();
        Serial.println("完成");
        draw("done!");
  //draw("SD_Done!");
    }
    else
    {
      Serial.println("错误!");
      draw("Write_SD_Error!");
    }


}



//OLED void
void draw(char s[])
{
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.setPrintPos(0, 22); 
    u8g.print(vision);
    u8g.setFont(u8g_font_unifont);
    u8g.setPrintPos(0, 44); 
    u8g.print(s); 
  } while( u8g.nextPage() );
} 

void drawint(int s)
{
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.setPrintPos(0, 22); 
    u8g.print(vision);
    u8g.setFont(u8g_font_unifont);
    u8g.setPrintPos(0, 44); 
    u8g.print(s); 
  } while( u8g.nextPage() );
}
