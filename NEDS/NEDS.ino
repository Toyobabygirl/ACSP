#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Keypad pins
int rowPins[4] = {2, 3, 4, 5};
int colPins[3] = {6, 7, 8};

char keyMap[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Modes
enum Mode { PASSWORD_MODE, ADMIN_MODE };
Mode mode = PASSWORD_MODE;

// Passwords
String userInput = "";
String password = "0000";
String adminInput = "";
String adminPassword = "4251";

int wrongCount = 0;

// interrupt flag
volatile bool interruptFlag = false;

// FUNCTION PROTOTYPES (IMPORTANT)
void setupInterrupt();
char getKey();
void showStars(int count);
void askPassword();
void askAdmin();

void setup() {
  lcd.init();
  lcd.backlight();

  // Keypad setup
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  setupInterrupt();
  askPassword();
}

void loop() {
  if (!interruptFlag) return;
  interruptFlag = false;

  char k = getKey();
  if (k == ' ') return;

  switch (mode) {

    case PASSWORD_MODE:
      handlePasswordMode(k);
      break;

    case ADMIN_MODE:
      handleAdminMode(k);
      break;
  }
}

