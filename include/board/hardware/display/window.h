class Window
{
public:
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;

    Window(int16_t x0, int16_t y0, int16_t x1, int16_t y1) : x0(x0), y0(y0), x1(x1), y1(y1) {}

    inline int16_t width(void)
    {
        return x1 - x0;
    }

    inline int16_t height(void)
    {
        return y1 - y0;
    }
};