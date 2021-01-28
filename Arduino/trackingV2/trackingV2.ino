// 使用12个循迹模块
// 到位置才调整
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

unsigned int PWM=0;

int const fTrack1 = 31;
int const fTrack2 = 32;
int const fTrack3 = 33;

int const lTrack1 = 25;
int const lTrack2 = 26;
int const lTrack3 = 27;

int const rTrack1 = 30;
int const rTrack2 = 29;
int const rTrack3 = 28;

int const bTrack1 = 24;
int const bTrack2 = 23;
int const bTrack3 = 22;

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
    while((digitalRead(lTrack2) == LOW))
    {
      turnRight(2);
      while(digitalRead(rTrack2) == LOW)
      {
        if(digitalRead(rTrack1) == HIGH)
          moveForward(1);
        else
          moveBackward(1);
      }
    }
  }
  else // 左侧靠前
  {
    while(digitalRead(rTrack2) == LOW)
    {
      turnLeft(2);
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

void moveForwardToLine()
{
  while((digitalRead(lTrack2) == LOW) && (digitalRead(rTrack2) == LOW))
    moveForward(2);
  if(digitalRead(lTrack2) == LOW && digitalRead(rTrack2) == HIGH)
    horzCorrect(1);
  else if(digitalRead(lTrack2) == HIGH && digitalRead(rTrack2) == LOW)
    horzCorrect(0);
}

void moveLeftToLine()
{
  bool bTrackMet = false;
  while(digitalRead(fTrack2) == LOW)
  {
    moveLeft(2);
    bTrackMet = (digitalRead(bTrack2) == HIGH) ? true : false;
  }
  delay(100);
  if(bTrackMet)
  {
    
    while(digitalRead(bTrack2) == LOW)
    {
      turnLeft(5);
      moveRight(2);
//      while(digitalRead(fTrack1) == HIGH)
//      {
//        moveLeft(1);
//      }
//      while(digitalRead(fTrack3) == HIGH)
//      {
//        moveRight(1);
//      }
    }
  }
  else
  {
    while(digitalRead(bTrack2) == LOW)
    {
      turnRight(5);
      moveLeft(2);
//      while(digitalRead(fTrack1) == HIGH)
//        moveLeft(1);
//      while(digitalRead(fTrack3) == HIGH)
//        moveRight(1);
    }
  }
  
}

void setup() {
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


  // 前进，使横向中线对齐
  moveForwardToLine();
  delay(100);

  // 左移，使竖向中线对齐
  moveLeftToLine();
  delay(100);

  moveForward(1000);

  // 前进，直到到达二维码的位置

  // 扫码

  // 后退，到达物料位置

  // 循环三次，每次从物料区到粗加工区，除最后一次外都回来

  // 右移 去扫码

  // 左移 到粗加工区

  // 循环三次 从粗加工区到半成品区 除最后一次外都回来

  // 后退 达到结束区

  // 左移进入结束区
  
}

void loop() {
  

}
