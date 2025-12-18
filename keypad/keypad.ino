
int rowPins[4] = {2, 3, 4, 5}; // Keypad row pins
int colPins[3] = {6, 7, 8};    // Keypad column pins

char keyMap[4][3] = {          // Key mapping
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

void setupKeypadPins() {
  for (int i=0;i<4;i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH); // Set rows HIGH initially
  }
  for (int i=0;i<3;i++) {
    pinMode(colPins[i], INPUT_PULLUP); // Enable internal pull-ups for columns
  }
}

char getKey() {
  for (int r=0;r<4;r++) {
    digitalWrite(rowPins[r], LOW); // Activate current row

    for (int c=0;c<3;c++) {
      if (digitalRead(colPins[c]) == LOW) { // Key pressed
        delay(15);                           // Debounce
        if (digitalRead(colPins[c]) == LOW) {
          char key = keyMap[r][c];
          while (digitalRead(colPins[c]) == LOW); // Wait until key released
          digitalWrite(rowPins[r], HIGH);         // Deactivate row
          return key;                             // Return detected key
        }
      }
    }
    digitalWrite(rowPins[r], HIGH); // Deactivate row
  }
  return ' '; // No key pressed
}
