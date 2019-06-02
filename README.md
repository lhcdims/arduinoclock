# arduinoclock

Arduino Clock (W/ TFT LCD, without screen touch)

# What do you need

- Arduino Mega

- tinyRTC

- 3.5 inch TFT LCD for Arduino

# Setup Instrctions: (Windows 10 PC)

1. Install arduino IDE from www.arduino.cc

2. Copy all folders (Adafruit_GFX, Adafruit_GFX_Library, Adafruit_TFTLCD, DS1307RTC, MCUFRIEND_kbv, RTClib) to:
    c:\users\Administrator\Document\Arduino\Libraries
    
3. open clock02.ino

4. select Arduino Mega 2560 in the Arduino IDE

5. Plug the TFT into the Arduino MEGA 2560

6. Connect the VCC, GND, SCL, SDA from the tinyRTC to the Arduino Mega 2560's +5V(Any +5v), GND(Any GND), SCL(21), SDA(20) respectively.

7. Plug the Arduino Mega 2560 to the PC via the USB Cable.

8. select the appropriate COM port for the Arduino Mega 2560

9. Click [Upload] in the Arduino IDE.

10. The clock show be shown in the TFT LCD.

11. If you have a 3D printer, print a cover for the clock!



