/**
 * Проект для тестирования, передачи данных, запускал через Arduino IDE.
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LED_FAILED 4
#define LED_SUCCESS 3

class Led {
    private:
      byte pin;
    public:
      Led(byte pin): pin(pin) {}
      void attach() {
         pinMode(pin, OUTPUT); 
      }

      void up() {
        digitalWrite(pin, HIGH);
      }

      void down() {
        digitalWrite(pin, LOW); 
      }
      
};

RF24 radio(10, 9); // CE, CSP

Led ledSuccess(LED_SUCCESS);
Led ledFailed(LED_FAILED);

const byte address[6] = "00001";

typedef struct {
  float lan;
  float lng;
  uint8_t n;
}
Package;

int serial_putc(char c, FILE *) {
    // tft.write(c);
    Serial.write(c);
    return c;
}

void printfBegin(void) {
   fdevopen(&serial_putc, 0 );
}


void setup() { 
  ledSuccess.attach();
  ledFailed.attach();
  ledSuccess.up();
  ledFailed.up();
   Serial.begin(9600);
   Serial.println("Start");
  printfBegin();
  radio.begin(); //активировать модуль
  
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(1, 30);     //(время между попыткой достучаться, число попыток)
  radio.setPayloadSize(32);     //размер пакета, в байтах
  radio.openWritingPipe(address);   //мы - труба 0, открываем канал для передачи данных
  
  radio.setChannel(40);  //выбираем канал (в котором нет шумов!)
  radio.setPALevel (RF24_PA_HIGH); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.printDetails();
  delay(5000);

  radio.powerUp(); //начать работу
  radio.stopListening();  //не слушаем радиоэфир, мы передатчик

  ledSuccess.down();
  ledFailed.down();
}


byte n = 2;
byte f = 0;
byte s = 0;
void loop() {
    if (n > 4) {
       n = 2;
    }

    Package pack;
    pack.lan = 41.234;
    pack.lng = 51.43434;
    pack.n = n;

    bool status = radio.write(&pack, sizeof(pack));
    if (status) {
      s++;
      n++;
      ledSuccess.up();
    } else {
      f++;
      ledFailed.up();
    }

    Serial.print(F("Success:"));
    Serial.print(s);
    Serial.print(F("  Failed: "));
    Serial.println(f);
  
    delay(500);
    ledSuccess.down();
    ledFailed.down();
    delay(500);
}
