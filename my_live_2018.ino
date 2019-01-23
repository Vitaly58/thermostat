unsigned long timing; // Переменная для хранения точки отсчета
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define TIME_STOP 300 // таймаут
#define LED_PIN_K 4 // термостат
#define POROG_TEMP 35 // порог температуры
#define TEMP_KOF 0.488
float grad;

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() // процедура setup
{

  //Функция определяет опорное напряжение относительно которого происходят аналоговые измерения 
  //analogReference(DEFAULT);
  //DEFAULT: стандартное опорное напряжение 5 В (на платформах с напряжением питания 5 В) или 3.3 В (на платформах с напряжением питания 3.3 В)
  //INTERNAL: встроенное опорное напряжение 1.1 В на микроконтроллерах ATmega168 и ATmega328, и 2.56 В на ATmega8.
  pinMode(LED_PIN_K, OUTPUT);
  
  /*lcd config*/
   lcd.init(); 
   lcd.backlight();
  /*lcd config*/

  pinMode(A0, INPUT); // сенсор LM35 подключим к аналоговому входу A0
  Serial.begin(9600); // подключаем монитор порта
  
  lcd.setCursor(1,0);
  lcd.print("Temperature: ");
}


void loop()
{
  grad = (analogRead(A0)*TEMP_KOF);
  
  if (grad>POROG_TEMP) {
      digitalWrite(LED_PIN_K,LOW);
    }
  else {
   for(int i=0;i<=255;i++)
        analogWrite(LED_PIN_K, 255);
  }
  
  show_screen();
}

void show_screen()
{
  if (millis() - timing > TIME_STOP){ // Вместо TIME_STOP подставьте нужное вам значение паузы
      timing = millis();
      lcd.setCursor(14,0);
      lcd.print(grad);
  } 
}
