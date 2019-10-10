#include "FastLED.h"
#define NUM_LEDS 4
#define LED_STRIP_PIN 22

CRGB leds[NUM_LEDS];

void setup(){ 
  //FastLED.addLeds<WS2812, LED_STRIP_PIN, GRB>(leds, NUM_LEDS); 
  FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(leds, NUM_LEDS);
}

void loop(){
  /*
  leds[0] = CRGB::White; FastLED.show(); delay(30);
  leds[0] = CRGB::Black; FastLED.show(); delay(30);
  leds[1] = CRGB::White; FastLED.show(); delay(30);
  leds[1] = CRGB::Black; FastLED.show(); delay(30);
  */
  //Blinking
  green_light_blinking();
  //red_light_stop();
  //delay(2000);
  
  //Stop!
  /*
  leds[1] = CRGB(0,255,0);
  FastLED.show();
  leds[2] = CRGB(0,0,255);
  FastLED.show();
  leds[3] = CRGB(255,0,0);
  FastLED.show();*/
}
void green_light_blinking(){
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Green; 
  }
  FastLED.show();
  delay(900);
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Black; 
  }
  FastLED.show();
  delay(900);
}

void red_light_stop(){
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Red; 
  }
  FastLED.show();
}

void blue_light_unloading(){
for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Blue; 
  }
  FastLED.show();
  delay(900);
  for(int i=0; i<NUM_LEDS; i++){
  leds[i] = CRGB::Black; 
  }
  FastLED.show();
  delay(900);
}
