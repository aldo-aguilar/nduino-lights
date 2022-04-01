#ifndef RESOURCES_H
#define RESOURCES_H
#endif

#include <FastLED.h>

#define DATA_PIN 5
#define CLOCK_PIN 13

// number of lights in LED strip
#define NUM_LEDS 60

// array of LEDS
CRGB leds[NUM_LEDS];

//
int board_delay = 100;

//-------------------------- utility functions ------------------------

bool within_bounds(int curr_idx){
  return (curr_idx >= 0 && curr_idx < NUM_LEDS);
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void fill_leds(int r, int g, int b){
  for (int i = NUM_LEDS; i > 0; i--) {
    // Now turn the LED off, then pause
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
}
