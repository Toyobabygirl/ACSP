
void showStars(int count) {
  lcd.setCursor(0, 1);
  for (int i = 0; i < count; i++) lcd.print('*');
}

void askPassword() {
  lcd.clear();
  lcd.print("Enter Password:");
}

void askAdmin() {
  lcd.clear();
  lcd.print("Admin Code:");
}
