#include "resources.h"
#include "fixture.h"
#include "lfo.h"
#include "patterns/huewash.h"
//#include "patterns/snake.h"
#include "patterns/pulse.h"

// vector of all lighting objects
std::vector<LightObjectPattern*> light_objs;

// initalize panels and lighting objects for this fixture
CRGB object1_leds[NUM_LEDS_FIXTURE1];
LightObjectPattern* light_obj1 = new HueWash(object1_leds, NUM_LEDS_FIXTURE1);


FixtureManager fixture;
  
void setup() {
  // start serial port at set baud rate
  Serial.begin(SERIAL_BAUD);
   
  // initalize all data pins and led arrays for each fixture,
  // push lighting objects onto global vector
  FastLED.addLeds<WS2812B, DATA_PIN_LIGHTOBJ5, GRB>(object1_leds, NUM_LEDS_FIXTURE1);  

  light_objs.push_back(light_obj1);
 
  fixture = FixtureManager(light_objs);    
  
  fixture.fill(CHSV(0, 0, 0));

  delay(RECOVER_TIME);
}

void OSCMsgReceive(){
  OSCBundle bundle;
  // TODO: this is pausing the program, we want to buffer messages so that
  // serial writes don't wait until the end of a package, they should wait 
  // until the full message has come in
  int size = SLIPSerial.available();
  while(!SLIPSerial.endofPacket()){
  
    if (size > 0){
      //fill the msg with all of the available bytes
      while(size--){
        byte current_byte = SLIPSerial.read();
        bundle.fill(current_byte);
      }
    }
    size = SLIPSerial.available();
  }
  if(!bundle.hasError()){
    bundle.dispatch("/color", color_mode);
  }
  else{
    Serial.println("error parsing OSC message");
  }
}

void color_mode(OSCMessage& msg) {
  fixture.update_hsv(CHSV(msg.getInt(0), msg.getInt(1), msg.getInt(2)));
}

void serialEvent() {
  OSCMsgReceive();
}

void loop() { 
  EVERY_N_MILLISECONDS(15){
    fixture.draw();
  }
}
