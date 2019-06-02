
#include <Wire.h>
#include "RTClib.h"
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>    // Core graphics library

RTC_DS1307 RTC;

// wiring with UNO or Mega2560:
//--------------POWER Pins--------------------------------
//   5V  connects to DC 5V
//   GND connects to Ground
//   3V3 do not need to connect(NC)
//--------------LCD Display Pins--------------------------
//   LCD_RD   connects to Analog pin A0  
//   LCD_WR   connects to Analog pin A1  
//   LCD_RS   connects to Analog pin A2  
//   LCD_CS   connects to Analog pin A3  
//   LCD_RST  connects to Analog pin A4  
//   LCD_D0   connects to digital pin 8  
//   LCD_D1   connects to digital pin 9  
//   LCD_D2   connects to digital pin 2
//   LCD_D3   connects to digital pin 3
//   LCD_D4   connects to digital pin 4
//   LCD_D5   connects to digital pin 5
//   LCD_D6   connects to digital pin 6
//   LCD_D7   connects to digital pin 7
//--------------SD-card fuction Pins ----------------------
//This Connection Only for UNO, Do not support Mega2560
//because they use different Hardware-SPI Pins
//SD_SS    connects to digital pin 10
//SD_DI    connects to digital pin 11
//SD_DO    connects to digital pin 12
//SD_SCK   connects to digital pin 13


#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define LCD_CS A3   // Chip Select goes to Analog 3
#define LCD_CD A2  // Command/Data goes to Analog 2
#define LCD_WR A1  // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


MCUFRIEND_kbv tft;


void setup(void) {
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  Serial.println(F("TFT LCD test"));

  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9595) {
    Serial.println(F("Found HX8347-I LCD driver"));
  } else if(identifier == 0x4747) {
    Serial.println(F("Found HX8347-D LCD driver"));
  } else if(identifier == 0x8347) {
    Serial.println(F("Found HX8347-A LCD driver"));
  }else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  }else if(identifier == 0x7783) {
    Serial.println(F("Found ST7781 LCD driver"));
  }else if(identifier == 0x8230) {
    Serial.println(F("Found UC8230 LCD driver"));  
  }else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101){     
      identifier=0x9341;
      Serial.println(F("Found 0x9341 LCD driver"));
  }else if(identifier==0x7793){     
       Serial.println(F("Found ST7793 LCD driver"));
  }else if(identifier==0xB509){     
       Serial.println(F("Found R61509 LCD driver"));
  }else if(identifier==0x9486){     
       Serial.println(F("Found ILI9486 LCD driver"));
  }else if(identifier==0x9488){     
       Serial.println(F("Found ILI9488 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9486; 
  }
  tft.begin(identifier); 
  tft.setRotation(1);
  tft.fillScreen(BLACK);
}

String strDate = "";
String strTime = "";
String strDateL = "";
String strTimeL = "";

void loop(void) {
  DateTime now = RTC.now(); 
  String strYear = String(now.year());
  String strMonth = "";
  String strDay = "";
  String strHour = "";
  String strMinute = "";
  String strSecond = "";
  String strAMPM = "";
  if (now.month() < 10) {
    strMonth = "0" + String(now.month());
  } else {
    strMonth = String(now.month());    
  }
  if (now.day() < 10) {
    strDay = "0" + String(now.day());
  } else {
    strDay = String(now.day());    
  }
  int intHour = now.hour();
  if (intHour >= 12) {
    if (intHour > 12) {
      intHour = intHour - 12;
    }
    strAMPM = "PM";
  } else {
    strAMPM = "AM";
  }
  if (intHour < 10) {
    strHour = "0" + String(intHour);
  } else {
    strHour = String(intHour);    
  }
  if (now.minute() < 10) {
    strMinute = "0" + String(now.minute());
  } else {
    strMinute = String(now.minute());    
  }
  if (now.second() < 10) {
    strSecond = "0" + String(now.second());
  } else {
    strSecond = String(now.second());    
  }
  strDate = strYear + "/" + strMonth + "/" + strDay;
  //strTime = strHour + ":" + strMinute + ":" + strSecond + strAMPM;
  strTime = strHour + ":" + strMinute + strAMPM;

  if (strTime != strTimeL) {
    strTimeL = strTime;
    strDateL = strDate;
    printDateTime();
  }
  delay(200);
}

void printDateTime() {
  tft.setCursor(0, 0);
  tft.setTextColor(YELLOW, BLACK);  tft.setTextSize(2);
  tft.println();
  tft.println();
  tft.println();
  tft.setTextColor(YELLOW, BLACK);  tft.setTextSize(8);
  tft.println(strDate);
  tft.setTextColor(YELLOW, BLACK);  tft.setTextSize(1);
  tft.println();
  tft.setTextColor(GREEN, BLACK);  tft.setTextSize(11);
  tft.println(strTime);  
}
