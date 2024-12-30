#include <GyverOLED.h>
GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;

// приёмник на D2
#define IR_1    0xA2
#define IR_2    0x62
#define IR_3    0xE2
#define IR_4    0x22
#define IR_5    0x2
#define IR_6    0xC2
#define IR_7    0xE0
#define IR_8    0xA8
#define IR_9    0x90
#define IR_STAR 0x68
#define IR_0    0x98
#define IR_HASH 0xB0
#define IR_UP   0x18
#define IR_LEFT 0x10
#define IR_OK   0x38
#define IR_RIGHT 0x5A
#define IR_DOWN 0x4A
#include <NecDecoder.h>
NecDecoder ir;

String oldtext = "Hello!";
String newtext= "Hello!";
bool flag = false;

void setup() {

  Serial.begin(9600);
  attachInterrupt(0, irIsr, FALLING);
  
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


void irIsr() {
  ir.tick();
}

void loop() {

  if (ir.available()) {
    switch (ir.readCommand()) {
      // выводим в порт, тут может быть ваш код
      case IR_1: Serial.println("Pressed 1"); newtext = "Vluchaven"; break;
      case IR_2: Serial.println("Pressed 2"); newtext = "Moscow"; break;
      case IR_3: Serial.println("Pressed 3"); newtext = "Maastricht"; break;
      case IR_4: Serial.println("Pressed 4"); newtext = "Leuven"; break;
      case IR_5: Serial.println("Pressed 5"); newtext = "Heerlen"; break;
      case IR_6: Serial.println("Pressed 6"); newtext = "Tokio"; break;
      case IR_7: Serial.println("Pressed 7"); newtext = "Amsterdam"; break;
      case IR_8: Serial.println("Pressed 8"); newtext = "St.Peterburg"; break;
      case IR_9: Serial.println("Pressed 9"); newtext = "Brussels"; break;
      case IR_STAR: Serial.println("Pressed *"); break;
      case IR_0: Serial.println("Pressed 0"); break;
      case IR_HASH: Serial.println("Pressed #"); break;
      case IR_UP: Serial.println("Pressed up"); break;
      case IR_LEFT: Serial.println("Pressed left"); break;
      case IR_OK: Serial.println("Pressed ok"); break;
      case IR_RIGHT: Serial.println("Pressed right"); break;
      case IR_DOWN: Serial.println("Pressed down"); break;
    }
  }

if (newtext != oldtext){
  oldtext = newtext;
    oled.clear();       // очистка
  oled.setScale(2);   // масштаб текста (1..4)
  oled.home();        // курсор в 0,0
  oled.print(newtext);
}

  
}
