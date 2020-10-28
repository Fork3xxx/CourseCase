/*
 * LED驱动程序
 *   1. 呼吸灯
 *   2. 
 */
 #define LED 9           // the PWM pin the LED is attached to
 int brightness = 0;    // how bright the LED is
 int fadeAmount = 5;    // how many points to fade the LED by

 //初始化端口
 void Init_LED()
 {
      pinMode(LED, OUTPUT);
 } 


 //LED
 void LED_PWM(int brightness)
 { 
      analogWrite(LED, brightness);
      delay(30);    
 }

 void LED_OFF()
 {
      digitalWrite(LED,LOW);
 }

 
 
