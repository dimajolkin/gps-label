#include <mbed.h>
#include "app.h"
#include "service-locator.h"

class AppRuntime {
 private:
  ServiceLocator *container;
  App *app;

 public:
    void taskReadGps() {
      while (true) {
        container->getGPS()->read();
        thread_sleep_for(10);
      }
    }

    void taskBattry() {
      while (true) {
        container->getServer()->setPowerLevel(container->getBattery()->level());
        thread_sleep_for(1000);
      }
    }

    void onKeyPressed(Keyboard::KEY key)
    {
      if (key == Keyboard::KEY::OK)
      {
        container->getRender()->clear();
      }

      // led = !led;
      app->onClick(key);
    }

    AppRuntime(ServiceLocator *container): container(container)
    {
        this->app = new App(container);
    }

    void run() {
      this->container->getKeyboard()->onKeyPress(callback(this, &AppRuntime::onKeyPressed));
      this->app->init();
  
      Thread gpsThread;
      gpsThread.start(callback(this, &AppRuntime::taskReadGps));

      Thread batteryThread;
      batteryThread.start(callback(this, &AppRuntime::taskBattry));

      // Thread thread;
      // thread.start(onMembersStart);
      // irq.fall(&interruptHandler);

      while (true)
      {
        container->getLogger()->dispatch();
        // led = !led;
        thread_sleep_for(100);
      }
    }
};