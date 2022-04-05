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
LightObject* light_obj1 = new TwoSideFill(CRGB(255, 255, 0), object1_leds, NUM_LEDS_FIXTURE1);

CRGB* object2_leds = new CRGB[NUM_LEDS_FIXTURE2];
LightObject* light_obj2 = new TwoSideFill(CRGB(255, 0, 0), object2_leds, NUM_LEDS_FIXTURE2);

// global serial port manager 
// TODO: this is being declared here with the empty vec because I don't have a 
// TODO: empty contructor written. I would like to do this a better way
// TODO: instead of just re-declaring it 
FixtureManager fixture(light_objs);

void setup() { 
  // initalize all data pins and led arrays for each fixture
  FastLED.addLeds<NEOPIXEL, DATA_PIN_LIGHTOBJ5>(object1_leds, NUM_LEDS_FIXTURE1);  
  FastLED.addLeds<NEOPIXEL, DATA_PIN_LIGHTOBJ7>(object2_leds, NUM_LEDS_FIXTURE2); 

  // push all lighting objects to the lighting object vector
  light_objs.push_back(light_obj1);
  light_objs.push_back(light_obj2);

  // initalize the serial port manager and call setup
  fixture = FixtureManager(light_objs);    
  
  fixture.clear();

  // recover time
  delay(RECOVER_TIME);
}

void OSCMsgReceive(){
  OSCMessage msg;
  
   
   while(!SLIPSerial.endofPacket()){
    int size = SLIPSerial.available();
    if (size > 0){
      //fill the msg with all of the available bytes
      while(size--){
        msg.fill(SLIPSerial.read());
      }
    }
  }
    
  if(!msg.hasError()){
    msg.route("/test", test);
    msg.route("/vest", vest);
  }

}

void test(OSCMessage& msg, int addressOffset) {
  return;
}

void vest(OSCMessage& msg, int addressOffset) {
  return;
}

void serialEvent() {
  OSCMsgReceive();
//  spm.draw();
//  while (Serial.available()){
//    fixture.handle_serial_message();
//  }
}

void loop() { 
//  delay(board_delay);
  fixture.draw();
}
