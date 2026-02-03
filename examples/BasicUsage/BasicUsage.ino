#include <Arduino.h>
#include <AutoOLED.h>

/* 
 * ==========================================
 *      AutoOLED Library - Tutorial Demo
 * ==========================================
 * This sketch demonstrates how to use the AutoOLED library.
 * The library automatically handles the differences between
 * SSD1306 and SH1106 displays, letting you focus on drawing.
 */

// 1. Create the Display Object
// Standard 0.96" or 1.3" displays are usually 128x64 pixels.
AutoOLED display(128, 64);

// Example Bitmap (16x16 Smile Icon)
// Bitmaps are arrays of bytes where each bit represents a pixel.
// You can generate these using online tools like "Image2CPP".
const unsigned char PROGMEM smile_bmp[] = {
  0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x10, 0x08, 0x20, 0x04, 0x40, 0x02, 0x40, 0x02, 0x42, 0x42, 
  0x42, 0x42, 0x40, 0x02, 0x40, 0x02, 0x21, 0x84, 0x10, 0x08, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00
};

void setup() {
  Serial.begin(115200);
  Serial.println(F("\nStarting AutoOLED Tutorial..."));

  // 2. Initialize the Display
  // begin() scans I2C addresses 0x3C and 0x3D to find a display.
  // It returns true if an SSD1306 or SH1106 is found.
  if (!display.begin()) {
    Serial.println(F("Error: No display found! Check wiring."));
    while(1); // Stop here if failed
  }
  
  Serial.print(F("Success! Found type: "));
  Serial.println(display.getType() == OLED_SSD1306 ? "SSD1306" : "SH1106");

  // --- STEP 1: The Basics ---
  // The OLED uses a memory buffer. Nothing appears on screen
  // until you call display.display().
  
  display.clearDisplay(); // Always clear the buffer first!
  display.display();      // Show the empty black screen
  delay(500);

  // --- STEP 2: Drawing Text ---
  display.setTextSize(1);      // Normal 1:1 scale
  display.setTextColor(WHITE); // White text
  display.setCursor(0, 0);     // Top-Left corner
  display.println(F("Hello, World!")); // Print text
  
  display.setTextSize(2);      // Double size
  display.println(F("Large Text"));
  
  display.display(); // Don't forget this!
  delay(2000);

  // --- STEP 3: Drawing Shapes ---
  display.clearDisplay();
  
  // Draw a standard rectangle (x, y, width, height, color)
  display.drawRect(0, 0, 60, 40, WHITE);
  
  // Draw a filled rectangle
  display.fillRect(65, 0, 60, 40, WHITE);
  
  // Draw a circle (centerX, centerY, radius, color)
  display.drawCircle(30, 55, 8, WHITE);
  
  // Draw a line connecting two points
  display.drawLine(0, 42, 128, 42, WHITE);
  
  display.display();
  delay(2000);

  // --- STEP 4: Bitmaps & Icons ---
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println(F("Drawing Bitmaps:"));
  
  // Draw the smile icon defined at the top
  // (x, y, data, width, height, color)
  display.drawBitmap(56, 20, smile_bmp, 16, 16, WHITE);
  
  display.display();
  delay(2000);

  // --- STEP 5: Hardware Effects ---
  // You can control the display hardware directly.
  
  // Invert Colors (Night Mode / Highlight)
  display.invertDisplay(true); 
  delay(1000);
  display.invertDisplay(false);
  
  // Dimming (Low brightness)
  display.dim(true); 
  delay(1000);
  display.dim(false); // Full brightness

  // --- STEP 6: Optimized Drawing ---
  // AutoOLED automatically routes these to the fast hardware drivers
  display.clearDisplay();
  // Drawing many horizontal lines is much faster with drawFastHLine
  for(int i=0; i<64; i+=4) {
      display.drawFastHLine(0, i, 128, WHITE);
  }
  display.display();
  delay(1000);

  // --- Final Screen ---
  display.clearDisplay();
  display.setCursor(25, 25);
  display.setTextSize(1);
  display.println(F("Tutorial Done!"));
  display.display();
}

void loop() {
  // Animation Loop could go here
}
