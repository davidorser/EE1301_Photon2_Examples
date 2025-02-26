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

#define COOL 0
#define OFF 1
#define HEAT 2
int mode = OFF;
int setModeFromString(String inputString);

int led2 = D7; // Instead of writing D7 over and over again, we'll write led2
int myCvar_tobeShared = 0;

// setup() runs once, when the device is first turned on
void setup()
{
  pinMode(led2, OUTPUT);
  Particle.variable("myCloudVarName", myCvar_tobeShared);
  Particle.variable("myMode", mode);
  Particle.function("cF_setMode", setModeFromString);

  // Put initialization like pinMode and begin functions here
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{

  if (mode == COOL)
  {
    digitalWrite(led2, HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
    delay(500);
  }

  myCvar_tobeShared = myCvar_tobeShared + 1;
  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}

int setModeFromString(String inputString)
{
  if (inputString == "Cool")
  {
    mode = COOL;
    return 0;
  }
  else if (inputString == "Off")
  {
    mode = OFF;
    return 1;
  }
  else if (inputString == "Heat")
  {
    mode = HEAT;
    return 2;
  }
  else
  {
    return -1; // If we get here return a Sentinel Value. -1 is common for errors.
  }
}
