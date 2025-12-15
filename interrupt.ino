volatile bool interruptFlag = false;

void timerISR() {
  interruptFlag = true;
}

void setupInterrupt() {
  Timer1.initialize(50000);
  Timer1.attachInterrupt(timerISR);
}
