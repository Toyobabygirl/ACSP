int rowPins[4] = {2, 3, 4, 5};
int colPins[3] = {6, 7, 8};

char keyMap[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

void setupKeypadPins() {
  for (int i=0;i<4;i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  for (int i=0;i<3;i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

char getKey() {
  for (int r=0;r<4;r++) {
    digitalWrite(rowPins[r], LOW);

    for (int c=0;c<3;c++) {
      if (digitalRead(colPins[c]) == LOW) {
        delay(15);
        if (digitalRead(colPins[c]) == LOW) {
          char key = keyMap[r][c];
          while (digitalRead(colPins[c]) == LOW);
          digitalWrite(rowPins[r], HIGH);
          return key;
        }
      }
    }
    digitalWrite(rowPins[r], HIGH);
  }
  return ' ';
}
