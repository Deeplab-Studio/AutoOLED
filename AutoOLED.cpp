#include "AutoOLED.h"

AutoOLED::AutoOLED(int width, int height, int resetPin) 
    : Adafruit_GFX(width, height), _resetPin(resetPin)
{
    _type = OLED_NONE;
    _ssd1306 = nullptr;
    _sh1106 = nullptr;
}

AutoOLED::~AutoOLED() {
    if (_ssd1306) delete _ssd1306;
    if (_sh1106) delete _sh1106;
}

bool AutoOLED::begin(TwoWire *wire, uint8_t addr) {
    _ssd1306 = new Adafruit_SSD1306(WIDTH, HEIGHT, wire, _resetPin);
    if (_ssd1306->begin(SSD1306_SWITCHCAPVCC, addr)) {
        _type = OLED_SSD1306;
        _ssd1306->clearDisplay();
        _ssd1306->setTextColor(SSD1306_WHITE);
        _ssd1306->display();
        return true;
    }
    delete _ssd1306; _ssd1306 = nullptr;

    _sh1106 = new Adafruit_SH1106G(WIDTH, HEIGHT, wire, _resetPin);
    if (_sh1106->begin(addr, true)) {
        _type = OLED_SH1106;
        _sh1106->clearDisplay();
        _sh1106->setTextColor(SH110X_WHITE);
        _sh1106->display();
        return true;
    }
    delete _sh1106; _sh1106 = nullptr;
    
    _type = OLED_NONE;
    return false;
}

// --- Core Display Functions ---

void AutoOLED::display() {
    if (_type == OLED_SSD1306) _ssd1306->display();
    else if (_type == OLED_SH1106) _sh1106->display();
}

void AutoOLED::clearDisplay() {
    if (_type == OLED_SSD1306) _ssd1306->clearDisplay();
    else if (_type == OLED_SH1106) _sh1106->clearDisplay();
}

void AutoOLED::invertDisplay(bool i) {
    if (_type == OLED_SSD1306) _ssd1306->invertDisplay(i);
    else if (_type == OLED_SH1106) _sh1106->invertDisplay(i);
}

void AutoOLED::dim(bool dim) {
    if (_type == OLED_SSD1306) _ssd1306->dim(dim);
}

void AutoOLED::on() { 
    if (_type == OLED_SSD1306) _ssd1306->ssd1306_command(SSD1306_DISPLAYON);
}

void AutoOLED::off() {
    if (_type == OLED_SSD1306) _ssd1306->ssd1306_command(SSD1306_DISPLAYOFF);
}

void AutoOLED::setContrast(uint8_t contrast) {
    if (_type == OLED_SSD1306) {
        _ssd1306->ssd1306_command(SSD1306_SETCONTRAST);
        _ssd1306->ssd1306_command(contrast);
    } else if (_type == OLED_SH1106) {
        _sh1106->setContrast(contrast);
    }
}

// --- Graphics Functions ---

void AutoOLED::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawPixel(x, y, color);
    else if (_type == OLED_SH1106) _sh1106->drawPixel(x, y, color);
}

void AutoOLED::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawLine(x0, y0, x1, y1, color);
    else if (_type == OLED_SH1106) _sh1106->drawLine(x0, y0, x1, y1, color);
}

void AutoOLED::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawFastVLine(x, y, h, color);
    else if (_type == OLED_SH1106) _sh1106->drawFastVLine(x, y, h, color);
}

void AutoOLED::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawFastHLine(x, y, w, color);
    else if (_type == OLED_SH1106) _sh1106->drawFastHLine(x, y, w, color);
}

void AutoOLED::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawRect(x, y, w, h, color);
    else if (_type == OLED_SH1106) _sh1106->drawRect(x, y, w, h, color);
}

void AutoOLED::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->fillRect(x, y, w, h, color);
    else if (_type == OLED_SH1106) _sh1106->fillRect(x, y, w, h, color);
}

void AutoOLED::fillScreen(uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->fillScreen(color);
    else if (_type == OLED_SH1106) _sh1106->fillScreen(color);
}

void AutoOLED::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawCircle(x0, y0, r, color);
    else if (_type == OLED_SH1106) _sh1106->drawCircle(x0, y0, r, color);
}

void AutoOLED::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->fillCircle(x0, y0, r, color);
    else if (_type == OLED_SH1106) _sh1106->fillCircle(x0, y0, r, color);
}

void AutoOLED::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawTriangle(x0, y0, x1, y1, x2, y2, color);
    else if (_type == OLED_SH1106) _sh1106->drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

void AutoOLED::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->fillTriangle(x0, y0, x1, y1, x2, y2, color);
    else if (_type == OLED_SH1106) _sh1106->fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

void AutoOLED::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawRoundRect(x0, y0, w, h, radius, color);
    else if (_type == OLED_SH1106) _sh1106->drawRoundRect(x0, y0, w, h, radius, color);
}

void AutoOLED::fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->fillRoundRect(x0, y0, w, h, radius, color);
    else if (_type == OLED_SH1106) _sh1106->fillRoundRect(x0, y0, w, h, radius, color);
}

void AutoOLED::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawBitmap(x, y, bitmap, w, h, color);
    else if (_type == OLED_SH1106) _sh1106->drawBitmap(x, y, bitmap, w, h, color);
}

void AutoOLED::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    if (_type == OLED_SSD1306) _ssd1306->drawBitmap(x, y, bitmap, w, h, color, bg);
    else if (_type == OLED_SH1106) _sh1106->drawBitmap(x, y, bitmap, w, h, color, bg);
}

void AutoOLED::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
     if (_type == OLED_SSD1306) _ssd1306->drawBitmap(x, y, bitmap, w, h, color);
    else if (_type == OLED_SH1106) _sh1106->drawBitmap(x, y, bitmap, w, h, color);
}

void AutoOLED::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
     if (_type == OLED_SSD1306) _ssd1306->drawBitmap(x, y, bitmap, w, h, color, bg);
    else if (_type == OLED_SH1106) _sh1106->drawBitmap(x, y, bitmap, w, h, color, bg);
}

void AutoOLED::drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {
    if (_type == OLED_SSD1306) _ssd1306->drawXBitmap(x, y, bitmap, w, h, color);
    else if (_type == OLED_SH1106) _sh1106->drawXBitmap(x, y, bitmap, w, h, color);
}

void AutoOLED::drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h) {
    if (_type == OLED_SSD1306) _ssd1306->drawGrayscaleBitmap(x, y, bitmap, w, h);
    else if (_type == OLED_SH1106) _sh1106->drawGrayscaleBitmap(x, y, bitmap, w, h);
}

void AutoOLED::drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h) {
    if (_type == OLED_SSD1306) _ssd1306->drawGrayscaleBitmap(x, y, bitmap, w, h);
    else if (_type == OLED_SH1106) _sh1106->drawGrayscaleBitmap(x, y, bitmap, w, h);
}


// --- Text Functions ---

void AutoOLED::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
    if (_type == OLED_SSD1306) _ssd1306->drawChar(x, y, c, color, bg, size);
    else if (_type == OLED_SH1106) _sh1106->drawChar(x, y, c, color, bg, size);
}

void AutoOLED::setTextSize(uint8_t s) {
    if (_type == OLED_SSD1306) _ssd1306->setTextSize(s);
    else if (_type == OLED_SH1106) _sh1106->setTextSize(s);
}

void AutoOLED::setTextSize(uint8_t sx, uint8_t sy) {
    if (_type == OLED_SSD1306) _ssd1306->setTextSize(sx, sy);
    else if (_type == OLED_SH1106) _sh1106->setTextSize(sx, sy);
}

void AutoOLED::setTextColor(uint16_t c) {
    if (_type == OLED_SSD1306) _ssd1306->setTextColor(c);
    else if (_type == OLED_SH1106) _sh1106->setTextColor(c);
}

void AutoOLED::setTextColor(uint16_t c, uint16_t bg) {
    if (_type == OLED_SSD1306) _ssd1306->setTextColor(c, bg);
    else if (_type == OLED_SH1106) _sh1106->setTextColor(c, bg);
}

void AutoOLED::setTextWrap(bool w) {
    if (_type == OLED_SSD1306) _ssd1306->setTextWrap(w);
    else if (_type == OLED_SH1106) _sh1106->setTextWrap(w);
}

void AutoOLED::setCursor(int16_t x, int16_t y) {
    if (_type == OLED_SSD1306) _ssd1306->setCursor(x, y);
    else if (_type == OLED_SH1106) _sh1106->setCursor(x, y);
}

void AutoOLED::cp437(bool x) {
    if (_type == OLED_SSD1306) _ssd1306->cp437(x);
    else if (_type == OLED_SH1106) _sh1106->cp437(x);
}

void AutoOLED::setFont(const GFXfont *f) {
    if (_type == OLED_SSD1306) _ssd1306->setFont(f);
    else if (_type == OLED_SH1106) _sh1106->setFont(f);
}

void AutoOLED::getTextBounds(const char *string, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
    if (_type == OLED_SSD1306) _ssd1306->getTextBounds(string, x, y, x1, y1, w, h);
    else if (_type == OLED_SH1106) _sh1106->getTextBounds(string, x, y, x1, y1, w, h);
}

void AutoOLED::getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
    if (_type == OLED_SSD1306) _ssd1306->getTextBounds(str, x, y, x1, y1, w, h);
    else if (_type == OLED_SH1106) _sh1106->getTextBounds(str, x, y, x1, y1, w, h);
}


// --- Print Interface ---

size_t AutoOLED::write(uint8_t c) {
    if (_type == OLED_SSD1306) return _ssd1306->write(c);
    else if (_type == OLED_SH1106) return _sh1106->write(c);
    return 0;
}

size_t AutoOLED::write(const uint8_t *buffer, size_t size) {
    if (_type == OLED_SSD1306) return _ssd1306->write(buffer, size);
    else if (_type == OLED_SH1106) return _sh1106->write(buffer, size);
    return 0;
}

// --- Advanced / Misc ---

void AutoOLED::setRotation(uint8_t r) {
    if (_type == OLED_SSD1306) _ssd1306->setRotation(r);
    else if (_type == OLED_SH1106) _sh1106->setRotation(r);
}

int16_t AutoOLED::getCursorX() const {
    if (_type == OLED_SSD1306) return _ssd1306->getCursorX();
    else if (_type == OLED_SH1106) return _sh1106->getCursorX();
    return 0;
}

int16_t AutoOLED::getCursorY() const {
    if (_type == OLED_SSD1306) return _ssd1306->getCursorY();
    else if (_type == OLED_SH1106) return _sh1106->getCursorY();
    return 0;
}


bool AutoOLED::getPixel(int16_t x, int16_t y) {
    if (_type == OLED_SSD1306) return _ssd1306->getPixel(x, y);
    else if (_type == OLED_SH1106) return _sh1106->getPixel(x, y);
    return false;
}

uint8_t* AutoOLED::getBuffer() {
    if (_type == OLED_SSD1306) return _ssd1306->getBuffer();
    return nullptr;
}


void AutoOLED::ssd1306_command(uint8_t c) {
    if (_type == OLED_SSD1306) _ssd1306->ssd1306_command(c);
}

// --- Scrolling ---

void AutoOLED::startscrollright(uint8_t start, uint8_t stop) {
    if (_type == OLED_SSD1306) _ssd1306->startscrollright(start, stop);
}
void AutoOLED::startscrollleft(uint8_t start, uint8_t stop) {
    if (_type == OLED_SSD1306) _ssd1306->startscrollleft(start, stop);
}
void AutoOLED::startscrolldiagright(uint8_t start, uint8_t stop) {
    if (_type == OLED_SSD1306) _ssd1306->startscrolldiagright(start, stop);
}
void AutoOLED::startscrolldiagleft(uint8_t start, uint8_t stop) {
    if (_type == OLED_SSD1306) _ssd1306->startscrolldiagleft(start, stop);
}
void AutoOLED::stopscroll(void) {
    if (_type == OLED_SSD1306) _ssd1306->stopscroll();
}

AutoOLEDType AutoOLED::getType() {
    return _type;
}
