// размеры клавиатуры
#define KP_ROWS 4
#define KP_COLS 4
// пины подключения (по порядку штекера)
byte colPins[KP_COLS] = { 7, 6, 5, 4 };
byte rowPins[KP_ROWS] = { 11, 10, 9, 8 };
// массив имён кнопок
char keys[KP_ROWS][KP_COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
// подключаем либу
#include <SimpleKeypad.h>
// создаём клавиатуру
SimpleKeypad pad((char*)keys, rowPins, colPins, KP_ROWS, KP_COLS);


#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;


#define RED_LED_PIN 2
#define GREEN_LED_PIN 3

char password[4] = "1234";

boolean locked = false;
boolean setting_password = false;
int i = 0;
int j = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  oled.init();       // инициализация
  oled.clear();      // очистка
  oled.setScale(2);  // масштаб текста (1..4)
  oled.home();       // курсор в 0,0
  oled.print("Привет!");

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, HIGH);

  Serial.print(password[0]);
  Serial.print(password[1]);
  Serial.print(password[2]);
  Serial.print(password[3]);
  Serial.println();
}



void loop() {

  // получить текущую нажатую клавишу
  // вернёт 0 символ если ничего не нажато
  char key = pad.getKey();
  // если кнопка нажата (не 0 символ)

  if (key) {
    // выводим в порт
    Serial.println(key);
    oled.clear();
    oled.home();
    oled.print(key);

    if (setting_password & !locked) {
      password[i] = key;
      i++;
      if (i > 3) {
        Serial.println("Password is set");
        Serial.print(password[0]);
        Serial.print(password[1]);
        Serial.print(password[2]);
        Serial.print(password[3]); 
        Serial.println();
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);
        setting_password = false;
        locked = true;
        i = 0;
      }
    }
    if (key == '*' & !setting_password) {
      Serial.println("* is pressed. setting new password");
      setting_password = true;
    }

    if (locked) {
      Serial.print("j value is ");
      Serial.println(j);
      if (password[j] == key) {
        j++;

        if (j >= 4) {
          Serial.println("lock is opened");
          locked = false;
          digitalWrite(GREEN_LED_PIN, LOW);
          digitalWrite(RED_LED_PIN, HIGH);
          j = 0;
        }
      } else {
        j = 0;
      }
    }
  }

  /*  
  if (key) {
    switch (key) {
      // выводим в порт, тут может быть ваш код
      case '1': Serial.println("Pressed 1"); break;
        case '2': Serial.println("Pressed 2"); break;
        case '3': Serial.println("Pressed 3"); break;
        case '4': Serial.println("Pressed 4"); break;
        case '5': Serial.println("Pressed 5"); break;
        case '6': Serial.println("Pressed 6"); break;
        case '7': Serial.println("Pressed 7"); break;
        case '8': Serial.println("Pressed 8"); break;
        case '9': Serial.println("Pressed 9"); break;
        case '*': Serial.println("Pressed *"); break;
        case '0': Serial.println("Pressed 0"); break;
        case '#': Serial.println("Pressed #"); break;
        case 'A': Serial.println("Pressed A"); break;
        case 'B': Serial.println("Pressed A"); break;
        case 'C': Serial.println("Pressed A"); break;
        case 'D': Serial.println("Pressed A"); break;                
    }
  }
  */
}