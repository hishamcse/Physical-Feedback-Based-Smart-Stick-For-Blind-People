#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// https://www.google.com.ph/maps/place/23.71993,90.3899678

const int RXPin = 3, TXPin = 4;
const uint32_t GPSBaud = 9600; //Default baud of NEO-6M is 9600

TinyGPSPlus gps; // the TinyGPS++ object
SoftwareSerial gpsSerial(RXPin, TXPin); // the serial interface to the GPS device

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);

  Serial.println(F("Arduino - GPS module"));
}

void loop() {
  if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print(F("- latitude: "));
        Serial.println(gps.location.lat(), 6);

        Serial.print(F("- longitude: "));
        Serial.println(gps.location.lng(), 6);

        Serial.print(F("- altitude: "));
        if (gps.altitude.isValid())
          Serial.println(gps.altitude.meters());
        else
          Serial.println(F("INVALID"));
      } else {
        Serial.println(F("- location: INVALID"));
      }

      Serial.print(F("- speed: "));
      if (gps.speed.isValid()) {
        Serial.print(gps.speed.kmph());
        Serial.println(F(" km/h"));
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.print(F("- GPS date&time: "));
      if (gps.date.isValid() && gps.time.isValid()) {
        Serial.print(gps.date.year());
        Serial.print(F("-"));
        Serial.print(gps.date.month());
        Serial.print(F("-"));
        Serial.print(gps.date.day());
        Serial.print(F(" "));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        Serial.println(gps.time.second());
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.println();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}
