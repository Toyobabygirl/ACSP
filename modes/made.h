#ifndef _MODE_H_
#define _MODE_H_


void askPassword();
void askAdmin();
void handlePasswordMode(char k);
void handleAdminMode(char k);
void setupKeypadPins();
void setupInterrupt();
char getKey();

#endif