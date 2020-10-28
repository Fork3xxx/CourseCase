/*
 * 音乐播放机器人主程序
 */

void setup() {
   Init_LDR(); //光敏传感器端口初始化
   Init_LED(); //LED辅助照明灯端口初始化
  Init_Buzzer();//声光播放模块初始化
  Init_Trigger();
  Init_LCD();
}

void loop() {
  
  if(Val_LDR()<200)  
     LED_PWM(Val_LDR()); //用光敏传感器的值作为亮度值
  else LED_OFF;
  

  if(Val_LDR()>200)
      Disp_LCD(0,0,"bright ");
  else if (Val_LDR() > 100)
  {
      Disp_LCD(0,0,"obscure");
  }
  else 
       Disp_LCD(0,0,"too dark");

     if( Val_LDR() < 110)
  {   Play1(); 
     //播放
    }else if ( Val_LDR() <220){
      Play2();   //播放
  }else {
      Play3();   //播放
  }

    Disp_LCD(0,1,"move and change");  
}

 
