#include <Wire.h>
#include "hd44780.h"
#include "hd44780_I2Cexp.h"

hd44780_I2Cexp lcd;
const int LCD_COLS = 20;
const int LCD_ROWS = 4;

const int BUTTON_START_STOP = 14;
const int BUTTON_PAUZE = 15;

const int BUZZER = 13;

bool gestart = false;
bool gepauzeerd = false;
int totaal_gewerkt = 0;
int totaal_gepauzeerd = 0;

String string_totaal_gewerkt = "0";
String string_totaal_gepauzeerd = "0";
String tijd_upload = "0";

int werk_tijd = 0;
int pauze_tijd = 0;

int max_werk_tijd_minuten = 120;
int max_pauze_tijd_minuten = 15;
int max_werk_tijd = max_werk_tijd_minuten * 60;
int max_pauze_tijd = max_pauze_tijd_minuten * 60;


float startms = 0;

void setup() {
  Serial.begin(9600);

  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if(status) // non zero status means it was unsuccesful
  {
    hd44780::fatalError(status); // does not return
  }
  // initalization was successful, the backlight should be on now

  
  pinMode(BUTTON_START_STOP, INPUT_PULLUP);
  pinMode(BUTTON_PAUZE, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  
  lcd.clear();
  lcd.print("druk op START/STOP  om te beginnen");
  Serial.println("e");
//  lcd.clear();
  delay(1000);
}

void loop() {
  if (!digitalRead(BUTTON_START_STOP)){
    delay(200);
    if (!digitalRead(BUTTON_START_STOP)) {
      lcd.clear();
      start_stop();
      }
  }
}



//=========================================================================

void start_stop(){
  if (gestart == false){
    gestart = true;
    lcd.print("start");
    Serial.println("s");
    tone(BUZZER, 700);
    delay(1000);
    lcd.clear();
    noTone(BUZZER);

    while (true){
//      Serial.println("in de start_stop");
      startms = millis();
      while (true){        
        if (millis() >= (startms + 1000)){
          werk_tijd = werk_tijd + 1;
//          Serial.println(werk_tijd);
          bereken_minuten(werk_tijd);

          if (werk_tijd == max_werk_tijd){
            Serial.println("gp");
            tone(BUZZER, 700);
            }
          break;
          }
        }

    if (!digitalRead(BUTTON_PAUZE)){
      delay(10);
      if (!digitalRead(BUTTON_PAUZE)) {
        totaal_gewerkt = totaal_gewerkt + werk_tijd;
        werk_tijd = 0;
        noTone(BUZZER);
        pauze(); /////// pauze()
//        break;
        }        
      }


      else if (!digitalRead(BUTTON_START_STOP)){
      delay(10);
      if (!digitalRead(BUTTON_START_STOP)) {
//        Serial.println("stop de hele app");
          totaal_gewerkt = totaal_gewerkt + werk_tijd;
          string_totaal_gewerkt = String(totaal_gewerkt);
          string_totaal_gepauzeerd = String(totaal_gepauzeerd);
          tijd_upload = string_totaal_gewerkt + " " + string_totaal_gepauzeerd;
          Serial.println(tijd_upload);
        break;
        }        
      }
    }
  }
   
    gestart = false;
    lcd.clear();
    lcd.print("gestopt");
    Serial.println("e");
    delay(1000);    
}



//=========================================================================

void pauze(){
  if (gestart == true && gepauzeerd == false){
    gepauzeerd = true;
    lcd.clear();
    lcd.print("pauze");
    Serial.println("p");
    delay(1000);
    lcd.clear();
    
    while (true){
//      Serial.println("in de pauze");
      startms = millis();
      while (true){        
        if (millis() >= (startms + 1000)){
          pauze_tijd = pauze_tijd + 1;
          bereken_minuten(pauze_tijd);

          if (pauze_tijd == max_pauze_tijd){
            Serial.println("gw");
            tone(BUZZER, 700);
            }
          break;
          }
        }

    if (!digitalRead(BUTTON_PAUZE)){
//      Serial.println("ik wil pauze breken");
      delay(10);
      if (!digitalRead(BUTTON_PAUZE)) {
        totaal_gepauzeerd = totaal_gepauzeerd + pauze_tijd;
        pauze_tijd = 0;
        noTone(BUZZER);
        gepauzeerd = false;
        lcd.clear();
        lcd.print("werk hervat");
        Serial.println("r");
        delay(1000);
        lcd.clear();
        break;
        }        
      }
    }
    }
}



//=========================================================================

void bereken_minuten(int seconden){
//  Serial.print(seconden);
//  Serial.println(" seconden");

  String string_seconden = "";
  String string_minuten = "";
  String string_uren = "";

  int minuten = seconden / 60;
  seconden = seconden % 60;
  int uren = minuten / 60;
  minuten = minuten % 60;

  if (uren < 10){
    string_uren = String(uren);
    string_uren = "0" + string_uren;
    }
  else{
    string_uren = String(uren);
    }


  if (minuten < 10){
    string_minuten = String(minuten);
    string_minuten = "0" + string_minuten;
    }
  else{
    string_minuten = String(minuten);
    }


  if (seconden < 10){
    string_seconden = String(seconden);
    string_seconden = "0" + string_seconden;
    }
  else{
    string_seconden = String(seconden);
    }

  String hele_tijd = String(string_uren + " : " + string_minuten + " : " + string_seconden);

  lcd.clear();
  lcd.print(hele_tijd);
  }
