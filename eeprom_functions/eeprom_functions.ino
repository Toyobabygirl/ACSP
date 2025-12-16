#include "EEPROM_DATA.h"
<<<<<<< HEAD

SystemData data; //stores system

void loadSystemData() {
  EEPROM.get(0, data); //read system

  if (strlen(data.userPassword) != 4) strcpy(data.userPassword, "0000");
  if (strlen(data.adminPassword) != 4) strcpy(data.adminPassword, "4251");

  if (data.systemMode > 5) data.systemMode = 0;// Reset invalid system mode
  if (data.wrongAttempts > 10) data.wrongAttempts = 0;// Reset wrong attempts

  EEPROM.put(0, data);
}

void saveSystemData() {
  EEPROM.put(0, data);
=======
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
>>>>>>> dc33c52 (I removed the magic fig and merged the eeprom files)
}
