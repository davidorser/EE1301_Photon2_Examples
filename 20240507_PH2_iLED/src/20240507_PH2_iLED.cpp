/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "neopixel.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

#define PIXEL_PIN SPI  // Only use SPI=MO=S0 or SPI1=D2 on Photon 2
#define PIXEL_COUNT 1
#define PIXEL_TYPE WS2812B // Only WS2812 is supported...
                           // color order is wrong for our neopixels.

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// Prototypes for local build, ok to leave in for Build IDE
void rainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);

// setup() runs once, when the device is first turned on
void setup() {
  pinMode(A5,OUTPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  delay(1000);
  Log.info("Sending Hello World!");
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  const int myBright = 100;

  digitalWrite(A5,HIGH);
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();   // Send the updated pixel colors to the hardware.
  delay(400);
  strip.setPixelColor(0, strip.Color(myBright, 0, 0));
  strip.show();   // Send the updated pixel colors to the hardware.
  digitalWrite(A5,LOW);
  delay(400);
  strip.setPixelColor(0, strip.Color(0, myBright, 0));
  strip.show();   // Send the updated pixel colors to the hardware.
  digitalWrite(A5,HIGH);
  delay(400);
  strip.setPixelColor(0, strip.Color(0, 0, myBright));
  strip.show();   // Send the updated pixel colors to the hardware.
  digitalWrite(A5,LOW);
  delay(400);

  // Pink Baggy Result: RGB request outputs GRB color order
  // Pololu Item #2536 Result: RGB request outputs GRB color order
  // ClearPlastic Bag from EE1301 Kit: RGB request outputs GRB color order
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}