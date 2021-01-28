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
  Serial1.begin(9600);
}

int state = 0;
bool turnl = 0;
void loop() {
  if(Serial1.available())
  {
    int c = Serial1.read();
    if(state == 0)
    {
      switch(c)
      {
        case 0:
          turnl = 1;
          break;
        case 1:
          turnl = 0;
          break;
      }
    }
    else
    {
      if(turnl)
      {
        turnLeft(c*20);
      }
      else
      {
        turnRight(c*20);
      }
    }
    state = 1 - state;
  }
}
