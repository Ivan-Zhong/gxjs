#include <Servo.h>                // 声明调用Servo.h库
Servo myServo0;              //机械臂舵机，命名为myServo0
Servo myServo1;                  
Servo myServo2; 
Servo myServo3; 
Servo myServo4;
Servo myServo5;                                  

#define  SERVO_PINcatch 8            //宏定义舵机控制引脚，命令为#define  舵机名字_PIN  端口 ;
#define  SERVO_PIN1  9            //宏定义舵机控制引脚，命令为#define  舵机名字_PIN  端口 ;
#define  SERVO_PIN2  10            //宏定义舵机控制引脚，命令为#define  舵机名字_PIN  端口 ;
#define  SERVO_PIN3  11            //宏定义舵机控制引脚，命令为#define  舵机名字_PIN  端口 ;
#define  SERVO_PIN4  12            //宏定义舵机控制引脚，命令为#define  舵机名字_PIN  端口 ;
#define  SERVO_PINground 13            //宏定义舵机控制引脚，命令为#define  舵机名字_PIN  端口 ;

// 左前方的电机 left front
int lfCLK=45;
int lfCW=44;
int lfEN=43;
// 右前方的电机 right front
int rfCLK=39;
int rfCW=38;
int rfEN=37;
// 左后方的电机 left rear
int lrCLK=36;
int lrCW=35;
int lrEN=34;
// 右后方的电机 right rear
int rrCLK=42;
int rrCW=41;
int rrEN=40;

int myServo1Angle;
int myServo2Angle;
int myServo3Angle;
int myServo4Angle;
int myServo5Angle;


unsigned int PWM=0;

void pwmServoControl(Servo servo, int startAngle, int endAngle)
{ 
  if(startAngle<=endAngle)
  {
    servo.write(startAngle);
    delay(500);
    servo.write(startAngle);
    delay(100);
    for(PWM = startAngle; PWM < endAngle; ++PWM)
    {   
      servo.write(PWM);
      delay(20);      
    }
  }
  else if(startAngle>endAngle)
  {
    servo.write(startAngle);
    delay(500);
    servo.write(startAngle);
    delay(100);
    for(PWM = startAngle; PWM >endAngle; PWM -=1)
    {   
      servo.write(PWM);
      delay(20);      
    }
  }   
}

void myServo4Control(int angle)//想让myServo4转到位的角度；如果想在一个范围内旋转还可以增加函数咯口哦，
{ 
  myServo4Angle = angle;
  pwmServoControl(myServo4,angle,angle);
}

void myServo3Control(int angle)
{ 
  myServo3Angle = angle;
  pwmServoControl(myServo3,angle,angle);
}

void myServo2Control(int angle)
{ 
  myServo2Angle = angle;
  pwmServoControl(myServo2,angle,angle);
}


void myServo1Control(int angle)
{ 
  myServo1Angle = angle;
  pwmServoControl(myServo1,angle,angle);
}

void myServo5Control(int angle)//最底下那个基座
{ 
  myServo5Angle = angle;
  pwmServoControl(myServo5,angle,angle);
}

void catchOn()      //张开爪子
{
  pwmServoControl(myServo0,110,160);
}

void catchOff()      //闭合爪子
{
  pwmServoControl(myServo0,160,110);
}

void normalState()
{
  myServo4Control(180);
  delay(500); 
  myServo3Control(30);
  delay(500);
  myServo2Control(180);
  delay(500);
  myServo1Control(90);
  delay(500);
  myServo5Control(45);                         
}

void catchControl(int state)
{
  if(state)
    catchOn();
  else
    catchOff();
}

void motorMove(int steps)
{
  for(int i = 0; i < steps; i++){
    digitalWrite(rrCLK,HIGH);
    digitalWrite(lrCLK,HIGH);
    digitalWrite(lfCLK,HIGH);
    digitalWrite(rfCLK,HIGH);
    delayMicroseconds(500);
    digitalWrite(rrCLK,LOW);
    digitalWrite(lrCLK,LOW);
    digitalWrite(lfCLK,LOW);
    digitalWrite(rfCLK,LOW);
    delayMicroseconds(500);
  }
}

void moveForward(int steps)
{
  digitalWrite(lfCW, 0);
  digitalWrite(rfCW, 1);
  digitalWrite(lrCW, 0);
  digitalWrite(rrCW, 1);
  motorMove(steps);
}

void moveLeft(int steps)
{
  digitalWrite(lfCW, 0);
  digitalWrite(rfCW, 0);
  digitalWrite(lrCW, 1);
  digitalWrite(rrCW, 1);
  motorMove(steps);  
}

void moveRight(int steps)
{
  digitalWrite(lfCW, 1);
  digitalWrite(rfCW, 1);
  digitalWrite(lrCW, 0);
  digitalWrite(rrCW, 0);
  motorMove(steps);  
}

void moveBackward(int steps)
{
  digitalWrite(lfCW, 1);
  digitalWrite(rfCW, 0);
  digitalWrite(lrCW, 1);
  digitalWrite(rrCW, 0);
  motorMove(steps);  
}

void turnLeft(int steps)
{
  digitalWrite(lfCW, 1);
  digitalWrite(rfCW, 1);
  digitalWrite(lrCW, 1);
  digitalWrite(rrCW, 1);
  motorMove(steps);   
}

void turnRight(int steps)
{
  digitalWrite(lfCW, 0);
  digitalWrite(rfCW, 0);
  digitalWrite(lrCW, 0);
  digitalWrite(rrCW, 0);
  motorMove(steps); 
}

int angleFlag = 0;
int control;
int servoNumber;

void serialControl()
{
  if(Serial1.available())
  {
    control = Serial1.read();
    if(angleFlag == 1) // 此时要改变角度
    {
      switch(servoNumber)
      {
        case 0:
          catchControl(control);
          break;
        case 1:
          myServo1Control(control);
          break;
        case 2:
          myServo2Control(control);
          break;
        case 3:
          myServo3Control(control);
          break;
        case 4:
          myServo4Control(control);
          break;
        case 5:
          myServo5Control(control);
          break;
      }
      angleFlag = 0;
    }
    else
    {
      if(control >= 'A')
      {
        switch(control) 
        {
          case 'A':
            turnLeft(500);
            break;
          case 'B':
            turnRight(500);
            break;
          case 'G':
            moveForward(500);
            break;
          case 'H':
            moveLeft(500);
            break;
          case 'J':
            moveRight(500);
            break;
          case 'K':
            moveBackward(500);
            break;    
        }
      }
      else
      {
        servoNumber = control;
        angleFlag = 1;
      }
    }
  }
  else if(Serial2.available()) //读取openmv的消息
  {
    char openmvCommand = Serial2.read();
    switch(openmvCommand)
    {
      case 'A':
        moveForward(2);
        break;
      case 'B':
        moveBackward(2);
        break;
      case 'C':
        catchOn();
        break;
      case 'D':
        catchOff();
        break;
      case 'E':
        pwmServoControl(myServo1, myServo1Angle, myServo1Angle = myServo1Angle+2);
        break;
      case 'F':
        pwmServoControl(myServo1, myServo1Angle, myServo1Angle = myServo1Angle-2);
        break;
      case 'G':
        pwmServoControl(myServo2, myServo2Angle, myServo2Angle = myServo2Angle+2);
        break;
      case 'H':
        pwmServoControl(myServo2, myServo2Angle, myServo2Angle = myServo2Angle-2);
        break;
      case 'I':
        pwmServoControl(myServo3, myServo3Angle, myServo3Angle = myServo3Angle+2);
        break;
      case 'J':
        pwmServoControl(myServo3, myServo3Angle, myServo3Angle = myServo3Angle-2);
        break;
      case 'K':
        pwmServoControl(myServo4, myServo4Angle, myServo4Angle = myServo4Angle+2);
        break;
      case 'L':
        pwmServoControl(myServo4, myServo4Angle, myServo4Angle = myServo4Angle-2);
        break;
      case 'M':
        pwmServoControl(myServo5, myServo5Angle, myServo5Angle = myServo5Angle+2);
        break;
      case 'N':
        pwmServoControl(myServo5, myServo5Angle, myServo5Angle = myServo5Angle-2);
        break;
    }
  }
}

void setup(){ 
  // 左前方电机使能
  pinMode(lfCLK,OUTPUT);
  pinMode(lfCW,OUTPUT);
  pinMode(lfEN,OUTPUT);
  digitalWrite(lfEN,LOW);//电机使能
  
  // 右前方电机使能
  pinMode(rfCLK,OUTPUT);
  pinMode(rfCW,OUTPUT);
  pinMode(rfEN,OUTPUT);
  digitalWrite(rfEN,LOW);//电机使能
   
  // 右后方电机使能
  pinMode(rrCLK,OUTPUT);
  pinMode(rrCW,OUTPUT);
  pinMode(rrEN,OUTPUT);
  digitalWrite(rrEN,LOW);//电机使能
  
  // 左后方电机使能
  pinMode(lrCLK,OUTPUT);
  pinMode(lrCW,OUTPUT);
  pinMode(lrEN,OUTPUT);
  digitalWrite(lrEN,LOW);
  
  myServo0.attach(SERVO_PINcatch);    // 将10引脚与声明的舵机对象连接起来
  myServo1.attach(SERVO_PIN1);
  myServo2.attach(SERVO_PIN2);
  myServo3.attach(SERVO_PIN3);
  myServo4.attach(SERVO_PIN4);
  myServo5.attach(SERVO_PINground);
  
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial.println("Please input serial data.");
  delay(2000);
  normalState();

  // 向右转
  pwmServoControl(myServo5, myServo5Angle, myServo5Angle = 21);
  // 识别二维码
  Serial2.print("qrcode");
  // 向前转
//  pwmServoControl(myServo5, myServo5Angle, myServo5Angle = 90);
  // 识别颜色三次
  
}

void loop()
{ 
  
} 
