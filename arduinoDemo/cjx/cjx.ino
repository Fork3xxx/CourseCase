#include <IRremote.h>//红外
#include <IRremoteInt.h>

#include "Timer.h"        //计时器头文件
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A2 //温度 使用A2端口

Timer t;                //计时器对象
int buzzer_pin=8;     //蜂鸣器的pin
boolean buzzer_state=true;       //蜂鸣器状态
boolean hours_state=false;      //小时设置
boolean minutes_state=false;   //分钟设置
long hours=0;   //默认0小时
long minutes=600000; //默认十分钟
long Ttime;    //定时总时间
int a=1;  //count方法传入个数

#include <Adafruit_NeoPixel.h>//RGB
#define PIN 13
#define MAX_LED 9
//#define add_length sizeof(key_add)/sizeof(key_add[0])+1
Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );

int key_add[100] ;
int init_light=100;//初始亮度
int init_color = 0;//初始颜色
uint32_t color_green = strip.Color(255,0,0); 
uint32_t color_red = strip.Color(0,255,0); 
uint32_t color_blue = strip.Color(0,0,255); 
uint32_t color_yellow = strip.Color(255,255,0); 
uint32_t color_white = strip.Color(255,255,255); 
uint32_t color[] = {color_red,color_green,color_blue,color_yellow,color_white};
int length = sizeof(color)/sizeof(color[0])-1;//颜色数组长度
int add_length=0;

int RECV_PIN = 2;
int GM=A1;
int WD=A2;
bool flag;
bool flag_n=true;
int gm;
float wd;
int key;
int second;

int label;
int _add_;
int next;
bool flag_add=false;
bool flag_next=false;
int _ok;
int w=0;
IRrecv irrecv(RECV_PIN);//红外
OneWire oneWire(ONE_WIRE_BUS);//温度
DallasTemperature sensors(&oneWire);//温度
decode_results results;

/*****************语音动作相应********************************/
int yu_ying[6];
int i=0;
int j=0;
bool flag_sing=false;                  //唱歌类       0X02
bool flag_awaken=false;                //唤醒语句     0X01
bool flag_dialogue=false;              //对话类       0X03
bool flag_common_sense =false;         //常识类       0X04    
bool flag_English=false;               //英语类       0X05
bool flag_arithmetic=false;            //算术类       0X06
bool flag_weather=false;               //天气类       0X07
bool flag_qita=false;                  //其他类       0X08
//+++++++++++电机++++++++++++++++++++++++++++++++++
#define forward 1
#define backoff 2
#define leftturn 3
#define rightturn 4
#define M1 3
#define M2 11


/****************头部按键**************************************/
int RedPin = 9; //select the pin for the red LED
int BluePin =7; // select the pin for the  blue LED
int GreenPin =10;// select the pin for the green LED

int stand_ang[6] = { 512,512,512,512,894,130 };//894=512+382  130=512-382

float stand_ang_[6] = { 512,512,512,512,894,130 };//894=512+382  130=512-382
int head_key=0;

int zuohuishou[3][6] ={ 
{ 512,512,512,512,894,130 },//初始
{512,512,512,512,130,130},//举起左手
{512,512,512,512,360,130},//挥动左手
};

int niuyao_buf[2][6] = 
{
  {347,606,794,534,449,560},
  {441,703,477,208,448,559}
};

int ceyatui_bufs[6][6] = 
{
{388,574,737,528,681,225},

{344,620,826,528,630,300},
{425,540,668,529,300,720},//you

{468,641,484,328,713,389},

{384,689,496,216,630,450},
{485,593,484,370,300,720}

};

int dancefs[25][6]={
{512,512,512,512,272,130},    //0
{412,512,512,512,272,130},    //1

{512,512,512,512,894,752},    //2
{512,612,512,512,894,752},    //3

{443,512,588,512,894,720},    //左Post4
{394,512,588,512,894,720},    //左Post踮脚5

{512,581,512,436,304,130},    //右Post6
{512,630,512,436,304,130},    //右Post踮脚7

{512,512,512,512,120,130},    //举左手8
{512,512,512,512,894,904},    //举右手9

{512,581,512,436,304,130},    //10
{512,630,512,436,204,130},    //11

{443,512,588,512,894,720},    //左Post12
{394,512,588,512,894,820},    //13

{512,512,512,512,612,612},    //举左手14
{512,512,512,512,412,412},    //举右手15

{470,485,546,546,512,512},    //举左手16
{550,560,478,478,512,512},    //举右手17

{474,550,533,491,226,780},    //18
{512,512,512,512,800,224},    //19

{512,512,512,512,612,412},    //20
{412,612,512,512,794,230},    //21

{512,512,512,512,512,512},

{512,512,512,512,420,430},    //举左手
{512,512,512,512,594,604},    //举右手
};

int dancef[11][6]={
{512,512,512,512,512,130},    //
{412,512,512,512,512,130},    //

{512,512,512,512,894,512},    //
{512,612,512,512,894,512},    //

{512,512,512,512,312,712},    //
{412,612,512,512,612,412},    //

{390,558,635,509,512,512},    //
{466,634,515,389,512,512},    //

{512,662,526,506,894,894},    //
{362,512,518,498,130,130},    //

{512,512,800,224,312,712},    //
};

void one(){//飞翔姿势，踮脚双挥手
  eyeRGB(0,0,0);
  weifen(dancef[5],dancef[4],20,10);
  eyeRGB(255,0,0);
  weifen(dancef[4],dancef[5],20,10);
}

void two(){//左踮脚举高左手
  eyeRGB(0,0,0);
  weifen(dancefs[0],dancefs[1],20,10);
  eyeRGB(0,255,0);
  weifen(dancefs[1],dancefs[0],20,10);
}

void three(){//右踮脚举高右手
   eyeRGB(0,0,0);
   weifen(dancefs[2],dancefs[3],20,10);
   eyeRGB(0,0,255);
   weifen(dancefs[3],dancefs[2],20,10);
}

void four(){//左踮脚举平左手
   eyeRGB(0,0,0);
   weifen(dancef[0],dancef[1],20,10);
   eyeRGB(255,255,0);
   weifen(dancef[1],dancef[0],20,10);
}

void five(){//左踮脚举平右手
  eyeRGB(0,0,0);
  weifen(dancef[2],dancef[3],20,10);
  eyeRGB(255,0,255);
  weifen(dancef[3],dancef[2],20,10);
}

void six(){//举手
    eyeRGB(0,0,0);
    weifen(dancefs[8],dancefs[9],20,20);
    eyeRGB(0,255,255);
    weifen(dancefs[9],dancefs[8],20,20);
}

void seven(){//左Post踮脚
    eyeRGB(0,0,0);
    weifen(dancefs[4],dancefs[5],10,10);
    eyeRGB(60,60,60);
    weifen(dancefs[5],dancefs[4],10,10);
}

void eight(){//右Post踮脚
    eyeRGB(0,0,0);
    weifen(dancefs[6],dancefs[7],10,10);
    eyeRGB(0,255,255);
    weifen(dancefs[7],dancefs[6],10,10);
}

void nine1(){//测压腿
    weifen(ceyatui_bufs[5],ceyatui_bufs[4],10,10);
    weifen(ceyatui_bufs[4],ceyatui_bufs[5],10,10);
}

void nine2(){//测压腿
    weifen(ceyatui_bufs[2],ceyatui_bufs[1],10,10);
    weifen(ceyatui_bufs[1],ceyatui_bufs[2],10,10);
}

void ten(){//扭腰
    weifen(niuyao_buf[0],niuyao_buf[1],20,10);
    weifen(niuyao_buf[1],niuyao_buf[0],20,10);
}

void eleven(){
  weifen(dancefs[18],dancefs[19],10,30);
  weifen(dancefs[19],dancefs[18],10,30);
}

void twelve(){
  weifen(dancefs[20],dancefs[21],10,30);
  weifen(dancefs[21],dancefs[20],10,30);
}

void thirteen(){
  weifen(dancefs[24],dancefs[23],30,30);
  delay(300);
  weifen(dancefs[23],dancefs[24],30,30);
}

void lefr_wave_0(){
  _send(stand_ang_);
  delay(500);
  weifen(stand_ang,zuohuishou[1],30,40);
  for(int i=0;i<3;i++)
  { 
    weifen(zuohuishou[1],zuohuishou[2],20,20);
    weifen(zuohuishou[2],zuohuishou[1],20,20);
  }
  weifen(zuohuishou[1],stand_ang,50,20);
  delay(200);
}

void eyeRGB(int r,int g,int b){//RGB灯光
  analogWrite(RedPin, 255-r);
  analogWrite(GreenPin, 255-g);
  analogWrite(BluePin, 255-b);
}

bool headkey(int x){//头部按键
 switch(x){
    case 1:
      pinMode(6,INPUT_PULLUP);
      if(digitalRead(6)==LOW)
      return true;
      else
      return false;
      break;
    case 2:
      pinMode(4,INPUT_PULLUP);
      if(digitalRead(4)==LOW)
      return true;
      else
      return false;
      break;
    case 3:
      pinMode(5,INPUT_PULLUP);
      if(digitalRead(5)==LOW)
      return true;
      else
      return false;
      break;
    case 4:
      pinMode(A0,INPUT_PULLUP);
      if(digitalRead(A0)==LOW)
      return true;
      else
      return false;
      break;  
    default:
      return false;
  } 
  
}


void beat_it(){//舞蹈 1 minute
   for(int i=0;i<3;i++)
  one();
  for(int i=0;i<3;i++)
  two();
  for(int i=0;i<3;i++)
  three();
  weifen(dancefs[2],stand_ang,20,10);
  delay(500);
  for(int i=0;i<3;i++)
  four();
  for(int i=0;i<3;i++)
  five();
  weifen(dancef[2],stand_ang,20,10);
  delay(40);
  for(int i=0;i<3;i++)
  six();
  for(int i=0;i<5;i++)
  seven();
  six();
  weifen(dancefs[9],stand_ang,10,10);
  delay(500);
  for(int i=0;i<5;i++)
  eight();
  delay(500);
  for(int i=0;i<5;i++)
  nine1();
  delay(500); 
  for(int i=0;i<5;i++)
  nine2();
  delay(500);  
  for(int i=0;i<3;i++)
  ten();
  for(int i=0;i<2;i++)  //
  eleven();
  delay(500);
  for(int i=0;i<5;i++)  //
  twelve();
  delay(1000);
  thirteen();
  weifen(dancefs[24],dancefs[22],30,30);
  lefr_wave_0();
}





 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); //初始化红外遥控
  strip.begin(); 
  pinMode(GM,INPUT);
  pinMode(buzzer_pin,OUTPUT);   //设置蜂鸣器的pin为输出模式
//  pinMode(9,OUTPUT);
//  pinMode(10,OUTPUT);
  sensors.begin();
  for(int i=0;i<3;i++)
  Initialize();
  //clean_eye();
  pinMode(RedPin, OUTPUT); //端口设置成输出
  pinMode(BluePin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  eyeRGB(0,0,255);//初始化灯光 蓝眼睛
  //蜂鸣器响一下
  for(int i=0;i<200;i++){
    digitalWrite(buzzer_pin,HIGH);
    delay(2);
    digitalWrite(buzzer_pin,LOW);
    delay(2);
  }
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop() {
  t.update();         //必须在loop中调用，它会服务于计时器相关的事件
 // guangmi();
  //wendu();
  //Night_light();
   work();
   work2();
   work3();
}

void work3(){
    Serial.begin(9600);
  delay(200);
  if(Serial.available()>0){
    yu_ying[i]=Serial.read(); 
    Serial.println(yu_ying[i],HEX);
   if(yu_ying[0]==0xFF){
      i++;
    }
  } else if(yu_ying[0]==0xFF&&yu_ying[1]==0xFF&&yu_ying[2]==0x02&&yu_ying[3]==0x02&&yu_ying[4]==0x02)//唱歌类
  {
     flag_sing=true;
  }
  else if(yu_ying[0]==0xFF&&yu_ying[1]==0xFF&&yu_ying[2]==0x02&&yu_ying[3]==0x02&&yu_ying[4]==0x01)//唤醒语句
  {
     flag_awaken=true;
     flag_sing=false;
  }
   else if(yu_ying[0]==0xFF&&yu_ying[1]==0xFF&&yu_ying[2]==0x02&&yu_ying[3]==0x02&&yu_ying[4]==0x03)//对话类
  {
     flag_dialogue=true;
     flag_sing=false;
  }
   else if(yu_ying[0]==0xFF&&yu_ying[1]==0xFF&&yu_ying[2]==0x02&&yu_ying[3]==0x02&&yu_ying[4]==0x04)//常识类
  {
     flag_common_sense=true;
     flag_sing=false;
  }
   else if(yu_ying[0]==0xFF&&yu_ying[1]==0xFF&&yu_ying[2]==0x02&&yu_ying[3]==0x02&&yu_ying[4]==0x05)//英语类
  {
     flag_English=true;
     flag_sing=false;
  }
   else if(yu_ying[0]==0xFF&&yu_ying[1]==0xFF&&yu_ying[2]==0x02&&yu_ying[3]==0x02&&yu_ying[4]==0x06)//算术类
  {
     flag_arithmetic=true;
     flag_sing=false;
  }
   else if(yu_ying[0]==0xFF&&yu_ying[1]==0xFF&&yu_ying[2]==0x02&&yu_ying[3]==0x02&&yu_ying[4]==0x07)//天气类
  {
     flag_weather=true;
     flag_sing=false;
  }
   else if(yu_ying[0]==0xFF&&yu_ying[1]==0xFF&&yu_ying[2]==0x02&&yu_ying[3]==0x02&&yu_ying[4]==0x08)//其他类
  {
     flag_qita=true;
     flag_sing=false;
  }else if(i>5){
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;
    i=0;
   }else{
    i=0;
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;
   }

  if(flag_sing){
    Serial.println(222);
    delay(6000);
    eyeRGB(0,20,255);
    for(int k=0; k<1;k++){
//      dian_jiao();
    Right_wave();
    Letf_wave(); 
    left_foot_hand();
    right_foot_hand();
    two_foot_head();
    niuyao();
    beat_it();//舞蹈
    }
    delay(1000);
    flag_sing=false;
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;
    i=0;
  }

  if(flag_qita){
    Serial.println(888);
    delay(1000);
//    right_foot_hand();
    for(int i=0;i<2;i++){
      eyeRGB(0,255,0);
      delay(500);
      eyeRGB(0,0,0);
    }
    flag_qita=false;
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;
    i=0;
  }

 if(flag_awaken){
    Serial.println(111);
    delay(1000);
//    Letf_wave();
    for(int i=0;i<2;i++){
        eyeRGB(255,0,255);
        delay(500);
        eyeRGB(0,0,0);
      }
    flag_awaken=false;
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;
    i=0;
    
  }

  if(flag_dialogue){
    Serial.println(333);
    delay(1000);
//    Right_wave();
    for(int i=0;i<2;i++){
      eyeRGB(0,255,255);
      delay(500);
      eyeRGB(0,0,0);
    }
    flag_dialogue=false;
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;
    i=0;
  }

  if(flag_common_sense){
    Serial.println(444);
    delay(1000);
//    Right_wave();
    for(int i=0;i<2;i++){
      eyeRGB(255,255,255);
      delay(500);
      eyeRGB(0,0,0);
    }
    flag_common_sense=false;
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;;
    i=0;
  }

  if(flag_English){
    Serial.println(555);
    delay(1000);
//    left_foot_hand();
  for(int i=0;i<2;i++){
      eyeRGB(255,255,0);
      delay(500);
      eyeRGB(0,0,0);
    }
    flag_English=false;
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;
    i=0;
  }

 if(flag_arithmetic){
    Serial.println(666);
    delay(1000);
    Tiptoe();
    flag_arithmetic=false;
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;
    i=0;
  }
  
  if(flag_weather){
    Serial.println(777);
    delay(1000);
//    Right_wave();
   for(int i=0;i<2;i++){
        eyeRGB(255,0,0);
        delay(500);
        eyeRGB(0,0,0);
      }
    flag_weather=false;
    yu_ying[0]=0x00;
    yu_ying[4]=0x00;;
    i=0;
  }

  if(j==0){
    Initialize();
    j++;
  }
   

  
  
}


void work2(){//头部按键工作
   if(headkey(1)){//灯光切换 RGB
     head_key+=1;
     delay(500);
  }

 if(headkey(2)){//扭腰动作
  _send(stand_ang_);//发送初始化动作
  delay(500);
  for(int i=0;i<3;i++)
  ten();
  delay(500);
  _send(stand_ang_);
  delay(500);
  }
 if(headkey(3)){//侧压腿动作
  _send(stand_ang_);
  delay(500);
  for(int i=0;i<5;i++)
  nine1();
  delay(500); 
  for(int i=0;i<5;i++)
  nine2();
  _send(stand_ang_);
  delay(500);
  }
  if(headkey(4)){
     beat_it();//舞蹈
  }
  if(head_key==1){
    eyeRGB(255,0,0);
  }
  if(head_key==2){
     eyeRGB(0,255,0);
  }
  if(head_key==3){
     eyeRGB(0,0,255);
  }
  if(head_key==4){
    head_key=0;
    eyeRGB(0,0,0);
  }
}



//五大功能工作
void work(){
  if(hongwai(1)){//小夜灯
    while(!hongwai(0)){
     if(w==0){
     Rgb();
     w++;
     }
    Night_light();
    }
   clean_RGB();
    a=0;
    w=0;
  }
 
  if(hongwai(2)){//定时闹钟
     setTime();//进入闹钟模式
  }
  
  if(hongwai(3)){//温室检测
    while(!hongwai(0)){
      wendu();
      strip.setBrightness(250);
      if(wd>=30){
       strip.setPixelColor(0,0,255,0);
       strip.setPixelColor(1,0,255,0);
       strip.show();
      }else if(wd<30&&wd>25){
       strip.setPixelColor(0,0,255,255);
       strip.setPixelColor(1,0,255,255);
       strip.show();
      }else{
       strip.setPixelColor(0,0,0,255);
       strip.setPixelColor(1,0,0,255);
       strip.show();
      }
    }
    clean_RGB();
  }

  if(hongwai(4)){//照明检测
    while(!hongwai(0)){
      guangmi();
      if(gm>=900){
        eye_light(1);
      }else if(gm<900&&gm>500){
        eye_light(2);
      }else{
        eye_light(3);
      }
    }
    clean_eye();
  }
  
  if(hongwai(5)){//遥控编舞
     key=0;
     second=0;
     int i=0;
    while(!hongwai(0)){
      
      //动作组合逻辑
      if(_add_==16){
        flag_add=true;
      }
      if(key!=0&&flag_add){
//        Serial.print("key1: ");
//        Serial.println(key);
//        delay(500);
         key_add[i]=key;
//        Serial.print("key2: ");
//        Serial.println(key);
//        delay(500);
         Serial.print("key_add: ");
        Serial.println(key_add[i]);
          i++;
          flag_add=false;
          _add_=0;
           key=0;
//        Serial.print("key3: ");
//        Serial.println(key);
          Serial.println("88");
        }
        //发送次数，执行动作次数
        if(next==17){
           flag_next=true;
        }
        if(key!=0&&flag_next){
          second=key;
          Serial.print("---");
          Serial.print(second);
          Serial.println("---");
          flag_add=false;
           key=0;
        }
        if(second==0){
          second=1;
        }

      //确认发送，执行相应动作
      if(_ok==15){
        add_length=0;
        shuzu_length(key_add);
        while(second--){
          for(int q =0;q<add_length;q++){
          key=key_add[q];
          duoji_action();
          Serial.println(key_add[q],DEC);
         }
        }
        for(int j=0;j<add_length;j++){
           key_add[j]={}; 
        }
//         Serial.print("-#-");
//         Serial.print(second,DEC);
//         Serial.println("-#-");
        key=0;
       _ok=0;
       i=0;
       second=0;
      } 
    }
//    add_length=0;
//   shuzu_length(key_add);
//     for(int q =0;q<add_length;q++)
//    Serial.println(key_add[q],DEC);
//    key_add[100]={};
  }

  if(hongwai(6)){//照明检测
    while(!hongwai(0)){
      if(hongwai(11)){
         move_(forward,255);
      } 
      if(hongwai(12)){
        move_(backoff,255);
      }
      if(hongwai(13)){
        move_(leftturn,255);
      }
      if(hongwai(14)){
        move_(rightturn,255);;
      }
      if(hongwai(15)){
         move_(forward,0);
      }
    }
    clean_eye();
  }

  if(hongwai(17)){
    
  }
   
}

/**************语音动作相应***********************/
//左挥手踮脚
void left_foot_hand_w(){
   int buf5_dz1[6]={490,512,512,512,900,124};
  int buf5_dz2[6]={380,512,512,512,400,124};
  int buf5_dz3[6]={490,512,512,512,600,124};
   weifen(buf5_dz1,buf5_dz2,20,10);
   for(int i=0;i<2;i++){
    weifen(buf5_dz2,buf5_dz3,20,5);
    weifen(buf5_dz3,buf5_dz2,20,5);
   }
   weifen(buf5_dz2,buf5_dz1,20,10);
//    for(int j=0;j<2;j++){
//      sendangle(1,400);
//      sendangle(5,400);
//      delay(500);
//      sendangle(1,512);
//      sendangle(5,600);
//      delay(500);       
//    }
//    sendangle(5,900);
    delay(500);
}

//右挥手踮脚
void right_foot_hand_w(){
  int buf5_dz1[6]={490,512,512,512,900,124};
  int buf5_dz2[6]={490,624,512,512,900,624};
  int buf5_dz3[6]={490,512,512,512,900,400};
   weifen(buf5_dz1,buf5_dz2,20,10);
   for(int i=0;i<2;i++){
    weifen(buf5_dz2,buf5_dz3,20,5);
    weifen(buf5_dz3,buf5_dz2,20,5);
   }
   weifen(buf5_dz2,buf5_dz1,20,10);
    delay(500);
}


void Letf_wave(){//左挥手
  int buf5_dz1[6]={490,512,512,512,900,124};
  int buf5_dz2[6]={490,512,512,512,900,870};
  int buf5_dz3[6]={490,512,512,512,900,729};
  weifen(buf5_dz1,buf5_dz2,20,10);
  for(int i=0;i<1;i++){
  weifen(buf5_dz2,buf5_dz3,20,5);
  weifen(buf5_dz3,buf5_dz2,20,5);
//  weifen(buf5_dz2,buf5_dz1,20,10);
//    sendangle(6,870);
//    delay(500);
//    sendangle(6,729);
//    delay(500);
  }
   Initialize();
}

void Right_wave(){//右挥手
  int buf5_dz1[6]={490,512,512,512,900,124};
  int buf5_dz2[6]={490,512,512,512,205,124};
  int buf5_dz3[6]={490,512,512,512,300,124};
  weifen(buf5_dz1,buf5_dz2,20,10);
  for(int i=0;i<2;i++){
  weifen(buf5_dz2,buf5_dz3,20,5);
  weifen(buf5_dz3,buf5_dz2,20,5);
//    sendangle(5,205);
//    delay(500);
//    sendangle(5,300);
//    delay(500);
  }
   Initialize();
}

void Tiptoe(){//踮脚
  int buf5_dz1[6]={490,512,512,512,900,124};
  int buf5_dz2[6]={350,620,512,512,900,124};
     
     for(int i =0;i<1;i++){
        eyeRGB(20,255,60);
        weifen(buf5_dz1,buf5_dz2,20,10);
        eyeRGB(0,0,0);
        weifen(buf5_dz2,buf5_dz1,20,10);
      }
      delay(500); 
//  for(int i=0;i<2;i++){
//    sendangle(1,430);
//    sendangle(2,572);
//    delay(500);
//    sendangle(1,512);
//    sendangle(2,512);
//    delay(500);
//  }
   Initialize();
}

void Shaking_hands(){//摆手
  for(int i=0;i<12;i++){
    sendangle(5,450);
//    sendangle(1,380);
//   sendangle(2,620);
    sendangle(6,870);
    delay(1000);
    sendangle(5,200);
//    sendangle(1,490);
//    sendangle(2,512);  
    sendangle(6,600);
    delay(1000);
  }
   Initialize();
}

void dian_jiao(){
  int buf5_dz1[6]={490,512,512,512,900,124};
  int buf5_dz2[6]={350,620,512,512,900,124};

      for(int i =0;i<20;i++){
        weifen(buf5_dz1,buf5_dz2,20,10);
        weifen(buf5_dz2,buf5_dz1,20,10);
      }
      delay(500); 
}




/****************************************/



void shuzu_length(int a[]){//计算组合动作个数
  for(int i=0;i<100;i++){
    if(a[i]!=0)
      add_length=add_length+1;
    else
      break; 
  } 
}

void eye_light(int color){//眼睛灯光
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  switch(color){
    case 1://红色
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      break;
   case 2://红绿色
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
     break;
  case 3://绿色
     digitalWrite(10,LOW);
     digitalWrite(9,HIGH);
     break;
  default:
    clean_eye();
    break;
  }
}

void clean_eye(){//关闭眼睛
   digitalWrite(7,HIGH);
   digitalWrite(9,HIGH);
   digitalWrite(10,HIGH);
}

void clean_RGB(){//清理RGB
   strip.setPixelColor(0,0,0,0);
   strip.setPixelColor(1,0,0,0);
    strip.show();
}

void RGB_shansuo(){//闪烁提示
  //RGB闪烁提示
//  strip.setBrightness(250);
//  strip.setPixelColor(0,0,255,0);
//  strip.setPixelColor(1,0,255,0);
//  strip.show();
//  delay(500);
//  strip.setPixelColor(0,0,0,0);
//   strip.setPixelColor(1,0,0,0);
//    strip.show();

//眼睛闪烁提示
   eyeRGB(255,0,0);
   delay(500);
   eyeRGB(0,0,0);
    
}
  


void wendu(){//室温检测
  sensors.requestTemperatures();
  wd=sensors.getTempCByIndex(0);
  Serial.println(wd);  
  delay(200);
}



void guangmi(){//照明检测
  gm=analogRead(GM);
  Serial.println(gm,DEC);
  delay(500);
}

//小夜灯
void Night_light(){
if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
  switch(results.value)
  {
     //up 增加亮度
     case 0xFF18E7: RgbLight_add();RGB_shansuo();
        break;
     //down 降低亮度
      case 0xFF4AB5:RgbLight_sub();RGB_shansuo();
        break;
     //left 上个颜色
      case 0xFF10EF:color_add();RGB_shansuo();
        break;
      //right 下个颜色
      case 0xFF5AA5: color_sub();RGB_shansuo();
        break;
  }
    irrecv.resume();
  } 
}

void Rgb(){  //初始颜色亮度
//   uint32_t test = strip.Color(0,255,255); 
   strip.setPixelColor(0, color[init_color]);
   strip.setPixelColor(1, color[init_color]);
//   strip.setPixelColor(0, test);
//   strip.setPixelColor(1, test);
   strip.setBrightness(init_light);
   strip.show();
}
void RgbLight_add(){          //增加亮度
 
 init_light = init_light+50;
 Serial.println(init_light);
  if(init_light>250){init_light=250;}
  strip.setBrightness(init_light);
   delay(100);
   strip.show();
}
void RgbLight_sub(){         //降低亮度
  init_light = init_light-50;
  Serial.println(init_light);
  if(init_light==0){init_light=50;}//最低亮度
  strip.setBrightness(init_light);
  delay(100);
   strip.show();
}
void color_add(){      //上个颜色
     init_color++;
     if(init_color>length) init_color=0;
     strip.setPixelColor(0, color[init_color]);
     strip.setPixelColor(1, color[init_color]);
     strip.show();
}
void color_sub(){      //下个颜色
      init_color--;
      if(init_color<0) init_color=length;
      strip.setPixelColor(0, color[init_color]);
      strip.setPixelColor(1, color[init_color]);
      strip.show();
 
}


//红外遥控函数
bool hongwai(int r){
  flag=false;
  if (irrecv.decode(&results)) {
//    Serial.println(results.value,HEX);
     switch(results.value){
        //1
      case 0xFFA25D:
      RGB_shansuo();
       Serial.println("1");
        label=1;
        key=1;
        break;
        //2
      case 0xFF629D:
      RGB_shansuo();
       Serial.println("2");
        label=2;
        key=2;
        break;
        //3
      case 0xFFE21D:
      RGB_shansuo();
       Serial.println("3");
        label=3;
        key=3;
        break;
        //4
      case 0xFF22DD:
      RGB_shansuo();
       Serial.println("4");
        label=4;
        key=4;
        break;
        //5
      case 0xFF02FD:
      RGB_shansuo();
       Serial.println("5");
        label=5;
        key=5;
        break;
        //6
      case 0xFFC23D:
      RGB_shansuo();
      Serial.println("6");
        label=6;
        key=6;
        break;
        //7
      case 0xFFE01F:
      RGB_shansuo();
       Serial.println("7");
        label=7;
        key=7;
        break;
        //8
      case 0xFFA857:
      RGB_shansuo();
       Serial.println("8");
        label=8;
        key=8;
        break;
        //9
      case 0xFF906F:
      RGB_shansuo();
       Serial.println("9");
        label=9;
        key=9;
        break;
        //0
      case 0xFF9867:
      RGB_shansuo();
       Serial.println("0");
        label=0;
        break;
        //up
      case 0xFF18E7:
       Serial.println("up");
        label=11;
        break;
        //down
      case 0xFF4AB5:
       Serial.println("down");
        label=12;
        break;
        //left
      case 0xFF10EF:
       Serial.println("left");
        label=13;
        break;
        //right
      case 0xFF5AA5:
       Serial.println("right");
        label=14;
        break;
        //ok
      case 0xFF38C7:
      RGB_shansuo();
       Serial.println("ok");
        label=15;
        _ok=15;
        break;  
        //*
      case 0xFF6897:
      RGB_shansuo();
       Serial.println("*");
        label=16;
        _add_=16;
        break;
        //#
      case 0xFFB04F:
      RGB_shansuo();
       Serial.println("#");
        label=17;
        next=17;
        break;
        //else
      default:
        break;
     }
  
//    if(results.value==0xFFB04F){
//       Serial.println(results.value,HEX);//获取红外码值
//    }
    irrecv.resume(); // 接收下一个值
  }
    //Serial.println(key);
    if(label==r) {
      flag=true;//确定返回
      label=99;//复位
  }
  return flag;
}

//舞蹈动作
void duoji_action(){
  
  switch(key){
    case 1:
    Initialize();
    left_foot_hand();
    break;
    case 2:
    Initialize();
    right_foot_hand();
    break;
    case 3:
    Initialize();
    two_foot_head();
    break;
    case 4:
    Initialize();
    niuyao();
    break;
    case 5:
    Initialize();
    letf_hand_light_foot();
    break;
    case 6:
    Initialize();
    light_hand_letf_foot();
    break;
  }
}

//左挥手踮脚
void left_foot_hand(){
    for(int j=0;j<3;j++){
      sendangle(1,400);
      sendangle(5,400);
      delay(500);
      sendangle(1,512);
      sendangle(5,600);
      delay(500);       
    }
    sendangle(5,900);
    delay(500);
}

//右挥手踮脚
void right_foot_hand(){
   for(int j=0;j<3;j++){
      sendangle(2,624);
      sendangle(6,624);
      delay(500);
      sendangle(2,512);
      sendangle(6,400);
      delay(500);       
    }
    sendangle(6,124);
    delay(500);
}

//左右 挥手 踮脚
void two_foot_head(){
  for(int j=0;j<3;j++){
      sendangle(1,400);
      sendangle(2,624);
      sendangle(5,200);
      sendangle(6,824);
      delay(500);
      sendangle(1,512);
      sendangle(2,512);
      sendangle(5,512);
      sendangle(6,512);
      delay(500);       
    }
    Initialize();
    delay(500);
}

//扭腰
void niuyao(){
  int buf5_dz1[6]={512,512,512,512,900,150};
  int buf5_dz2[6]={397,601,611,420,512,512};
  int buf5_dz3[6]={347,606,794,534,449,560};
  int buf5_dz4[6]={441,703,477,208,448,559};

    weifen(buf5_dz1,buf5_dz3,20,10);
      for(int i =0;i<4;i++){
        weifen(buf5_dz3,buf5_dz4,20,10);
        weifen(buf5_dz4,buf5_dz3,20,10);
      }
      weifen(buf5_dz3,buf5_dz1,20,10);
      delay(500); 
}
//左挥手 有踮脚
void letf_hand_light_foot(){
   for(int j=0;j<3;j++){
      sendangle(2,624);
      sendangle(5,400);
      delay(500);
      sendangle(2,512);
      sendangle(5,600);
      delay(500);       
    }
    sendangle(5,900);
    delay(500);
}

//右挥手 左踮脚
void light_hand_letf_foot(){
  for(int j=0;j<3;j++){
      sendangle(1,400);
      sendangle(6,624);
      delay(500);
      sendangle(1,512);
      sendangle(6,400);
      delay(500);       
    }
    sendangle(6,124);
    delay(500);
}

//动作初始化
void Initialize(){
   int b=512;
  for(int i=1;i<=6;i++){
    if(i==5){
      b=900;
    }else if(i==6){
      b=150;    
    }
    sendangle(i,b);      
  } 
  delay(500); 
}

//发送6个舵机
void _send(float *buff){
  for(int i=0;i<6;i++){
    int b=i+1;
    sendangle_(b,buff[i]);
  }
}

//微分处理舵机角度
void weifen(int *buf_1,int *buf_2,int times,int wave_time){
 float buff_1[6], buff_2[6];
  float buf[6];
  for(int i =0;i<6;i++){
    buff_1[i]=(float)(*(buf_2+i)-*(buf_1+i))/times;
    buff_2[i]=(float)*(buf_1+i);
  
  }
  for(int j=0;j<times;j++){
    //次数 
    for(int q=0;q<6;q++){
      //发送角度 
      buff_2[q]+=buff_1[q];
      buf[q]=buff_2[q];
    }
    _send(buf);
  
    delay(wave_time);
  }
}

//舵机角度函数
void sendangle(int idnumber,int value)//idnumber 舵机ID  value 舵机角度
{
 
  uint16_t result=0;
  uint8_t data[6]={0};
  uint8_t i=0;
  int z=(int)value;
  
  switch(idnumber) {
    case 1:
      z=(z>300)?z:300,z=(z<600)?z:600;//600>z>300 
      break;
    case 2:
      z=(z>300)?z:300,z=(z<600)?z:600;//600>z>300
      break;
    case 3:
      z=(z>400)?z:400,z=(z<800)?z:800;//800>z>400
      break;
    case 4:
      z=(z>200)?z:400,z=(z<600)?z:600;//600>z>200
      break;
    case 5:
      z=(z>200)?z:200,z=(z<900)?z:900;//900>z>200
      break;
    case 6:
      z=(z>150)?z:150,z=(z<824)?z:824;//824>z>150
      break;
    default:
      break;
          
      
  } 
  result=z;


    Serial.begin(111100,SERIAL_8N1);
  data[0]=255;
  data[1]=255;
  data[2]=idnumber; 
  data[4]=(uint8_t)result;
  result>>=8;
  data[3]=(uint8_t)result;  
  
  data[5]=(uint8_t)(data[2]+data[3]+data[4]);
  data[5]=~data[5];

  for(i=0;i<=5;i++)
    Serial.write(data[i]);
  delay(50);
  Serial.end();
}

//减少延迟及角度限制
void sendangle_(int idnumber,int value)//idnumber 舵机ID  value 舵机角度
{
 
  uint16_t result=0;
  uint8_t data[6]={0};
  uint8_t i=0;
  int z=(int)value;
  result=z;
  Serial.begin(111100,SERIAL_8N1);
  data[0]=255;
  data[1]=255;
  data[2]=idnumber; 
  data[4]=(uint8_t)result;
  result>>=8;
  data[3]=(uint8_t)result;  
  
  data[5]=(uint8_t)(data[2]+data[3]+data[4]);
  data[5]=~data[5];

  for(i=0;i<=5;i++)
    Serial.write(data[i]);
  delay(5);
  Serial.end();

}

void move_(int direction_,int speed_){//电机驱动
  int leftSpeed = 0;
  int rightSpeed = 0;
  if(direction_ == 1){
    digitalWrite(A3,LOW);
    digitalWrite(12,HIGH);
    analogWrite(M1,speed_);
    analogWrite(M2,speed_);
  }else if(direction_ == 2){
    digitalWrite(A3,HIGH);
    digitalWrite(12,LOW);
    analogWrite(M1,speed_);
    analogWrite(M2,speed_);
  }else if(direction_ == 3){
    digitalWrite(A3,HIGH);
    digitalWrite(12,HIGH);
    analogWrite(M1,speed_);
    analogWrite(M2,speed_);
  }else if(direction_ == 4){
    digitalWrite(A3,LOW);
    digitalWrite(12,LOW);
    analogWrite(M1,speed_);
    analogWrite(M2,speed_);
  } 
}

/*——————————定时闹钟—————————————*/
void callbackfun(){//蜂鸣器闹铃
  boolean state = true;
  while(state){
        for(int i=0;i<80;i++)//输出一个频率的声音
        {
            digitalWrite(buzzer_pin,HIGH);//发声音
            delay(1);//延时1ms
            digitalWrite(buzzer_pin,LOW);
            delay(1);
        }
         for(int i=0;i<100;i++)//输出另一个频率的声音,这里的100与前面的80一样，用来控制频率，可以自己调节
        {
          digitalWrite(buzzer_pin,HIGH);
          delay(2);
          digitalWrite(buzzer_pin,LOW);
          delay(2);
        }
        if (irrecv.decode(&results)) {
          if(results.value==0xFF9867) {
            state=false;
          }
        }
}
}
void  setTime(){ //设置时间           //unsigned long 0-4,294,967,295
  boolean settime_state = true; //定时状态
  
   while(settime_state){
          if (irrecv.decode(&results)) {
                 switch(results.value){
                    //*
                  case 0xFF6897:RGB_shansuo();
                  Hours();break;
                    //#
                  case 0xFFB04F:RGB_shansuo();
                  Minutes();break;
                    //OK
                  case 0xFF38C7:RGB_shansuo();
                  StarClock();settime_state = false;break;
                  //0
                  case 0xFF9867:RGB_shansuo();
                  hours=0;
                  settime_state = false;break;
                }
          irrecv.resume();
    }
   }
}
void Hours(){   //小时
  Serial.println(111);
  boolean hours_state = true; 
  while(hours_state){
        if (irrecv.decode(&results)) {
          switch(results.value){
               //1
            case 0xFFA25D:RGB_shansuo();
            hours=3600000;break;
              //2 
            case 0xFF629D:RGB_shansuo();
            hours=7200000;break;
              //3
            case 0xFFE21D:RGB_shansuo();
            hours=10800000;break;
              //4
            case 0xFF22DD:RGB_shansuo();
            hours=14400000;break;
              //5
            case 0xFF02FD:RGB_shansuo();
            hours=18000000;break;
              //6
            case 0xFFC23D:RGB_shansuo();
            hours=21600000;break;
              //7
            case 0xFFE01F:RGB_shansuo();
            hours=25200000;break;
              //8
            case 0xFFA857:RGB_shansuo();
            hours=28800000;break;
              //9
            case 0xFF906F:RGB_shansuo();
            hours=32400000;break;
              //0
           case 0xFF9867:RGB_shansuo();
           hours=0;break;
           //OK
           case 0xFF38C7:RGB_shansuo();
           hours_state = false;break;
          }
    irrecv.resume();
     }
  }
    Serial.println(333);
}
void Minutes(){    //分钟
  boolean minutes_state = true; 
  
  while(minutes_state){
     if (irrecv.decode(&results)) {
          switch(results.value){
                  //1
                case 0xFFA25D:RGB_shansuo();
                count(1);break;
                  //2 
                case 0xFF629D:RGB_shansuo();
                count(2);break;
                  //3
                case 0xFFE21D:RGB_shansuo();
                count(3);break;
                  //4
                case 0xFF22DD:RGB_shansuo();
                count(4);break;
                  //5
                case 0xFF02FD:RGB_shansuo();
                count(5);break;
                  //6
                case 0xFFC23D:RGB_shansuo();
                count(6);break;
                  //7
                case 0xFFE01F:RGB_shansuo();
                count(7);break;
                  //8
                case 0xFFA857:RGB_shansuo();
                count(8);break;
                  //9
                case 0xFF906F:RGB_shansuo();
                count(9);break;
                  //0
               case 0xFF9867:RGB_shansuo();
               count(0);break;
                //OK
               case 0xFF38C7:RGB_shansuo();
               minutes_state = false;a=1;break;
          }
    irrecv.resume();
     }
  }
}
void StarClock(){       //开始定时
  Ttime = hours+minutes;
 t.after(Ttime,callbackfun);   //1000mm=1s   60000=1min;
 Serial.println(Ttime);
 Serial.println(666);
 
}
void count(int num){//计算秒数
  Serial.println(num);
  if(a==1){minutes = 60000 * num;a++;}    
  else if(a==2){int shi =minutes*10 ;int ge = 6000*num; minutes = shi + ge;a++;}  
  Serial.println(minutes);
}
