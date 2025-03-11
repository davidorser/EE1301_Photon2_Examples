/*
 * Project myProject
 * Author: Your Name
 * Date:
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

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

// #include <DHT20.h>
#include "../lib/DHT20_I2C_Particle/src/DHT20.h"

DHT20 DHT;

double humidity = 0.0;
double temperature = 0.0;

bool heaterOn = false;
int heaterPin = D19;

void timer_print_temp();

Timer timer(1000 * 60 * 60, timer_print_temp); // Setup timer for 1 hour : Production Timer
// Timer timer(1000 * 15, timer_print_temp); // Setup timer for 15 seconds : Testing Timer

void timer_print_temp()
{
  char buf[100]; // Buffer of 'size' bytes on the stack
  JSONBufferWriter writer(buf, sizeof(buf));
  writer.beginObject();
  writer.name("Temp").value(temperature);
  writer.name("Hum").value(humidity);
  writer.endObject();

  Particle.publish(
      "TempHum",
      buf);
}

void setup()
{
  DHT.begin();
  Serial.begin(9600);
  delay(1000);
  Particle.variable("temp", temperature);
  Particle.variable("humidity", humidity);
  timer.start();
  pinMode(heaterPin, OUTPUT);
}

void loop()
{
  int status = DHT.read();

  if (status == DHT20_OK)
  { // valid read
    humidity = DHT.getHumidity();
    temperature = DHT.getTemperature();
    Serial.print("DHT20 \t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\t\t");
  }
  else
  {
    Serial.println("Invalid read");
  }

  heaterOn = (temperature < 7.2); // 45.0F
  digitalWrite(heaterPin, heaterOn);
  Serial.print("Heater:");
  Serial.print(heaterOn);
  Serial.print("\n");

  delay(2000);
}
