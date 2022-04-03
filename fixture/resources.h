#ifndef RESOURCES_H
#define RESOURCES_H
#endif

#include <ArduinoSTL.h>
#include <FastLED.h>
#include <utility>
#include <vector> 

// potential data pins for lighting objects
#define DATA_PIN_LIGHTOBJ1 1
#define DATA_PIN_LIGHTOBJ2 2
#define DATA_PIN_LIGHTOBJ3 3 
#define DATA_PIN_LIGHTOBJ4 4
#define DATA_PIN_LIGHTOBJ5 5  
#define DATA_PIN_LIGHTOBJ6 6 
#define DATA_PIN_LIGHTOBJ7 7 
#define DATA_PIN_LIGHTOBJ8 8 
#define DATA_PIN_LIGHTOBJ9 9 
#define DATA_PIN_LIGHTOBJ10 10 
#define DATA_PIN_LIGHTOBJ11 11
#define DATA_PIN_LIGHTOBJ12 12
#define DATA_PIN_LIGHTOBJ13 13

// number of LEDs corresponding to the fixtures data pin
#define NUM_LEDS_FIXTURE1 60
#define NUM_LEDS_FIXTURE2 150 

// delay in MS this is just for testing, no delay should 
// be set durning a real performance 
int board_delay = 100;

// serial port message codes

#define SERIAL_BAUD 9600

#define COLOR_MODE 'c'
#define PATTERN_MODE 'p'
#define UPDATE_MODE 'u'

#define MAX_MSG_LEN 24
#define MAX_MSG_PARAMETERS 3

struct SPMsg {
  char type;
  int data[MAX_MSG_PARAMETERS] {0};
};

//-------------------------- utility functions ------------------------

bool within_bounds(int curr_idx, int num_leds){
  return (curr_idx >= 0 && curr_idx < num_leds);
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void fill_leds(int r, int g, int b, CRGB* leds, int num_leds){
  for (int i = 0; i < num_leds; i++) {
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
}
