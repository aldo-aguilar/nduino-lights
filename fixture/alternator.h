#ifndef ALTERNATOR_H
#define ALTERNATOR_H
#endif

// lighting object that alternates between 2 colors
class Alternator : public LightObject{
public:
  Alternator(CRGB color, CRGB* leds, int num_leds) {
    m_color = color;
    m_num_leds = num_leds;
    m_leds = leds;
  }

  void draw() {
    for (int i = 0; i < m_num_leds; i++) {
      if (m_leds[i] == m_color)
        m_leds[i] = m_alt_color;
      else
        m_leds[i] = m_color; 
    }
  }

private:
  CRGB m_alt_color {CRGB(0, 0, 0)};
};
