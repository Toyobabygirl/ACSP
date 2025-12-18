
#ifndef EEPROM_DATA_H
#define EEPROM_DATA_H

#include <EEPROM.h>
const int passwordbyte = 5;

struct SystemData {
  char userPassword[passwordbyte];
  char adminPassword[passwordbyte];
  byte systemMode;
  byte wrongAttempts;
};

extern SystemData data;

void loadSystemData();
void saveSystemData();

#endif
