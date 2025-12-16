#include <EEPROM.h>
#include <TimerOne.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
<<<<<<< HEAD
#include "EEPROM_DATA.h"   // <-- VERY IMPORTANT, defines SystemData structure

LiquidCrystal_I2C lcd(0x3F, 16, 2); // Initialize I2C LCD
=======
#include "EEPROM_DATA.h"  // <-- VERY IMPORTANT, defines SystemData structure

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Initialize I2C LCD
>>>>>>> dc33c52 (I removed the magic fig and merged the eeprom files)

enum Mode {
  PASSWORD_MODE,
  ADMIN_MODE,
  LOCKED_MODE,
  SUCCESS_MODE
};

<<<<<<< HEAD
Mode currentMode;                   // Tracks current system mode
extern volatile bool interruptFlag; // Flag set by timer interrupt
=======
Mode currentMode;                    // Tracks current system mode
extern volatile bool interruptFlag;  // Flag set by timer interrupt
>>>>>>> dc33c52 (I removed the magic fig and merged the eeprom files)

void setup() {
  lcd.init();
  lcd.backlight();

<<<<<<< HEAD
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
=======
  loadSystemData();  // Load saved passwords and settings from EEPROM

  currentMode = (Mode)data.systemMode;  // Set current mode from saved data

  switch (currentMode) {  // Show appropriate prompt or message
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

  setupKeypadPins();  // Configure keypad pins
  setupInterrupt();   // Start timer interrupt
}

void loop() {
  if (!interruptFlag) return;  // Wait until timer triggers
  interruptFlag = false;

  char k = getKey();     // Read keypad input
  if (k == ' ') return;  // No key pressed

  switch (currentMode) {  // Handle input based on current mode
>>>>>>> dc33c52 (I removed the magic fig and merged the eeprom files)
    case PASSWORD_MODE:
      handlePasswordMode(k);
      break;

    case ADMIN_MODE:
      handleAdminMode(k);
      break;
  }
}
