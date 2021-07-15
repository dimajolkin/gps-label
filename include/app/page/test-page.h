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

    Response* onClick(Keyboard::KEY key)
    {
        testModel->click((uint8_t) key);
        printf("inc model %i %i \n", key, testModel->count(key));
        if (key == Keyboard::KEY::LEFT) {
            return toBack();
        }

        return render(view);
    }
};