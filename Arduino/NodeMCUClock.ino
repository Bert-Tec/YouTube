#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <time.h>

const char* ssid = "xxx";
const char* password = "xxxx";

//0 = GMT
int timezone = 1 * 3600;
int dst = 0;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
//for display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

//for clock
  //start wifi connection
  WiFi.begin(ssid,password);
  //set time parameters, you can change the ntp servers to such in your area
  configTime(timezone, dst, "de.pool.ntp.org","europe.pool.ntp.org");
}

void loop() {

  //clear display
  display.clearDisplay();
  
  time_t now = time(nullptr);
  struct tm* pTime = localtime(&now);
    
  //write time inversive
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(20,5);
  display.setTextSize(2);
  display.print(pTime->tm_hour);
  display.print(":");
  display.print(pTime->tm_min);
  display.print(":");
  display.print(pTime->tm_sec);
  display.display();

  //write date normally
  display.setTextColor(WHITE);
  display.setCursor(40,24);
  display.setTextSize(1);
  display.print(pTime->tm_mday);
  display.print(".");
  display.print(1+pTime->tm_mon);
  display.print(".");
  display.print(1900+pTime->tm_year);
  display.display();

  delay(1000);
}
