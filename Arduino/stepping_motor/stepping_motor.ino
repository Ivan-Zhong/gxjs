
int dir = 1;  // 小车向前运动时dir为1，向后运动dir为0

// 左前方的电机 left front
int lfCLK=30;
int lfCW=29;
int lfEN=28;
// 右前方的电机 right front
int rfCLK=33;
int rfCW=32;
int rfEN=31;
// 左后方的电机 left rear
int lrCLK=40;
int lrCW=39;
int lrEN=38;
// 右后方的电机 right rear
int rrCLK=36;
int rrCW=35;
int rrEN=34;

void setup()
{
  // 左前方电机使能
  pinMode(lfCLK,OUTPUT);
  pinMode(lfCW,OUTPUT);
  pinMode(lfEN,OUTPUT);
  digitalWrite(lfEN,LOW);//电机使能
  digitalWrite(lfCW,!dir);
  
  // 右前方电机使能
  pinMode(rfCLK,OUTPUT);
  pinMode(rfCW,OUTPUT);
  pinMode(rfEN,OUTPUT);
  digitalWrite(rfEN,LOW);//电机使能
  digitalWrite(rfCW,dir);
   
  // 右后方电机使能
  pinMode(rrCLK,OUTPUT);
  pinMode(rrCW,OUTPUT);
  pinMode(rrEN,OUTPUT);
  digitalWrite(rrEN,LOW);//电机使能
  digitalWrite(rrCW,dir);//控制电机转向
  
  // 左后方电机使能
  pinMode(lrCLK,OUTPUT);
  pinMode(lrCW,OUTPUT);
  pinMode(lrEN,OUTPUT);
  digitalWrite(lrEN,LOW);
  digitalWrite(lrCW,!dir);
}

void moveForward()
{
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

void turn_left()
{
  
}

void turn_right()
{
  
}

void move_backward()
{
  
}

void move_right()
{
  
}

void move_left()
{
  
}

void loop()
{

}
