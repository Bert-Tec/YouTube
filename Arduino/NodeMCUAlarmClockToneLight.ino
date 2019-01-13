//--------------Description--------------
// Loudspeaker Pin D5
// Display Pin SDA = D2 ; SDC = D1
// Button D7 & D8
// WS2801 Strip: 5v = VU ; Ground = G ; SI = D3 ; CLK = D4

//--------------libaries include
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <time.h>

#include "Adafruit_WS2801.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif

//--------------NTP Time
const char* ssid = "Franck";
const char* password = "62046022";

//0 = GMT
int timezone = 1 * 3600;
int dst = 0;

//--------------Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//--------------Tone
//GPIO14 is D5 at NodeMcu
#define BUZZER_PIN 14

//--------------Alarm
int alarmTimeHH = 23;
int alarmTimeMM = 30;
// alarmLightTime in minutes | max. 59 minutes
int alarmLightTime = 5;

//--------------Buttons
//13 = D7 ; 15 = D8
const int buttonHHPin = 13;
const int buttonMMPin = 15;
int buttonHHState = 0;
int buttonMMState = 0;

//--------------LED STRIP
uint8_t dataPin  = 0;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 2;    // Green wire on Adafruit Pixels
// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(7, dataPin, clockPin);

void setup() {

  Serial.begin(9600);
  
//for display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

//for clock
  //start wifi connection
  WiFi.begin(ssid,password);
  //set time parameters, you can change the ntp servers to such in your area
  configTime(timezone, dst, "de.pool.ntp.org","europe.pool.ntp.org");

//for Buttons
  // initialize the pushbuttons pins as an input:
  pinMode(buttonHHPin, INPUT);
  pinMode(buttonMMPin, INPUT);

//for LED Strip
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif
  strip.begin();
  // Update LED contents, to start they are all 'off'
  strip.show();
  colorWipe(Color(0, 0, 0), 10);
}

//for LED Strip
// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
/* Helper function */
// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//for Alarm Tone
void doAlarmSound(int lenght){
  analogWriteFreq(5000);
  analogWrite(BUZZER_PIN, 512);
  delay(lenght/2);
  analogWriteFreq(30000);
  analogWrite(BUZZER_PIN, 512);
  delay(lenght/2);
  analogWrite(BUZZER_PIN, 0);
}
//for alarm LED light
void doAlarmLight(int tm_min, int tm_sec)
{
  int help = alarmLightTime * 60 / 19;
  int help2 = (tm_min - (alarmTimeMM - alarmLightTime)) * 60 + tm_sec;
  
  Serial.println("led alarm ");
  Serial.println(help);
  Serial.println(help2);
  
  if(help * 1 < help2 && help * 2 > help2)
  {
    colorWipe(Color(25, 25, 0), 0);
  }
  if(help * 2 < help2 && help * 3 > help2)
  {
    colorWipe(Color(50, 25, 0), 0);
  }
  if(help * 3 < help2 && help * 4 > help2)
  {
    colorWipe(Color(70, 35, 0), 0);
  }
  if(help * 4 < help2 && help * 5 > help2)
  {
    colorWipe(Color(150, 50, 0), 0);
  }
  if(help * 5 < help2 && help * 6 > help2)
  {
    colorWipe(Color(220, 70, 0), 0);
  }
  if(help * 6 < help2 && help * 7 > help2)
  {
    colorWipe(Color(240, 40, 0), 0);
  }
  if(help * 7 < help2 && help * 8 > help2)
  {
    colorWipe(Color(250, 10, 30), 0);
  }   
  if(help * 8 < help2 && help * 9 > help2)   
  {
    colorWipe(Color(255, 0, 40), 0);
  }   
  if(help * 9 < help2 && help * 10 > help2)   
  {
    colorWipe(Color(230, 0, 70), 0);
  }   
  if(help * 10 < help2 && help * 11 > help2)   
  {
    colorWipe(Color(220, 0, 100), 0);
  }   
  if(help * 11 < help2 && help * 12 > help2)   
  {
    colorWipe(Color(210, 0, 120), 0);
  }   
  if(help * 12 < help2 && help * 13 > help2)   
  {
    colorWipe(Color(200, 0, 150), 0);
  }   
  if(help * 13 < help2 && help * 14 > help2)   
  {
    colorWipe(Color(200, 20, 170), 0);
  }   
  if(help * 14 < help2 && help * 15 > help2)   
  {
    colorWipe(Color(200, 50, 200), 0);
  }   
  if(help * 15 < help2 && help * 16 > help2)   
  {
    colorWipe(Color(200, 100, 200), 0);
  }   
  if(help * 16 < help2 && help * 17 > help2)   
  {
    colorWipe(Color(200, 150, 200), 0);
  }   
  if(help * 17 < help2 && help * 18 > help2)   
  {
    colorWipe(Color(200, 170, 200), 0);
  }   
  if(help * 18 < help2 && help * 19 > help2)   
  {
    colorWipe(Color(220, 170, 220), 0);
  }   
  if(help * 19 < help2 && help * 20 > help2)   
  {
    colorWipe(Color(250, 170, 250), 0);
  }   
}

void loop() {

  //clear display
  display.clearDisplay();
  
  time_t now = time(nullptr);
  struct tm* pTime = localtime(&now);
    
  //write time inversive
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(10,5);
  display.setTextSize(2);
  //print 0 if hour under 10
  if(pTime->tm_hour < 10)
  {
    display.print("0");
  }
  display.print(pTime->tm_hour);
  display.print(":");
  //print 0 if min under 10
  if(pTime->tm_min < 10)
  {
    display.print("0");
  }
  display.print(pTime->tm_min);
  display.print(":");
  //print 0 if seconds under 10
  if(pTime->tm_sec < 10)
  {
    display.print("0");
  }
  display.print(pTime->tm_sec);
  display.display();

  //write date normally
  display.setTextColor(WHITE);
  display.setCursor(10,24);
  display.setTextSize(1);
  //print 0 if day under 10
  if(pTime->tm_mday < 10)
  {
    display.print("0");
  }
  display.print(pTime->tm_mday);
  display.print(".");
  //print 0 if month under 10
  if(pTime->tm_mon < 10)
  {
    display.print("0");
  }
  display.print(1+pTime->tm_mon);
  display.print(".");
      //1900 is start of year count
  display.print(1900+pTime->tm_year);
  display.display();

  //write alarmTime normally
  display.setTextColor(WHITE);
  display.setCursor(76,24);
  display.setTextSize(1);
  //print 0 if hour under 10
  if(alarmTimeHH < 10)
  {
    display.print("0");
  }
  display.print(alarmTimeHH);
  display.print(":");
  //print 0 if min under 10
  if(alarmTimeMM < 10)
  {
    display.print("0");
  }
  display.print(alarmTimeMM);
  display.display();

  unsigned long StartTime = millis();
  unsigned long CurrentTime = 0;
  
  do{
    //check if alarmTime is now
    if (pTime->tm_hour == alarmTimeHH && pTime->tm_min == alarmTimeMM)
    {
      //make sound
        doAlarmSound(500);
    }
    else if(pTime->tm_hour == alarmTimeHH || ((pTime->tm_min - alarmLightTime) <= 0 && pTime->tm_hour == alarmTimeHH - 1))
    {
      if(pTime->tm_min - alarmLightTime > 0 && (pTime->tm_min > (alarmTimeMM - alarmLightTime) && pTime->tm_min < alarmTimeMM))
      {
        //control light
        doAlarmLight(pTime->tm_min, pTime->tm_sec);
      }
      else
      {
        //reset led strip
        colorWipe(Color(0, 0, 0), 10);
      }
    }
    // read the state of the pushbutton value:
    buttonMMState = digitalRead(buttonMMPin);
    buttonHHState = digitalRead(buttonHHPin);
  
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonHHState == HIGH) 
    {
      if(alarmTimeHH < 23)
      {
        alarmTimeHH++;
      }
      else
      {
      alarmTimeHH = 0;
      }
      delay(200);
      break;
    } 
    else if (buttonMMState == HIGH)
    {
      if(alarmTimeMM < 59)
      {
        alarmTimeMM++;
      }
      else
      {
      alarmTimeMM = 0;
      }
      delay(200);
      break;
    }
    //reset button states
    buttonMMState = 0;
    buttonHHState = 0;
  
    CurrentTime = millis();
  }
  //exit button check loop if 500 milliseconds are over
  while(((CurrentTime - StartTime) < 500)); 
  
}
