#include "EEPROM_DATA.h"

SystemData data;

void loadSystemData() {
  EEPROM.get(0, data);

  if (strlen(data.userPassword) != 4) strcpy(data.userPassword, "0000");
  if (strlen(data.adminPassword) != 4) strcpy(data.adminPassword, "4251");

  if (data.systemMode > 5) data.systemMode = 0;
  if (data.wrongAttempts > 10) data.wrongAttempts = 0;

  EEPROM.put(0, data);
}

void saveSystemData() {
  EEPROM.put(0, data);
}
