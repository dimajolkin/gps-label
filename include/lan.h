#include <nRF24L01.h>
#include <RF24.h>

#define NUM_CHANELS 128

int serial_putc( char c, FILE * ) {
    Serial.write( c );
    return c;
}

void printf_begin(void) {
   fdevopen(&serial_putc, 0 );
}
       
class Lan {
  private:
    uint8_t values[NUM_CHANELS];
    RF24 *radio;
    const int num_reps = 100;
  public:
    Lan(RF24 *radio): radio(radio) {}

    void init() {
        printf_begin();
        radio->begin();
        radio->setAutoAck(false);
        radio->startListening();

        radio->printDetails();  // Вот эта строка напечатает нам что-то, если все правильно соединили.
        delay(5000);              // И посмотрим на это пять секунд.

        radio->stopListening();
        int i = 0;    // А это напечатает нам заголовки всех 127 каналов
        while ( i < NUM_CHANELS )  {
            printf("%x",i>>4);
            ++i;
        }
        printf("\n\r");
        i = 0;
        while ( i < NUM_CHANELS ) {
            printf("%x",i&0xf);
            ++i;
        }
        printf("\n\r");
    }

    void test() {
         memset(values,0,sizeof(values));
        int rep_counter = num_reps;
        while (rep_counter--) {
            int i = NUM_CHANELS;
            while (i--) {
            radio->setChannel(i);
            radio->startListening();
            delayMicroseconds(128);
            radio->stopListening();
            if ( radio->testCarrier() )
                ++values[i];
            }
        }
        int i = 0;
        while ( i < NUM_CHANELS ) {
            printf("%x",min(0xf,values[i]&0xf));
            ++i;
        }
        printf("\n\r");
    }
};

