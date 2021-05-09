// GPS gps(GPO_GPS_RX, GPO_GPS_TX);
// Display display(TFT_CS, TFT_DC, TFT_RST);

// Logger logger;
// Server server;

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
#include "SWO.h"
#include "hardware/display/display.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"
#include "hardware/keyboard/keyboard.h"

DigitalOut led(PC_13);

Keyboard keyboard(BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_OK);
Display display(SPI_MOSI, SPI_MISO, SPI_SCK, TFT_CS, TFT_DC, TFT_RST);
Lan lan(SPI_MOSI, SPI_MISO, SPI_SCK, RADIO_CE, RADIO_CSP);

EventFlags displayDrawFlag;
SWO_Channel swo("channel");
Thread thread;

#define SAMPLE_FLAG1 1

int counts[5] = {0, 0, 0, 0, 0};

void displayThread() {
   while (true) {
      displayDrawFlag.wait_any(SAMPLE_FLAG1);
      displayDrawFlag.clear();

      printf("draw \n");
      display.fillScreen(ST7735_GREEN);
      display.setTextCursor(10, 10);
      display.setTextColor(ST7735_BLACK);
      display.setTextSize(2);
      display.setTextWrap(true);
      for (uint16_t i = 0; i < 5; i++)
      {
        display.setTextCursor(10, 20 * i);
        display.printf("%d) - %d \n", i, counts[i]);
      }
      lan.test();
    }
}

void click(uint8_t key) {
    // printf("click..");
    led = !led;
    counts[key]++;
    displayDrawFlag.set(SAMPLE_FLAG1);
}

int main() {
    swo.claim();
    display.initR(INITR_BLACKTAB); 
    display.setRotation(0);
    display.fillScreen(ST7735_RED);
  
    thread.start(displayThread);
    keyboard.onKeyPressed(click);
    printf("start app");
    lan.init();

    while(1) {
      thread_sleep_for(100);
    }
}