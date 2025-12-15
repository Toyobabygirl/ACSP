#ifndef EEPROM_DATA_H
#define EEPROM_DATA_H

#include <EEPROM.h>

struct SystemData {
  char userPassword[5];
  char adminPassword[5];
  byte systemMode;
  byte wrongAttempts;
};

extern SystemData data;

void loadSystemData();
void saveSystemData();

#endif
