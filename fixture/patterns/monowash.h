#ifndef MONOWASH_H
#define MONOWASH_H
#endif

// lighting object that alternates between a list of colors
class MonoWash : public LightObjectPattern{
public:
  MonoWash(CRGB* leds, int num_leds, int group, uint8_t hue, uint8_t value, uint8_t spacing) {
    m_hue = hue;
    m_value = value;
    m_leds = leds;
    m_num_leds = num_leds;
    m_id = group;
    m_space_factor = 255/spacing;
  }

  void draw() {
    for(int i = 0; i < m_num_leds; i++) {
        m_leds[i] = CHSV(m_hue, 255, (uint8_t)(m_value - (i*m_space_factor)));
    }
    m_value++;
  }

private:
  uint8_t m_space_factor {1};
};
