void setup() {
pinMode(7, OUTPUT);
}

void loop() {
  digitalWrite(7,0);
  delay(1000);
  digitalWrite(7,1);
  delay(100);
  for( int i=0; i<5;i++) {
    digitalWrite(7,0);
    delay(100);
    digitalWrite(7,1);
    delay(100);
  }
  while(1) {}

}
