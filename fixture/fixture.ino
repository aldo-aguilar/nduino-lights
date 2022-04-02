#include <ArduinoSTL.h>
#include <FastLED.h>
#include <vector> 

#include "fixture.h"

#include "alternator.h"
// #include "lfo.h"
#include "resources.h"
#include "snake.h"
#include "SerialPortManager.h"

// vector of all lighting objects
std::vector<LightObject*> light_objs;

// initalize panels and lighting objects for this fixture
CRGB* object1_leds = new CRGB[NUM_LEDS_FIXTURE1];
Snake* light_obj1 = new Snake(0, 20, object1_leds, NUM_LEDS_FIXTURE1);
// Alternator* light_obj1 = new Alternator(CRGB(0, 255, 0), object1_leds, NUM_LEDS_FIXTURE1);


CRGB* object2_leds = new CRGB[NUM_LEDS_FIXTURE2];
// Snake* light_obj2 = new Snake(0, 20, object2_leds, NUM_LEDS_FIXTURE2);
Alternator* light_obj2 = new Alternator(CRGB(255, 0, 0), object2_leds, NUM_LEDS_FIXTURE2);



// global serial port manager 
SerialPortManager spm(light_objs);

void setup() { 
  // initalize all data pins and led arrays for each fixture
  FastLED.addLeds<NEOPIXEL, DATA_PIN_FIXTURE5>(object1_leds, NUM_LEDS_FIXTURE1);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_FIXTURE7>(object2_leds, NUM_LEDS_FIXTURE2); 

  // push all lighting objects to the lighting object vector
  light_objs.push_back(light_obj1);
  light_objs.push_back(light_obj2);

  // initalize the serial port manager and call setup
  spm = SerialPortManager(light_objs);    
  spm.setup();
  
  fill_leds(0, 0, 0, object1_leds, NUM_LEDS_FIXTURE1);
  fill_leds(0, 0, 0, object2_leds, NUM_LEDS_FIXTURE2);
}

void serialEvent() {
//  spm.draw();
 spm.handle_serial_message();
}

void loop() { 
  delay(board_delay);
  spm.draw();
}
