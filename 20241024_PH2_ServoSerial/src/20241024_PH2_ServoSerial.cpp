/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
int myDelay=500;
String storedString = "";
String inString = "";
Servo myServo; // create a servo

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  myServo.attach(A5);
  pinMode(D7,OUTPUT);
  Serial.begin(9600);
  delay(5000);
  Serial.println("hello world");
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  inString = "";
  Serial.println("start of loop");
  while (Serial.available() > 0) {
    Serial.println("Serial Read Triggered");
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }

    Serial.print("I received: ");
    Serial.println(inChar);
    Serial.print("I assembled: ");
    Serial.println(inString);
    Serial.print("I interpretted it to be:");
    Serial.println(inString.toInt());

    storedString = inString;
  }

  myServo.write(storedString.toInt());

// Include a heart beat so we can see program loaded correctly
  digitalWrite(D7, HIGH);
  delay(myDelay/2);
  digitalWrite(D7, LOW);
  delay(myDelay/2);
}
