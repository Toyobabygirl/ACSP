
char getKey() {
  for (int r = 0; r < 4; r++) {
    digitalWrite(rowPins[r], LOW);

    for (int c = 0; c < 3; c++) {
      if (digitalRead(colPins[c]) == LOW) {
        delay(20);
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
