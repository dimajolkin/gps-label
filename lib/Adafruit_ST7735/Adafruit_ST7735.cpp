/***************************************************
  This is a library for the Adafruit 1.8" SPI display.
  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

// + GREENTAB2 display
// BurstSPI

#include "Adafruit_ST7735.h"
#include "mbed.h"

inline uint16_t swapcolor(uint16_t x) {
  return (x << 11) | (x & 0x07E0) | (x >> 11);
}

inline void _wait_ms(uint16_t ms) {
  thread_sleep_for(ms);
}

// Constructor
Adafruit_ST7735::Adafruit_ST7735(PinName mosi, PinName miso, PinName sck,
                                 PinName cs, PinName rs, PinName rst)
    : Adafruit_GFX(ST7735_TFTWIDTH, ST7735_TFTHEIGHT), lcdPort(mosi, miso, sck), _cs(cs), _rs(rs), _rst(rst) {}

void Adafruit_ST7735::writecommand(uint8_t c) {
  _rs = 0;
  _cs = 0;

  lcdPort.fastWrite(c);
  lcdPort.clearRX();
  _cs = 1;
}

void Adafruit_ST7735::writedata(uint8_t c) {
  _rs = 1;
  _cs = 0;
  lcdPort.fastWrite(c);
  lcdPort.clearRX();

  _cs = 1;
}

// Rather than a bazillion writecommand() and writedata() calls, screen
// initialization commands and arguments are organized in these tables
// stored in PROGMEM.  The table may look bulky, but that's mostly the
// formatting -- storage-wise this is hundreds of bytes more compact
// than the equivalent code.  Companion function follows.
#define DELAY 0x80

static unsigned char Bcmd[] =
    {                              // Initialization commands for 7735B screens
        18,                        // 18 commands in list:
        ST7735_SWRESET, DELAY,     //  1: Software reset, no args, w/delay
        50,                        //     50 ms delay
        ST7735_SLPOUT, DELAY,      //  2: Out of sleep mode, no args, w/delay
        255,                       //     255 = 500 ms delay
        ST7735_COLMOD, 1 + DELAY,  //  3: Set color mode, 1 arg + delay:
        0x05,                      //     16-bit color
        10,                        //     10 ms delay
        ST7735_FRMCTR1, 3 + DELAY, //  4: Frame rate control, 3 args + delay:
        0x00,                      //     fastest refresh
        0x06,                      //     6 lines front porch
        0x03,                      //     3 lines back porch
        10,                        //     10 ms delay
        ST7735_MADCTL, 1,  //  5: Memory access ctrl (directions), 1 arg:
        0x08,              //     Row addr/col addr, bottom to top refresh
        ST7735_DISSET5, 2, //  6: Display settings #5, 2 args, no delay:
        0x15,              //     1 clk cycle nonoverlap, 2 cycle gate
                           //     rise, 3 cycle osc equalize
        0x02,              //     Fix on VTL
        ST7735_INVCTR, 1,  //  7: Display inversion control, 1 arg:
        0x0,               //     Line inversion
        ST7735_PWCTR1, 2 + DELAY, //  8: Power control, 2 args + delay:
        0x02,                     //     GVDD = 4.7V
        0x70,                     //     1.0uA
        10,                       //     10 ms delay
        ST7735_PWCTR2, 1,         //  9: Power control, 1 arg, no delay:
        0x05,                     //     VGH = 14.7V, VGL = -7.35V
        ST7735_PWCTR3, 2,         // 10: Power control, 2 args, no delay:
        0x01,                     //     Opamp current small
        0x02,                     //     Boost frequency
        ST7735_VMCTR1, 2 + DELAY, // 11: Power control, 2 args + delay:
        0x3C,                     //     VCOMH = 4V
        0x38,                     //     VCOML = -1.1V
        10,                       //     10 ms delay
        ST7735_PWCTR6, 2,         // 12: Power control, 2 args, no delay:
        0x11, 0x15, ST7735_GMCTRP1,
        16,                     // 13: Magical unicorn dust, 16 args, no delay:
        0x09, 0x16, 0x09, 0x20, //     (seriously though, not sure what
        0x21, 0x1B, 0x13, 0x19, //      these config values represent)
        0x17, 0x15, 0x1E, 0x2B, 0x04, 0x05, 0x02, 0x0E, ST7735_GMCTRN1,
        16 + DELAY,             // 14: Sparkles and rainbows, 16 args + delay:
        0x0B, 0x14, 0x08, 0x1E, //     (ditto)
        0x22, 0x1D, 0x18, 0x1E, 0x1B, 0x1A, 0x24, 0x2B, 0x06, 0x06, 0x02, 0x0F,
        10,                   //     10 ms delay
        ST7735_CASET, 4,      // 15: Column addr set, 4 args, no delay:
        0x00, 0x02,           //     XSTART = 2
        0x00, 0x81,           //     XEND = 129
        ST7735_RASET, 4,      // 16: Row addr set, 4 args, no delay:
        0x00, 0x02,           //     XSTART = 1
        0x00, 0x81,           //     XEND = 160
        ST7735_NORON, DELAY,  // 17: Normal display on, no args, w/delay
        10,                   //     10 ms delay
        ST7735_DISPON, DELAY, // 18: Main screen turn on, no args, w/delay
        255},                 //     255 = 500 ms delay

    Rcmd1[] =
        {       // Init for 7735R, part 1 (red or green tab)
            15, // 15 commands in list:
            ST7735_SWRESET,
            DELAY, //  1: Software reset, 0 args, w/delay
            150,   //     150 ms delay
            ST7735_SLPOUT,
            DELAY, //  2: Out of sleep mode, 0 args, w/delay
            255,   //     500 ms delay
            ST7735_FRMCTR1,
            3, //  3: Frame rate ctrl - normal mode, 3 args:
            0x01,
            0x2C,
            0x2D, //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
            ST7735_FRMCTR2,
            3, //  4: Frame rate control - idle mode, 3 args:
            0x01,
            0x2C,
            0x2D, //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
            ST7735_FRMCTR3,
            6, //  5: Frame rate ctrl - partial mode, 6 args:
            0x01,
            0x2C,
            0x2D, //     Dot inversion mode
            0x01,
            0x2C,
            0x2D, //     Line inversion mode
            ST7735_INVCTR,
            1,    //  6: Display inversion ctrl, 1 arg, no delay:
            0x07, //     No inversion
            ST7735_PWCTR1,
            3, //  7: Power control, 3 args, no delay:
            0xA2,
            0x02, //     -4.6V
            0x84, //     AUTO mode
            ST7735_PWCTR2,
            1,    //  8: Power control, 1 arg, no delay:
            0xC5, //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
            ST7735_PWCTR3,
            2,    //  9: Power control, 2 args, no delay:
            0x0A, //     Opamp current small
            0x00, //     Boost frequency
            ST7735_PWCTR4,
            2,    // 10: Power control, 2 args, no delay:
            0x8A, //     BCLK/2, Opamp current small & Medium low
            0x2A,
            ST7735_PWCTR5,
            2, // 11: Power control, 2 args, no delay:
            0x8A,
            0xEE,
            ST7735_VMCTR1,
            1, // 12: Power control, 1 arg, no delay:
            0x0E,
            ST7735_INVOFF,
            0, // 13: Don't invert display, no args, no delay
            ST7735_MADCTL,
            1,    // 14: Memory access control (directions), 1 arg:
            0xC8, //     row addr/col addr, bottom to top refresh
            ST7735_COLMOD,
            1,     // 15: set color mode, 1 arg, no delay:
            0x05}, //     16-bit color

    Rcmd2green[] =
        {      // Init for 7735R, part 2 (green tab only)
            2, //  2 commands in list:
            ST7735_CASET,
            4, //  1: Column addr set, 4 args, no delay:
            0x00,
            0x02, //     XSTART = 0
            0x00,
            0x7F + 0x02, //     XEND = 127
            ST7735_RASET,
            4, //  2: Row addr set, 4 args, no delay:
            0x00,
            0x01, //     XSTART = 0
            0x00,
            0x9F + 0x01}, //     XEND = 159
    Rcmd2red[] =
        {      // Init for 7735R, part 2 (red tab only)
            2, //  2 commands in list:
            ST7735_CASET,
            4, //  1: Column addr set, 4 args, no delay:
            0x00,
            0x00, //     XSTART = 0
            0x00,
            0x7F, //     XEND = 127
            ST7735_RASET,
            4, //  2: Row addr set, 4 args, no delay:
            0x00,
            0x00, //     XSTART = 0
            0x00,
            0x9F}, //     XEND = 159

    Rcmd2green144[] =
        {      // Init for 7735R, part 2 (green 1.44 tab)
            2, //  2 commands in list:
            ST7735_CASET,
            4, //  1: Column addr set, 4 args, no delay:
            0x00,
            0x00, //     XSTART = 0
            0x00,
            0x7F, //     XEND = 127
            ST7735_RASET,
            4, //  2: Row addr set, 4 args, no delay:
            0x00,
            0x00, //     XSTART = 0
            0x00,
            0x7F}, //     XEND = 127

    Rcmd3[] = { // Init for 7735R, part 3 (red or green tab)
        4,      //  4 commands in list:
        ST7735_GMCTRP1,
        16, //  1: Magical unicorn dust, 16 args, no delay:
        0x02,
        0x1c,
        0x07,
        0x12,
        0x37,
        0x32,
        0x29,
        0x2d,
        0x29,
        0x25,
        0x2B,
        0x39,
        0x00,
        0x01,
        0x03,
        0x10,
        ST7735_GMCTRN1,
        16, //  2: Sparkles and rainbows, 16 args, no delay:
        0x03,
        0x1d,
        0x07,
        0x06,
        0x2E,
        0x2C,
        0x29,
        0x2D,
        0x2E,
        0x2E,
        0x37,
        0x3F,
        0x00,
        0x00,
        0x02,
        0x10,
        ST7735_NORON,
        DELAY, //  3: Normal display on, no args, w/delay
        10,    //     10 ms delay
        ST7735_DISPON,
        DELAY, //  4: Main screen turn on, no args w/delay
        100},  //     100 ms delay
    RILI9341[] = {
      20, // 20 commands in list:

      0xEF, // c1
      3, // args
      0x03,
      0x80,
      0x02,

      0xCF, // c2
      3,
      0x00,
      0XC1,
      0X30,

      0xED, // c3
      4,
      0x64,
      0x03,
      0X12,
      0X81,

      0xE8,
      3,
      0x85,
      0x00,
      0x78,

      0xCB,
      5,
      0x39,
      0x2C,
      0x00,
      0x34,
      0x02,

      0xF7,
      1,
      0x20,

      0xEA,
      2,
      0x00,
      0x00,

      ST7735_PWCTR1,
      1,
      0x23,

      ST7735_PWCTR2,
      1,
      0x10,

      ST7735_VMCTR1,
      2,
      0x3e,
      0x28,

      0xC7, //ST7735_VMCTR2,
      1,
      0x86,

      ST7735_MADCTL,
      1,
      0x48,

      0x3A, //ST7735_PIXFMT,
      1,
      0x55,

      ST7735_FRMCTR1,
      2,
      0x00,
      0x18,

      0xB6, //ST7735_DFUNCTR,
      3,
      0x08,
      0x82,
      0x27,

      0xF2, // 3Gamma Function Disable
      1,
      0x00,

      ST7735_GMCTRP1,
      15,
      0x0F,
      0x31,
      0x2B,
      0x0C,
      0x0E,
      0x08,
      0x4E,
      0xF1,
      0x37,
      0x07,
      0x10,
      0x03,
      0x0E,
      0x09,
      0x00,

      ST7735_GMCTRN1, //Set Gamma
      15,
      0x00,
      0x0E,
      0x14,
      0x03,
      0x11,
      0x07,
      0x31,
      0xC1,
      0x48,
      0x08,
      0x0F,
      0x0C,
      0x31,
      0x36,
      0x0F,

      ST7735_SLPOUT, DELAY,
      120,

      ST7735_DISPON, DELAY,
      100
    };

// Companion code to the above tables.  Reads and issues
// a series of LCD commands stored in byte array.
void Adafruit_ST7735::commandList(uint8_t *addr) {
  uint8_t numCommands, numArgs;
  uint16_t ms;

  numCommands = *addr++;   // Number of commands to follow
  while (numCommands--) {  // For each command...
    writecommand(*addr++); //   Read, issue command
    numArgs = *addr++;     //   Number of args to follow
    ms = numArgs & DELAY;  //   If hibit set, delay follows args
    numArgs &= ~DELAY;     //   Mask out delay bit
    while (numArgs--) {    //   For each argument...
      writedata(*addr++);  //     Read, issue argument
    }

    if (ms) {
      ms = *addr++; // Read post-command delay time (ms)
      if (ms == 255)
        ms = 500; // If 255, delay for 500 ms
      _wait_ms(ms);
    }
  }
}

// Initialization code common to both 'B' and 'R' type displays
void Adafruit_ST7735::commonInit(uint8_t *cmdList) {

  colstart = rowstart = 0; // May be overridden in init func

  _rs = 1;
  _cs = 1;

  // use default SPI format

  // lcdPort.format(8, 0);
  // lcdPort.frequency(1000000);

  lcdPort.format(8, 0);
  lcdPort.frequency(50 * 1000000 - 100);
  // toggle RST low to reset; CS low so it'll listen to us
  _cs = 0;
  _rst = 1;
  _wait_ms(100);
  _rst = 0;
  _wait_ms(100);
  _rst = 1;
  _wait_ms(100);

  if (cmdList)
    commandList(cmdList);
}

// Initialization for ST7735B screens
void Adafruit_ST7735::initB(void) { commonInit(Bcmd); }

// Initialization for ST7735R screens (green or red tabs)
void Adafruit_ST7735::initR(uint8_t options) {
  commonInit(Rcmd1);
  if (options == INITR_GREENTAB) {
    commandList(Rcmd2green);
    colstart = 2;
    rowstart = 1;
  } else if (options == INITR_GREENTAB2) {
    commandList(Rcmd2green);
    colstart = 1;
    rowstart = 2;
  } else if (options == INITR_144GREENTAB) {
    _height = ST7735_TFTHEIGHT_144;
    commandList(Rcmd2green144);
    colstart = 2;
    rowstart = 3;
  } else if (options == INITR_ILI9341) {
    _width = 240;
    _height = 320;
    _rawHeight = _height;
    _rawWidth = _width;
    commandList(RILI9341);
    colstart = 0;
    rowstart = 0;
    tabcolor = options;
    _wait_ms(100);
    return;
  } else {
    // colstart, rowstart left at default '0' values
    commandList(Rcmd2red);
  }
  commandList(Rcmd3);

  // if black, change MADCTL color filter
  if (options == INITR_BLACKTAB || INITR_GREENTAB2) {
    writecommand(ST7735_MADCTL);
    writedata(0xC0);
  }

  tabcolor = options;
}

void Adafruit_ST7735::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1,
                                    uint16_t y1) {
  if (tabcolor == INITR_ILI9341) {
      writecommand(ST7735_CASET); // Column addr set
      writedata(x0 >> 8);
      writedata(x0 & 0xFF); // XSTART
      writedata(x1 >> 8);
      writedata(x1 & 0xFF); // XEND

      writecommand(ST7735_RASET); // Row addr set
      writedata(y0 >> 8);
      writedata(y0); // YSTART
      writedata(y1 >> 8);
      writedata(y1); // YEND

      writecommand(ST7735_RAMWR); // write to RAM
      return;
  }                                      

  writecommand(ST7735_CASET); // Column addr set
  writedata(0x00);
  writedata(x0 + colstart); // XSTART
  writedata(0x00);
  writedata(x1 + colstart); // XEND

  writecommand(ST7735_RASET); // Row addr set
  writedata(0x00);
  writedata(y0 + rowstart); // YSTART
  writedata(0x00);
  writedata(y1 + rowstart); // YEND

  writecommand(ST7735_RAMWR); // write to RAM
}

void Adafruit_ST7735::pushColor(uint16_t color) {
  _rs = 1;
  _cs = 0;

  lcdPort.fastWrite(color >> 8);
  lcdPort.clearRX();
  lcdPort.fastWrite(color);
  lcdPort.clearRX();
  _cs = 1;
}

void Adafruit_ST7735::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
    return;

  setAddrWindow(x, y, x + 1, y + 1);

  _rs = 1;
  _cs = 0;

  lcdPort.fastWrite(color >> 8);
  lcdPort.clearRX();
  lcdPort.fastWrite(color);
  lcdPort.clearRX();

  _cs = 1;
}

void Adafruit_ST7735::drawFastVLine(int16_t x, int16_t y, int16_t h,
                                    uint16_t color) {
  // Rudimentary clipping
  if ((x >= _width) || (y >= _height))
    return;
  if ((y + h - 1) >= _height)
    h = _height - y;
  setAddrWindow(x, y, x, y + h - 1);

  uint8_t hi = color >> 8, lo = color;
  _rs = 1;
  _cs = 0;
  while (h--) {
    lcdPort.fastWrite(hi);
    lcdPort.clearRX();
    lcdPort.fastWrite(lo);
    lcdPort.clearRX();
  }
  _cs = 1;
}

void Adafruit_ST7735::drawFastHLine(int16_t x, int16_t y, int16_t w,
                                    uint16_t color) {
  // Rudimentary clipping
  if ((x >= _width) || (y >= _height))
    return;
  if ((x + w - 1) >= _width)
    w = _width - x;
  setAddrWindow(x, y, x + w - 1, y);

  uint8_t hi = color >> 8, lo = color;
  _rs = 1;
  _cs = 0;
  while (w--) {
    lcdPort.fastWrite(hi);
    lcdPort.clearRX();
    lcdPort.fastWrite(lo);
    lcdPort.clearRX();
  }
  _cs = 1;
}

void Adafruit_ST7735::fillScreen(uint16_t color) {
  fillRect(0, 0, _width, _height, color);
}


// fill a rectangle
void Adafruit_ST7735::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                               uint16_t color) {
  // rudimentary clipping (drawChar w/big text requires this)
  if ((x >= _width) || (y >= _height))
    return;
  if ((x + w - 1) >= _width)
    w = _width - x;
  if ((y + h - 1) >= _height)
    h = _height - y;

  setAddrWindow(x, y, x + w - 1, y + h - 1);

  _rs = 1;
  _cs = 0;
  for (y = h; y > 0; y--) {
    for (x = w; x > 0; x--) {
      lcdPort.fastWrite(color >> 8);
      lcdPort.fastWrite(color);
    }
  }
 
  lcdPort.clearRX();
  _cs = 1;
}



// fill a rectangle
void Adafruit_ST7735::flush(int16_t x1, int16_t y1, int16_t x2, int16_t y2, lv_color_t* color)
{
  // rudimentary clipping (drawChar w/big text requires this)
  uint32_t w = ( x2 - x1 + 1 );
  uint32_t h = ( y2 - y1 + 1 );

  setAddrWindow(x1, y1, x2, y2);

  _rs = 1;
  _cs = 0;
  for (y1 = h; y1 > 0; y1--) {
    for (x1 = w; x1 > 0; x1--) {
      lcdPort.fastWrite(color->full >> 8);
      lcdPort.fastWrite(color->full);
      color++;
    }
  }
 
  lcdPort.clearRX();
  _cs = 1;
}


// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t Adafruit_ST7735::Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

#define MADCTL_MY 0x80
#define MADCTL_MX 0x40
#define MADCTL_MV 0x20
#define MADCTL_ML 0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH 0x04

void Adafruit_ST7735::setRotation(uint8_t m) {
  writecommand(ST7735_MADCTL);
  rotation = m % 4; // can't be higher than 3
  switch (rotation) {
  case 0:
    if (tabcolor == INITR_ILI9341) {
      break;
    }
    
    if (tabcolor == INITR_BLACKTAB || INITR_GREENTAB2) {
      writedata(MADCTL_MX | MADCTL_MY | MADCTL_RGB);
    } else {
      writedata(MADCTL_MX | MADCTL_MY | MADCTL_BGR);
    }
    _width = ST7735_TFTWIDTH;

    if (tabcolor == INITR_144GREENTAB)
      _height = ST7735_TFTHEIGHT_144;
    else
      _height = ST7735_TFTHEIGHT_18;

    break;
  case 1:
    if (tabcolor == INITR_BLACKTAB || INITR_GREENTAB2) {
      writedata(MADCTL_MY | MADCTL_MV | MADCTL_RGB);
    } else {
      writedata(MADCTL_MY | MADCTL_MV | MADCTL_BGR);
    }

    if (tabcolor == INITR_144GREENTAB)
      _width = ST7735_TFTHEIGHT_144;
    else
      _width = ST7735_TFTHEIGHT_18;

    _height = ST7735_TFTWIDTH;
    break;
  case 2:
    if (tabcolor == INITR_BLACKTAB || INITR_GREENTAB2) {
      writedata(MADCTL_RGB);
    } else {
      writedata(MADCTL_BGR);
    }
    _width = ST7735_TFTWIDTH;
    if (tabcolor == INITR_144GREENTAB)
      _height = ST7735_TFTHEIGHT_144;
    else
      _height = ST7735_TFTHEIGHT_18;

    break;
  case 3:
    if (tabcolor == INITR_BLACKTAB || INITR_GREENTAB2) {
      writedata(MADCTL_MX | MADCTL_MV | MADCTL_RGB);
    } else {
      writedata(MADCTL_MX | MADCTL_MV | MADCTL_BGR);
    }
    if (tabcolor == INITR_144GREENTAB)
      _width = ST7735_TFTHEIGHT_144;
    else
      _width = ST7735_TFTHEIGHT_18;

    _height = ST7735_TFTWIDTH;
    break;
  }
}

void Adafruit_ST7735::invertDisplay(boolean i) {
  writecommand(i ? ST7735_INVON : ST7735_INVOFF);
}