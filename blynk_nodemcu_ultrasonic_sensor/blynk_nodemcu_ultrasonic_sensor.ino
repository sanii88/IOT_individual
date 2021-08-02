/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  Output any data on LCD widget!

  App project setup:
    LCD widget, switch to ADVANCED mode, select pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define TRIGGERPIN D1
#define ECHOPIN    D2
#define buzzer D6
#define ledpin D7



// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "1yhi3za3TACsT08fE6VM1dGAzWfsSC8v";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iPhone";
char pass[] = "password";

WidgetLCD lcd(V1);

void setup()
{
  
  Serial.begin(9600);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledpin, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
  
  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Distance in cm"); 
}

void loop()
{
  lcd.clear();
  lcd.print(0, 0, "Distance in cm");
  
  long duration, distance, safetyDistance;
  
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERPIN, LOW);
  
  duration = pulseIn(ECHOPIN, HIGH);
  
  distance = duration*0.034/2;

   safetyDistance = distance;
  if (safetyDistance <= 15){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledpin, HIGH);
 }
  else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledpin, LOW);
 }


  Serial.print(distance);
  Serial.println("Cm");
  lcd.print(7, 1, distance);
  Blynk.run();

  delay(1000);

}
