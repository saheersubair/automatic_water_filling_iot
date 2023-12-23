/*
 * this program is under editing for push notification
 */
// Fill-in information from your Blynk Template here
#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPL686qJHKjb"
#define BLYNK_TEMPLATE_NAME "IOT Project"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define USE_NODE_MCU_BOARD

#include "BlynkEdgent.h"

#define echoPin D5
#define trigPin D6

#define SOUND_VELOCITY 0.034

long duration;
float distance; 
long max_depth, current_depth, rec_max_height, rec_max_depth, max_water;
long height, current_water, rec_min_height, rec_min_depth, min_water, area;

BLYNK_WRITE(V0)
{
  if(param.asInt()==1){
    digitalWrite(4, HIGH);
    Serial.println("Relay ON");
  }
  else{
    digitalWrite(4, LOW);
    Serial.println("Relay OFF");
  }
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
}


void water_level(float distance)
{
  area = 69.97;
  height = 22.17;

  max_depth = 5;
  rec_max_height = (height - max_depth);

  if(distance > (max_depth + 3)){
    current_depth = distance;
    current_water = ((height - current_depth)*area)-59;
    Serial.print("Water Level: ");
    Serial.println(current_water);
    Blynk.virtualWrite(V3, current_water);
    delay(500);
  }
  else{
    Serial.print("Water Level: ");
    Serial.println(1000);
    Blynk.virtualWrite(V3, 1000);
    delay(500);
  }
}


void ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance
    distance = duration * SOUND_VELOCITY/2;
    
    Serial.print("Distance: ");
    Serial.println(distance);
    Blynk.virtualWrite(V2, distance);
    delay(500);
}

void setup()
{
  Serial.begin(9600);
  pinMode(34, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(4, OUTPUT);
  
  BlynkEdgent.begin();
  delay(2000); 
}

void loop() 
{
  BlynkEdgent.run();
  ultrasonic();
  water_level(distance);
}
