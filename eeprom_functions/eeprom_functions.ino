#include <EEPROM.h>
#include "EEPROM_DATA.h" 

const int userPasswordLength = 4;
const int userAdminLength    = 4;
const int EEPROM_ADDRESS     = 0;
const int minWrongAttemptt   = 0;
const int maxWrongAttemptss   = 3;

// Global system data
SystemData data;

// load data
void loadSystemData() {
    EEPROM.get(EEPROM_ADDRESS, data);

    // Initialize user password if invalid
    if (strlen(data.userPassword) != userPasswordLength) {
        strncpy(data.userPassword, "0000", userPasswordLength);
        
    }

    // Initialize admin password if invalid
    if (strlen(data.adminPassword) != userAdminLength) {
        strncpy(data.adminPassword, "4251", userAdminLength);
     
    }

    // Initialize wrongAttempts if corrupted
    if (data.wrongAttempts < minWrongAttemptt || data.wrongAttempts > maxWrongAttemptss) {
        data.wrongAttempts = minWrongAttemptt;
    }

    
}

// ---------------- Save Data to EEPROM ----------------
void saveSystemData() {
    EEPROM.put(EEPROM_ADDRESS, data);
}
