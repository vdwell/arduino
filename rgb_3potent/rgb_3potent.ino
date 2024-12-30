#define RGB_RED_PIN 6
#define RGB_GREEN_PIN 5
#define RGB_BLUE_PIN 3
#define RED_COLOR_POTENT A0
#define GREEN_COLOR_POTENT A1
#define BLUE_COLOR_POTENT A2
#include <GRGB.h>


GRGB led(COMMON_CATHODE, RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN);

void setup() {
  led.setBrightness(96);
  led.setCRT(true);
  Serial.begin(9600);
}

void loop() {
  static byte red;
  static byte green;
  static byte blue;
  red = byte(analogRead(RED_COLOR_POTENT) / 4);
  green = byte(analogRead(GREEN_COLOR_POTENT) / 4);
  blue = byte(analogRead(BLUE_COLOR_POTENT) / 4);
  led.setRGB(red, green, blue);

  static uint32_t myTimer;
  if (millis() - myTimer >= 1000) {
    myTimer = millis();
    Serial.print(red);
    Serial.print(",");
    Serial.print(green);
    Serial.print(",");
    Serial.println(blue);
  }
}
