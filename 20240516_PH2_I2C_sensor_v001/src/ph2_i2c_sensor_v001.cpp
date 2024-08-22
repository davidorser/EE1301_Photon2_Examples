// Include Particle Device OS APIs
#include "Particle.h"
#include "Adafruit_VEML7700.h"
#include "Adafruit_LTR329_LTR303.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

Adafruit_VEML7700 veml;
Adafruit_LTR303 ltr = Adafruit_LTR303();

void setup()
{
  Serial.begin(115200);
  delay(5000);

  Serial.println("Adafruit VEML7700 Test");

  if (!veml.begin())
  {
    Serial.println("VEML Sensor not found");
    while (1)
      ;
  }
  Serial.println("VEML Sensor found");
  
  veml.setGain(VEML7700_GAIN_1);
  veml.setIntegrationTime(VEML7700_IT_800MS);

  Serial.print(F("Gain: "));
  switch (veml.getGain())
  {
  case VEML7700_GAIN_1:
    Serial.println("1");
    break;
  case VEML7700_GAIN_2:
    Serial.println("2");
    break;
  case VEML7700_GAIN_1_4:
    Serial.println("1/4");
    break;
  case VEML7700_GAIN_1_8:
    Serial.println("1/8");
    break;
  }

  Serial.print(F("Integration Time (ms): "));
  switch (veml.getIntegrationTime())
  {
  case VEML7700_IT_25MS:
    Serial.println("25");
    break;
  case VEML7700_IT_50MS:
    Serial.println("50");
    break;
  case VEML7700_IT_100MS:
    Serial.println("100");
    break;
  case VEML7700_IT_200MS:
    Serial.println("200");
    break;
  case VEML7700_IT_400MS:
    Serial.println("400");
    break;
  case VEML7700_IT_800MS:
    Serial.println("800");
    break;
  }

  //veml.powerSaveEnable(true);
  //veml.setPowerSaveMode(VEML7700_POWERSAVE_MODE4);

  veml.setLowThreshold(10000);
  veml.setHighThreshold(20000);
  veml.interruptEnable(true);

  if ( ! ltr.begin() ) {
    Serial.println("Couldn't find LTR sensor!");
    while (1) delay(10);
  }
  Serial.println("Found LTR sensor!");
  // Set gain of 1 (see advanced demo for all options!
  ltr.setGain(LTR3XX_GAIN_1);
  // Set integration time of 50ms (see advanced demo for all options!
  ltr.setIntegrationTime(LTR3XX_INTEGTIME_50);
  // Set measurement rate of 50ms (see advanced demo for all options!
  ltr.setMeasurementRate(LTR3XX_MEASRATE_50);
}

void loop()
{
  Serial.print("Lux: ");
  Serial.println(veml.readLux());
  Serial.print("White: ");
  Serial.println(veml.readWhite());
  Serial.print("Raw ALS: ");
  Serial.println(veml.readALS());

  uint16_t irq = veml.interruptStatus();
  if (irq & VEML7700_INTERRUPT_LOW)
  {
    Serial.println("** Low threshold");
  }
  if (irq & VEML7700_INTERRUPT_HIGH)
  {
    Serial.println("** High threshold");
  }

  bool valid;
  uint16_t visible_plus_ir, infrared;

  if (ltr.newDataAvailable()) {
    valid = ltr.readBothChannels(visible_plus_ir, infrared);
    if (valid) {
      Serial.print("CH0 Visible + IR: ");
      Serial.print(visible_plus_ir);
      Serial.print("\t\tCH1 Infrared: ");
      Serial.println(infrared);
    }
  }  

  delay(500);
}