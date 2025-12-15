volatile bool interruptFlag = false; // Flag set by timer interrupt

void timerISR() {
  interruptFlag = true; // Set flag when interrupt occurs
}

void setupInterrupt() {
  Timer1.initialize(50000);       // Set timer interval (50 ms)
  Timer1.attachInterrupt(timerISR); // Attach interrupt function
}
