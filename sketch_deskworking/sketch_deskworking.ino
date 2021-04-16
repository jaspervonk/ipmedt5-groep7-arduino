#include <Wire.h>
#include "hd44780.h"
#include "hd44780_I2Cexp.h"

hd44780_I2Cexp lcd;
const int LCD_COLS = 20;
const int LCD_ROWS = 4;

const int BUTTON_START_STOP = 14;

const int BUZZER = 8;
const int sensorPin = A2;

int sensor_value;
bool sensor_bijhouden = false;

bool gestart = false;
bool gepauzeerd = false;
int totaal_gewerkt = 0;
int totaal_gepauzeerd = 0;

int aantal_pauzes = 0;
String string_aantal_pauzes = "0";

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
float sensor_startms = 0;

void setup() {
  Serial.begin(9600);

  int status;
  status = lcd.begin(20, 4);
  if(status) // non zero status means it was unsuccesful
  {
    hd44780::fatalError(status); // does not return
  }
  // initalization was successful, the backlight should be on now

  
  pinMode(BUTTON_START_STOP, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  lcd.clear();
  lcd.print("druk op START/STOP  om te beginnen");
  lcd.backlight();
  Serial.println("e");
//  lcd.clear();
  delay(1000);
}

void loop() {;
  sensor_value = analogRead(sensorPin);

  // Als de Start knop wordt ingedrukt, start de applicatie
  if (!digitalRead(BUTTON_START_STOP)){
    delay(200);
    if (!digitalRead(BUTTON_START_STOP)) {
      lcd.clear();
      start_stop();
      }
  }

  delay(500);

}



//=========================================================================

void start_stop(){
  if (gestart == false){
    gestart = true;
    lcd.print("start");
    Serial.println("s");
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(BUZZER, LOW);

    //De timerunctie voor de werktijd
    while (true){
      startms = millis();
      while (true){        
        if (millis() >= (startms + 1000)){
          werk_tijd = werk_tijd + 1;
          bereken_minuten(werk_tijd); //Werktijd wordt gestuurd naar- en berekend in berekenminuten()

          //Max-tijd waarschuwfunctie
          if (werk_tijd == max_werk_tijd){
            Serial.println("gp");
            digitalWrite(BUZZER, HIGH);
            }
          break;
          }
        }


    //De condition loops om in de timerfucntie van de druksenosr te komen
    sensor_value = analogRead(sensorPin);
    if (sensor_value > 200){
      sensor_bijhouden = false;
      }

    if (sensor_value < 200 && sensor_bijhouden == false){
      sensor_startms = millis();
      sensor_bijhouden = true;
      }


    //De tierfunctie van 5 seconden van de druksensor
    if (sensor_value < 200 && millis() >= (sensor_startms + 5000)){
        totaal_gewerkt = totaal_gewerkt + werk_tijd;
        werk_tijd = 0;
        digitalWrite(BUZZER, LOW);
        pauze();
      }


      //functie om de sessie te beëindigen
      if (!digitalRead(BUTTON_START_STOP)){
      delay(10);
      if (!digitalRead(BUTTON_START_STOP)) {
//        Serial.println("stop de hele app");
          totaal_gewerkt = totaal_gewerkt + werk_tijd;
          string_totaal_gewerkt = String(totaal_gewerkt);
          string_totaal_gepauzeerd = String(totaal_gepauzeerd);
          string_aantal_pauzes = String(aantal_pauzes);
          tijd_upload = string_totaal_gewerkt + " " + string_totaal_gepauzeerd + " " + string_aantal_pauzes; //alle waardes worden netjes op een rijtje gezet zodat de python het kan uitlezen
          Serial.println(tijd_upload);
        break;
        }        
      }
    }
  }

    //Alle variabelen worden weer gerest, sessie word afgesloten
    gestart = false;
    lcd.clear();
    lcd.print("gestopt");
    aantal_pauzes = 0;
    werk_tijd = 0;
    totaal_gewerkt = 0;
    totaal_gepauzeerd = 0;
    Serial.println("e");
    delay(1000);
    lcd.clear();
    lcd.print("druk op START/STOP  om te beginnen");    
}



//=========================================================================

void pauze(){
  if (gestart == true && gepauzeerd == false){
    gepauzeerd = true;
    aantal_pauzes = aantal_pauzes + 1;
    lcd.clear();
    lcd.print("pauze");
    Serial.println("p");
    delay(1000);
    lcd.clear();

    //Timerfunctie pauzes    
    while (true){
      startms = millis();
      while (true){        
        if (millis() >= (startms + 1000)){
          pauze_tijd = pauze_tijd + 1;
          bereken_minuten(pauze_tijd);

          if (pauze_tijd == max_pauze_tijd){
            Serial.println("gw");
            digitalWrite(BUZZER, HIGH);
            }
          break;
          }
        }

    //Bij hoge waarde pauze beëindigen
    sensor_value = analogRead(sensorPin);
    if (sensor_value > 200){
      totaal_gepauzeerd = totaal_gepauzeerd + pauze_tijd;
        pauze_tijd = 0;
        digitalWrite(BUZZER, LOW);
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



//=========================================================================

void bereken_minuten(int seconden){
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

  
