
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Adafruit_I2CDevice.h"

// For the Adafruit shield, these are the default.

#undef ILI9341_TFTWIDTH
#undef ILI9341_TFTHEIGHT

#define ILI9341_TFTWIDTH     128
#define ILI9341_TFTHEIGHT     160
class TFTDisplay: public Adafruit_ILI9341 {
    public:
       TFTDisplay(int8_t cs, int8_t dc, int8_t rst):
       Adafruit_SPITFT(ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT, cs, dc, rst)
       {
           
       }
}