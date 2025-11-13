#include <LiquidCrystal_I2c.h>
LiquidCrystal_I2c lcd(0x3F,16,2);
const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] {
{'1', '2', '3'},
{'4', '5', '6'},
{'7', '8', '9'},
{'*', '0', '#'},

}
byte rowPins[ROWS]{4, 5, 6},
byte colPins[COLS]{2, 5, 8, 0}

String enterCode = "";
String correctCode = "1234";
String adminCode = "0000";
int attemptCount = 0;
bool systemLocked = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Enter Code:");

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Door locked
}

void loop() {
  // put your main code here, to run repeatedly:

}
