int rows[4] = {2, 3, 4, 5};
int cols[3] = {6, 7, 8};

char keys[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

void setup() {
  Serial.begin(9600);

  // Set rows as outputs HIGH
  for (int i = 0; i < 4; i++) {
    pinMode(rows[i], OUTPUT);  
    digitalWrite(rows[i], HIGH);
  }

  // Set columns as pullup inputs
  for (int i = 0; i < 3; i++) {
    pinMode(cols[i], INPUT_PULLUP);
  }
}

char getKey() {
  for (int r = 0; r < 4; r++) {
    digitalWrite(rows[r], LOW);   // activate row

    for (int c = 0; c < 3; c++) {
      if (digitalRead(cols[c]) == LOW) {
        delay(20); // debounce
        if (digitalRead(cols[c]) == LOW) {
          char key = keys[r][c];

          // wait until release
          while (digitalRead(cols[c]) == LOW);

          digitalWrite(rows[r], HIGH);
          return key;
        }
      }
    }

    digitalWrite(rows[r], HIGH);   // deactivate row
  }

  return ' '; // no key
}

void loop() {
  char k = getKey();

  if (k != ' ') {
    Serial.print("Key: ");
    Serial.println(k);
  }

  delay(10);
}
