#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 10, 9, 8}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal_I2C lcd(0x27,16,2);  // Hex code en 16x2 display
int uur = 0;
int minuut = 0;
int seconde = 1;
int beoordelen = 1;
int timerstart = 0;
int tijdInvoer = 0;
int tijdKeuze = 0;
int minuut2 = 0;
int uur2 = 0;
String numString;
String numString2;
String minuutString;
String uurString;

void setup() {
  Serial.begin(9600);
  // functies om het lcd schermpje aan het werk te krijgen
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Daily Routine");
  lcd.setCursor(6,1);
  lcd.print("koken");    
}

void loop() {
  char customKey = customKeypad.getKey();
  // Wanneer je op B klikt kom je in een loop waarbij je een beoordeling kan kiezen en doorsturen naar laravel
  if (customKey == 'B'){
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Geef een");
    lcd.setCursor(2,1);
    lcd.print("beoordeling!");
    while (beoordelen == 1){
      char customKey = customKeypad.getKey();
      // Alle cijfer keys om te beoordelen
      if (customKey == 'A'){
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Beoordeling is");
        lcd.setCursor(2, 1);
        lcd.print("geannuleerd!");
        Serial.println("annuleren");
        break;
      }
      
      else if(customKey){
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("Goed gedaan!");
        lcd.setCursor(1,1);
        lcd.print("Beoordeling:");
        lcd.setCursor(14,1);
        lcd.print(customKey);
        Serial.println(customKey);
        Serial.println('b');
        break;
      }
      // Door op A van annuleren te klikken breek je de beoordelingsloop
    }
  }
  // Wanneer je op C van clock klikt kun je de uren invoeren voor de timer
  else if(customKey == 'C' && tijdKeuze == 0){
    tijdInvoer = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Voer uren in:");
    tijdInvoer = 1;
    while(tijdInvoer == 1){
      char customKey = customKeypad.getKey();
      if(customKey){
        Serial.println(customKey);
        lcd.setCursor(0, 1);
        lcd.print(customKey);
        uur = customKey - '0';
        numString = String(uur);
        Serial.println(uur);
        tijdInvoer = 2;
        //break;  
        while(tijdInvoer == 2){ 
          char customKey = customKeypad.getKey();
            if(customKey == '*'){
              tijdInvoer = 2;
              tijdKeuze = 1;
              break;  
            }
            if(customKey){
            Serial.println(customKey);
            lcd.setCursor(1, 1);
            lcd.print(customKey);
            uur2 = customKey - '0';
            numString2 = String(uur2);
            uurString = numString + numString2;
            Serial.println(uur);
            Serial.println(uurString);
            uur = uurString.toInt();
            tijdInvoer = 2;
            tijdKeuze = 1;
            break;  
        }     
        }
        break;
      }
      
    }
  }
  
  // Wanneer je opnieuw C van clock klikt kun je de minuten invoeren voor de timer
  else if(customKey == 'C' && tijdKeuze == 1){
    tijdInvoer = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Voer minuten in:");
    tijdInvoer = 1;
    while(tijdInvoer == 1){
      char customKey = customKeypad.getKey();
      if(customKey){
        Serial.println(customKey);
        lcd.setCursor(0, 1);
        lcd.print(customKey);
        minuut = customKey - '0';
        numString = String(minuut);
        Serial.println(minuut);
        tijdInvoer = 2;
        //break;  
        while(tijdInvoer == 2){ 
          char customKey = customKeypad.getKey();
            if(customKey == '*'){
              tijdInvoer = 2;
              break;  
            }
            if(customKey){
            Serial.println(customKey);
            lcd.setCursor(1, 1);
            lcd.print(customKey);
            minuut2 = customKey - '0';
            numString2 = String(minuut2);
            minuutString = numString + numString2;
            Serial.println(minuut);
            Serial.println(minuutString);
            minuut = minuutString.toInt();
            tijdInvoer = 2;
            break;  
        }     
        }
        break;
      }
      
    }
  }

  // Nadat je een tijd hebt ingevuld klik je op sterretje om de timer te starten
  else if(customKey == '*'){
    Serial.println(customKey);
    Serial.println(timerstart);
    Serial.println(tijdInvoer);
    timerstart = 1;
    tijdKeuze = 0;
    if(timerstart == 1 && tijdInvoer == 2){
      timer();
    }    
  }
}


void timer(){
  lcd.clear();
  while(timerstart == 1 && tijdInvoer == 2){
    char customKey = customKeypad.getKey();
    // Als de timer verlopen is
    if (uur == 0 && minuut == 0 && seconde == 1){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tijd is voorbij!");
      timerstart = 0;
      tijdInvoer = 0;
    } 
    // Door op A van annuleren te klikken breek je de timer loop
    else if (customKey == 'A'){
      Serial.println("annuleren");
      lcd.setCursor(4, 0);
      lcd.print("Timer is");
      lcd.setCursor(2, 1);
      lcd.print("geannuleerd!");
      timerstart = 0;
      tijdInvoer = 0;
      uur = 0;
      minuut = 0;
      seconde = 1;
      break;
    }
    else{
      // Statements waarbij de juiste waarde aangetoond wordt en er een 0 voor komt als de minuten en/of secondes onder de 10 zijn
      if(minuut >=10){
        lcd.setCursor(1, 0);
        lcd.print("Timer bereiden");
        lcd.setCursor(4, 1);
        lcd.print("0");
        lcd.setCursor(5, 1);
        lcd.print(uur);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(minuut);
        lcd.setCursor(9, 1);
        lcd.print(":");
        lcd.setCursor(10, 1);
        lcd.print(seconde);}
      else if(minuut < 10 && seconde < 10){
        lcd.setCursor(1, 0);
        lcd.print("Timer bereiden");
        lcd.setCursor(4, 1);
        lcd.print("0");
        lcd.setCursor(5, 1);
        lcd.print(uur);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print("0");
        lcd.setCursor(8, 1);
        lcd.print(minuut);
        lcd.setCursor(9, 1);
        lcd.print(":");
        lcd.setCursor(10, 1);
        lcd.print("0");
        lcd.setCursor(11, 1);
        lcd.print(seconde);
      }
      else if(minuut < 10){
        lcd.setCursor(1, 0);
        lcd.print("Timer bereiden");
        lcd.setCursor(4, 1);
        lcd.print("0");
        lcd.setCursor(5, 1);
        lcd.print(uur);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print("0");
        lcd.setCursor(8, 1);
        lcd.print(minuut);
        lcd.setCursor(9, 1);
        lcd.print(":");
        lcd.setCursor(10, 1);
        lcd.print(seconde);
      }
      else if(seconde < 10){
        lcd.setCursor(1, 0);
        lcd.print("Timer bereiden");
        lcd.setCursor(4, 1);
        lcd.print("0");
        lcd.setCursor(5, 1);
        lcd.print(uur);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(minuut);
        lcd.setCursor(9, 1);
        lcd.print(":");
        lcd.setCursor(10, 1);
        lcd.print("0");
        lcd.setCursor(11, 1);
        lcd.print(seconde);
      }
      // Delay van 1 seconde nadat er weer een seconde afmoet
      delay(1000);
      lcd.clear();
      seconde -= 1;
      // Wanneer seconde 0 is gaat er een minuut af en wordt seconde 59
      if(seconde == 0 && minuut != 0){
        lcd.setCursor(1, 0);
        lcd.print("Timer bereiden");
        lcd.setCursor(4, 1);
        lcd.print("0");
        lcd.setCursor(5, 1);
        lcd.print(uur);
        lcd.setCursor(6, 1);
        lcd.print(":");
        lcd.setCursor(7, 1);
        lcd.print(minuut);
        lcd.setCursor(9, 1);
        lcd.print(":");
        lcd.setCursor(10, 1);
        lcd.print("00");
        // Wanneer minuut 0 is gaat er een uur af en wordt minuut 59
        if(minuut >=10){
          lcd.setCursor(1, 0);
          lcd.print("Timer bereiden");
          lcd.setCursor(4, 1);
          lcd.print("0");
          lcd.setCursor(5, 1);
          lcd.print(uur);
          lcd.setCursor(6, 1);
          lcd.print(":");
          lcd.setCursor(7, 1);
          lcd.print(minuut);
          lcd.setCursor(8, 1);
          lcd.print(":");
          lcd.setCursor(9, 1);
          lcd.print(seconde);
        }
        // Dezelfde statements waarbij de juiste waarde aangetoond wordt en er een 0 voor komt als de minuten en/of secondes onder de 10 zijn
        // Als dit niet herhaalt wordt hier dan update het schermpje niet goed bij de overgangen van 10 naar 9
        else if(minuut < 10 && seconde < 10){
          lcd.setCursor(1, 0);
          lcd.print("Timer bereiden");
          lcd.setCursor(4, 1);
          lcd.print("0");
          lcd.setCursor(5, 1);
          lcd.print(uur);
          lcd.setCursor(6, 1);
          lcd.print(":");
          lcd.setCursor(7, 1);
          lcd.print("0");
          lcd.setCursor(8, 1);
          lcd.print(minuut);
          lcd.setCursor(9, 1);
          lcd.print(":");
          lcd.setCursor(10, 1);
          lcd.print("0");
          lcd.setCursor(11, 1);
          lcd.print(seconde);
        }
        else if(minuut < 10){
          lcd.setCursor(1, 0);
          lcd.print("Timer bereiden");
          lcd.setCursor(4, 1);
          lcd.print("0");
          lcd.setCursor(5, 1);
          lcd.print(uur);
          lcd.setCursor(6, 1);
          lcd.print(":");
          lcd.setCursor(7, 1);
          lcd.print("0");
          lcd.setCursor(8, 1);
          lcd.print(minuut);
          lcd.setCursor(9, 1);
          lcd.print(":");
          lcd.setCursor(10, 1);
          lcd.print(seconde);
        }
        else if(seconde < 10){
          lcd.setCursor(1, 0);
          lcd.print("Timer bereiden");
          lcd.setCursor(4, 1);
          lcd.print("0");
          lcd.setCursor(5, 1);
          lcd.print(uur);
          lcd.setCursor(6, 1);
          lcd.print(":");
          lcd.setCursor(7, 1);
          lcd.print(minuut);
          lcd.setCursor(9, 1);
          lcd.print(":");
          lcd.setCursor(10, 1);
          lcd.print("0");
          lcd.setCursor(11, 1);
          lcd.print(seconde);
        }
        delay(1000);
        lcd.clear();
        seconde = 59;
        minuut -= 1;
      }
      // Het goed omzetten wanneer er een uur af gaat
      if(minuut == 0 && seconde == 0 && uur != 0){
        minuut = 59;
        seconde = 59;
        uur -= 1;
      }  
    }
  }
}
