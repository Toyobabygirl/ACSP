#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);   // Change to 0x3F if needed

// ---------------- KEYPAD ----------------
int rows[4] = {2, 3, 4, 5};
int cols[3] = {6, 7, 8};

char keys[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// ----------- MODES ------------
enum Mode { PASSWORD_MODE, AUTO_MODE, MANUAL_MODE, ADMIN_MODE, LOCKED_MODE };
Mode currentMode = PASSWORD_MODE;

// Interrupt flag
volatile bool taskFlag = false;

// ---------------- INTERRUPT ----------------
ISR(TIMER1_COMPA_vect) {
  taskFlag = true;
}

// ---------------- PASSWORD SYSTEM VARIABLES ----------------
String enteredPassword = "";
String correctPassword = "0000";
int wrongAttempts = 0;

String adminEntered = "";
String adminCode = "4251";

// ---------------- KEYPAD FUNCTION ----------------
char getKey() {
  for (int r = 0; r < 4; r++) {
    digitalWrite(rows[r], LOW);

    for (int c = 0; c < 3; c++) {
      if (digitalRead(cols[c]) == LOW) {
        delay(20);
        if (digitalRead(cols[c]) == LOW) {
          char key = keys[r][c];
          while (digitalRead(cols[c]) == LOW);
          digitalWrite(rows[r], HIGH);
          return key;
        }
      }
    }

    digitalWrite(rows[r], HIGH);
  }

  return ' ';
}

void resetSystem() {
  wrongAttempts = 0;
  enteredPassword = "";
  currentMode = PASSWORD_MODE;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
}

// ---------------- SETUP ----------------
void setup() {
  lcd.init();
  lcd.backlight();

  // keypad pins
  for (int i = 0; i < 4; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(cols[i], INPUT_PULLUP);
  }

  // timer interrupt
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();

  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
}

// ---------------- MAIN LOOP ----------------
int autoCounter = 0;

void loop() {

  char k = getKey();

  // ==========================
  //  PASSWORD ENTRY MODE
  // ==========================
  if (currentMode == PASSWORD_MODE) {

    if (k >= '0' && k <= '9') {
      if (enteredPassword.length() < 4) {
        enteredPassword += k;

        lcd.setCursor(0,1);
        lcd.print(String(enteredPassword.length(), '*'));
      }

      if (enteredPassword.length() == 4) {
        if (enteredPassword == correctPassword) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Access Granted");
          delay(2000);

          enteredPassword = "";
          lcd.clear();
          lcd.print("Mode: MANUAL");
          currentMode = MANUAL_MODE;
        } 
        else {
          wrongAttempts++;
          lcd.clear();
          lcd.print("Incorrect Pass");
          delay(2000);

          if (wrongAttempts >= 3) {
            currentMode = LOCKED_MODE;
            lcd.clear();
            lcd.print("SYSTEM LOCKED");
            delay(2000);
            lcd.clear();
            lcd.print("Enter Admin:");
          }

          enteredPassword = "";
          resetSystem();
        }
      }
    }

    return;
  }

  // ==========================
  //  LOCKED MODE → ADMIN CODE
  // ==========================
  if (currentMode == LOCKED_MODE) {

    if (k >= '0' && k <= '9') {
      adminEntered += k;

      lcd.setCursor(0,1);
      lcd.print(String(adminEntered.length(), '*'));

      if (adminEntered.length() == 4) {
        if (adminEntered == adminCode) {
          lcd.clear();
          lcd.print("Admin Correct!");
          delay(2000);

          adminEntered = "";
          resetSystem();
          currentMode = PASSWORD_MODE;
        } 
        else {
          lcd.clear();
          lcd.print("Wrong Admin");
          delay(2000);

          adminEntered = "";
          lcd.clear();
          lcd.print("Enter Admin:");
        }
      }
    }

    return;
  }

  // ==========================
  //  MANUAL MODE (Normal Keypad Use)
  // ==========================
  if (currentMode == MANUAL_MODE) {

    if (k == '#') {
      currentMode = AUTO_MODE;
      lcd.clear();
      lcd.print("Mode: AUTO");
      return;
    }

    if (k != ' ' && k != '#') {
      lcd.clear();
      lcd.print("Pressed:");
      lcd.setCursor(0,1);
      lcd.print(k);
    }
  }

  // ==========================
  //  AUTO MODE (Interrupt every 1 sec)
  // ==========================
  if (currentMode == AUTO_MODE && taskFlag) {
    taskFlag = false;

    lcd.clear();
    lcd.print("AUTO Running");
    lcd.setCursor(0,1);
    lcd.print("Count: ");
    lcd.print(autoCounter++);

    if (autoCounter > 9999) autoCounter = 0;
  }
}
