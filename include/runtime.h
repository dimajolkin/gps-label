#include <mbed.h>
#include "app/app.h"
#include "boot-app/boot-app.h"


class AppRuntime
{
private:
  Container *container;
  App *app;
  uint8_t c = 0;
  
public:
  

  void taskReadGps()
  {
    while (true)
    {
      container->getGPS()->read();
      thread_sleep_for(10);
    }
  }

  void taskBattry()
  {
    while (true)
    {
      container->getServer()->setPowerLevel(container->getBattery()->level());
      thread_sleep_for(5000);
    }
  }

  void lanInterruptHandler() {
      // auto radio = container->getLanIn()->getRadio();
      // bool tx_ds, tx_df, rx_dr;
      // radio->whatHappened(tx_ds, tx_df, rx_dr);

      container->getBoard()->getLed()->toggle();
  }

  AppRuntime(Container *container) : container(container)
  {
    this->app = new App(container);
  }

  void run()
  {
    auto boot = new BootApp(container->getBoard());
    boot->run();
    container->getDisplay()->fillScreen(BACKGROUND_COLOR);
    
    this->app->init();

    // container->getTaskManager()->registerGps(callback(this, &AppRuntime::taskReadGps));
    // container->getTaskManager()->registerBattery(callback(this, &AppRuntime::taskBattry));

    container->getLanIn()->setOnInterrup(callback(this, &AppRuntime::lanInterruptHandler));

    while (true)
    {
      container->getLogger()->dispatch();
      thread_sleep_for(100);
    }
  }
};