#include "resources.h"
#include "fixture.h"

#include "alternator.h"
#include "lfo.h"
#include "snake.h"

#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial);
#endif

#include <vector> 

// TODO (maybe): move this all into a setup file, and if you have time add a config 
// TODO (maybe): file to fill out fields maybe?

// vector of all lighting objects
std::vector<LightObject*> light_objs;

// initalize panels and lighting objects for this fixture
CRGB* object1_leds = new CRGB[NUM_LEDS_FIXTURE1];
LightObject* light_obj1 = new Snake(0, 5, object1_leds, NUM_LEDS_FIXTURE1);
//
//CRGB* object2_leds = new CRGB[NUM_LEDS_FIXTURE2];
//LightObject* light_obj2 = new TwoSideFill(CRGB(20, 20, 10), object2_leds, NUM_LEDS_FIXTURE2);

// global serial port manager 
// TODO: this is being declared here with the empty vec because I don't have a 
// TODO: empty contructor written. I would like to do this a better way
// TODO: instead of just re-declaring it 
FixtureManager fixture(light_objs);

void setup() {
  Serial.begin(SERIAL_BAUD);
   
  // initalize all data pins and led arrays for each fixture
  FastLED.addLeds<NEOPIXEL, DATA_PIN_LIGHTOBJ5>(object1_leds, NUM_LEDS_FIXTURE1);  
//  FastLED.addLeds<NEOPIXEL, DATA_PIN_LIGHTOBJ7>(object2_leds, NUM_LEDS_FIXTURE2); 

  // push all lighting objects to the lighting object vector
  light_objs.push_back(light_obj1);
//  light_objs.push_back(light_obj2);

  // initalize the serial port manager and call setup
  fixture = FixtureManager(light_objs);    
  
  fixture.clear();

  // recover time
  delay(RECOVER_TIME);
}

void OSCMsgReceive(){
  OSCBundle bundle;
  // TODO: this is pausing the program, we want to buffer messages so that
  // serial writes don't wait until the end of a package, they should wait 
  // until the full message has come in
   while(!SLIPSerial.endofPacket()){
    int size = SLIPSerial.available();
    
    if (size > 0){
      //fill the msg with all of the available bytes
      while(size--){
        byte current_byte = SLIPSerial.read();
        bundle.fill(current_byte);
      }
    }
  }
  
  if(!bundle.hasError()){
    bundle.dispatch("/color", color_mode);
  }
}

void color_mode(OSCMessage& msg) {
  fixture.update_color(msg.getInt(0), msg.getInt(1), msg.getInt(2));
}

void serialEvent() {
  OSCMsgReceive();
}

void loop() { 
  fixture.draw();
}
