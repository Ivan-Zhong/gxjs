void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    char c = Serial.read();
    if(c == 'A')
    {
      Serial1.write("Hello");
    }
    else if(c == 'B')
    {
      Serial1.write('B');
    }
  }
  if(Serial1.available())
  {
    Serial.println(Serial1.read());
  }
}
