void DisplayMonth(Adafruit_AlphaNum4 MonthDisplay, int monthNr) {
  char *MonthName[13] = { "NONE", "JAN ", "FEB ", "MAR ", "APR ", "MEI ", "JUN ", "JUL ", "AUG ", "SEPT", "OKT", "NOV ", "DEC " };
  // keep pos 0 blank, as monthname = 3 pos
  MonthDisplay.writeDigitAscii(0, MonthName[monthNr][0]);
  MonthDisplay.writeDigitAscii(1, MonthName[monthNr][1]);
  MonthDisplay.writeDigitAscii(2, MonthName[monthNr][2]);
  MonthDisplay.writeDigitAscii(3, MonthName[monthNr][3]);
  MonthDisplay.writeDisplay();
}