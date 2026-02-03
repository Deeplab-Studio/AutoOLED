#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SH110X.h>

enum AutoOLEDType {
    OLED_NONE,
    OLED_SSD1306,
    OLED_SH1106
};

class AutoOLED : public Adafruit_GFX {
public:
    AutoOLED(int width = 128, int height = 64, int resetPin = -1);
    ~AutoOLED();

    // --- Initialization ---
    bool begin(TwoWire *wire = &Wire, uint8_t addr = 0x3C);

    // --- Core Display Functions ---
    void display();
    void clearDisplay();
    void invertDisplay(bool i) override;
    void dim(bool dim);
    void on();
    void off();
    void setContrast(uint8_t contrast);
    
    // --- Basic Drawing Functions (Adafruit_GFX Wrappers) ---
    // These are explicitly listed here for reference, but implementation 
    // may just use the base class or forward to driver.
    
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    
    // Lines
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) override;
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;

    // Rectangles
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    virtual void fillScreen(uint16_t color) override;
    
    // Circles
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    
    // Triangles
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    
    // Rounded Rectangles
    void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);

    // Bitmaps
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color, uint16_t bg);
    void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);
    void drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
    void drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h);
    void drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h);
    
    // Characters & Text
    void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
    void setTextSize(uint8_t s);
    void setTextSize(uint8_t sx, uint8_t sy);
    void setTextColor(uint16_t c);
    void setTextColor(uint16_t c, uint16_t bg);
    void setTextWrap(bool w);
    void setCursor(int16_t x, int16_t y);
    void cp437(bool x = true);
    void setFont(const GFXfont *f = NULL);
    void getTextBounds(const char *string, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
    void getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);

    // Print Interface
    virtual size_t write(uint8_t c) override;
    virtual size_t write(const uint8_t *buffer, size_t size) override;

    // --- Advanced / Misc ---
    void setRotation(uint8_t r) override;
    int16_t getCursorX(void) const;
    int16_t getCursorY(void) const;
    
    bool getPixel(int16_t x, int16_t y);
    uint8_t* getBuffer();

    // --- Scrolling ---
    void startscrollright(uint8_t start, uint8_t stop);
    void startscrollleft(uint8_t start, uint8_t stop);
    void startscrolldiagright(uint8_t start, uint8_t stop);
    void startscrolldiagleft(uint8_t start, uint8_t stop);
    void stopscroll(void);
    
    // --- Direct Access ---
    void ssd1306_command(uint8_t c);
    Adafruit_SSD1306* getSSD1306() { return _ssd1306; }
    Adafruit_SH1106G* getSH1106() { return _sh1106; }
    AutoOLEDType getType();

private:
    int _resetPin;
    AutoOLEDType _type;
    
    Adafruit_SSD1306* _ssd1306;
    Adafruit_SH1106G* _sh1106;
};
