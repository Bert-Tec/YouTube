//--------------Description--------------
// Loudspeaker Pin D5
// Display Pin SDA = D2 ; SDC = D1
// Button D7 & D8

//--------------libaries include
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <time.h>

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
int alarmTimeHH = 18;
int alarmTimeMM = 30;

//--------------Buttons
//13 = D7 ; 15 = D8
const int buttonHHPin = 13;
const int buttonMMPin = 15;
int buttonHHState = 0;
int buttonMMState = 0;

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

//for Buttons
  // initialize the pushbuttons pins as an input:
  pinMode(buttonHHPin, INPUT);
  pinMode(buttonMMPin, INPUT);
}

//for Alarm Tone
void doAlarm(int lenght){
  analogWriteFreq(5000);
  analogWrite(BUZZER_PIN, 512);
  delay(lenght/2);
  analogWriteFreq(30000);
  analogWrite(BUZZER_PIN, 512);
  delay(lenght/2);
  analogWrite(BUZZER_PIN, 0);
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
      doAlarm(500);
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
