#include "SevenSegmentTM1637.h"

const int DISPLAY_CLK = 3;
const int DISPLAY_DIO = 2;

const int BUTTON_START_STOP = 12;
const int BUTTON_PAUZE = 11;


bool gestart = false;
bool gepauzeerd = false;
int totaal_gewerkt = 0;
int totaal_gepauzeerd = 0;

int werk_tijd = 0;
int pauze_tijd = 0;


float startms = 0;

SevenSegmentTM1637 display(DISPLAY_CLK, DISPLAY_DIO);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_START_STOP, INPUT_PULLUP);
  pinMode(BUTTON_PAUZE, INPUT_PULLUP);
  
  display.begin();
  display.setBacklight(100);
  display.clear();
  display.print("BOOT");
  delay(1000);
}

void loop() {
  if (!digitalRead(BUTTON_START_STOP)){
    delay(200);
    if (!digitalRead(BUTTON_START_STOP)) {
      start_stop();
      }
  }

//  else if (!digitalRead(BUTTON_PAUZE)){
//    delay(200);
//    if (!digitalRead(BUTTON_PAUZE)) {
//      pauze();
//      }
//   }


//  display.println("menu");
}



//=========================================================================

void start_stop(){
  if (gestart == false){
    gestart = true;
    display.print("STAR");
    delay(1000);

    while (true){
//      Serial.println("in de start_stop");
      startms = millis();
      while (true){        
        if (millis() >= (startms + 1000)){
          werk_tijd = werk_tijd + 1;
//          Serial.println(werk_tijd);
          bereken_minuten(werk_tijd);
          break;
          }
        }

    if (!digitalRead(BUTTON_PAUZE)){
      delay(200);
      if (!digitalRead(BUTTON_PAUZE)) {
        totaal_gewerkt = totaal_gewerkt + werk_tijd;
        werk_tijd = 0;
        pauze(); /////// pauze()
//        break;
        }        
      }


      else if (!digitalRead(BUTTON_START_STOP)){
      delay(200);
      if (!digitalRead(BUTTON_START_STOP)) {
//        Serial.println("stop de hele app");
        break;
        }        
      }
    }
  }
   
    gestart = false;
    display.print("stop");
    delay(1000);    
}



//=========================================================================

void pauze(){
  if (gestart == true && gepauzeerd == false){
    gepauzeerd = true;
    display.print("PAUS");
    delay(1000);
    
    while (true){
//      Serial.println("in de pauze");
      startms = millis();
      while (true){        
        if (millis() >= (startms + 1000)){
          pauze_tijd = pauze_tijd + 1;

          bereken_minuten(pauze_tijd);
          break;
          }
        }

    if (!digitalRead(BUTTON_PAUZE)){
//      Serial.println("ik wil pauze breken");
      delay(10);
      if (!digitalRead(BUTTON_PAUZE)) {
        totaal_gepauzeerd = totaal_gepauzeerd + werk_tijd;
        pauze_tijd = 0;
        gepauzeerd = false;
        display.print("HERV");
        delay(1000);
        break;
        }        
      }
    }
    }
    
    
//  else if (gestart == true && gepauzeerd == true){
//    gepauzeerd = false;
//    display.print("HERV");
//    }
}



//=========================================================================

void bereken_minuten(int seconden){
//  Serial.print(seconden);
//  Serial.println(" seconden");

  int minuten = seconden / 60;
//  Serial.println(minuten);

  if (minuten < 10){
    String deel_1 = "000";
    String deel_2 = String(minuten);
    String compleet = deel_1 + deel_2;
    display.print(compleet);
    }

  else if (minuten < 100){
    String deel_1 = "00";
    String deel_2 = String(minuten);
    String compleet = deel_1 + deel_2;
    display.print(compleet);
    }

  else if (minuten < 1000){
    String deel_1 = "000";
    String deel_2 = String(minuten);
    String compleet = deel_1 + deel_2;
    display.print(compleet);
    }
  }
