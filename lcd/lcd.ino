void showStars(int count) {
  lcd.setCursor(0,1);        // Move cursor to second line
  for (int i=0; i<count; i++) lcd.print("*"); // Display '*' for each entered character
}

void askPassword() {
  lcd.clear();               // Clear LCD
  lcd.print("Enter Password:"); // Prompt user
}

void askAdmin() {
  lcd.clear();               // Clear LCD
  lcd.print("Admin Code:");     // Prompt for admin code
}
