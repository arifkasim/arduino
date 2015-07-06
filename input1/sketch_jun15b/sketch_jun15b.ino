int inputPin = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(inputPin);
  Serial.println(reading);
  delay(1000);
}
