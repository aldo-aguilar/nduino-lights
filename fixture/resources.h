#ifndef RESOURCES_H
#define RESOURCES_H
#endif

#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

#include <ArduinoSTL.h>
#include <FastLED.h>
#include <utility>
#include <vector> 

//#ifdef BOARD_HAS_USB_SERIAL
//#include <SLIPEncodedUSBSerial.h>
//SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
//#else
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial);
//#endif

// potential data pins for lighting objects
#define DATA_PIN_LIGHTOBJ2 2
#define DATA_PIN_LIGHTOBJ3 3 
#define DATA_PIN_LIGHTOBJ4 4
#define DATA_PIN_LIGHTOBJ5 5  
#define DATA_PIN_LIGHTOBJ6 6 
#define DATA_PIN_LIGHTOBJ7 7 
#define DATA_PIN_LIGHTOBJ8 8 
#define DATA_PIN_LIGHTOBJ9 9 
#define DATA_PIN_LIGHTOBJ10 10 
#define DATA_PIN_LIGHTOBJ11 11
#define DATA_PIN_LIGHTOBJ12 12
#define DATA_PIN_LIGHTOBJ13 13

// number of LEDs corresponding to the fixtures data pin
#define LEDS_3FTFIXTURE 68
#define LEDS_4FTFIXTURE 96
#define LEDS_6FTFIXTURE 148
// delay in MS this is just zfor testing, no delay should 
// be set durning a real performance 
#define BOARD_DELAY 400

// recovery time after a restart, set it to 0 durning a performance to avoid any issues
// incase of a reset
#define RECOVER_TIME 3000

// serial port & osc message codes
#define SERIAL_BAUD 115200

// CHSV color defintions
CHSV CHSV_ORANGE = CHSV(32, 255, 255);
CHSV CHSV_YELLOW = CHSV(64, 255, 255);
CHSV CHSV_GREEN = CHSV(96, 255, 255);
CHSV CHSV_AQUA = CHSV(128, 255, 255);
CHSV CHSV_BLUE = CHSV(160, 255, 255);
CHSV CHSV_PURPLE = CHSV(192, 255, 255);
CHSV CHSV_PINK = CHSV(224, 255, 255);
CHSV CHSV_OFF = CHSV(0, 255, 0);

std::vector<CHSV> CHSV_TESTV{CHSV_ORANGE, 
                             CHSV_YELLOW, 
                             CHSV_GREEN, 
                             CHSV_AQUA, 
                             CHSV_BLUE, 
                             CHSV_PURPLE,
                             CHSV_PINK};

//-------------------------- utility functions ------------------------

bool within_bounds(int curr_idx, int num_leds){
  return (curr_idx >= 0 && curr_idx < num_leds);
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
