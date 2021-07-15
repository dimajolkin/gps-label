#pragma once

#include "framework/ui/controller.h"
#include "framework/ui/response.h"
#include "app/model/test-model.h"
#include "app/view/test.h"

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