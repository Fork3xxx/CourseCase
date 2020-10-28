/*
 * LCD显示屏驱动程序
 *   
 * author: xxx
 * date:2020.06.21
 */
#include<LiquidCrystal.h>
  LiquidCrystal lcd(12,11,5,4,3,2);//用arduino数字口12，11，5，4，3，2
void Init_LCD(){

  lcd.begin(16,2);          //初始化LCD
  lcd.clear();              //清屏
}

void Disp_LCD(byte row,byte line,char Str[]){
  lcd.setCursor(row,line);
  lcd.print(Str);
}
