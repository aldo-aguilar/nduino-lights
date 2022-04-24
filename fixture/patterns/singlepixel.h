#ifndef SINGLEPIXEL_H
#define SINGLEPIXEL_H
#endif

// lighting object that alternates between a list of colors
class SinglePixel : public LightObjectPattern{
public:
  SinglePixel(CRGB* leds, int num_leds, CHSV hsv) {
    m_hsv = hsv;
    m_hue = hsv.h;
    m_leds = leds;
    m_num_leds = num_leds;
    m_pos = 0;
  }

  void draw() {
    // uncomment me out to do a single pixel walk
    // if (m_pos > 0 && m_pos < m_num_leds - 1)
    // m_leds[m_pos - 1] = CHSV(0, 0, 0);

    m_leds[m_pos] = CHSV(m_hue, m_hsv.s, m_hsv.v);
    m_pos = (m_pos + 1) % m_num_leds; 

    if (m_pos == 0) {
        fill(CHSV(0, 0, 0));
    }
    
    m_hue++;
  }

private:
  uint8_t m_hue;
  int m_pos {0};   
};

