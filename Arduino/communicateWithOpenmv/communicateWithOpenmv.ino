void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  if(Serial2.available())
  {
    Serial.print(Serial2.read());
  }
  Serial2.print("hasdfhas");
  delay(1000);
}
