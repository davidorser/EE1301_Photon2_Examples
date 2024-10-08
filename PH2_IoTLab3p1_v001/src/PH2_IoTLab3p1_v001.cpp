/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */
#include "Particle.h"
#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

int PIXEL_COUNT = 3;
#define PIXEL_PIN SPI // Only use SPI=MO=S0 or SPI1=D2 on Photon 2
                      // NOTE: On the Photon 2, this must be a compiler constant!
int PIXEL_TYPE = WS2812;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int tempPIN = A0;
double tempC = 0.0;
double targetTemp = 75;
#define COOL 0
#define OFF  1
#define HEAT 2
#define REDALERT 3
bool blinkOn = true;
int mode = OFF;
int setModeFromString(String inputString);
void djoEventHandler(String event, String data);

void setup() {
  pinMode(tempPIN,INPUT);
  Serial.begin(9600);
  Particle.variable("cV_temp",tempC);
  Particle.variable("cV_targetTemp",targetTemp);
  Particle.function("cF_setMode", setModeFromString);
  Particle.subscribe("djoTest",djoEventHandler);
  strip.begin();
}

void loop() {
  int ADCreading = analogRead(tempPIN);
  tempC = (ADCreading - 620) * 0.0806;
  Serial.print(mode);
  Serial.print(", ");
  Serial.print(ADCreading);
  Serial.print(", ");
   Serial.print(tempC);
  Serial.println(" degC");
  //Serial.printf("%4d, %6.3f degC\n",ADCreading,tempC);
  if(mode==COOL) {
    strip.setColor(0,0,0,100); // Blue
  } else if(mode==OFF) {
    strip.setColor(0,0,0,0); // LED off
  } else if(mode==HEAT) {
    strip.setColor(0,0,100,0); // Red
  } else if(mode==REDALERT) {
    if(blinkOn) {
      strip.setColor(0,100,150,50); // Orange
    } else {
      strip.setColor(0,0,0,0);
    }
    blinkOn = !blinkOn;
  }
  strip.show();
  delay(500);
}

int setModeFromString(String inputString) {
    if (inputString == "Cool") {
        mode = COOL;
        return 0;
    } else if (inputString == "Off" ) {
        mode = OFF;
        return 1;
    } else if (inputString == "Heat") {
        mode = HEAT;
        return 2;
    } else if (inputString == "REDALERT") {
        Particle.publish("REDALERT","myData");
        mode = REDALERT;
        return 3;
    } else {
        return -1; //If we get here return a Sentinel Value. -1 is common for errors.
    }
}

void djoEventHandler(String event, String data) {
  Serial.print(event);
  Serial.print(",");
  Serial.println(data);
}
