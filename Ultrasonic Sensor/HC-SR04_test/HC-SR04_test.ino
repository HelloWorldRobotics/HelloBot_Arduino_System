/*
  HC-SR04 NewPing Iteration Demonstration
  HC-SR04-NewPing-Iteration.ino
  Demonstrates using Iteration function of NewPing Library for HC-SR04 Ultrasonic Range Finder
  Displays results on Serial Monitor

  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// This uses Serial Monitor to display Range Finder distance readings

// Include NewPing Library
#include "NewPing.h"

// Hook up HC-SR04 with Trig to Arduino Pin 10, Echo to Arduino pin 13
// Maximum Distance is 400 cm

#define TRIGGER_PIN     2
#define ECHO_PIN        3
#define TRIGGER_PIN_02  4
#define ECHO_PIN_02     5
#define MAX_DISTANCE    400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar02(TRIGGER_PIN_02, ECHO_PIN_02, MAX_DISTANCE);

float duration, distance;
float duration02, distance02;

int iterations = 5;

void setup() {
  Serial.begin (9600);
}

void loop() {
   
  duration   = sonar.ping_median(iterations);
  duration02 = sonar02.ping_median(iterations);
  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  
  distance = (duration / 2) * 0.0343;
  distance02 = (duration02 / 2) * 0.0343;
  
  // Send results to Serial Monitor
  Serial.print("Distance = ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("Sonar01 Out of range");
  }
  else if (distance02 >= 400 || distance02 <= 2) {
    Serial.println("Sonar02 Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print(distance02);
    Serial.println(" cm");
    //delay(500);
  }
  //delay(500);
}
