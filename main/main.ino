#include <EEPROM.h>
#include <TimerOne.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "EEPROM_DATA.h"  // <-- VERY IMPORTANT

LiquidCrystal_I2C lcd(0x3F, 16, 2);

enum Mode {
  PASSWORD_MODE,
  ADMIN_MODE,
  LOCKED_MODE,
  SUCCESS_MODE
};

Mode currentMode;

extern volatile bool interruptFlag;

void setup() {
  lcd.init();
  lcd.backlight();

  loadSystemData();  // load from EEPROM

  currentMode = (Mode)data.systemMode;

  switch (currentMode) {
    case PASSWORD_MODE:
      askPassword();
      break;
    case ADMIN_MODE:
      askAdmin();
      break;
    case LOCKED_MODE:
      lcd.print("SYSTEM LOCKED");
      break;
    case SUCCESS_MODE:
      lcd.print("WELCOME BACK");
      break;
  }

  setupKeypadPins();
  setupInterrupt();
}

void loop() {
  if (!interruptFlag) return;
  interruptFlag = false;

  char k = getKey();
  if (k == ' ') return;

  switch (currentMode) {
    case PASSWORD_MODE:
      handlePasswordMode(k);
      break;

    case ADMIN_MODE:
      handleAdminMode(k);
      break;
  }
}
