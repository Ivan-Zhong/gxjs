// 使用12个循迹模块
#include <Servo.h>                // 声明调用Servo.h库
Servo myServo0;              //机械臂舵机，命名为myServo0
Servo myServo1;                  
Servo myServo2; 
Servo myServo3; 
Servo myServo4;
Servo myServo5;    
                              
#define  SERVO_PINcatch 8            //宏定义舵机控制引脚，命令为#define  舵机名字_PIN  端口 ;
#define  SERVO_PIN1  9            //宏定义舵机控制引脚，命令为#define  舵机名字_PIN  端口 ;
#define  SERVO_PIN2  4            //宏定义舵机控制引脚，命令为#define  舵机名字_PIN  端口 ;
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

unsigned int PWM=0;

int const fTrack1 = 31;
int const fTrack2 = 32;
int const fTrack3 = 33;

int const lTrack1 = 27;
int const lTrack2 = 26;
int const lTrack3 = 25;

int const rTrack1 = 30;
int const rTrack2 = 29;
int const rTrack3 = 28;

int const bTrack1 = 22;
int const bTrack2 = 23;
int const bTrack3 = 24;

void pwmServoControl(Servo servo, int startAngle, int endAngle)
{ 
  if(startAngle <= endAngle)
  {
    servo.write(startAngle);
    delay(100);
    servo.write(startAngle);
    delay(100);
    for(PWM = startAngle; PWM < endAngle; ++PWM)
    {   
      servo.write(PWM);
      delay(20);      
    }
  }
  else if(startAngle > endAngle)
  {
    servo.write(startAngle);
    delay(100);
    servo.write(startAngle);
    delay(100);
    for(PWM = startAngle; PWM > endAngle; --PWM)
    {   
      servo.write(PWM);
      delay(20);      
    }
  }   
}

void catchon()      //张开爪子
{
  pwmServoControl(myServo0,110,160);
}

void catchoff()      //闭合爪子
{
  pwmServoControl(myServo0,160,110);
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

void moveDiagonal1Forward(int steps)
{
  digitalWrite(lfCW, 0);
  digitalWrite(rrCW, 1);
  digitalWrite(lrEN,HIGH);
  digitalWrite(rfEN,HIGH);
  motorMove(steps); 
  digitalWrite(lrEN,LOW);
  digitalWrite(rfEN,LOW);
}

void moveDiagonal1Backward(int steps)
{
  digitalWrite(lfCW, 1);
  digitalWrite(rrCW, 0);
  digitalWrite(lrEN,HIGH);
  digitalWrite(rfEN,HIGH);
  motorMove(steps); 
  digitalWrite(lrEN,LOW);
  digitalWrite(rfEN,LOW);
}

void moveDiagonal2Forward(int steps)
{
  digitalWrite(lfEN, HIGH);
  digitalWrite(rfCW, 1);
  digitalWrite(lrCW, 0);
  digitalWrite(rrEN, HIGH);
  motorMove(steps);
  digitalWrite(lfEN, LOW);
  digitalWrite(rrEN, LOW);
}

void moveDiagonal2Backward(int steps)
{
  digitalWrite(lfEN, HIGH);
  digitalWrite(rfCW, 0);
  digitalWrite(lrCW, 1);
  digitalWrite(rrEN, HIGH);
  motorMove(steps);
  digitalWrite(lfEN, HIGH);
  digitalWrite(rrEN, HIGH);
}

void horzCorrect(int mode)
{
  if(mode) // 右侧靠前
  {
    while(digitalRead(lTrack2) == LOW)
    {
      turnRight(2);
      delay(50);
      while(digitalRead(rTrack2) == LOW)
      {
        if(digitalRead(rTrack3) == HIGH)
          moveBackward(1);
        else
          moveForward(1);
        delay(10);
      }
    }
  }
  else // 左侧靠前
  {
    while(digitalRead(rTrack2) == LOW)
    {
      turnLeft(2);
      delay(50);
      while(digitalRead(lTrack2) == LOW)
      {
        if(digitalRead(lTrack3) == HIGH)
          moveBackward(1);
        else
          moveForward(1);
        delay(10);
      }
    }
  }
}

void moveForwardToLine()
{
  int lineCount = 0;
  int stepCount = 0;
  bool lineMet = false;
  while(lineCount < 1)
  {
    moveForward(1);
    ++stepCount;
    if(stepCount > 2000)
    {
      if(digitalRead(fTrack2) == HIGH)
        break;
    }
  }
  while((digitalRead(lTrack2) == LOW) && (digitalRead(rTrack2) == LOW))
    moveForward(10);
  delay(200);
  if(digitalRead(lTrack2) == LOW && digitalRead(rTrack2) == HIGH)
    horzCorrect(1);
  else if(digitalRead(lTrack2) == HIGH && digitalRead(rTrack2) == LOW)
    horzCorrect(0);
}

void moveLeftToLine()
{
  while((digitalRead(fTrack2) == LOW) && (digitalRead(bTrack2) == LOW))
  {
    moveLeft(2);
    if(digitalRead(lTrack2) == LOW)
    {
      if(digitalRead(lTrack1) == HIGH)
      {
        while(digitalRead(lTrack2) == LOW)
        {
          turnRight(1);
          while(digitalRead(rTrack2) == LOW)
          {
            if(digitalRead(rTrack3) == HIGH)
              moveBackward(1);
            else
              moveForward(1);
          }
        }
      }
      else if(digitalRead(lTrack3) == HIGH)
      {
        while(digitalRead(lTrack2) == LOW)
        {
          turnLeft(1);
          while(digitalRead(rTrack2) == LOW)
          {
            if(digitalRead(rTrack3) == HIGH)
              moveForward(1);
            else
              moveBackward(1);
          }
        }
      }
    }
    else if(digitalRead(rTrack2) == LOW)
    {
      if(digitalRead(rTrack1) == HIGH)
      {
        while(digitalRead(rTrack2) == LOW)
        {
          turnLeft(1);
          while(digitalRead(lTrack2) == LOW)
          {
            if(digitalRead(lTrack3) == HIGH)
              moveBackward(1);
            else
              moveForward(1);
          }
        }
      }
      else if(digitalRead(rTrack3) == HIGH)
      {
        while(digitalRead(rTrack2) == LOW)
        {
          turnRight(1);
          while(digitalRead(lTrack2) == LOW)
          {
            if(digitalRead(lTrack1) == HIGH)
              moveForward(1);
            else
              moveBackward(1);
          }
        }
      }
    }
  }
}

void modifyforwardposition()//前进方向调整
{
  if(digitalRead(fTrack2)==LOW)
  { 
    if(digitalRead(fTrack1) == HIGH)//偏右
    {
      while((digitalRead(fTrack1) != LOW)||(digitalRead(fTrack2) != HIGH))
        moveLeft(1);
        delay(200);
    }
    
    else if(digitalRead(fTrack3) == HIGH)//偏左
    {
     while((digitalRead(fTrack3) != LOW)||(digitalRead(fTrack2) != HIGH))
        moveRight(1);
        delay(200);
    }

   else if(digitalRead(fTrack1)==LOW&&digitalRead(fTrack3)==LOW)
   { while((digitalRead(fTrack1) != LOW)||(digitalRead(fTrack2) != HIGH)||(digitalRead(fTrack3) != LOW))
       moveRight(1);
       delay(200);
   } 
   
  }
}

void modifyhorizposition()//水平调整
{
  if(digitalRead(lTrack2)==LOW)
  { 
    if(digitalRead(lTrack1) == HIGH)//偏前
    {
      while((digitalRead(lTrack1) != LOW)||(digitalRead(lTrack2) != HIGH))
        moveBackward(1);
        delay(200);
    }
    
    else if(digitalRead(lTrack3) == HIGH)//偏后
    {
     while((digitalRead(lTrack3) != LOW)||(digitalRead(lTrack2) != HIGH))
        moveForward(1);
        delay(200);
    }
  }
}

void moveRightToLine()
{
  moveRight(800);
  while(digitalRead(fTrack2) == LOW)
  {
    moveRight(1);
  }
}

//void turnRightToLine()
//{
//  turnRight(1600);
//  bool bTrackMet = false;
//  while(digitalRead(fTrack2) == LOW)
//  {
//    turnRight(1);
//    bTrackMet = (digitalRead(bTrack2) == HIGH) ? true : false;
//  }
//  delay(1000);
//  if(bTrackMet)
//  {
//    while(digitalRead(bTrack2) == LOW)
//    {
//      turnLeft(5);
//      delay(10);
//      while(digitalRead(fTrack1) == HIGH)
//      {
//        moveLeft(2);
//        delay(10);
//      }
//      while(digitalRead(fTrack3) == HIGH)
//      {
//        moveRight(2);
//        delay(10);
//      }
//    }
//  }
//  else
//  {
//    while(digitalRead(bTrack2) == LOW)
//    {
//      turnRight(5);
//      delay(10);
//      while(digitalRead(fTrack1) == HIGH)
//      {
//        moveLeft(2);
//        delay(10);
//      }
//      while(digitalRead(fTrack3) == HIGH)
//      {
//        moveRight(2);
//        delay(10);
//      }
//    }
//  }
//}

void turnRightToLine()
{
  turnRight(1600);
  while(digitalRead(fTrack2) == LOW && digitalRead(bTrack2) == LOW)
    turnRight(5);
  delay(1000);
  if(digitalRead(bTrack2) == HIGH)
  {
    while(digitalRead(fTrack2) == LOW)
    {
      turnRight(5);
      delay(10);
      while(digitalRead(bTrack1) == HIGH)
      {
        moveLeft(2);
        delay(10);
      }
      while(digitalRead(bTrack3) == HIGH)
      {
        moveRight(2);
        delay(10);
      }
    }
  }
  else if(digitalRead(fTrack2) == HIGH)
  {
    while(digitalRead(bTrack2) == LOW)
    {
      turnRight(5);
      delay(10);
      while(digitalRead(fTrack1) == HIGH)
      {
        moveLeft(2);
        delay(10);
      }
      while(digitalRead(fTrack3) == HIGH)
      {
        moveRight(2);
        delay(10);
      }
    }
  }
}

void moveForwardOnTrack(int steps)
{
  int stepCount = 0;
  int lineCount = 0;
  int stepCountBetweenLine = 0;
  while(stepCount < steps)
  {
    moveForward(5);
    stepCount += 5;
    while(digitalRead(fTrack1) == HIGH && digitalRead(fTrack2) == LOW)
    {
      turnLeft(2);
      moveLeft(2);
      delay(10);
    }
    while(digitalRead(fTrack3) == HIGH && digitalRead(fTrack2) == LOW)
    {
      turnRight(2);
      moveRight(2);
      delay(10);
    }
    while(digitalRead(bTrack1) == HIGH && digitalRead(bTrack2) == LOW)
    {
      turnRight(2);
      moveLeft(2);
      delay(10);
    }
    while(digitalRead(bTrack3) == HIGH && digitalRead(bTrack2) == LOW)
    {
      turnLeft(2);
      moveRight(2);
      delay(10);
    }
  }
}

void normalState()
{
  pwmServoControl(myServo1,25,106);
  pwmServoControl(myServo2,25,58);
  pwmServoControl(myServo3,25,25);
  pwmServoControl(myServo4,25,0);
  pwmServoControl(myServo5,25,94);
  catchon();                         
}

void scanState()
{
  catchon();
  pwmServoControl(myServo5, 94, 28);
  pwmServoControl(myServo2, 58, 82);
  pwmServoControl(myServo3, 25, 80);
  pwmServoControl(myServo4, 0, 85);
}

//void scanQRCode()
//{
//  Serial2.print("qrcode");
//  while(true)
//  {
//    if(Serial2.available())
//    {
//      Serial1.print(Serial2.read());
//    }
//  }
//}

void setup() {
  delay(1000);
  myServo0.attach(SERVO_PINcatch);    // 将10引脚与声明的舵机对象连接起来
  myServo1.attach(SERVO_PIN1);
  myServo2.attach(SERVO_PIN2);
  myServo3.attach(SERVO_PIN3);
  myServo4.attach(SERVO_PIN4);
  myServo5.attach(SERVO_PINground);

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
  // 循迹模块初始化
  for(int i = 22; i <= 33; ++i)
    pinMode(i, INPUT);
  Serial1.begin(9600);
  // Serial2.begin(9600);

  normalState();

  // 前进，使横向中线对齐
  moveForwardToLine();
  delay(500);

  moveRightToLine();
  delay(500);

  turnRightToLine();
  delay(500);

  moveForwardOnTrack(4200);
  delay(500);

  scanState();
  delay(500);

  //scanQRCode();
    
//
//  // 前进，直到到达二维码的位置
//  moveForwardOnTrack(10000);
//  delay(1000);
//
//  moveForwardToLine();
//  delay(1000);
//
//  turnRightToLine();
//  delay(1000);
//
//  moveForwardOnTrack(2000);

  // 扫码

  // 后退，到达物料位置

  // 循环三次，每次从物料区到粗加工区，除最后一次外都回来

  // 右移 去扫码
  // 循环三次 从粗加工区到半成品区 除最后一次外都回来

  // 后退 达到结束区

  // 左移进入结束区
  
}

void loop() {

  

}
