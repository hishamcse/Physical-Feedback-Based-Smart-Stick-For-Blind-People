
<p align="center">
 <img width="300px" 
      style="border-radius:50%" src="https://github.com/hishamcse/Physical-Feedback-Based-Smart-Stick-For-Blind-People/blob/master/Final%20Videos/algorithm_1.jpg"  alt="Smart Stick"/>
</p>

<h1 align="center"> Physical Feedback Based Smart Stick For Blind People</h1><br />

### table of contents
   * [Overview](#overview)
   * [Circuit](#configuring-frontend)
   * [Instruments, Modules and Sensors](#tools)
   * [Features](#features)
   * [Video Demonstration](#video-demonstration)
   * [Problems & Solution](#api-reference)
      * [Power Issue](#power)
      * [Working GPS](#gps)
      * [GPS and SONAR in same Arduino](#gps-sonar)
      * [SONAR Trig and Echo on Same Pin](#sonar-trig)
   * [Contributors](#contribute)

## Overview<a name="overview"></a>
   This smart stick project was made for CSE 316 Microcontroller Project having two features. One, physical Feedback based on obstacle detection around blind person. Second, an emergency alert system if the blind person needs any immediate help

## Circuit<a name="configuring-frontend"></a>
   <p align="center">
 <img width="800px" 
      style="border-radius:50%" src="https://github.com/hishamcse/Physical-Feedback-Based-Smart-Stick-For-Blind-People/blob/master/Diagram%20%26%20CKT/Final%20CKT.bmp"       alt="Smart Stick"/>
</p>

## Instruments, Modules and Sensors:<a name="tools"></a>
* Arduino Uno - 2
* HC-SR04 Ultrasonic sensor - 3
* SG90 Micro Servo Motor - 3
* NEO-6M GPS - 1
* GSM SIM 900A - 1
* LED - 2
* Buzzer - 1
* Breadboard - 4

## Features:<a name="features"></a>
* This will notify a blind person about the obstacles around him (e.g: Front, Left and Right). So, he can move accordingly.
* If blind person needs any immediate help, he can press a button and make an emergency alert/message to the server which will contain detailed information about the     location(e.g: latitude and longitude) and also the link of the location at google map
   
## Video Demonstration:<a name="video-demonstration"></a>
   * [Demo (Youtube)](https://youtu.be/FH343aWnILk)

## Problems & Solution:<a name="api-reference"></a>
### Power issue<a name="power"></a>
  #### Problem
  We first naively tried to power up all our components using Arduino’s VCC and GND pin. This obviously
did not work since the VCC pin of Arduino may supply around .4A when powered up using USB. We did
not face any issues with this approach at first. The servo motors, sonar sensors, GPS sensors all seem to
work fine. However, the GSM module did not work reliably. It did power up, but most of the time it could
not connect to the network. Or even if connected to the network, the network dropped immediately we tried
to make a call or send an SMS.
  #### Solution
  We cut a USB charging cable, plugged it into a 10W power bank, and used it to power up all the components
including the Arduino (Using Vin and GND pins). We found that the modules and sensors may not work
correctly if Arduino is powered from different sources if they do not share a common ground.

### Working GPS<a name="gps"></a>
   #### Problem
   The GPS module was not getting any signal.
   #### Solution
   The GPS module did not work indoors. We had to go to an open space and waited around 5 to 10 minutes
for it to get the proper signal and provide the location.

### GPS and SONAR in same Arduino<a name="gps-sonar"></a>
   #### Problem
   We needed to continuously read both the SONAR sensor and GPS sensor. But it seems like that is not
possible. [This](https://stackoverflow.com/questions/49782864/using-ultrasonic-sensor-hc-sr04-and-gps-neogps-6m-together-on-arduino-uno) question’s answer dives deeper on this issue.
   #### Solution
   We ended up using 2 Arduino. Useful Link regarding this issue: [GPS & Sonar together at UNO](https://stackoverflow.com/questions/49782864/using-ultrasonic-sensor-hc-sr04-and-gps-neogps-6m-together-on-arduino-uno)

### SONAR Trig and Echo on Same Pin<a name="sonar-trig"></a>
   #### Problem
   We found in an article that SONAR can work even if the Trig and Echo pin is connected to the same pin of
Arduino. We found it to be true while powering up the SONARS from Arduino. However, when we powered
up the sensors and Arduino from an external source, the SONARs stopped working properly
   #### Solution
   Used 2 different pins for Echo and Trig.
   

## Contributors:<a name="contribute"></a>
   * [Syed Jarullah Hisham (1805004)](https://hishamcse.github.io/)
   * [Abdur Rafi (1805008)](https://github.com/abdur-rafi)
   * Md. Zarzees Uddin Shah Chowdhury (1805009)
     

 
