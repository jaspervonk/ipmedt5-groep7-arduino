#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Hex code en 16x2 display
int uur = 0;
int minuut = 1;
int seconde = 1;
void setup() {
  // functies om het lcd schermpje aan het werk te krijgen
  lcd.init();
  lcd.clear();         
  lcd.backlight();      
}

void loop() {
  // Als de timer verlopen is
  if (uur == 0 && minuut == 0 && seconde == 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tijd is voorbij!");
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
      if(minuut == 0 && uur != 0){
        minuut = 59;
        uur -= 1;
      }
    }
  }
}