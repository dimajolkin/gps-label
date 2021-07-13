#pragma once

#include "lib/ui/controller.h"
#include "ui/model/test-model.h"
#include "ui/view/test.h"

class TestController : public Controller
{
// private:
//     TestModel *testModel;
public:
    TestController(ServiceLocator *container) : Controller(container)
    {
        // testModel = new TestModel();
        // view = new TestView(testModel);
    }

    Controller* onClick(uint8_t key)
    {
        // testModel->click(key);
        // container->getLogger()->printf("inc model %i %i \n", key, testModel->count(key));
        // view->refresh();

        return this;
    }
};