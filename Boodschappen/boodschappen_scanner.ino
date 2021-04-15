#include <Wire.h>
#include <hd44780.h>                       // Library voor LCD display
#include <hd44780ioClass/hd44780_I2Cexp.h> 

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

const int LCD_COLS = 20;
const int LCD_ROWS = 4;

int buzzerPin = 8;
int c = 261;
int d = 293;
int e = 329;
int f = 349;
int g = 391;
int a = 440;
int Bb = 466;
int b = 493;
int hogeC = 523;
int achtste = 500/2;
int kwart = 1000/2;
int half = 2000/2;

void setup()
{
  Serial.begin(9600); 
  lcd.begin(0,1);
  Serial.println("Running");
  pinMode(buzzerPin, OUTPUT);
  int status;

	status = lcd.begin(LCD_COLS, LCD_ROWS);
	if(status) // non zero status means it was unsuccesful
	{
		hd44780::fatalError(status); // does not return
	}
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Scan barcode");
  if(Serial.available()) //Controleer of er er Seriele data binennkomt.
  { 
    lcd.clear();
    while(Serial.available()) //Blijf byte voor byte inlezen totdat alle bytes binnen zijn.

    {

      char input = Serial.read(); //Lees 1 byte van de data en sla het op in de variabele input.

      Serial.print(input); 
      lcd.print(input); // Print deze variabele op het lcd display


      delay(5); // A small delay 

    }
    // Laat de buzzer 3 x piepen als de data is ontvangen
    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
    }
    delay(5000);// Print deze variabele op het lcd display voor 5 seconden.
    lcd.clear();// Maak het lcd display leeg.
  }  
  
}