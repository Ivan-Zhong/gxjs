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
  myServo4control(180);
  delay(500); 
  myServo3control(30);
  delay(500);
  myServo2control(180);
  delay(500);
  myServo1control(90);
  delay(500);
  catchon();
  delay(500);
  catchoff();
  delay(500);
  myServo5control(45);                         
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
  pwmServoControl(myServo2, 0, 180);
  delay(1000);
}

int angleFlag = 0;
int control;
int servoNumber;

void loop()
{ 
  
} 
