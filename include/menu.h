
class Element {
    private:
        uint8_t n;
        const char *text;
    public:
     Element(uint8_t _n, const char *_text) {
         n = _n;
         text = _text;
     }
};

class Menu {
  private:
    Adafruit_ST7735 *_tft;
    uint8_t active = -1;

  public:
    Menu(Adafruit_ST7735 *tft): _tft(tft) {}

    void element(byte n, const char *chars) {
       _tft->setCursor(1, n * 10);
       if (n == active) {
           _tft->print("* ");
       } else {
           _tft->print("  ");
       }
       _tft->print(n);
       _tft->print(". ");
       _tft->print(chars);
    }

    void setActive(uint8_t n) {
        active = n;
    }

    void render() {
        _tft->fillRect(0, 0, 7, 5 * 10, ST77XX_BLACK);
        
       _tft->setTextColor(ST77XX_WHITE);
       _tft->setTextWrap(true);
        
        element(1, "LAN");
        element(2, "GPS");
        element(3, "Navigation");
        element(4, "Exit");
    }
};