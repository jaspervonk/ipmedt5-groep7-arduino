// Pin Setup
const int target1 = 19; // A0
const int target2 = 20; // A1

void setup() {
  Serial.begin(9600);
  pinMode(target1, INPUT);
  pinMode(target2, INPUT);
}

void loop() {
  Serial.println(String(analogRead(target1)));
  Serial.println(String(analogRead(target2)) + "\n");

  delay(1000);
}
