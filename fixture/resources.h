#ifndef RESOURCES_H
#define RESOURCES_H
#endif

#define DATA_PIN_FIXTURE1 1
#define DATA_PIN_FIXTURE2 2
#define DATA_PIN_FIXTURE3 3 
#define DATA_PIN_FIXTURE4 4
#define DATA_PIN_FIXTURE5 5  
#define DATA_PIN_FIXTURE6 6 
#define DATA_PIN_FIXTURE7 7 
#define DATA_PIN_FIXTURE8 8 
#define DATA_PIN_FIXTURE9 9 
#define DATA_PIN_FIXTURE10 10 
#define DATA_PIN_FIXTURE11 11
#define DATA_PIN_FIXTURE12 12
#define DATA_PIN_FIXTURE13 13

#define CLOCK_PIN 13

#define NUM_LEDS_FIXTURE1 60
#define NUM_LEDS_FIXTURE2 150 

//
int board_delay = 100;

// serial port message codes
#define COLOR_MODE 'c'
#define PATTERN_MODE 'p'
#define UPDATE_MODE 'u'

struct SPMsg {
  char type;
  bool status {false}; // status to indicate if a msg has been fully parsed
  int field1;
  int field2;
  int field3;
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
