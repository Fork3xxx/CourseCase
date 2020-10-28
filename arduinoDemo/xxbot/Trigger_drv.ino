/*
 * 超声波测距驱动程序
 * 1. 给Trigger发送一个低高低的短时间脉冲,触发测距
 * 2. 根据返回的距离发出对应的光和声音 
 * author: xxx
 * date:2020.06.21
 */
#define TriggerPin 6
#define EchoPin 4
int Value_dis;


 //初始化端口
void Init_Trigger()
 {
   Serial.begin(9600);    //测量结果将通过此串口输出至 PC 上的串口监视器
   pinMode(EchoPin,INPUT);
   pinMode(TriggerPin, OUTPUT);
 }

 int Distance()
 {
     //产生40kHz超声波
    digitalWrite(TriggerPin, LOW); //给Trigger发送一个低电平
    delayMicroseconds(2); //2 ms
    digitalWrite(TriggerPin, HIGH);//给Trigger发送一个高电平
    delayMicroseconds(10); //10ms
    digitalWrite(TriggerPin, LOW);//给Trigger发送一个低电平

    /** 有信号返回时，echoPin引脚会输出高电平，
      * 高电平持续的时间就是超声波从发射到返回的时间。
      * 此时pulseIn()函数获取到高电平维持的时间
      */
    Value_dis = pulseIn(EchoPin, HIGH); // 返回值,回波等待时间
  
    /**
     * 超声波速度是:340m/s, 换算称 34000cm / 1000 000μs = 34 / 1000
     * 因为发送到接收，实际是相同距离走了2回，所以要除以2
     * 距离（厘米） = (回波时间 * (34 / 1000)) / 2
     * 简化后的计算公式为(回波时间 * 17) / 1000
     */
     int distance = Value_dis * 17.0 /1000 ; //把回波时间换算成cm
    return distance;
 }
