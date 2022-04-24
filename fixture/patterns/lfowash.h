#ifndef LFOWASH_H
#define LFOWASH_H
#endif

// lighting object that alternates between a list of colors
class LFOWash : public LightObjectPattern{
public:
  LFOWash(CRGB* leds, int num_leds, CHSV hsv) {
    m_hsv = hsv;
    m_leds = leds;
    m_num_leds = num_leds;
  }

  void draw() {
    for(int i = 0; i < m_num_leds; i++) {
        m_leds[i] = CHSV(m_hsv.h, 255, m_value);
    }
    m_hue++; 
  }

private:
  uint8_t m_value {0};   
};

