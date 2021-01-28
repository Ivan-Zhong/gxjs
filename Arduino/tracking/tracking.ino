void setup()
{
  pinMode(42, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(42) == LOW)
  {
    Serial.println("LOW    ");
  }
  else
  {
    Serial.println("HIGH   ");
  }
}
