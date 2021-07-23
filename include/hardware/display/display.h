#pragma once

// #include <stdint.h>
#include <Adafruit_ST7735.h>
// #include <Adafruit_I2CDevice.h>
// #include <SPI.h>

class Window
{
public:
    uint8_t x0;
    uint8_t y0;
    uint8_t x1;
    uint8_t y1;

    Window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) : x0(x0), y0(y0), x1(x1), y1(y1) {}

    inline uint8_t width(void)
    {
        return x1 - x0;
    }

    inline uint8_t height(void)
    {
        return y1 - y0;
    }
};

class Display : public Stream
{
private:
    Adafruit_ST7735 *display;
    Window *window;

public:
    Display(PinName mosi, PinName miso, PinName sck, PinName CS, PinName RS, PinName RST)
    {
        display = new Adafruit_ST7735(mosi, miso, sck, CS, RS, RST);
        window = new Window(0, 0, display->width(), display->height());
    }

    Window *getWindow()
    {
        return window;
    }

    Display(Display *_display, Window *_window)
    {
        display = _display->display;
        window = _window;
    }

    void init()
    {
        display->initR();
    }

    int _putc(int value) { return writeChar(value); }
    int _getc() { return -1; }

    inline void setTextCursor(int16_t x, int16_t y)
    {
        display->setTextCursor(x + window->x0, y + +window->y0);
    }

    inline void setTextSize(uint8_t s)
    {
        display->setTextSize(s);
    }

    inline void setTextWrap(bool w)
    {
        display->setTextWrap(w);
    }

    inline void setTextColor(uint16_t c)
    {
        display->setTextColor(c);
    }

    int writeChar(uint8_t t)
    {
        return display->writeChar(t);
    }

    void setRotation(uint8_t r)
    {
        return display->setRotation(r);
    }

    inline uint8_t getRotation(void)
    {
        return display->getRotation();
    }

    void fillScreen(uint16_t color)
    {
        fillRect(window->x0, window->y0, window->width(), window->height(), color);
    }

    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
    {
        display->fillRect(x + window->x0, y + window->y0, w, h, color);
    }

    void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
    {
        display->fillRoundRect(x + window->x0, y + window->y0, w, h, r, color);
    }

    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
    {
        display->drawRect(x + window->x0, y + window->y0, w, h, color);
    }

    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
    {
        display->fillTriangle(x0 + window->x0, y0 + window->y0, x1 + window->x0, y1 + window->y0, x2 + window->x0, y2 + window->y0, color);
    }

    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
    {
        display->drawLine(x0 + window->x0, y0 + window->y0, x1 + window->x0, y1 + window->y0, color);
    }

    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
    {
        display->fillCircle(x0 + window->x0, y0 + window->y0, r, color);
    }

    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
    {
        display->drawCircle(x0 + window->x0, y0 + window->y0, r, color);
    }

    /// Get the width of the display in pixels
    inline int16_t width(void) { return window->width(); };
    /// Get the height of the display in pixels
    inline int16_t height(void) { return window->height(); };
};