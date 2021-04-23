// #include <Arduino.h>
// #include <EEPROM.h>
// // 

// #include "hardware/server/server.h"
// #include "hardware/lan/lan.h"
// #include "hardware/gps/gps.h"

// #include "config.h"
// #include "buttons.h"
// #include "container.h"
// #include "app.h"
// #include "lib/logger/logger.h"
// #include "stdio.h"

// RF24 radio(RADIO_CE, RADIO_CSP);
// GPS gps(GPO_GPS_RX, GPO_GPS_TX);
// Display display(TFT_CS, TFT_DC, TFT_RST);

// Logger logger;
// Server server;
// Lan lan(&radio);

// Container container(&gps, &lan, &server, &logger);
// App app = App(&display, &container);

// void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState);

// void tick() {
//   digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(100);                       // wait for a second
//   digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
//   delay(100);  
// }

// void setup(void) {
//   // initialize digital pin LED_BUILTIN as an output.
//   pinMode(PC13, OUTPUT); 

//   //  SPIClass SPI_2(PB5, PB4, PB3);
//   //  SPI_2.begin();
//   app.setup();
//   app.registerHandlerKeyboard(handleEvent);
// }

// void loop(void) {
//   logger.printf("start \n");
//     app.loop();
//     // tick();
//     logger.printf("stop \n");
// }

// void handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState) {
//   if (eventType != AceButton::kEventClicked) {
//     return;
//   }
//   logger.printf("click! \n");
//   app.onClick(button->getId());
// }
#include "mbed.h"

#include "config.h"
#include <stdint.h>
#include "DebounceIn.h"
#include "hardware/display/display.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"

DigitalOut led(PC_13);

class Keyboard {
  public:
    DigitalIn *ok;
    DigitalIn *left;
    DigitalIn *right;
    DigitalIn *up;
    DigitalIn *down;
    Keyboard() {
      ok = new DigitalIn(BTN_OK);
      left = new DigitalIn(BTN_LEFT);
      right = new DigitalIn(BTN_RIGHT);
      up = new DigitalIn(BTN_UP);
      down = new DigitalIn(BTN_DOWN);
    }
};

DigitalIn pb(BTN_OK);
Display display(SPI_MOSI, SPI_MISO, SPI_SCK, TFT_CS, TFT_DC, TFT_RST);
Keyboard keyboard();


Thread thread;
Thread threadKeyborad;

void displayThread() {
   while (true) {
        display.fillScreen(ST7735_RED);
        thread_sleep_for(1000);
        display.fillScreen(ST7735_GREEN);
        thread_sleep_for(1000);
        // ThisThread::sleep_for(1000);
    }
}

DebounceIn buttonDown(BTN_DOWN);

int main() {
    display.initR(INITR_BLACKTAB); 
    display.setRotation(0);
    display.fillScreen(ST7735_RED);
    
    thread.start(displayThread);

    // pb.mode(PullUp);
    // button.fall([] {
      // led = !led;
    // });
    buttonDown.mode(PullDown);
    while(1) {
        if (buttonDown.read()) {
          led = !led;
          thread_sleep_for(100);
        }
    }
}