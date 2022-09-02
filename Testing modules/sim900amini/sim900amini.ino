
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9);
char msg;
double gpslat;
double gpslong;
char charLat[10];
char charLng[10];
char message[100];
int val = 0;

void setup()
{
  mySerial.begin(115200);
  Serial.begin(9600);
  delay(100);
}

int sent = false;

void loop()
{  
  if(!val){
          SendMessage();
          val = 1;
        }
}
void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+8801732005497\"\r"); // Replace x with mobile number
  delay(1000);
  
  mySerial.println("sms");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
