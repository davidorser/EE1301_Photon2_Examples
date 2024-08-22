/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

Servo myServo;

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  pinMode(A2,OUTPUT);
  //myServo.attach(A2);
  pinMode(S3,OUTPUT);
  Log.info("Sending Hello World!");
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  digitalWrite(S3,HIGH);
  //tone(A5,1000,500);
  analogWrite(A2,1023); // 25% of 4096
  //myServo.write(10);
  delay(2000);

  digitalWrite(S3,LOW);
  //noTone(A5);
  analogWrite(A2,3079); // 75% of 4096
  //myServo.write(170);
  delay(2000);


  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}
