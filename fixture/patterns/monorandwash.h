#ifndef MONORANDWASH_H
#define MONORANDWASH_H
#endif

// lighting object that alternates between a list of colors
class MonoRandWash : public LightObjectPattern{
public:
  MonoRandWash(CRGB* leds, int num_leds, uint8_t hue) {
    m_hue = hue;
    m_leds = leds;
    m_num_leds = num_leds;

    for (int i = 0; i < m_num_leds; i++) {
        m_values.push_back(random8());
    } 

  }

  void draw() {
    for(int i = 0; i < m_num_leds; i++) {
        m_leds[i] = CHSV(m_hue, 255, m_values[i]);
        m_values[i]++; 
    }
  }

private:
  uint8_t m_hue {0};   
  std::vector<uint8_t> m_values;
};
