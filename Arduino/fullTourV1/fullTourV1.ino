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

const int fTrack = 22;
//const int fTrack2 = 31;
const int lTrack = 26;
//const int lTrack2 = 29;

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

bool isLeftOnTrack()
{
  return (digitalRead(lTrack) == HIGH);
}

bool isFrontOnTrack()
{
  return (digitalRead(fTrack) == HIGH);
}

void correctLeft()
{
  bool leftOnTrack = isLeftOnTrack();
  if(!leftOnTrack)
  {
    for(int i = 0; i < 50; ++i)
    {
      turnLeft(2);
      if(leftOnTrack = isLeftOnTrack())
        break;
    }
    if(!leftOnTrack)
    {
      for(int i = 0; i < 150; ++i)
      {
        turnRight(2);
        if(leftOnTrack = isLeftOnTrack())
          break;
      }
    }
  }
}

void correctFront()
{
  bool frontOnTrack = isFrontOnTrack();
  if(!frontOnTrack)
  {
    for(int i = 0; i < 50; ++i)
    {
      turnLeft(2);
      if(frontOnTrack = isFrontOnTrack())
        break;
    }
    if(!frontOnTrack)
    {
      for(int i = 0; i < 150; ++i)
      {
        turnRight(2);
        if(frontOnTrack = isFrontOnTrack())
          break;
      }
    }
  }
}

void setup()
{  
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

  // 巡线模块初始化
  pinMode(fTrack, INPUT);
  pinMode(lTrack, INPUT);
//  pinMode(fTrack1, INPUT);
//  pinMode(fTrack2, INPUT);
//  pinMode(lTrack1, INPUT);
//  pinMode(lTrack2, INPUT);

  // 前进，直到左侧位置对准、
  while(!isLeftOnTrack())
    moveForward(2);

  delay(2);
  
  // 左移，直到前方对准
  while(!isFrontOnTrack())
  {
    moveLeft(2);
    correctLeft();
  }

  delay(2);

  // 前进，直到到达二维码的位置

  for(int i = 0; i < 1000; ++i)
  {
    moveForward(100);
    correctFront();
  }

  // 扫码

  // 后退，到达物料位置

  // 循环三次，每次从物料区到粗加工区，除最后一次外都回来

  // 右移 去扫码

  // 左移 到粗加工区

  // 循环三次 从粗加工区到半成品区 除最后一次外都回来

  // 后退 达到结束区

  // 左移进入结束区
}

void loop()
{
  
}
