/*
 * Project Temperature and Humidity Sensor with Heater Toggle
 * Author: David Orser
 * Date: 3/11/2025
 */

#include "Particle.h"
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// Parts borrowed from Rob Parke
// Demo for DHT20 I2C humidity & temperature sensor
// Front view
//          +--------------+
//  VDD ----| 1            |
//  SDA ----| 2    DHT20   |
//  GND ----| 3            |
//  SCL ----| 4            |
//          +--------------+

#include "../lib/DHT20_I2C_Particle/src/DHT20.h"

DHT20 DHT;
double humidity = 0.0;
double temperature = 0.0;

bool heaterOn = false;
int heaterPin = D19;
double tempSetPoint = 7.2; // 7.2C = 45.0F, 15.6C = 60.0F

void timer_print_temp();
int setTempTarget(String inputString);

// Timer timer(1000 * 60 * 60, timer_print_temp); // Setup timer for 1 hour : Production Timer
Timer timer(1000 * 60, timer_print_temp); // Setup timer for 60 seconds : Testing Timer

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
  delay(20000);
  Particle.variable("temp", temperature);
  Particle.variable("humidity", humidity);
  Particle.variable("HeatState", heaterOn);
  Particle.variable("tempSetPoint", tempSetPoint);
  Particle.function("setTempTarget", setTempTarget);
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

  if (heaterOn == true && (temperature > (tempSetPoint + 0.5)))
  {
    heaterOn = false;
  }
  else if (heaterOn == false && (temperature < (tempSetPoint - 0.5)))
  {
    heaterOn = true;
  }

  digitalWrite(heaterPin, heaterOn);
  Serial.print("Heater:");
  Serial.print(heaterOn);
  Serial.print("\n");

  delay(2000);
}

int setTempTarget(String inputString)
{
  tempSetPoint = inputString.toFloat();
  if (tempSetPoint == 0)
  {
    tempSetPoint = 7.2;
  }
  return tempSetPoint;
}
