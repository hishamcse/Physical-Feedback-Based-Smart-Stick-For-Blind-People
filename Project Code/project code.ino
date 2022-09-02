#include <NewPing.h>
#include <Servo.h>

Servo servo1,servo2,servo3;

#define trigPin1  2
#define echoPin1  2
#define trigPin2  3
#define echoPin2  3
#define trigPin3  4
#define echoPin3  4

#define MAX_DISTANCE 30

NewPing sonar1(trigPin1, echoPin1, MAX_DISTANCE);

NewPing sonar2(trigPin2, echoPin2, MAX_DISTANCE);

NewPing sonar3(trigPin3, echoPin3, MAX_DISTANCE);
float duration, distance1, distance2, distance3;

void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(7);
}

void loop() {
  delay(500); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
//  duration = sonar.ping();
//  distance = (duration / 2) * 0.0343;
  distance1 = sonar1.ping_cm();
  distance2 = sonar2.ping_cm();
  distance3 = sonar3.ping_cm();
  
  Serial.print("Distance1 = ");
  Serial.print(distance1); // Distance will be 0 when out of set max range.
  Serial.println(" cm");

  if(distance1 != 0) {
    servo1.write(90);
  } else {
    servo1.write(0);
  }

  
  Serial.print("Distance2 = ");
  Serial.print(distance2); // Distance will be 0 when out of set max range.
  Serial.println(" cm");

  if(distance2 != 0) {
    servo2.write(90);
  } else {
    servo2.write(0);
  }


  Serial.print("Distance3 = ");
  Serial.print(distance3); // Distance will be 0 when out of set max range.
  Serial.println(" cm");

  if(distance3 != 0) {
    servo3.write(90);
  } else {
    servo3.write(0);
  }
}
