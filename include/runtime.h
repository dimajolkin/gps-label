#include <mbed.h>
#include "app/app.h"
#include "boot-app/boot-app.h"


class AppRuntime
{
private:
  ServiceLocator *container;
  App *app;
  
public:
  // void onMembersStart()
  // {
  //   Lan *lan = container->getLan();
  //   MemberService *memberService = container->getMemberService();

  //   while (true)
  //   {
  //     if (lan->available())
  //     {
  //       Package pack = lan->read();
  //       if (pack.validate())
  //       {
  //         memberService->registerPakage(&pack);
  //       }
  //     }
  //   }
  // }

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
      thread_sleep_for(1000);
    }
  }

  void onKeyPressed(Keyboard::KEY key)
  {
    // led = !led;
    app->onClick(key);
  }

  AppRuntime(ServiceLocator *container) : container(container)
  {
    this->app = new App(container);
  }

  void run()
  {
    auto boot = new BootApp(container);
    boot->run();
    
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