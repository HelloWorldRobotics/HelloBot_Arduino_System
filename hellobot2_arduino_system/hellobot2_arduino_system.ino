/**
The stepper motor rotates 6400 steps (a cycle), and reverses 6400 steps (a cycle).
步距角为1.8度的步进电机（小电机），转一圈所用的脉冲数为 n=360/1.8=200个脉冲。
Setup:
we'll use a bipolar stepper motor, 1.8 step angle, 1.7A
-Set current: 1.7A
-Set Micro Step: 32
-Connect a 9-42V DC power supply
Tips:
-When “EN” is Low, the motor is in a free states (Off-line mode). In this mode, you can adjust the motor shaft position manually; when “EN” is High (Vacant), the motor will be in an automatic control mode.
-"Direction" is the motor direction signal pin,
-"PULSE" is the motor pulse signal pin. Once the driver get a pulse, the motor move a step.
**/
#include "FastLED.h"
#include <Servo.h>

//Unloading Part Stepper Motor 01
#define PUL_01 28
#define DIR_01 26
#define ENA_01 24
#define LIMIT_SWITCH_01 53  //front limit switch
#define LIMIT_SWITCH_02 45  //back limit switch

//Sliding Part Stepper Motor 02(left)+03(right)
#define PUL_02 52
#define DIR_02 50
#define ENA_02 48
#define PUL_03 46
#define DIR_03 44
#define ENA_03 42
#define LIMIT_SWITCH_03 43  //bottom limit switch
#define LIMIT_SWITCH_04 41  //top limit switch

//Lid Opening Part Servo Motors 01+02 & Stepper Motor 04
//Servo Motors
#define double_head_servo 9

//LED Strip
#define NUM_LEDS 10
#define LED_STRIP_PIN 40
//Stepper Motor 02
/*
const int ENA_02=5; //define Enable Pin
const int DIR_02=6; //define Direction pin
const int PUL_02=7; //define Pulse pin
*/
//Stop Buttons
//const int BUTTON_01=8; //define Button pin
//const int BUTTON_02=9; //define Button pin
const int rev   = 5;     //revolutions of stepper motor
int step_counts = 0;    
int microstep   = 6400;
int stop_flag   = 0;
int steps       = 0;    //home position of stepper motors
long previousMillis = 0;//will store last time LED was updated
long interval = 1000;   //interval at which to blink (milliseconds)
int ledState = LOW;     //ledState used to set the LED

CRGB leds[NUM_LEDS];

//class LED_Flashing:
//To Be Continued...

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  //Unloading Part
  pinMode(LIMIT_SWITCH_01, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH_02, INPUT_PULLUP);
  pinMode(PUL_01, OUTPUT);
  pinMode(DIR_01, OUTPUT);
  pinMode(ENA_01, OUTPUT);
  
  //Sliding Part
  pinMode(LIMIT_SWITCH_03, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH_04, INPUT_PULLUP);
  pinMode(PUL_02, OUTPUT);//left 
  pinMode(DIR_02, OUTPUT);
  pinMode(ENA_02, OUTPUT);
  pinMode(PUL_03, OUTPUT);//right
  pinMode(DIR_03, OUTPUT);
  pinMode(ENA_03, OUTPUT);
  
  //FastLED.addLeds<WS2812, LED_STRIP_PIN, GRB>(leds, NUM_LEDS); 
  FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(leds, NUM_LEDS);
  
  //start homing procedure of stepper motors at startup
  //home_position();
  //sliding_down();
  //sliding_up();
  ENA_Disabled();
  //steps = 0;
}

void loop() {
    ENA_Disabled();
    // if there's any serial available, read it:
    while(Serial.available() > 0){
      char inByte(Serial.read());
        switch(inByte){
        case 'A':
        unloading_start();
        break;
        
        case 'B':
        sliding_up();
        ENA_Disabled();
        break;

        case 'C':
        //lid_opening();
        break;
        
        case 'D':
        home_position();
        break;

        case 'E':
        sliding_down();
        ENA_Disabled();
        break;

        case 'F':
        //lid_closing();
        break;
        
        default:
        break;
      }
      }
}
void home_position(){
  while(digitalRead(LIMIT_SWITCH_01)){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    if(ledState == LOW){
      blue_light_on();
      ledState = HIGH;
      }
    else{
      lights_off();
      ledState = LOW;
      }
    }
    digitalWrite(DIR_01,LOW);// remember to change it back to LOW
    digitalWrite(ENA_01,LOW);
    digitalWrite(PUL_01,LOW);
    delayMicroseconds(50);
    digitalWrite(PUL_01,HIGH);
    delayMicroseconds(50);
    }
}
void unloading_start(){
  while(digitalRead(LIMIT_SWITCH_02)){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    if(ledState == LOW){
      blue_light_on();
      ledState = HIGH;
      }
    else{
      lights_off();
      ledState = LOW;
      }
    }
    digitalWrite(DIR_01,HIGH);
    digitalWrite(ENA_01,LOW);
    digitalWrite(PUL_01,LOW);
    delayMicroseconds(50);
    digitalWrite(PUL_01,HIGH);
    delayMicroseconds(50);
    }
}

void sliding_down(){
  while(digitalRead(LIMIT_SWITCH_03)){ 
    digitalWrite(DIR_02,HIGH);//left
    digitalWrite(ENA_02,LOW);
    digitalWrite(PUL_02,LOW);
    digitalWrite(DIR_03,HIGH);//right
    digitalWrite(ENA_03,LOW);
    digitalWrite(PUL_03,LOW);
    delayMicroseconds(50);
    digitalWrite(PUL_02,HIGH);
    digitalWrite(PUL_03,HIGH);
    delayMicroseconds(50);
    }
}

void sliding_up(){
  while(digitalRead(LIMIT_SWITCH_04)){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    if(ledState == LOW){
      yellow_light_on();
      ledState = HIGH;
      }
    else{
      lights_off();
      ledState = LOW;
      }
    }
    digitalWrite(DIR_02,LOW);//left
    digitalWrite(ENA_02,LOW);
    digitalWrite(PUL_02,LOW);
    digitalWrite(DIR_03,LOW);//right
    digitalWrite(ENA_03,LOW);
    digitalWrite(PUL_03,LOW);
    delayMicroseconds(50);
    digitalWrite(PUL_02,HIGH);//left
    digitalWrite(PUL_03,HIGH);//right
    delayMicroseconds(50);
    }
    /*
  while(!digitalRead(LIMIT_SWITCH_04)){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    if(ledState == LOW){
      yellow_light_on();
      ledState = HIGH;
      }
    else{
      lights_off();
      ledState = LOW;
      }
    }
    digitalWrite(DIR_02,HIGH);//left
    digitalWrite(ENA_02,LOW);
    digitalWrite(PUL_02,LOW);
    digitalWrite(DIR_03,HIGH);//right
    digitalWrite(ENA_03,LOW);
    digitalWrite(PUL_03,LOW);
    delayMicroseconds(50);
    digitalWrite(PUL_02,HIGH);
    digitalWrite(PUL_03,HIGH);
    delayMicroseconds(50);
    }*/
}

void ENA_Disabled(){
  digitalWrite(ENA_01,HIGH);
  digitalWrite(ENA_02,HIGH);
  digitalWrite(ENA_03,HIGH);
}

void stepper_motor_test(int PUL_PIN, int ENA_PIN,int DIR_PIN){
  //Testing code
  for (step_counts=0; step_counts<rev*microstep; step_counts++)    //Forward 6400 steps
    {
    digitalWrite(DIR_PIN,LOW);
    digitalWrite(ENA_PIN,LOW);
    digitalWrite(PUL_PIN,LOW);
    delayMicroseconds(50);
    digitalWrite(PUL_PIN,HIGH);
    delayMicroseconds(50);
    }
  for (step_counts=0; step_counts<rev*microstep; step_counts++)   //Backward 6400 steps
  {
    digitalWrite(DIR_PIN,HIGH);
    digitalWrite(ENA_PIN,LOW);
    digitalWrite(PUL_PIN,LOW);
    delayMicroseconds(50);
    digitalWrite(PUL_PIN,HIGH);
    delayMicroseconds(50); 
  }
}

//LED Stips Control
void right_green_light_on(){
  for(int i=0; i<NUM_LEDS-5; i++){
  leds[i] = CRGB::Green; 
  }
  FastLED.show();
}

void left_green_light_on(){
  for(int i=5; i<NUM_LEDS; i++){
  leds[i] = CRGB::Green; 
  }
  FastLED.show();
}

void green_light_on(){
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Green; 
  }
  FastLED.show();
}
void red_light_stop(){
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Red; 
  }
  FastLED.show();
}

void blue_light_on(){
for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Blue; 
  }
  FastLED.show();
}

void yellow_light_on(){
for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Yellow; 
  }
  FastLED.show();
}

void lights_off(){
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Black; 
  }
  FastLED.show();
}

void blue_light_blinking(){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
  // save the last time you blinked the LED 
  previousMillis = currentMillis;
    if(ledState == LOW){
      blue_light_on();
      ledState = HIGH;
      }
    else{
      lights_off();
      ledState = LOW;
      }
  }
}
