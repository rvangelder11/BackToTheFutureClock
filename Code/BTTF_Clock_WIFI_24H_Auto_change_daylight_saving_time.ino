#include <Arduino.h>
#include <TM1637Display.h>         // for the 7 segment DIO CLK displays
#include <WiFiManager.h>           // to make an AP if no WiFo connection is found
#include <ezTime.h>                // set NL time and DST
#include <NTPClient.h>             // for NTP Time
#include <Wire.h>                  // for I2C connection
#include <Adafruit_LEDBackpack.h>  // for alphanumeric I2C displays

// Module connection pins (Digital Pins)
#define red_CLK 14
#define red1_DIO 8
#define red2_DIO 11
#define redPMa 12  // original output has a defect
#define redAMa 10  // original output has a defect
#define redPMb 34
#define redAMb 35
#define red3_DIO 13

#define green_CLK 9
#define green1_DIO 2
#define green2_DIO 5
#define greenPM 7
#define greenAM 4
#define green3_DIO 6

#define orange_CLK 33
#define orange1_DIO 17
#define orange2_DIO 16
#define orangePM 18
#define orangeAM 15
#define orange3_DIO 21

#define SDA 39
#define SCL 38

bool WifiConnected = false;

//Set the red displays
int red_day = 4;
int red_month = 11;
int red_year = 2027;

//set the orange displays
int orange_day = 4;
int orange_month = 11;
int orange_year = 1960;

char* HostName = "BTTFclock";
//=====================================================================
Timezone myTZ;
TwoWire I2Cmonth = TwoWire(0);  //define I2C to be able to define non-standard pins

TM1637Display green1(green_CLK, green1_DIO);
TM1637Display green2(green_CLK, green2_DIO);
TM1637Display green3(green_CLK, green3_DIO);

TM1637Display red1(red_CLK, red1_DIO);
TM1637Display red2(red_CLK, red2_DIO);
TM1637Display red3(red_CLK, red3_DIO);

TM1637Display orange1(orange_CLK, orange1_DIO);
TM1637Display orange2(orange_CLK, orange2_DIO);
TM1637Display orange3(orange_CLK, orange3_DIO);

Adafruit_AlphaNum4 MonthRed = Adafruit_AlphaNum4();
Adafruit_AlphaNum4 MonthGreen = Adafruit_AlphaNum4();
Adafruit_AlphaNum4 MonthOrange = Adafruit_AlphaNum4();

void setup() {
  Serial.begin(115200);
  delay(5000);  // wait long enough to switch over to serial monitor
  Serial.println();

  I2Cmonth.begin(SDA, SCL, 100000);  // set non standard I2C pins. see defines
  MonthRed.begin(0x70, &I2Cmonth);   // refer to non-std I2C pins
  MonthGreen.begin(0x71, &I2Cmonth);
  MonthOrange.begin(0x72, &I2Cmonth);
  MonthGreen.setBrightness(12);  // reduce brightness of emerald alphanumeric display as it is brighter than red and orange,
  MonthOrange.setBrightness(2);
  MonthRed.setBrightness(15);
  Serial.println("Connecting");
  connectWiFi();  // start WiFi connection brings up an A/P on 192.168.4.1 on accesspoint with the name as set in  <HostName>

  analogWriteResolution(6);  // set resolution to 6 bits = 0-63
  red1.clear();              // left two positions need to remain blank
  red1.setBrightness(2);     // red needs to be set very low to compare with green
  red2.setBrightness(2);
  red3.setBrightness(2);

  green1.clear();           // left two positions need to remain blank
  green1.setBrightness(7);  // green is on max brightness
  green2.setBrightness(7);
  green3.setBrightness(7);

  orange1.clear();           // left two positions need to remain blank
  orange1.setBrightness(3);  // orange needs to be set to compare with green
  orange2.setBrightness(3);
  orange3.setBrightness(3);
  unsigned long millis_since_start = millis();
  while (!waitForSync(20)) Serial.println("Reconnecting...");
  Serial.println("time synced");
  Serial.print("it took: ");
  unsigned long delta = millis() - millis_since_start;
  Serial.print(delta);
  Serial.println(" ms");
  Serial.println(myTZ.dateTime("H:i:s"));
  //if (!myTZ.setCache(0))
  myTZ.setLocation(F("nl"));  // set to Dutch time incl DST
}
int oldminute = 60;  // to be sure that there will be a difference at start
int newminute;
byte pattern;
void loop() {
  events(); // to enable timesyncing
  newminute = myTZ.minute();
   orange3.showNumberDecEx(myTZ.second(), pattern, true, 4, 0);
  if (newminute != oldminute) {
    oldminute = newminute;
    //((MyTZ.second() % 2) == 0) ? pattern = 0b01000000 : pattern = 0b00000000;
    pattern = 0b01000000;
    Serial.print("Time: ");
    Serial.println(myTZ.dateTime("d-M-Y H:i:s"));

    red1.showNumberDecEx(red_day, 0b01000000, false, 2, 1);  //0b01000000 is with colon, leading zero = true, length = 2, pos = 0 (start at left most digit)
    DisplayMonth(MonthRed, red_month);                       // Month in text via I2C
    red2.showNumberDecEx(red_year, 0b00000000, true);        //0b00000000 is without colon
    red3.showNumberDecEx(myTZ.hour(), pattern, true, 2, 0);
    red3.showNumberDecEx(myTZ.minute(), pattern, true, 2, 2);
    AMPM(redAMa, redPMa, myTZ.hour(), 12);
    AMPM(redAMb, redPMb, myTZ.hour(), 12);  //pin 10 and 12 have become NC 10 is connected to 35 and 12 is connected to 34

    green1.showNumberDecEx(myTZ.day(), 0b01000000, false, 2, 1);
    DisplayMonth(MonthGreen, myTZ.month());  // Month in text via I2C
    green2.showNumberDecEx(myTZ.year(), 0b00000000, true);
    green3.showNumberDecEx(myTZ.hour(), pattern, true, 2, 0);
    green3.showNumberDecEx(myTZ.minute(), pattern, true, 2, 2);
    AMPM(greenAM, greenPM, myTZ.hour(), 40);

    orange1.showNumberDecEx(orange_day, 0b01000000, false, 2, 1);
    DisplayMonth(MonthOrange, orange_month);  // Month in text via I2C
    orange2.showNumberDecEx(orange_year, 0b00000000, true);
    orange3.showNumberDecEx(myTZ.hour(), pattern, true, 2, 0);
    orange3.showNumberDecEx(myTZ.minute(), pattern, true, 2, 2);
    AMPM(orangeAM, orangePM, myTZ.hour(), 6);
  }
}
