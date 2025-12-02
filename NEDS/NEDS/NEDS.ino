#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); // Change 0x3F to 0x27 if your LCD uses that address

// Keypad setup
const byte ROWS = 4;
const byte COLS = 3;

 char keys[ROWS][COLS] = {
   {'1', '2', '3'},
   {'4', '5', '6'},
   {'7', '8', '9'},
   {'*', '0', '#'}
 };

 byte rowPins[ROWS] = {9, 8, 7, 6};
 byte colPins[COLS] = {5, 4, 3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// System variables
String enteredCode = "";
String correctCode = "1234";
String adminCode = "4251";
int attemptCount = 0;
bool systemLocked = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Enter Code:");
}

void loop() {
  auto key = keypad.getKey();

  if (key) {
    switch (key) {
      case '*': // Clear
        enteredCode = "";
        lcd.clear();
        lcd.print("Enter Code:");
        break;

      case '#': // Enter
        if (systemLocked) {
          checkUserCode();
        } else {
          checkAdminCode();
        }
        break;

      default: // Numbers
        if (key) {
       
          if (enteredCode.length() < 4) {
            enteredCode += key;
            displayCode();
          } else {
            lcd.setCursor(0, 1);
            lcd.print("Max 4 digits");
            delay(800);
            displayCode(); // return to normal display
          }
        }
        break;
    }
  }
}

// Display * for each digit
void displayCode() {
  lcd.clear();
  lcd.print("Code: ");
  for (auto i = 0; i < enteredCode.length(); i++) {
    lcd.print("*");
  }
}

// Check user’s entered code
void checkUserCode() {
  if (enteredCode == correctCode) {
    lcd.clear();
    lcd.print("Access Granted");
    delay(3000);
    resetSystem();
  } else {
    attemptCount++;
    lcd.clear();
    lcd.print("Wrong Code");
    delay(1000);

    if (attemptCount >= 3) {
      systemLocked = true;
      lcd.clear();
      lcd.print("System Locked");
      lcd.setCursor(0, 1);
      lcd.print("Enter Admin Code");
    } else {
      lcd.clear();
      lcd.print("Try Again");
    }
    enteredCode = "";
  }
}

// Check admin code
void checkAdminCode() {
  if (enteredCode == adminCode) {
    lcd.clear();
    lcd.print("Admin Access");
    delay(1000);
    resetSystem();
  } else {
    lcd.clear();
    lcd.print("Invalid Admin");
    delay(1000);
    lcd.clear();
    lcd.print("Enter Admin Code");
    enteredCode = "";
  }
}

// Reset system
void resetSystem() {
  attemptCount = 0;
  systemLocked = false;
  enteredCode = "";
  lcd.clear();
  lcd.print("Enter Code:");
}
