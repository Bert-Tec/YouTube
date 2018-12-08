#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  //hello world normal
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(5,10);
  display.setTextSize(1);
  display.println("Hello World!");
  display.display();
  
  delay(2500);

  //hello world inversive
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(5,10);
  display.println("Hello World!");
  display.display();

  delay(2500);

  //different text size
  display.clearDisplay();
  display.setCursor(5,10);
  display.setTextColor(WHITE);
  display.print("x");
  display.setTextSize(2);
  display.print("x");
  display.setTextSize(3);
  display.print("x");
  display.setTextSize(4);
  display.print("x");
  display.setTextSize(5);
  display.print("x");
  display.display();

  delay(2500);

  display.clearDisplay();

  //Lines
  //display.drawLine(startX, startY, endX, endY, color);
  display.clearDisplay();

  display.drawLine(0,0,display.width() - 1, display.height() - 1, WHITE);
  display.drawLine(display.width() - 1,0,0, display.height() - 1, WHITE);
  
  display.display();

  delay(2500);

  //rectangular
  //display.drawRect(upperLeftX, upperLeftY, width, height, color);
  //display.drawRoundRect(upperLeftX, upperLeftY, width, height, cornerRadius, color);
  display.clearDisplay();
  
  display.drawRect(10, 10, 10, 10, WHITE);
  display.fillRect(20, 20, 10, 10, WHITE);
  display.fillRect(25, 20, 5, 5, BLACK);
  display.drawRoundRect(50, 10, 20, 20, 5, WHITE);
  
  display.display();

  delay(2500);

  //circles
  //display.drawCircle(centerX, centerY, radius, color);
  display.clearDisplay();
    
  display.drawCircle(15, 15, 10, WHITE);
  display.fillCircle(50, 15, 15, WHITE);

  display.display();
  
  delay(2500);
  
  //triangles
  //display.drawTriangle(poin1X, point1Y, point2X, point2Y, point3X, point3Y, color);
  display.display();

  display.clearDisplay();

  display.drawTriangle(5, 5, 30, 5, 25, 20, WHITE);
  display.fillTriangle(50, 5, 50, 30, 70, 30, WHITE);

  display.display();

  delay(2500);
  
  //just pixels
  //display.drawPixel(pixelX, pixelY, color);
  display.clearDisplay();

  display.drawPixel(5, 5, WHITE);
  display.drawPixel(10, 10, WHITE);
    
  display.display();
  
  delay(2500);

static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };
    
  //  display.drawBitmap(topLeftX, topLeftY, pic, width, height, color);
  display.clearDisplay();
  
  display.drawBitmap(5, 5, logo_bmp, 16, 16, WHITE);

  display.display();
  
  delay(2500);
}
