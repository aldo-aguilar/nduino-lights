#include "resources.h"

#include "alternator.h"
#include "lfo.h"
#include "snake.h"
#include "SerialPortManager.h"



//Alternator alt(CRGB(100, 0, 0), CRGB(255, 255, 0));
Snake* snake = new Snake(0, 20);

SerialPortManager spm = SerialPortManager(snake);

void setup() { 
  Serial.print("----------DEBUGGING-------------\n");  // prints a label
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  

  // clear the LED strip
  spm.setup();
  fill_leds(0, 0, 0);
}

void serialEvent() {
//  spm.draw();
  spm.handle_serial_message();
}

void loop() { 
  delay(board_delay);
////  alt.draw();
  spm.draw();
//  spm.handle_serial_message();
}
