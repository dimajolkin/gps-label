#pragma once

#include "lib/ui/controller.h"

class StackController {
    private:
        Controller *mainController;
    public:
       StackController(Controller *mainController):  mainController(mainController) {}

       Controller getMain() 
       {
           return mainController;
       }
};