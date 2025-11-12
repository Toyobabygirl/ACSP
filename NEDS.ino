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

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
