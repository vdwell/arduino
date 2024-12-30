#include <GyverOLED.h>
GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;

void setup() {

  Serial.begin(9600);
  
  oled.init();        // инициализация
  oled.clear();       // очистка
  oled.setScale(3);   // масштаб текста (1..4)
  oled.home();        // курсор в 0,0
  oled.print(oldtext);
  delay(1000);
//  oled.setScale(1);
//  // курсор на начало 3 строки
//  oled.setCursor(0, 3);
//  oled.print("GyverOLED v1.3.2");
//  // курсор на (20, 50)
//  oled.setCursorXY(20, 50);
//  float pi = 3.14;
//  oled.print("PI = ");
//  oled.print(pi);

}



void loop() {

  Serial.println(analogRead(0));  // читаем и выводим


if (newtext != oldtext){
  oldtext = newtext;
    oled.clear();       // очистка
  oled.setScale(2);   // масштаб текста (1..4)
  oled.home();        // курсор в 0,0
  oled.print(newtext);
}

  
}
