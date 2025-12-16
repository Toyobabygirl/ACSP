
const int up =4;
const int ap =4;
const int  Da = 0;

SystemData data;

void loadSystemData() {
  EEPROM.get(Da , data);

  if (strlen(data.userPassword) !=up) strcpy(data.userPassword, "0000");
  if (strlen(data.adminPassword) !=ap) strcpy(data.adminPassword, "4251");

  
}

void saveSystemData() {
  EEPROM.put(Da , data);

