#include "framework/ui/view.h"
#include "app/view/header/header.h"

class LayoutView : public View
{
private:
    View *content;
    HeaderView *header;

public:
    LayoutView(HeaderView *header): header(header) {}

    void update(Display *display)
    {
        header->update(display);
    }
};