#pragma once

#include "lib/ui/controller.h"
#include "lib/ui/response.h"
#include "ui/model/test-model.h"
#include "ui/view/test.h"

class TestController : public Controller
{
private:
    TestModel *testModel;
public:
    TestController(ServiceLocator *container) : Controller(container)
    {
        testModel = new TestModel();
        view = new TestView(testModel);
    }

    Response* onClick(uint8_t key)
    {
        testModel->click(key);
        printf("inc model %i %i \n", key, testModel->count(key));

        return new Response(view);
    }
};