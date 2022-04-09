#ifndef TWO_SIDE_FILL_H
#define TWO_SIDE_FILL_H

// lighting object that alternates between 2 colors
class TwoSideFill : public LightObjectPattern{
public:
  TwoSideFill(CRGB color, CRGB* leds, int num_leds) {
    m_color = color;
    m_num_leds = num_leds;
    m_leds = leds;
    m_frontside = 0;
    m_backside = num_leds - 1;
  }

  void draw() {
    if (!m_reverse) {
      m_leds[m_frontside] = m_color;
      m_leds[m_backside] = m_color;
    }
    else{
      m_leds[m_frontside] = CRGB(0,0,0);
      m_leds[m_backside] = CRGB(0,0,0);
    }
    
    update_position();
  }

  void update_position() {
    if (m_reverse) {
      m_frontside = std::max(0, m_frontside - 1);
      m_backside = std::min(m_num_leds, m_backside + 1);
    }
    else{
      m_frontside++;
      m_backside--;
    }
    
    if (m_frontside > m_backside || m_frontside < 1 || m_backside > m_num_leds - 1){ 
      m_reverse = !m_reverse;
    }
  }

private:
  CRGB m_alt_color {CRGB(0, 0, 0)};
  int m_frontside;
  int m_backside;
  bool m_reverse {false};
};