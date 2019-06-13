#include "NewPing.h"

#define SR_TRIGGER_PIN       2
#define SR_ECHO_PIN          3
#define AJ_TRIG_PIN          4
#define AJ_ECHO_PIN          5
#define SR_MAX_DISTANCE    400
#define SR_MIN_DISTANCE     10
#define AJ_MAX_DISTANCE    800
#define AJ_MIN_DISTANCE     20

float duration, SR_distance;
int iterations = 5;

NewPing sonar(SR_TRIGGER_PIN, SR_ECHO_PIN, SR_MAX_DISTANCE);

void setup(){
  Serial.begin(115200);
  pinMode(AJ_ECHO_PIN, INPUT);
  pinMode(AJ_TRIG_PIN, OUTPUT);
  digitalWrite(AJ_ECHO_PIN, HIGH);
}
void loop(){
  duration   = sonar.ping_median(iterations);
  digitalWrite(AJ_TRIG_PIN, LOW); // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(AJ_TRIG_PIN, HIGH); // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(AJ_TRIG_PIN, LOW); // Send pin low again
  float AJ_distance = pulseIn(AJ_ECHO_PIN, HIGH,26000); // Read in times pulse
  SR_distance = (duration / 2) * 0.0343;
  AJ_distance = AJ_distance/58;
  
  if(SR_distance >= SR_MAX_DISTANCE || SR_distance <= SR_MIN_DISTANCE){
  Serial.println("Sonar01 Out of range");
  }
  else {
  Serial.print("SR_distance");
  Serial.print(SR_distance);
  Serial.println(" cm");
  }
  
  if(AJ_distance<AJ_MIN_DISTANCE || AJ_distance>AJ_MAX_DISTANCE)
  Serial.println("Blindspot!");
  else{
  Serial.print("AJ_distance");
  Serial.print(AJ_distance);
  Serial.println(" cm");
  }              
  delay(80);//cycle period should be no less than 50ms
}
