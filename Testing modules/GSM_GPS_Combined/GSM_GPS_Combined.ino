
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <string.h>

const int RXgps = 3, TXgps = 4;
const int RXgsm = 7, TXgsm = 8;
const uint32_t GPSBaud = 9600; 
const uint32_t GSMBaud = 115200;

TinyGPSPlus gps; // the TinyGPS++ object
SoftwareSerial gpsSerial(RXgps, TXgps); // the serial interface to the GPS device
SoftwareSerial gsmSerial(RXgsm, TXgsm);

double gpslat;
double gpslong;
char charLat[10];
char charLng[10];
char message[200];
int val = 1;
int gps_available = 0;

const int gsmLED = 11;
const int buttonPin = 12;
const int gpsLED = 13;

void setup()
{
  gsmSerial.begin(GSMBaud);
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
  pinMode(buttonPin, INPUT);
  pinMode(gpsLED, OUTPUT);
  pinMode(gsmLED, OUTPUT);
  digitalWrite(gpsLED, LOW);
  delay(100);
}

void loop()
{  
  val = digitalRead(buttonPin);
  if(!val) {
    SendMessage();
    delay(100);
  }
  
  if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print(F("- latitude: "));
        Serial.println(gps.location.lat(), 6);
        gpslat = gps.location.lat();
        Serial.print(F("- longitude: "));
        gpslong = gps.location.lng();
        Serial.println(gps.location.lng(), 6);

        digitalWrite(gpsLED, HIGH);
      } else {
        Serial.println(F("- location: INVALID"));
        digitalWrite(gpsLED, LOW);
      }

      Serial.println();
    }
  }
}

void SendMessage()
{
  digitalWrite(gsmLED, HIGH);
  gsmSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsmSerial.println("AT+CMGS=\"+8801533157211\"\r"); // Replace x with mobile number
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
  digitalWrite(gsmLED, LOW);
}
