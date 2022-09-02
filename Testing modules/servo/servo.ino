#include <Servo.h>

Servo servo1;

void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
  servo1.attach(5);
}

void loop() {
  servo1.write(60);
  delay(500); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  servo1.write(0);
  delay(500); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
}
