#include <NewPing.h>
#include <Servo.h>

Servo servoFront,servoLeft,servoRight;

#define trigPinFront  2
#define echoPinFront  8
#define FrontAttach  5
#define trigPinLeft  3
#define echoPinLeft  9
#define LeftAttach  6
#define trigPinRight  4
#define echoPinRight  10
#define RightAttach  7

#define MAX_DISTANCE_FRONT 75
#define MAX_DISTANCE_LEFT 50
#define MAX_DISTANCE_RIGHT 50

NewPing sonarFront(trigPinFront, echoPinFront, MAX_DISTANCE_FRONT);
NewPing sonarLeft(trigPinLeft, echoPinLeft, MAX_DISTANCE_LEFT);
NewPing sonarRight(trigPinRight, echoPinRight, MAX_DISTANCE_RIGHT);

float duration, distanceFront, distanceLeft, distanceRight;
const int buzzer = 12;

void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
  servoFront.attach(FrontAttach);
  servoLeft.attach(LeftAttach);
  servoRight.attach(RightAttach);
  
  pinMode(buzzer, OUTPUT);
}

void loop() {
  delay(500);
  
  distanceFront = sonarFront.ping_cm();
  distanceLeft = sonarLeft.ping_cm();
  distanceRight = sonarRight.ping_cm();
  
  Serial.print("DistanceFront = ");
  Serial.print(distanceFront); // Distance will be 0 when out of set max range.
  Serial.println(" cm");

  if(distanceFront != 0) {
    servoFront.write(90);
    digitalWrite(buzzer, HIGH);
  } else {
    servoFront.write(0);
    digitalWrite(buzzer, LOW);
  }

  
  Serial.print("DistanceLeft = ");
  Serial.print(distanceLeft); // Distance will be 0 when out of set max range.
  Serial.println(" cm");

  if(distanceLeft != 0) {
    servoLeft.write(75);
  } else {
    servoLeft.write(0);
  }


  Serial.print("DistanceRight = ");
  Serial.print(distanceRight); // Distance will be 0 when out of set max range.
  Serial.println(" cm");

  if(distanceRight != 0) {
    servoRight.write(0);
  } else {
    servoRight.write(60);
  }
}
