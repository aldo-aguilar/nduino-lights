#include <ArduinoSTL.h>
#include <FastLED.h>
#include <vector> 

#include "resources.h"
#include "fixture.h"

#include "alternator.h"
#include "lfo.h"
#include "snake.h"

// TODO (maybe): move this all into a setup file, and if you have time add a config 
// TODO (maybe): file to fill out fields maybe?

// vector of all lighting objects
std::vector<LightObject*> light_objs;

// initalize panels and lighting objects for this fixture
CRGB* object1_leds = new CRGB[NUM_LEDS_FIXTURE1];
LightObject* light_obj1 = new Snake(0, 20, object1_leds, NUM_LEDS_FIXTURE1);

CRGB* object2_leds = new CRGB[NUM_LEDS_FIXTURE2];
LightObject* light_obj2 = new Alternator(CRGB(255, 0, 0), object2_leds, NUM_LEDS_FIXTURE2);

// global serial port manager 
// TODO: this is being declared here with the empty vec because I don't have a 
// TODO: empty contructor written. I would like to do this a better way
// TODO: instead of just re-declaring it 
FixtureManager fixture(light_objs);

void setup() { 
  // initalize all data pins and led arrays for each fixture
  FastLED.addLeds<NEOPIXEL, DATA_PIN_FIXTURE5>(object1_leds, NUM_LEDS_FIXTURE1);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_FIXTURE7>(object2_leds, NUM_LEDS_FIXTURE2); 

  // push all lighting objects to the lighting object vector
  light_objs.push_back(light_obj1);
  light_objs.push_back(light_obj2);

  // initalize the serial port manager and call setup
  fixture = FixtureManager(light_objs);    
  
  fill_leds(0, 0, 0, object1_leds, NUM_LEDS_FIXTURE1);
  fill_leds(0, 0, 0, object2_leds, NUM_LEDS_FIXTURE2);
}

void serialEvent() {
//  spm.draw();
 fixture.handle_serial_message();
}

void loop() { 
  delay(board_delay);
  fixture.draw();
}
