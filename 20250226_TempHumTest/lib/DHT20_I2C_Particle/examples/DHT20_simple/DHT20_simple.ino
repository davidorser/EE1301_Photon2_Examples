//
//    FILE: DHT20_simple.ino
//  AUTHOR: Rob Parke
// PURPOSE: Demo for DHT20 I2C humidity & temperature sensor
//

//  Always check datasheet - front view
//
//          +--------------+
//  VDD ----| 1            |
//  SDA ----| 2    DHT20   |
//  GND ----| 3            |
//  SCL ----| 4            |
//          +--------------+

#include "DHT20.h"

DHT20 DHT;

void setup() {
    DHT.begin();
    Serial.begin(9600);
    delay(1000);
}

void loop() {
    int status = DHT.read();

    if (status == DHT20_OK) {  // valid read
        Serial.print("DHT20 \t");
        Serial.print(DHT.getHumidity(), 1);
        Serial.print("\t\t");
        Serial.print(DHT.getTemperature(), 1);
        Serial.print("\t\t");
        Serial.print("\t\t");
    } else {
        Serial.println("Invalid read");
    }

    delay(1000);
}
