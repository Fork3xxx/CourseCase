/*
 * 键盘驱动程序
 *   
 * author: xxx
 * date:2020.06.21
 */

#define NO_KEY 0

const byte ROWS = 4;   //4行
const byte COLS = 4;  //4列
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

int keyPadAnalogPin = 3;  //用analogRead(A3)读取keypad的电平
int keyDelay = 50;  //按键防抖，间隔50ms
unsigned int keyVal1 = 0;  //上一个密钥值
unsigned int keyVal2 = 0;  //当前的密钥值

unsigned int getKey(){
  keyVal1 = analogRead(keyPadAnalogPin);   //读key值，输入到串口
  Serial.println(keyVal1);
  delay(keyDelay);
  keyVal2 = analogRead(keyPadAnalogPin);  //在0.05秒内再读一次
  if(keyVal1 > keyVal2){  //在0.05秒内的电平不同，或按下（按键）>不按（低电平），避免长按重复键处理
    keyVal1 = max(keyVal1,keyVal2);  //取高
    return getMatrixValue(keyVal1);  //返回keyVal1对应的按键编号
  }
  else  //没有按键
    return NO_KEY; //NO_KEY
}

void Key(){
  char key = getKey(); //通过函数analogRead(keyPadAnalogPin)读取密钥值
  if(key != NO_KEY){  //检测有无按键
    if(key == 35){  //按下#，就能删除密码的值
     
     
   
    }
    else if(key == '*'){  //按下*，检查checkPass()
    
    }
    else{
      
    }
   
  }
}

char getMatrixValue(int val){
  switch(val){
    case 930 : return keys[0][0];
    case 912 : return keys[0][1];
    case 894 : return keys[0][2];
    case 877 : return keys[0][3];
    case 852 : return keys[1][0];
    case 837 : return keys[1][1];
    case 822 : return keys[1][2];
    case 808 : return keys[1][3];
    case 787 : return keys[2][0];
    case 774 : return keys[2][1];
    case 761 : return keys[2][2];
    case 749 : return keys[2][3];
    case 731 : return keys[3][0];
    case 719 : return keys[3][1];
    case 708 : return keys[3][2];
    case 698 : return keys[3][3];
    default : return NO_KEY;
  }
}
