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
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

void setup() {
  //pinMode(A2,OUTPUT);
  //pinMode(S3,OUTPUT);
  myServo.attach(A5);
  delay(2000);
  Log.info("Setup Complete!");
}

void loop() {
  // tone(A5,1000,500);
  myServo.write(10);
  Log.info("Move Servo to 10 degrees");
  delay(2000);

  // noTone(A5);
  // analogWrite(A2,3071); // 75% of 4096
  digitalWrite(S3,LOW);
  myServo.write(170);
  Log.info("Move Servo to 170 degrees");
  delay(2000);
}
