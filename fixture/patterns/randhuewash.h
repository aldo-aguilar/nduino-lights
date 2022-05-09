#ifndef RANDHUEWASH_H
#define RANDHUEWASH_H
#endif

// lighting object that alternates between a list of colors
class RandHueWash : public LightObjectPattern{
public:
  RandHueWash(CRGB* leds, int num_leds) {
    m_leds = leds;
    m_num_leds = num_leds;

    for (int i = 0; i < m_num_leds; i++) {
        m_hues.push_back(random8());
    } 

  }

  void draw() {
    for(int i = 0; i < m_num_leds; i++) {
        m_leds[i] = CHSV(m_hues[i], 255, 100);
        m_hues[i]++; 
    }
  }

private:
  uint8_t m_hue {0};   
  std::vector<uint8_t> m_hues;
};
