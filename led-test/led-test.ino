#include "FastLED.h"
#define NUM_LEDS 4
CRGB leds[NUM_LEDS];
void setup() { 
  FastLED.addLeds<NEOPIXEL, 24>(leds, NUM_LEDS); 
  }
void loop() {
  leds[0] = CRGB::Green; FastLED.show(); delay(1000);
  leds[0] = CRGB::Black; FastLED.show(); delay(1000);
}
