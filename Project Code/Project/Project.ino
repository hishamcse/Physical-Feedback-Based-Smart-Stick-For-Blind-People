#include <NewPing.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <string.h>

Servo servoFront,servoLeft,servoRight;

#define trigPinFront  2
#define echoPinFront  8
#define trigPinLeft  3
#define echoPinLeft  9
#define trigPinRight  4
#define echoPinRight  10

#define MAX_DISTANCE 30

NewPing sonarFront(trigPinFront, echoPinFront, MAX_DISTANCE);
NewPing sonarLeft(trigPinLeft, echoPinLeft, MAX_DISTANCE);
NewPing sonarRight(trigPinRight, echoPinRight, MAX_DISTANCE);

float duration, distanceFront, distanceLeft, distanceRight;

const int RXgsm = A0, TXgsm = A1;
const int RXgps = A2, TXgps = A3;

const uint32_t GSMBaud = 115200; 
const uint32_t GPSBaud = 9600; //Default baud of NEO-6M is 9600

TinyGPSPlus gps; // the TinyGPS++ object
SoftwareSerial gpsSerial(RXgps, TXgps); // the serial interface to the GPS device
SoftwareSerial gsmSerial(RXgsm, TXgsm);

const int buttonPin = 0;
const int gpsLED = 1;

double gpslat;
double gpslong;
char charLat[10];
char charLng[10];
char message[100];
int val = 1;
int gps_available = 0;

void setup() {
  servoFront.attach(5);
  servoLeft.attach(6);
  servoRight.attach(7);
  
  gsmSerial.begin(GSMBaud);
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
  pinMode(buttonPin, INPUT);
  pinMode(gpsLED, OUTPUT);
 
  delay(100);
}

void loop() 
{
  delay(500); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  distanceFront = sonarFront.ping_cm();
  distanceLeft = sonarLeft.ping_cm();
  distanceRight = sonarRight.ping_cm();
  
//  Serial.print("DistanceFront = ");
//  Serial.print(distanceFront); // Distance will be 0 when out of set max range.
//  Serial.println(" cm");

  if(distanceFront != 0) {
    servoFront.write(75);
  } else {
    servoFront.write(0);
  }

//  
//  Serial.print("DistanceLeft = ");
//  Serial.print(distanceLeft); // Distance will be 0 when out of set max range.
//  Serial.println(" cm");

  if(distanceLeft != 0) {
    servoLeft.write(60);
  } else {
    servoLeft.write(0);
  }

//
//  Serial.print("DistanceRight = ");
//  Serial.print(distanceRight); // Distance will be 0 when out of set max range.
//  Serial.println(" cm");

  if(distanceRight != 0) {
    servoRight.write(0);
  } else {
    servoRight.write(60);
  }
  
//  val = digitalRead(0);
//  if(!val && gps_available) {
//    SendMessage();
////    delay(100);
//  }
//
//  if (gpsSerial.available() > 0) {
//    if (gps.encode(gpsSerial.read())) {
//      if (gps.location.isValid()) {
//        Serial.print(F("- latitude: "));
//        Serial.println(gps.location.lat(), 6);
//        gpslat = gps.location.lat();
//        Serial.print(F("- longitude: "));
//        gpslong = gps.location.lng();
//        Serial.println(gps.location.lng(), 6);
//
//        gps_available = 1;
//        digitalWrite(gpsLED, HIGH);
//      } else {
//        Serial.println(F("- location: INVALID"));
//      }
//
//      Serial.println();
//    }
//  }
}

void SendMessage()
{
  gsmSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsmSerial.println("AT+CMGS=\"+8801732005497\"\r"); // Replace x with mobile number
  delay(1000);

  dtostrf(gpslat, 4, 3, charLat);
  dtostrf(gpslong, 4, 3, charLng);

  strcpy(message, "Please help!!\n");
  strcat(message, "Location data:\n");
  strcat(message, "Latitude: ");
  strcat(message,charLat);
  strcat(message, ",");
  strcat(message, "Longitude: ");
  strcat(message,charLng);
  strcat(message, "\nMap Location:\n");
  strcat(message, "https://www.google.com.ph/maps/place/");
  strcat(message, charLat);
  strcat(message, ",");
  strcat(message, charLng);
  
  gsmSerial.println(message);// The SMS text you want to send
  delay(100);
  gsmSerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
