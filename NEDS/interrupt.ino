
ISR(TIMER1_COMPA_vect) {
  interruptFlag = true;
}

void setupInterrupt() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 24999;              
  TCCR1B |= (1 << WGM12);     
  TCCR1B |= (1 << CS11) | (1 << CS10); 
  TIMSK1 |= (1 << OCIE1A);    
  sei();
}
