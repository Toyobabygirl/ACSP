#include <EEPROM.h>
#include <TimerOne.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "EEPROM_DATA.h"   // <-- VERY IMPORTANT, defines SystemData structure

LiquidCrystal_I2C lcd(0x3F, 16, 2); // Initialize I2C LCD

enum Mode {
  PASSWORD_MODE,
  ADMIN_MODE,
  LOCKED_MODE,
  SUCCESS_MODE
};

Mode currentMode;                   // Tracks current system mode
extern volatile bool interruptFlag; // Flag set by timer interrupt

void setup() {
  lcd.init();
  lcd.backlight();

  loadSystemData();   // Load saved passwords and settings from EEPROM

  currentMode = (Mode)data.systemMode; // Set current mode from saved data

  switch(currentMode) { // Show appropriate prompt or message
    case PASSWORD_MODE: askPassword(); break;
    case ADMIN_MODE:    askAdmin(); break;
    case LOCKED_MODE:   lcd.print("SYSTEM LOCKED"); break;
    case SUCCESS_MODE:  lcd.print("WELCOME BACK"); break;
  }

  setupKeypadPins(); // Configure keypad pins
  setupInterrupt();  // Start timer interrupt
}

void loop() {
  if (!interruptFlag) return; // Wait until timer triggers
  interruptFlag = false;

  char k = getKey();         // Read keypad input
  if (k == ' ') return;      // No key pressed

  switch(currentMode) {      // Handle input based on current mode
    case PASSWORD_MODE:
      handlePasswordMode(k);
      break;

    case ADMIN_MODE:
      handleAdminMode(k);
      break;
  }
}
