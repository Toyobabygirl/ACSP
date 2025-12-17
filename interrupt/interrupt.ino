
const int time = 50000;
bool flag = false;
volatile bool interruptFlag = flag;  // Flag set by timer interrupt

void timerISR() {
  interruptFlag = true;  // Set flag when interrupt occurs
}

void setupInterrupt() {

  Timer1.initialize(time);  // Set timer interval (50 ms)

  Timer1.initialize(time);           // Set timer interval (50 ms)
  Timer1.attachInterrupt(timerISR);  // Attach interrupt function
}
