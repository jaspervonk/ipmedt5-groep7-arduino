#define blackLED A5
#define whiteLED A4

void setup() {
  pinMode(blackLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);
}

void loop() {
  digitalWrite(blackLED, HIGH);
  digitalWrite(whiteLED, HIGH);
  delay(3000);
  digitalWrite(blackLED, LOW);
  digitalWrite(whiteLED, LOW);
  delay(3000);
}
