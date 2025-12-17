
const int userPasswordlength =4;
const int userAdminlength =4;
const int  EEPROM ADDRESS = 0;

SystemData data;

void loadSystemData() {
  EEPROM.get( EEPROM ADDRESS , data);

  if (strlen(data.userPassword) !=userPasswordlength) strncpy(data.userPassword, "0000");
  if (strlen(data.adminPassword) !=userAdminlength) strncpy(data.adminPassword, "4251");

  
}

void saveSystemData() {
  EEPROM.put( EEPROM ADDRESS , data);

