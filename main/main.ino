#include <EEPROM.h>
#include <TimerOne.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "EEPROM_DATA.h"  // <-- VERY IMPORTANT
#include "mode.h"

// LCD
const int columns = 16;
const int rows = 2;
const int I2c_ADDRESS = 0x3F;
LiquidCrystal_I2C lcd(I2c_ADDRESS, columns, rows);

// System modes
enum Mode { 
            PASSWORD_MODE,
            ADMIN_MODE,
            LOCKED_MODE,
            SUCCESS_MODE
 };
Mode currentMode;

// Interrupt flag (defined elsewhere)
extern volatile bool interruptFlag;

void setup() {
  lcd.init();
  lcd.backlight();

  loadSystemData();  // load EEPROM data

  // Ensure mode is valid
  if (data.systemMode > SUCCESS_MODE) data.systemMode = PASSWORD_MODE;
  currentMode = (Mode)data.systemMode;

  lcd.clear();
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
      lcd.print("WELCOME BACK");  // temporary display if system was saved as SUCCESS
      delay(2000);                // optional short display
      currentMode = PASSWORD_MODE;
      data.systemMode = currentMode;
      saveSystemData();
      lcd.clear();
      askPassword();
      break;
  }

  setupKeypadPins();
  setupInterrupt();
}

void loop() {
  if (!interruptFlag) return;
  interruptFlag = false;  // reset the flag

  char k = getKey();
  if (k == ' ') return;  // no key pressed

  switch (currentMode) {
    case PASSWORD_MODE:
      handlePasswordMode(k);
      break;

    case ADMIN_MODE:
      handleAdminMode(k);
      break;

    case SUCCESS_MODE:
      // After showing ACCESS GRANTED, go back to password mode
      currentMode = PASSWORD_MODE;
      data.systemMode = currentMode;
      saveSystemData();
      lcd.clear();
      askPassword();
      break;

    default:
      break;
  }
}