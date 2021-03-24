// Pin Setup
const int target1 = 19; // A0
const int target2 = 20; // A1

// Game Rules
const int targetGoal = 5;
const int targetSpeed = 5;
const int targetTimeBuffer = 1000;
const int targetTreshhold = 330;

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


void setup() {
  Serial.begin(9600);
  pinMode(target1, INPUT);
  pinMode(target2, INPUT);
}

void loop() {
  while(targetHits < targetGoal){
    // Choose a random Target and show
    selectedTarget = random(1, 3);
    Serial.println("===== TARGET SELECTED =====\nTarget " + String(selectedTarget) + " has been selected");
  
    // Calculate the amount of time the target is active
    targetTime = targetSpeed*1000;
    Serial.println("targetTime at the start " + String(targetTime));
  
    // While there is time left on the current target  
    while(targetTime > 0){
      Serial.println("Time left " + String(targetTime));
        
      // Read the Value of the selectedTarget
      if(selectedTarget == 1){
        targetValue = analogRead(target1);
      }
      if(selectedTarget == 2){
        targetValue = analogRead(target2);
      }
  
      // Show the targetValue
      Serial.println("The targetValue is: " + String(targetValue));
      
      // If the target has been hit. Else remove time and wait the targetTimeBuffer
      if(targetValue >= targetTreshhold){
        break;
      } else {
        Serial.println("Waiting...");
        targetTime = targetTime - targetTimeBuffer;
        totalTime = totalTime + targetTimeBuffer;
        delay(targetTimeBuffer);
      }
    }
  
    // If there was time left, the target was hit | Else not hit
    if(targetTime > 0){
      Serial.println("Target was hit :)");
      targetHits++;
    } else {
      Serial.println("Target was not hit :(");
      targetMisses++;
    }
  
    // Game Score Updates
    Serial.println("===== CURRENT SCORE =====");
    Serial.println("Targets hit: " + String(targetHits));
    Serial.println("Targets missed: " + String(targetMisses));

    // Wait
    Serial.println();
    delay(3000);
  }

  // Calculate Scores
  targetTotal = targetHits + targetMisses;
  
  targetAccuracy = targetHits/targetTotal;
  targetReactionTime = totalTime/targetTotal;
  

  Serial.println("===== GOOD MORNING!=====\nThe targetGoal has been reached! :)\nBEEP BEEP BEEP BEEP BEEP BEEP BEEP BEEP BEEP BEEP");
  Serial.println();
  Serial.println("Here are your results:");
  Serial.println("Targets total: " + String(targetTotal));
  Serial.println("Targets hit: " + String(targetHits));
  Serial.println("Targets missed: " + String(targetMisses));
  Serial.println("Target Accuracy hit: " + String(targetAccuracy*100) + "%");
  Serial.println();
  Serial.println("Total time: " + String(totalTime/1000) + "s");
  Serial.println("Average reaction time: " + String(targetReactionTime) + "ms");
  Serial.println();
  delay(60000);
}
