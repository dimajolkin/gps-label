#include <mbed.h>
#include "app/app.h"
#include "boot-app/boot-app.h"


class AppRuntime
{
private:
  Container *container;
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

  AppRuntime(Container *container) : container(container)
  {
    this->app = new App(container);
  }

  void run()
  {
    auto boot = new BootApp(container->getBoard());
    boot->run();
    
    this->app->init();

    container->getTaskManager()->append(callback(this, &AppRuntime::taskReadGps));
    container->getTaskManager()->append(callback(this, &AppRuntime::taskBattry));

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