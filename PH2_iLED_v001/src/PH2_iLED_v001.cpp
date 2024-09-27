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
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// These lines of code should appear AFTER the #include statements, and before
// the setup() function.
// IMPORTANT: Set pixel COUNT, PIN and TYPE
int PIXEL_COUNT = 3;
#define PIXEL_PIN SPI // Only use SPI=MO=S0 or SPI1=D2 on Photon 2
                      // NOTE: On the Photon 2, this must be a compiler constant!
int PIXEL_TYPE = WS2812;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
  strip.begin();
}

void loop() {
    int PixelColorCyan = strip.Color( 255,   0, 255);
    int PixelColorRed  = strip.Color(   0,  80,   0);
    int PixelColorGold = strip.Color(  50,  60,   5);

    //Set first pixel to cyan
    strip.setPixelColor(0, PixelColorCyan);
    //set second pixel to red
    strip.setPixelColor(1, PixelColorRed);
    //set third pixel to Gopher Gold!
    strip.setPixelColor(2, PixelColorGold);
    strip.show();
    delay(1000);  //wait 1sec

    //flip the red and gold
    strip.setPixelColor(0, PixelColorCyan);
    strip.setPixelColor(1, PixelColorGold);
    strip.setPixelColor(2, PixelColorRed);
    strip.show();
    delay(1000);  //wait 1sec
}
