#pragma once

// #include <stdint.h>
#include <Adafruit_ST7735.h>
// #include <Adafruit_I2CDevice.h>
// #include <SPI.h>
// void wait_ms(int ms) {}

typedef Adafruit_ST7735 Display;

class Window
{
public:
    uint8_t x0;
    uint8_t y0;
    uint8_t x1;
    uint8_t y1;

    Window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1): x0(x0), y0(y0), x1(x1), y1(y1) {}
};

class WindowDisplay
{
private:
    Display *display;
    Window *window;

public:
    WindowDisplay(Display *display, Window *window): display(display), window(window) {}
};