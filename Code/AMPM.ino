void AMPM(int AMLed, int PMLed, int hour, int dutycycle) {
  if (hour >= 12) {
    analogWrite(PMLed, dutycycle);
    analogWrite(AMLed, 0);
  } else {
    analogWrite(AMLed, dutycycle);
    analogWrite(PMLed, 0);
  }
}