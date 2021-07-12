#pragma once

#include "controller.h"

#include "ui/model/test-model.h"
#include "ui/view/test.h"

class TestController : public Controller
{
private:
    TestModel *testModel;
    TestView *view;

public:
    TestController(ServiceLocator *container) : Controller(container)
    {
        testModel = new TestModel();
        view = new TestView(testModel);
    }

    void onClick(uint8_t key)
    {
        testModel->click(key);
        container->getLogger()->printf("inc model %i %i \n", key, testModel->count(key));
        view->refresh();
    }
};