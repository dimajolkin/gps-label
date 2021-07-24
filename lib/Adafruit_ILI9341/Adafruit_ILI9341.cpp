/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
/*
    Ported to mbed by James Kidd
 */
#include <stdint.h>
#include <Adafruit_GFX.h>
#include "Adafruit_ILI9341.h"
#include "mbed.h"
#include "PinNames.h"
#include "BurstSPI.h"

Adafruit_ILI9341::Adafruit_ILI9341(PinName DC, PinName CS, PinName RST) : Adafruit_GFX(ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT)
{
  _pins.rst = RST;
  _pins.cs = CS;
  _pins.dc = DC;
  _pins.miso = SPI_MISO;
  _pins.mosi = SPI_MOSI;
  _pins.sclk = SPI_SCK;
  hwSPI = true;
}

Adafruit_ILI9341::Adafruit_ILI9341(PinName mosi, PinName miso, PinName sck, PinName cs, PinName dc, PinName rst) : Adafruit_GFX(ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT)
{
  _pins.rst = rst;
  _pins.cs = cs;
  _pins.dc = dc;
  _pins.miso = miso;
  _pins.mosi = mosi;
  _pins.sclk = sck;
  hwSPI = false;
}

inline void Adafruit_ILI9341::spiwrite(uint16_t c)
{

  //Serial.print("0x"); Serial.print(c, HEX); Serial.print(", ");
  LcdSPI->write(c);
  //LcdSPI->fastWrite(c >> 8);
  //LcdSPI->fastWrite(c);
}
void Adafruit_ILI9341::writecommand(uint8_t c)
{

  LcdSPI->format(8, 3);
  LcdSPI->setFormat();
  Pins[PIN_DC]->write(0);
  if (Pins[PIN_SCE] > 0)
  {
    Pins[PIN_SCE]->write(0);
  }
  LcdSPI->write(c);
  //spiwrite(c);
  if (Pins[PIN_SCE] > 0)
  {
    Pins[PIN_SCE]->write(1);
  }
  LcdSPI->format(16, 3);
  LcdSPI->setFormat();
}

void Adafruit_ILI9341::writedata(uint16_t c)
{

  LcdSPI->format(8, 3);
  LcdSPI->setFormat();
  Pins[PIN_DC]->write(1);
  if (Pins[PIN_SCE] > 0)
  {
    Pins[PIN_SCE]->write(0);
  }
  LcdSPI->write(c);
  //spiwrite(c);
  if (Pins[PIN_SCE] > 0)
  {
    Pins[PIN_SCE]->write(1);
  }
  LcdSPI->format(16, 3);
  LcdSPI->setFormat();
}

void Adafruit_ILI9341::commandList(uint8_t *addr)
{

  /*uint8_t  numCommands, numArgs;
  uint16_t ms;

  numCommands = pgm_read_byte(addr++);   // Number of commands to follow
  while(numCommands--) {                 // For each command...
    writecommand(pgm_read_byte(addr++)); //   Read, issue command
    numArgs  = pgm_read_byte(addr++);    //   Number of args to follow
    ms       = numArgs & DELAY;          //   If hibit set, delay follows args
    numArgs &= ~DELAY;                   //   Mask out delay bit
    while(numArgs--) {                   //   For each argument...
      writedata(pgm_read_byte(addr++));  //     Read, issue argument
    }

    if(ms) {
      ms = pgm_read_byte(addr++); // Read post-command delay time (ms)
      if(ms == 255) ms = 500;     // If 255, delay for 500 ms
      wait_ms(ms);
    }
  }*/
}
void Adafruit_ILI9341::init(void)
{
  LcdSPI = new BurstSPI(_pins.mosi, _pins.miso, _pins.sclk);
  LcdSPI->format(LCD_SPI_BITS, LCD_SPI_MODE);
  LcdSPI->frequency(LCD_FREQ);
  LcdSPI->setFormat();
  Pins = new DigitalOut *[3];
  Pins[PIN_RST] = new DigitalOut(_pins.rst);
  Pins[PIN_SCE] = new DigitalOut(_pins.cs);
  Pins[PIN_DC] = new DigitalOut(_pins.dc);

  if (Pins[PIN_RST] > 0)
  {
    Pins[PIN_RST]->write(0);
  }
  Pins[PIN_DC]->write(0);
  Pins[PIN_SCE]->write(0);

  // toggle RST low to reset
  if (Pins[PIN_RST] > 0)
  {
    Pins[PIN_RST]->write(1);
    thread_sleep_for(5);
    Pins[PIN_RST]->write(0);
    thread_sleep_for(20);
    Pins[PIN_RST]->write(1);
    thread_sleep_for(150);
  }

  /*
  uint8_t x = readcommand8(ILI9341_RDMODE);
  Serial.print("\nDisplay Power Mode: 0x"); Serial.println(x, HEX);
  x = readcommand8(ILI9341_RDMADCTL);
  Serial.print("\nMADCTL Mode: 0x"); Serial.println(x, HEX);
  x = readcommand8(ILI9341_RDPIXFMT);
  Serial.print("\nPixel Format: 0x"); Serial.println(x, HEX);
  x = readcommand8(ILI9341_RDIMGFMT);
  Serial.print("\nImage Format: 0x"); Serial.println(x, HEX);
  x = readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("\nSelf Diagnostic: 0x"); Serial.println(x, HEX);
*/
  //if(cmdList) commandList(cmdList);

  if (hwSPI)
  {
    spi_begin();
  }
  writecommand(0xEF);
  writedata(0x03);
  writedata(0x80);
  writedata(0x02);

  writecommand(0xCF);
  writedata(0x00);
  writedata(0XC1);
  writedata(0X30);

  writecommand(0xED);
  writedata(0x64);
  writedata(0x03);
  writedata(0X12);
  writedata(0X81);

  writecommand(0xE8);
  writedata(0x85);
  writedata(0x00);
  writedata(0x78);

  writecommand(0xCB);
  writedata(0x39);
  writedata(0x2C);
  writedata(0x00);
  writedata(0x34);
  writedata(0x02);

  writecommand(0xF7);
  writedata(0x20);

  writecommand(0xEA);
  writedata(0x00);
  writedata(0x00);

  writecommand(ILI9341_PWCTR1); //Power control
  writedata(0x23);              //VRH[5:0]

  writecommand(ILI9341_PWCTR2); //Power control
  writedata(0x10);              //SAP[2:0];BT[3:0]

  writecommand(ILI9341_VMCTR1); //VCM control
  writedata(0x3e);              //¶Ô±È¶Èµ÷½Ú
  writedata(0x28);

  writecommand(ILI9341_VMCTR2); //VCM control2
  writedata(0x86);              //--

  writecommand(ILI9341_MADCTL); // Memory Access Control
  writedata(0x48);

  writecommand(ILI9341_PIXFMT);
  writedata(0x55);

  writecommand(ILI9341_FRMCTR1);
  writedata(0x00);
  writedata(0x18);

  writecommand(ILI9341_DFUNCTR); // Display Function Control
  writedata(0x08);
  writedata(0x82);
  writedata(0x27);

  writecommand(0xF2); // 3Gamma Function Disable
  writedata(0x00);

  writecommand(ILI9341_GAMMASET); //Gamma curve selected
  writedata(0x01);

  writecommand(ILI9341_GMCTRP1); //Set Gamma
  writedata(0x0F);
  writedata(0x31);
  writedata(0x2B);
  writedata(0x0C);
  writedata(0x0E);
  writedata(0x08);
  writedata(0x4E);
  writedata(0xF1);
  writedata(0x37);
  writedata(0x07);
  writedata(0x10);
  writedata(0x03);
  writedata(0x0E);
  writedata(0x09);
  writedata(0x00);

  writecommand(ILI9341_GMCTRN1); //Set Gamma
  writedata(0x00);
  writedata(0x0E);
  writedata(0x14);
  writedata(0x03);
  writedata(0x11);
  writedata(0x07);
  writedata(0x31);
  writedata(0xC1);
  writedata(0x48);
  writedata(0x08);
  writedata(0x0F);
  writedata(0x0C);
  writedata(0x31);
  writedata(0x36);
  writedata(0x0F);

  writecommand(ILI9341_SLPOUT); //Exit Sleep
  if (hwSPI)
  {
    spi_end();
  }
  thread_sleep_for(120);
  if (hwSPI)
  {
    spi_begin();
  }
  writecommand(ILI9341_DISPON); //Display on
  if (hwSPI)
  {
    spi_end();
  }
}

void Adafruit_ILI9341::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1,
                                     uint16_t y1)
{
  writecommand(ILI9341_CASET); // Column addr set
  writedata(x0 >> 8);
  writedata(x0 & 0xFF); // XSTART
  writedata(x1 >> 8);
  writedata(x1 & 0xFF); // XEND

  writecommand(ILI9341_PASET); // Row addr set
  writedata(y0 >> 8);
  writedata(y0); // YSTART
  writedata(y1 >> 8);
  writedata(y1); // YEND

  writecommand(ILI9341_RAMWR); // write to RAM
}

void Adafruit_ILI9341::pushColor(uint16_t color)
{
  if (hwSPI)
  {
    spi_begin();
  }
  Pins[PIN_DC]->write(1);
  Pins[PIN_SCE]->write(0);
  //digitalWrite(_dc, HIGH);
  //*dcport |=  dcpinmask;
  //digitalWrite(_cs, LOW);
  //*csport &= ~cspinmask;

  //spiwrite(color >> 8);
  spiwrite(color);
  Pins[PIN_SCE]->write(1);
  //*csport |= cspinmask;
  //digitalWrite(_cs, HIGH);
  if (hwSPI)
  {
    spi_end();
  }
}
uint16_t buf[25][33];
void Adafruit_ILI9341::drawPixel(int16_t x, int16_t y, uint16_t color)
{

  if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
  {
    return;
  }

  if (hwSPI)
  {
    spi_begin();
  }
  setAddrWindow(x, y, x + 1, y + 1);

  //digitalWrite(_dc, HIGH);
  Pins[PIN_DC]->write(1);
  Pins[PIN_SCE]->write(0);

  //*dcport |=  dcpinmask;
  //digitalWrite(_cs, LOW);
  //*csport &= ~cspinmask;

  //spiwrite(color >> 8);
  spiwrite(color);
  //LcdSPI->fastWrite(color);
  Pins[PIN_SCE]->write(1);
  //*csport |= cspinmask;
  //digitalWrite(_cs, HIGH);
  if (hwSPI)
  {
    spi_end();
  }
}

void Adafruit_ILI9341::drawFastVLine(int16_t x, int16_t y, int16_t h,
                                     uint16_t color)
{

  // Rudimentary clipping
  if ((x >= _width) || (y >= _height))
  {
    return;
  }

  if ((y + h - 1) >= _height)
  {
    h = _height - y;
  }

  if (hwSPI)
  {
    spi_begin();
  }
  setAddrWindow(x, y, x, y + h - 1);

  // uint8_t hi = color >> 8, lo = color;

  //*dcport |=  dcpinmask;
  //digitalWrite(_dc, HIGH);
  //*csport &= ~cspinmask;
  //digitalWrite(_cs, LOW);
  Pins[PIN_DC]->write(1);
  Pins[PIN_SCE]->write(0);

  while (h--)
  {
    LcdSPI->fastWrite(color);
    //spiwrite(color);
    //spiwrite(hi);
    //spiwrite(lo);
  }
  Pins[PIN_SCE]->write(1);
  //*csport |= cspinmask;
  //digitalWrite(_cs, HIGH);
  if (hwSPI)
  {
    spi_end();
  }
  LcdSPI->clearRX();
}

void Adafruit_ILI9341::drawFastHLine(int16_t x, int16_t y, int16_t w,
                                     uint16_t color)
{

  // Rudimentary clipping
  if ((x >= _width) || (y >= _height))
  {
    return;
  }
  if ((x + w - 1) >= _width)
  {
    w = _width - x;
  }
  if (hwSPI)
  {
    spi_begin();
  }
  setAddrWindow(x, y, x + w - 1, y);

  // uint8_t hi = color >> 8, lo = color;
  //*dcport |=  dcpinmask;
  //*csport &= ~cspinmask;
  Pins[PIN_DC]->write(1);
  Pins[PIN_SCE]->write(0);
  //digitalWrite(_dc, HIGH);
  //digitalWrite(_cs, LOW);
  while (w--)
  {
    //spiwrite(color);
    LcdSPI->fastWrite(color);
    //spiwrite(hi);
    //spiwrite(lo);
  }
  Pins[PIN_SCE]->write(1);
  //*csport |= cspinmask;
  //digitalWrite(_cs, HIGH);
  if (hwSPI)
  {
    spi_end();
  }
  LcdSPI->clearRX();
}

void Adafruit_ILI9341::fillScreen(uint16_t color)
{
  fillRect(0, 0, _width, _height, color);
}

// fill a rectangle
void Adafruit_ILI9341::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                uint16_t color)
{

  // rudimentary clipping (drawChar w/big text requires this)
  if ((x >= _width) || (y >= _height))
  {
    return;
  }
  if ((x + w - 1) >= _width)
  {
    w = _width - x;
  }
  if ((y + h - 1) >= _height)
  {
    h = _height - y;
  }
  if (hwSPI)
  {
    spi_begin();
  }
  setAddrWindow(x, y, x + w - 1, y + h - 1);

  // uint8_t hi = color >> 8, lo = color;
  //LcdSPI->format(16, LCD_SPI_MODE);
  //LcdSPI->setFormat();
  //*dcport |=  dcpinmask;
  //digitalWrite(_dc, HIGH);
  //*csport &= ~cspinmask;
  //digitalWrite(_cs, LOW);
  Pins[PIN_DC]->write(1);
  Pins[PIN_SCE]->write(0);
  int32_t cnt;
  for (cnt = w * h; cnt > 0; cnt--)
  {
    LcdSPI->fastWrite(color);
    //spiwrite(hi);
    //spiwrite(color);
    //spiwrite(color);
    // LcdSPI->clearRX();
  }
  /*for(y=h; y>0; y--) {
    for(x=w; x>0; x--) {
        //LcdSPI->fastWrite(color);
        //LcdSPI->write(hi);
        //LcdSPI->write(lo);
      spiwrite(hi);
      spiwrite(lo);
    }
  }*/

  //digitalWrite(_cs, HIGH);
  Pins[PIN_SCE]->write(1);
  //*csport |= cspinmask;
  if (hwSPI)
  {
    spi_end();
  }

  //wait_ms(30);
  LcdSPI->clearRX();
  //LcdSPI->format(LCD_SPI_BITS, LCD_SPI_MODE);
  //LcdSPI->setFormat();
}

// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t Adafruit_ILI9341::color565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

#define MADCTL_MY 0x80
#define MADCTL_MX 0x40
#define MADCTL_MV 0x20
#define MADCTL_ML 0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH 0x04

void Adafruit_ILI9341::setRotation(uint8_t m)
{

  if (hwSPI)
  {
    spi_begin();
  }
  writecommand(ILI9341_MADCTL);
  rotation = m % 4; // can't be higher than 3
  switch (rotation)
  {
  case 0:
    writedata(MADCTL_MX | MADCTL_BGR);
    _width = ILI9341_TFTWIDTH;
    _height = ILI9341_TFTHEIGHT;
    break;
  case 1:
    writedata(MADCTL_MV | MADCTL_BGR);
    _width = ILI9341_TFTHEIGHT;
    _height = ILI9341_TFTWIDTH;
    break;
  case 2:
    writedata(MADCTL_MY | MADCTL_BGR);
    _width = ILI9341_TFTWIDTH;
    _height = ILI9341_TFTHEIGHT;
    break;
  case 3:
    writedata(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
    _width = ILI9341_TFTHEIGHT;
    _height = ILI9341_TFTWIDTH;
    break;
  }
  if (hwSPI) {
    spi_end();
  }
}

void Adafruit_ILI9341::invertDisplay(bool i)
{
  if (hwSPI) {
    spi_begin();
  }
  writecommand(i ? ILI9341_INVON : ILI9341_INVOFF);
  if (hwSPI) {
    spi_end();
  }
}

uint8_t Adafruit_ILI9341::spiread(void)
{
  //LcdSPI->clearRX();
  uint8_t r = 0;
  r = LcdSPI->write(0);
  return r;
}

uint8_t Adafruit_ILI9341::readdata(void)
{
  Pins[PIN_DC]->write(1);
  Pins[PIN_SCE]->write(0);
  //digitalWrite(_dc, HIGH);
  //digitalWrite(_cs, LOW);
  uint8_t r = spiread();
  //digitalWrite(_cs, HIGH);
  Pins[PIN_SCE]->write(1);
  return r;
}

uint8_t Adafruit_ILI9341::readcommand8(uint8_t c, uint8_t index)
{
  if (hwSPI) {
    spi_begin();
  }
  LcdSPI->format(8, LCD_SPI_MODE);

  Pins[PIN_DC]->write(0);
  Pins[PIN_SCE]->write(0);
  //digitalWrite(_dc, LOW); // command
  //digitalWrite(_cs, LOW);
  spiwrite(0xD9); // woo sekret command?
  Pins[PIN_DC]->write(1);
  //digitalWrite(_dc, HIGH); // data
  spiwrite(0x10 + index);
  //digitalWrite(_cs, HIGH);
  Pins[PIN_SCE]->write(1);

  Pins[PIN_DC]->write(0);
  Pins[PIN_SCE]->write(0);
  //digitalWrite(_dc, LOW);
  //digitalWrite(_sclk, LOW);
  //digitalWrite(_cs, LOW);
  spiwrite(c);
  Pins[PIN_DC]->write(1);
  //digitalWrite(_dc, HIGH);
  uint8_t r = spiread();
  Pins[PIN_SCE]->write(1);
  //digitalWrite(_cs, HIGH);
  if (hwSPI) {
    spi_end();
  }

  LcdSPI->format(LCD_SPI_BITS, LCD_SPI_MODE);
  return r;
}
