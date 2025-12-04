
void handlePasswordMode(char k) {

  if (k == '*') {
    userInput = "";
    askPassword();
    return;
  }

  if (k >= '0' && k <= '9') {
    if (userInput.length() < 4) {
      userInput += k;
      showStars(userInput.length());
    }
    return;
  }

  if (k == '#') {
    if (userInput == password) {
      lcd.clear();
      lcd.print("Access Granted");
      delay(1500);
      wrongCount = 0;
      userInput = "";
      askPassword();
    }
    else {
      wrongCount++;
      lcd.clear();
      lcd.print("Incorrect Pass");
      delay(1500);
      userInput = "";

      if (wrongCount >= 3) {
        lcd.clear();
        lcd.print("SYSTEM LOCKED");
        delay(1500);
        mode = ADMIN_MODE;
        askAdmin();
      }
      else askPassword();
    }
  }
}
void handleAdminMode(char k) {

  if (k == '*') {
    adminInput = "";
    askAdmin();
    return;
  }

  if (k >= '0' && k <= '9') {
    if (adminInput.length() < 4) {
      adminInput += k;
      showStars(adminInput.length());
    }
    return;
  }

  if (k == '#') {
    if (adminInput == adminPassword) {
      lcd.clear();
      lcd.print("Admin Correct");
      delay(1500);
      adminInput = "";
      wrongCount = 0;
      mode = PASSWORD_MODE;
      askPassword();
    }
    else {
      lcd.clear();
      lcd.print("Wrong Admin");
      delay(1500);
      adminInput = "";
      askAdmin();
    }
  }
}
