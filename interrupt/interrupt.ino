<<<<<<< HEAD
=======
const int time = 50000;
>>>>>>> dc33c52 (I removed the magic fig and merged the eeprom files)
volatile bool interruptFlag = false; // Flag set by timer interrupt

void timerISR() {
  interruptFlag = true; // Set flag when interrupt occurs
}

void setupInterrupt() {
<<<<<<< HEAD
  Timer1.initialize(50000);       // Set timer interval (50 ms)
=======
  Timer1.initialize(time);       // Set timer interval (50 ms)
>>>>>>> dc33c52 (I removed the magic fig and merged the eeprom files)
  Timer1.attachInterrupt(timerISR); // Attach interrupt function
}
