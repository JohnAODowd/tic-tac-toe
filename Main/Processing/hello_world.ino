void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  Serial.println("Hello, world!");
  //wait 100 milliseconds so we don't drive ourselves crazy
  delay(100);
}
