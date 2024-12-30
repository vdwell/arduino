#include "GyverTM1637.h"
GyverTM1637 disp(2, 3);

#include <microDS3231.h>
MicroDS3231 rtc;


#define MY_PERIOD1 1000  // период в мс
uint32_t tmr1;           // переменная таймера

#define MY_PERIOD2 500  // период в мс
uint32_t tmr2;          // переменная таймера

bool flag = false;

void setup() {
  Serial.begin(9600);
  disp.clear();        // очистить
  disp.brightness(2);  // яркость 0-7
}


void loop() {

  if (millis() - tmr1 >= MY_PERIOD1) {                    // ищем разницу
    tmr1 = millis();                                      // сброс таймера
    disp.displayClock(rtc.getHours(), rtc.getMinutes());  // вывести часы и минуты
  }


  if (millis() - tmr2 >= MY_PERIOD2) {  // ищем разницу
    tmr2 = millis();                    // сброс таймера
    // мигаем двоеточием дисплея
    disp.point(int(flag));
    flag = !flag;
  }
}
