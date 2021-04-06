#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Hex code en 16x2 display
int tijd = 10;
void setup() {
  // functies om het lcd schermpje aan het werk te krijgen
  lcd.init();
  lcd.clear();         
  lcd.backlight();      
}

void loop() {
  if (tijd == 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tijd is voorbij!");
  }
  // Functie waarbij de timer aftelt in secondes en laat zien 
  else{
    lcd.setCursor(1, 1);
    lcd.print(tijd);
    if (tijd > 0){
      lcd.setCursor(0, 0);
      lcd.print("Timer bereiden:");
      lcd.setCursor(6, 1);
      lcd.print("seconde");
      delay(1000);
      lcd.clear();    
      tijd -= 1;
    }
  }
}