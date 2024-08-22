//
//    FILE: DHT20_simple.ino
//  AUTHOR: Rob Parke based on work by Rob Tillaart
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

DHT20 dht;

void setup() {
    dht.begin();
    Serial.begin(9600);
    delay(1000);
}

void loop() {
    int status = dht.read();

    if (status == DHT20_OK) {  // valid read
        Serial.print("DHT20 \t");
        Serial.print("% Humidity: " + String(dht.getHumidity()));
        Serial.print("\t");
        Serial.print(String(dht.getTemperature()) + " C");
        Serial.print("\t");
        Serial.println(String(dht.getTemperatureF()) + " F");
    } else {
        Serial.println("Invalid read");
    }

    delay(1000);
}
