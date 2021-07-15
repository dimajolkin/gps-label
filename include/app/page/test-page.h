#pragma once

#include "framework/ui/page.h"
#include "framework/ui/response.h"
#include "app/model/test-model.h"
#include "app/view/test.h"

class TestPage : public Page
{
private:
    TestModel *testModel;
public:
    TestPage(ServiceLocator *container) : Page(container)
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