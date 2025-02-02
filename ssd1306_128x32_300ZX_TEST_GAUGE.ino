#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pixel art for the 300ZX (simplified for 128x32 OLED)
static const unsigned char PROGMEM car_bitmap[] = {
// 'pixilart-drawing', 113x32px
// 'pixilart-drawing', 114x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x27, 0xff, 0xff, 0xfc, 0x1e, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xdc, 0x00, 0x02, 0xe3, 0xe1, 0x80, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
0x38, 0x00, 0x01, 0x5e, 0x7e, 0x60, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xe0, 
0x00, 0x01, 0x41, 0xa3, 0x98, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x80, 0x00, 
0x01, 0x5e, 0x50, 0x67, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4e, 0x00, 0x00, 0x01, 
0x51, 0x28, 0x38, 0xe0, 0x1f, 0x40, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf8, 0x00, 0x00, 0x01, 0x50, 
0x94, 0x07, 0x19, 0xe6, 0x40, 0x00, 0x00, 0x03, 0xfc, 0x00, 0xe0, 0x00, 0x00, 0x01, 0x50, 0x4a, 
0x00, 0xf6, 0x0c, 0x40, 0x00, 0x00, 0x7c, 0x03, 0xff, 0x80, 0x00, 0x00, 0x01, 0x5f, 0xca, 0x00, 
0x1e, 0x18, 0x40, 0x00, 0x03, 0x83, 0xfc, 0x02, 0x00, 0x00, 0x00, 0x02, 0x40, 0x0a, 0x00, 0x02, 
0x70, 0x40, 0x00, 0x0c, 0x7c, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
0x40, 0x00, 0x33, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x10, 0x40, 
0x00, 0xfc, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x10, 0x40, 0x03, 
0xc0, 0x3f, 0x80, 0x06, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1f, 0xc0, 0x00, 0x10, 0x40, 0x0f, 0x81, 
0xc0, 0x70, 0x04, 0x00, 0x00, 0x00, 0x3c, 0x40, 0xe0, 0x38, 0x00, 0x0c, 0x40, 0x11, 0x02, 0x3f, 
0x88, 0x04, 0x00, 0x00, 0x00, 0x3c, 0x41, 0x1f, 0xc4, 0x00, 0x02, 0x40, 0x20, 0xfd, 0xc0, 0x74, 
0x04, 0x00, 0x00, 0x00, 0x00, 0x82, 0xe0, 0x3a, 0x00, 0x02, 0x40, 0x20, 0x0a, 0x20, 0x8a, 0x04, 
0x00, 0x00, 0x00, 0x00, 0x85, 0x10, 0x45, 0x00, 0x02, 0x40, 0x2f, 0x94, 0x11, 0x05, 0x04, 0x00, 
0x00, 0x00, 0x01, 0x0a, 0x08, 0x82, 0x80, 0xfe, 0x40, 0x28, 0x94, 0x0a, 0x05, 0x06, 0x00, 0x00, 
0x00, 0x03, 0x0a, 0x05, 0x02, 0x8f, 0x04, 0x40, 0x29, 0x17, 0xf5, 0xfd, 0x03, 0xff, 0xff, 0xff, 
0xfe, 0x0b, 0xfa, 0xfe, 0xf0, 0x04, 0x40, 0x2e, 0x14, 0x0a, 0x05, 0x02, 0x00, 0x00, 0x00, 0x06, 
0x0a, 0x05, 0x02, 0x80, 0x04, 0x40, 0x20, 0x14, 0x11, 0x05, 0x03, 0x00, 0x00, 0x00, 0x0c, 0x0a, 
0x08, 0x82, 0x80, 0x08, 0x40, 0x20, 0x2a, 0x20, 0x8a, 0x81, 0xff, 0xff, 0xff, 0xf8, 0x15, 0x10, 
0x45, 0x40, 0x08, 0x40, 0x20, 0x25, 0xc0, 0x74, 0x80, 0x00, 0x00, 0x00, 0x00, 0x12, 0xe0, 0x3a, 
0x40, 0xf0, 0x40, 0x78, 0x42, 0x3f, 0x88, 0x40, 0x00, 0x00, 0x00, 0x00, 0x21, 0x1f, 0xc4, 0x27, 
0x00, 0x40, 0x07, 0xc1, 0xc0, 0x70, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0x38, 0x38, 0x00, 
0x40, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x400
};

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();
  
  display.display();

  delay(2000);
  
  // Draw the car and start animation
  animateCar();
  display.clearDisplay();
  display.display();
  writeText();

}

void loop() {
  // Nothing to do here
}
void animateCar() {
  int carX = SCREEN_WIDTH; // Start at the right edge of the screen

  while (true) { // Infinite loop for continuous animation
    display.clearDisplay();

    // Draw the car
    display.drawBitmap(carX, 0, car_bitmap, 113, 32, SSD1306_WHITE);

    // Update screen
    display.display();
    
    // Move the car to the left
    carX -= 15;
    
    // If the car moves out of the screen, reset it to the right
    if (carX < -113) { // If the car is off the left side
      break;
    }

    delay(50); // Control the speed of the animation
  }
}
void writeText() {
  display.clearDisplay(); 
  display.setTextSize(1); // Set the text size (1 for standard text)
  display.setTextColor(SSD1306_WHITE); 

  String line1 = "NISSAN";
  String line2 = "300ZX";

  int x1, y1, w1, h1; // For line1
  int x2, y2, w2, h2; // For line2

  // Calculate the bounds of each line of text
  display.getTextBounds(line1, 0, 0, &x1, &y1, &w1, &h1);
  display.getTextBounds(line2, 0, 0, &x2, &y2, &w2, &h2);

  // Calculate the center position of each line
  int line1X = (SCREEN_WIDTH - w1) / 2; 
  int line2X = (SCREEN_WIDTH - w2) / 2; 

  int line1Y = SCREEN_HEIGHT / 4; // Y position for first line
  int line2Y = SCREEN_HEIGHT / 2; // Y position for second line

  // Gradually reveal each letter:
  for (int i = 0; i <= line1.length(); i++) {
    display.clearDisplay();
    display.setCursor(line1X, line1Y);
    display.print(line1.substring(0, i)); // Display part of line1

    display.setCursor(line2X, line2Y);
    display.print(line2.substring(0, i)); // Display part of line2

    display.display();
    delay(200); 
  }
  delay(1000);

  // Invert the display color (background and text)
  for (int j = 0; j < 3; j++) { // Flash 3 times
    display.invertDisplay(true);  
    delay(100); 
    display.invertDisplay(false); 
    delay(100); 
  }

  display.clearDisplay(); // Clear the screen
  display.setTextSize(1); // Set the text size for the new information
  display.setTextColor(SSD1306_WHITE); // Set text color to white

  // Display key information
  display.setCursor(10, 10); // Position for "Coolant Temperature"
  display.print("Coolant Temp: 85C"); 

  display.setCursor(10, 20); // Position for "Oil Temperature"
  display.print("Oil Temp: 100C"); 

  display.display(); 
}


