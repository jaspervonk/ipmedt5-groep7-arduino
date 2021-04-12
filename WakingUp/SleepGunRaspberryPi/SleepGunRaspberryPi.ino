#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin Setup
const int blackTarget = A7;
const int blackLED = A3;

const int whiteTarget = A1;
const int whiteLED = A2;

const int redTarget = A6;
const int redLED = A0;

const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_address = 0x27;
LiquidCrystal_I2C lcd(i2c_address, 20, 4);

// Game Rules
const int targetGoal = 10;
const int targetSpeed = 3000;
const int targetTimeBuffer = 50;
const int targetTreshhold = 700;
const int targetTimeBetween = 3000;

// Game Scores
int targetHits = 0;
int targetMisses = 0;
int targetReactionTime = 0;
float targetTotal = 0;
float targetAccuracy = 0;
float totalTime = 0;

// Misc
const String targetString = "target";
int selectedTarget = 0;
int targetTime = 0;
int targetValue = 0;
boolean targetRunning = true;

// Raspberry Pi
boolean piSignal = false;
int piSignalRawNew = ' ';
int piSignalRaw = '0';


void setup() {
  Serial.begin(9600);

  pinMode(blackTarget, INPUT);
  pinMode(blackLED, OUTPUT);
  
  pinMode(whiteTarget, INPUT);
  pinMode(whiteLED, OUTPUT);

  pinMode(redTarget, INPUT);
  pinMode(redLED, OUTPUT);

  randomSeed(analogRead(blackTarget));
  
  // Show startup on LCD display
  lcd.init();
}

void loop() {
  while(true){
    // Keep reading the Serial
    piSignalRawNew = Serial.read();

    // If the Serial is read, and its a new value; Use it!
    if((piSignalRawNew != piSignalRaw) and ((piSignalRawNew == '1') or (piSignalRawNew == '0'))){
      piSignalRaw = piSignalRawNew;
      break;
    }
  }

  

  // If the signal was 1 -> Play SleepGun Code
  if(piSignalRaw == '1'){
    Serial.println(piSignalRaw);
    // = LCD Feedback =
    lcd.backlight();
    lcd.setCursor(2,0);
    lcd.print("S L E E P G U N");
    lcd.setCursor(1,1);
    lcd.print("A C T I V A T E D");
    lcd.setCursor(0,3);
    lcd.print(">Get Ready to Shoot<");
    delay(3000);
    lcd.clear();
    lcd.setCursor(9, 1);
    lcd.print("3...");
    delay(1000);
    lcd.setCursor(9, 1);
    lcd.print("2...");
    delay(1000);
    lcd.setCursor(9, 1);
    lcd.print("1...");
    delay(1000);  
      
    while(targetHits < targetGoal){
      // Choose a random Target
      selectedTarget = random(1, 4);
    
      // Calculate the amount of time the target is active
      targetTime = targetSpeed;
  
      // = LCD Feedback =
      lcd.clear();
      lcd.setCursor(8, 1);
      lcd.print("SHOOT!");
    
      // While there is time left on the current target  
      while(targetTime > 0){
        // Read the Value of the selectedTarget
        if(selectedTarget == 1){
          targetValue = analogRead(blackTarget);
          digitalWrite(blackLED, HIGH);
        }
        if(selectedTarget == 2){
          targetValue = analogRead(whiteTarget);
          digitalWrite(whiteLED, HIGH);
        }

        if(selectedTarget == 3){
          targetValue = analogRead(redTarget);
          digitalWrite(redLED, HIGH);
        }
        
        // If the target has been hit. Else remove time and wait the targetTimeBuffer
        if(targetValue >= targetTreshhold){
          break;
        } else {
          targetTime = targetTime - targetTimeBuffer;
          totalTime = totalTime + targetTimeBuffer;
          delay(targetTimeBuffer);
        }
      }
    
      // If there was time left, the target was hit | Else not hit
      if(targetTime > 0){
        // = LCD Feedback =
        lcd.clear();
        lcd.setCursor(4, 1);
        lcd.print("Target Hit! :)");
        targetHits++;
      } else {
        // = LCD Feedback =
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Target Missed! :(");
        targetMisses++;
      }
  
      // Wait
      digitalWrite(blackLED, LOW);
      digitalWrite(whiteLED, LOW);
      digitalWrite(redLED, LOW);
      delay(targetTimeBetween);
    }
  
    // = LCD Feedback =
    while(targetRunning){ 
      // Calculate Scores
      targetTotal = targetHits + targetMisses;
      
      targetAccuracy = targetHits/targetTotal;
      targetReactionTime = totalTime/targetTotal;
    
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Good Morning!");
      lcd.setCursor(3,2);
      lcd.print("Calculating");
      delay(300);
      lcd.print(".");
      delay(300);
      lcd.print(".");
      delay(300);
      lcd.print(".");
      delay(100);
  
      // = LCD Feedback =
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Targets Hit: " + String(targetHits));
      lcd.setCursor(0,1);
      lcd.print("Targets Missed: " + String(targetMisses));
      lcd.setCursor(0,2);
      lcd.print("Accuracy: " + String(targetAccuracy*100) + "%");
      lcd.setCursor(0,3);
      lcd.print("Draw Time: " + String(targetReactionTime) + "ms");
      
      Serial.println(String(round(targetTotal)) + ":" + String(targetHits) + ":" + String(targetMisses) + ":" + String(targetAccuracy*100) + ":" + String(totalTime/1000) + ":" + String(targetReactionTime));
      targetRunning = false;
      break;
    }
  
    // Reset everything
    targetRunning = true;
    targetHits = 0;
    targetMisses = 0;
    targetReactionTime = 0;
    targetTotal = 0;
    targetAccuracy = 0;
    totalTime = 0;
    piSignal = false;
  
    // Wait for at least a minute
    delay(60000);
    lcd.clear();
    lcd.noBacklight();
  }
}
