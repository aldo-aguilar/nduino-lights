#include "resources.h"
#include "fixture.h"
#include "lfo.h"
#include "patterns/alternator.h"
#include "patterns/snake.h"

// vector of all lighting objects
std::vector<LightObjectPattern*> light_objs;

// initalize panels and lighting objects for this fixture
CRGB* object1_leds = new CRGB[NUM_LEDS_FIXTURE1];
LightObjectPattern* light_obj1 = new Alternator(object1_leds,
                                          NUM_LEDS_FIXTURE1,
                                          {CRGB::Blue, CRGB::Black, CRGB::Green, CRGB::Black}); // if I add red to this list the prgoram crashes? 

FixtureManager fixture;

void setup() {
  // start serial port at set baud rate
  Serial.begin(SERIAL_BAUD);
   
  // initalize all data pins and led arrays for each fixture,
  // push lighting objects onto global vector
  FastLED.addLeds<NEOPIXEL, DATA_PIN_LIGHTOBJ5>(object1_leds, NUM_LEDS_FIXTURE1);  

  light_objs.push_back(light_obj1);
 
  fixture = FixtureManager(light_objs);    
  
  fixture.fill(CRGB::Black);
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
  delay(BOARD_DELAY); // debugging only
  fixture.draw();
}
