#ifndef PULSE_H
#define PULSE_H
#endif

// lighting object that alternates between a list of colors
class Pulse : public LightObjectPattern{
public:
  Pulse(CRGB* leds, int num_leds, CHSV hsv) {
    m_hsv = hsv;
    m_leds = leds;
    m_num_leds = num_leds;
  }

  void update_color(CHSV new_hsv){
        m_hsv = new_hsv;
  }

  void draw() {
      fill(m_hsv);
  }
};

