/*
 * 声光播放器驱动程序
 *    1. 声光设备硬件初始化设置
 *    2. 播放音乐，并同步灯光闪烁
 *    3. 静音功能
 * author: xxx
 * date:2020.06.21
 */
 //Arduino UNO给LED和Buzzer分配的端口：
 #define LED 13
 #define Buzzer 10
 #define Button 2

 //端口初始化
 void Init_Buzzer()
 {
      pinMode(LED, OUTPUT);
      pinMode(Buzzer, OUTPUT);
      pinMode(Button, INPUT_PULLUP);
 }

 /*
  * 声光播放模块
  * 功能： 播放音乐，并让LED伴随闪烁
  */

  //引入音调频率头文件
  #include "pitches.h"

// notes in the melody:
int melody[] = {
  FH2,FH3,FH5,FH1,FH2,FH3,FH5,FH1,
  FH2,FH3,FH5,FH6,FH2,FH3,F6,FH1,
  FH2,FH3,FH5,FH1,FH2,FH3,FH5,FH1,
  FH2,FH3,FH5,FH6,FH2,FH3,F6,FH1,
  F2,F3,F5,F1,F2,F3,F5,F1,
  F2,F3,F5,F1,F2,F3,  
  FL3,FL5,FL6,F1,F2,F2,F1,FL5,FL4,FL3,FL5,F1,
  F1,FL7,FL6,F1,FL7,FL5,FL5,FL5
};
int melody2[] = {
  NOTE_C0,NOTE_C0,NOTE_C0,NOTE_C5,NOTE_C3,
NOTE_C3,NOTE_C5,NOTE_C2,NOTE_C2,NOTE_C3,NOTE_C2,
NOTE_C2,NOTE_C1,NOTE_C1,NOTE_C0,NOTE_C1,NOTE_CL7,
NOTE_CL6,NOTE_CL7,NOTE_C1,NOTE_CL7,NOTE_C1,NOTE_C1
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
float noteDurations[] = {
  0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
  0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
  0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
  0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
  0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
  0.5,0.5,0.5,0.5,0.5,0.5,
  0.5,0.5,0.7,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,1,
  0.5,0.5,0.7,0.7,.25,0.5,0.25,0.5
};

float duration[]= 
{ 
1,1,1,0.5+0.5,//听见
1,0.5+0.5,1,0.5+0.5,//冬天的离
0.5+0.5,1,1,0.5+0.5,//开  我在
0.5+0.5,0.5+0.5,0.5+0.5,0.5+0.5//某年某月醒过来
};



  //获取按钮值
 int Button_state()
 {
   int  button_state = digitalRead(Button);
      delay(500);
      return button_state;
      
 }


  //播放音乐
  void Play1()
  {
   int length = sizeof(melody)/sizeof(melody[0]);//计算长度
    for (int thisNote = 0; thisNote < length; thisNote++) {
    tone(Buzzer, melody[thisNote]);
    delay(700*noteDurations[thisNote]);
    noTone(Buzzer);
    }
  }

   //播放音乐
  void Play2()
  {
   int length = sizeof(melody2)/sizeof(melody2[0]);//计算长度
    for (int thisNote = 0; thisNote < length; thisNote++) {
    tone(Buzzer, melody2[thisNote]);
    delay(700*duration[thisNote]);
    noTone(Buzzer);
    }
  }

   //播放音乐
  void Play3()
  {
   int length = sizeof(melody2)/sizeof(melody2[0]);//计算长度
    for (int thisNote = 0; thisNote < length; thisNote++) {
    tone(Buzzer, melody[thisNote]);
    delay(700*noteDurations[thisNote]);
    noTone(Buzzer);
    }
  }

  

  //停止音乐
  void Mute()
  {
     noTone(Buzzer);
  }
