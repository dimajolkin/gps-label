#include <mbed.h>

#include "config.h"
#include <stdint.h>
#include "hardware/display/display.h"
#include "hardware/lan/lan.h"
#include "hardware/gps/gps.h"
#include "hardware/keyboard/keyboard.h"
#include "service-locator.h"
#include "app/app.h"

DigitalOut led(PC_13);

void onKeyPressed(Keyboard::KEY key);

ServiceLocator *container = new ServiceLocator(
    new Display(SPI_MOSI, SPI_MISO, SPI_SCK, TFT_CS, TFT_DC, TFT_RST),
    new Keyboard(BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_OK, onKeyPressed),
    new Lan(RADIO_SPI_MOSI, RADIO_SPI_MISO, RADIO_SPI_SCK, RADIO_CE, RADIO_CSP),
    new Server());

App app(container);

void onKeyPressed(Keyboard::KEY key)
{
  led = !led;
  app.onClick(key);
}

void onMembersStart()
{
  Lan *lan = container->getLan();
  MemberService *memberService = container->getMemberService();

  while (true)
  {
    if (lan->available())
    {
      Package pack = lan->read();
      if (pack.validate())
      {
        memberService->registerPakage(&pack);
      }
    }
  }
}

int main()
{
  app.init();
  Thread thread;
  thread.start(onMembersStart);
  thread_sleep_for(osFeature_Wait);
}

// void test_disp()
// {
  
  //  uint64_t time = get_ms_count();

  //   // disp->fillScreen(ST7735_BLACK);
  //   disp->fillRect(0, 0, 100, 100, ST7735_RED);
  //   uint64_t stop_time = get_ms_count() - time;

  //   disp->setTextCursor(50, 50);
  //   disp->printf("%llu ", stop_time);
  //   printf("%llu ", stop_time);
// }
