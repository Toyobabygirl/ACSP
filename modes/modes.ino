String userInput = "";   // Stores user password input
String adminInput = "";  // Stores admin code input

void handlePasswordMode(char k) {
  if (k == '*') {                // Clear input
    userInput = "";
    askPassword();
    return;
  }

  if (k >= '0' && k <= '9') {    // Accept digits only
    userInput += k;
    showStars(userInput.length()); // Show * for each digit
    return;
  }

  if (k == '#') {                // Submit password
    if (userInput == data.userPassword) {
      lcd.clear();
      lcd.print("Access Granted");

      data.systemMode = SUCCESS_MODE;
      data.wrongAttempts = 0;
      saveSystemData();          // Save success state

      delay(1500);
      askPassword();
      userInput = "";
    }
    else {
      data.wrongAttempts++;      // Increase wrong attempts
      saveSystemData();

      lcd.clear();
      lcd.print("Wrong Password");
      delay(1500);

      if (data.wrongAttempts >= 3) {
        data.systemMode = ADMIN_MODE; // Switch to admin mode
        saveSystemData();
        askAdmin();
      } else {
        askPassword();
      }
      userInput = "";
    }
  }
}

void handleAdminMode(char k) {
  if (k == '*') {                // Clear admin input
    adminInput = "";
    askAdmin();
    return;
  }

  if (k >= '0' && k <= '9') {    // Accept digits only
    adminInput += k;
    showStars(adminInput.length());
    return;
  }

  if (k == '#') {                // Submit admin code
    if (adminInput == data.adminPassword) {
      lcd.clear();
      lcd.print("Admin OK");

      data.systemMode = PASSWORD_MODE; // Reset to normal mode
      data.wrongAttempts = 0;
      saveSystemData();

      delay(1500);
      askPassword();
      adminInput = "";
    } else {
      lcd.clear();
      lcd.print("Wrong Admin");
      delay(1500);
      adminInput = "";
      askAdmin();
    }
  }
}
