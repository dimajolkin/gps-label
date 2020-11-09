/**
 * Проект для тестирования, передачи данных, запускал через Arduino IDE.
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSP
//RF24 radio(9,53);// Для Меги

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
   Serial.begin(9600);
   Serial.println("Start");
  printfBegin();
  radio.begin(); //активировать модуль
  
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 30);     //(время между попыткой достучаться, число попыток)
  radio.setPayloadSize(32);     //размер пакета, в байтах
  radio.openWritingPipe(address);   //мы - труба 0, открываем канал для передачи данных
  radio.setChannel(5);  //выбираем канал (в котором нет шумов!)
  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.printDetails();
  delay(5000);

  radio.powerUp(); //начать работу
  radio.stopListening();  //не слушаем радиоэфир, мы передатчик
  
  
 
 }

byte n = 0;
void loop() {
    if (n > 4) {
       n = 1;
    }

    Package pack;
    pack.lan = 41.234;
    pack.lng = 51.43434;
    pack.n = n;

    radio.write(&pack, sizeof(pack));
     n++;
    Serial.println(n);
  
     delay(10);  
}
