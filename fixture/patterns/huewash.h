#ifndef HUEWASH_H
#define HUEWASH_H
#endif

// lighting object that alternates between a list of colors
class HueWash : public LightObjectPattern{
public:
  HueWash(CRGB* leds, int num_leds) {
    m_hsv = CHSV(m_hue, 255, 50);
    m_leds = leds;
    m_num_leds = num_leds;
  }

  void draw() {
    for(int i = 0; i < m_num_leds; i++) {
        m_leds[i] = CHSV((uint8_t)(m_hue + (i * 5)), 255, 255);
    }
    m_hue++; 
  }

private:
  uint8_t m_hue {0};   
};
