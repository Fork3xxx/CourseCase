/*
 * 光敏传感器驱动程序
 *   
 * author: xxx
 * date:2020.06.21
 */

 #define LDR A0

 //初始化端口
void Init_LDR()
 {
      Serial.begin(9600);
      pinMode(LDR, INPUT);
 }

 //获取光照强度值
 int Val_LDR()
 {
   int  val_LDR = analogRead(LDR);
      return val_LDR;
      delay(100);
 }
