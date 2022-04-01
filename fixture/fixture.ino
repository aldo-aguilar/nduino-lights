#include <FastLED.h>

//#include "alternator.h"
//#include "lfo.h"
#include "resources.h"
#include "snake.h"
#include "SerialPortManager.h"

// panels and lighting objects for this fixture
CRGB* object1_leds = new CRGB[NUM_LEDS_FIXTURE1];
Snake* snake1 = new Snake(0, 20, object1_leds, NUM_LEDS_FIXTURE1);

//CRGB* object1_leds = new CRGB[NUM_LEDS];
//Snake* snake2 = new Snake(0, 5);

// global serial port manager 
SerialPortManager spm = SerialPortManager(snake1);

void setup() { 
  // clear the LED strip
  spm.setup();
  
  // only get's printed when serial monitor is open
  Serial.print("----------DEBUGGING-------------\n");  // prints a label

  // initalize all data pins and led arrays for each fixture
  FastLED.addLeds<NEOPIXEL, DATA_PIN_FIXTURE5>(object1_leds, NUM_LEDS_FIXTURE1);  

  
  
  fill_leds(255, 0, 0, object1_leds, 60);
  
  Serial.print("----------finished the startup loop-------------\n");  // prints a label
}

void serialEvent() {
//  spm.draw();
//  spm.handle_serial_message();
}

void loop() { 
//  delay(board_delay);
//  spm.draw();
}
