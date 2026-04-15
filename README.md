# AutoOLED Library

[![Sponsor](https://img.shields.io/badge/Sponsor-Deeplab--Studio-ea4aaa?style=for-the-badge&logo=github-sponsors)](https://github.com/sponsors/Deeplab-Studio)

**AutoOLED** is a smart wrapper library for ESP32/Arduino that simplifies working with monochrome OLED displays. It automatically detects whether you are using an **SSD1306** or **SH1106** display driver and provides a unified, high-performance interface.

## Features
*   **Auto-Detection**: No need to hardcode the driver type. The library probes I2C addresses and identifies the controller.
*   **Unified API**: Write your code once, run it on any common 0.96" or 1.3" OLED.
*   **Adafruit_GFX Compatible**: Fully inherits from `Adafruit_GFX`, exposing all standard drawing functions (`drawLine`, `drawCircle`, `print`, etc.).
*   **Performance Optimized**: Automatically routes calls like `drawFastHLine`, `fillRect`, and text writing to the underlying hardware-specific driver for maximum speed.
*   **Safe**: Handles differences between drivers (like scrolling support) gracefully.

## Installation
1.  Copy the `AutoOLED` folder to your project's `lib/` directory.
2.  Add the dependencies to your `platformio.ini`:
    ```ini
    lib_deps =
        adafruit/Adafruit GFX Library 
        adafruit/Adafruit SSD1306
        adafruit/Adafruit SH110X
    ```

## Usage

### 1. Include and Initialize
```cpp
#include <AutoOLED.h>

// Create instance (128x64 pixels, reset pin -1 if unused)
AutoOLED display(128, 64, -1);

void setup() {
    Serial.begin(115200);
    
    // Initialize (Auto-detects address 0x3C by default)
    if (!display.begin()) {
        Serial.println("OLED not found!");
        while(1);
    }
    
    Serial.println("OLED initialized!");
}
```

### 2. Drawing Shapes
All standard GFX functions work directly:
```cpp
display.clearDisplay(); // Always clear buffer first

display.drawPixel(10, 10, WHITE);
display.drawLine(0, 0, 128, 64, WHITE);
display.drawRect(10, 10, 50, 30, WHITE);
display.fillRect(10, 10, 50, 30, WHITE);
display.drawCircle(64, 32, 10, WHITE);
drawTriangle(10, 10, 20, 30, 0, 30, WHITE);

display.display(); // Push buffer to screen
```

### 3. Text & Typography
```cpp
display.setTextSize(1);      // Normal 1:1 pixel scale
display.setTextColor(WHITE); // White text
display.setCursor(0, 0);     // Top-left corner
display.println("Hello!");

display.setTextSize(2);      // 2x magnification
display.println("BIG TEXT");

// Inverted Text (Black text on White background)
display.setTextColor(BLACK, WHITE); 
display.print("Inverted");
```

### 4. Hardware Control
```cpp
display.dim(true);        // Dim the display
display.invertDisplay(true); // Invert all colors (Night mode)
display.off();            // Sleep mode (Display OFF)
display.on();             // Wake up (Display ON)
```

## API Reference

### Core
*   `bool begin(TwoWire *wire, uint8_t addr)`: Starts the display. Returns `true` on success.
*   `void display()`: Sends the buffer to the screen. **Must be called to see changes.**
*   `void clearDisplay()`: Clears the internal buffer.

### Drawing (Inherited from Adafruit_GFX)
*   `drawPixel(x, y, color)`
*   `drawLine(x0, y0, x1, y1, color)`
*   `drawFastVLine(x, y, h, color)` / `drawFastHLine(x, y, w, color)`
*   `drawRect(x, y, w, h, color)` / `fillRect(x, y, w, h, color)`
*   `drawCircle(x, y, r, color)` / `fillCircle(x, y, r, color)`
*   `drawTriangle(x0, y0, x1, y1, x2, y2, color)` / `fillTriangle(...)`
*   `drawRoundRect(x, y, w, h, r, color)` / `fillRoundRect(...)`
*   `drawBitmap(x, y, bitmap, w, h, color)`

### Text
*   `setCursor(x, y)`
*   `setTextSize(size)`
*   `setTextColor(color)` or `setTextColor(fg, bg)`
*   `setTextWrap(bool)`
*   `print(data)` / `println(data)`

### Advanced
*   `AutoOLEDType getType()`: Returns `OLED_SSD1306`, `OLED_SH1106`, or `OLED_NONE`.
*   `getPixel(x, y)`: Returns the color of a pixel in the buffer.
*   `setContrast(chunk)`: Sets display contrast (0-255).
