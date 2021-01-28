#include <Servo.h>
Servo myServoCatch;
Servo myServo1;                  
Servo myServo2; 
Servo myServo3; 
Servo myServo4;

int const SERVO_PINcatch = 8;
int const SERVO_PIN1 = 9;
int const SERVO_PIN2 = 10;
int const SERVO_PIN3 = 11;
int const SERVO_PIN4 = 12;
                                                     
unsigned int PWM=0;
void pwmServoControl(Servo servo,int phase)
{   
  int a=servo.read();
  Serial.println(a);
  if(a<phase)
  {
    for(PWM = a; PWM <phase; PWM +=1)
    {   
      servo.write(PWM);   //给舵机写入PWM  
      delay(15);      
    }//延时10ms让舵机转到指定位置
  }
  else
  {
    for(PWM = a; PWM>phase; PWM-=1){     
        servo.write(PWM);    
        delay(15);                       
    }        
  }
}

void setup(){ 
  myServoCatch.attach(SERVO_PINcatch);
  myServo1.attach(SERVO_PIN1);
  myServo2.attach(SERVO_PIN2);
  myServo3.attach(SERVO_PIN3);
  myServo4.attach(SERVO_PIN4);
  Serial.begin(9600);
  Serial.println("Please input serial data.");
}  

void loop(){ 
  if(Serial.available())
  {
    
  }
} 
