#include<string.h>
void setup() {
  for(int i = 22; i <= 33; ++i)
  {
    pinMode(i, INPUT);
  }
  Serial1.begin(9600);
}

void loop() {
  char str[10] = "";
  str[2] = ':';
  if(Serial1.available())
  {
    char c = Serial1.read();
    if(c == 'A')
    {
      for(int i = 22; i <= 33; ++i)
      {
        str[0] = i/10 + 48;
        str[1] = i%10 + 48;
        if(digitalRead(i) == LOW)
          strcpy((str + 3), "LOW\n");
        else
          strcpy((str + 3), "HIGH\n");
        Serial1.write(str);
      }
    }
  }
}
