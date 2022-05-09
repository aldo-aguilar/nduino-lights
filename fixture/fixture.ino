#include "resources.h"
#include "fixture.h"
//#include "lfo.h"
//#include "patterns/huewash.h"
#include "patterns/monowash.h"
//#include "patterns/randhuewash.h"
//#include "patterns/monorandwash.h"
//#include "patterns/pulse.h"
//#include "patterns/singlepixel.h"
//#include "patterns/snake.h"
//#include "patterns/two_side_fill.h"

// vector of all lighting objects
std::vector<LightObjectPattern*> light_objs;

// initalize panels and lighting objects for this fixture
CRGB object1_leds[LEDS_3FTFIXTURE ];
//LightObjectPattern* light_obj1 = new HueWash(object1_leds, LEDS_3FTFIXTURE);
LightObjectPattern* light_obj1 = new MonoWash(object1_leds, LEDS_3FTFIXTURE, 0, 255, 255, 10);

//CRGB object2_leds[LEDS_4FTFIXTURE];
//LightObjectPattern* light_obj2 = new Pulse(object2_leds, LEDS_4FTFIXTURE, CHSV_GREEN);

//CRGB object3_leds[LEDS_6FTFIXTURE ];
//LightObjectPattern* light_obj3 = new MonoWash(object3_leds, LEDS_6FTFIXTURE, 0, 255, 255, 10);
//CRGB object2_leds[LEDS_4FTFIXTURE ];
//LightObjectPattern* light_obj2 = new HueWash(object2_leds, LEDS_4FTFIXTURE);

FixtureManager fixture;
  
void setup() {
  // start serial port at set baud rate
  Serial.begin(SERIAL_BAUD);
   
  // initalize all data pins and led arrays for each fixture,
  // push lighting objects onto global vector
  FastLED.addLeds<WS2812B, DATA_PIN_LIGHTOBJ5, GRB>(object1_leds, LEDS_3FTFIXTURE);
//  FastLED.addLeds<WS2812B, DATA_PIN_LIGHTOBJ6, GRB>(object2_leds, LEDS_4FTFIXTURE);
//  FastLED.addLeds<WS2812B, DATA_PIN_LIGHTOBJ6, GRB>(object3_leds, LEDS_6FTFIXTURE);

//  FastLED.addLeds<WS2812B, DATA_PIN_LIGHTOBJ7, GRB>(object2_leds, LEDS_4FTFIXTURE);    

  light_objs.push_back(light_obj1);
//  light_objs.push_back(light_obj2);
//  light_objs.push_back(light_obj3);
 
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
    fixture.update_hsv(msg.getInt(0), msg.getInt(1), msg.getInt(2), msg.getInt(2));
}

void serialEvent() {
  OSCMsgReceive();
}

void loop() { 
  EVERY_N_MILLISECONDS(20){
    fixture.draw();
  }
}
