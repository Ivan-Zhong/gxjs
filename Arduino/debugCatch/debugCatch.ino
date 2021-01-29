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

void pwmServoControl(Servo servo, int startAngle, int endAngle)
{ 
  if(startAngle<=endAngle)
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
  else if(startAngle>endAngle)
  {
    servo.write(startAngle);
    delay(100);
    servo.write(startAngle);
    delay(100);
    for(PWM = startAngle; PWM >endAngle; PWM -=1)
    {   
      servo.write(PWM);
      delay(20);      
    }
  }   
}

void myServo4control(int angle)//想让servo4转到位的角度；如果想在一个范围内旋转还可以增加函数咯口哦，
{  
  pwmServoControl(myServo4,angle,angle);
}

void myServo3control(int angle)
{  
  pwmServoControl(myServo3,angle,angle);
}

void myServo2control(int angle)
{  
  pwmServoControl(myServo2,angle,angle);
}


void myServo1control(int angle)
{  
  pwmServoControl(myServo1,angle,angle);
}

void myServo5control(int angle)//最底下那个基座
{  
  pwmServoControl(myServo5,angle,angle);
}

void catchon()      //张开爪子
{
  pwmServoControl(myServo0,110,160);
}

void catchoff()      //闭合爪子
{
  pwmServoControl(myServo0,160,110);
}

void normalstate()
{
  myServo0control(25);
  myServo1control(90);
  myServo2control(25);
  myServo3control(25);
  myServo4control(25);
  myServo5control(90);                         
}

void catchControl(int state)
{
  if(state)
    catchon();
  else
    catchoff();
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
  Serial.println("Please input serial data.");
  delay(2000);
  normalstate();
}

int angleFlag = 0;
int control;
int servoNumber;

void loop()
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
          myServo1control(control);
          break;
        case 2:
          myServo2control(control);
          break;
        case 3:
          myServo3control(control);
          break;
        case 4:
          myServo4control(control);
          break;
        case 5:
          myServo5control(control);
          break;
      }
      angleFlag = 0;
    }
    else
    {
      if(control >= 'A')
      {
        ;
      }
      else
      {
        servoNumber = control;
        angleFlag = 1;
      }
    }
  }
} 
