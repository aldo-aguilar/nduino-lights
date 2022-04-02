#ifndef ALTERNATOR_H
#define ALTERNATOR_H
#endif

class Alternator : public LightObject{
public:
  Alternator(CRGB color, CRGB* leds, int num_leds){
    m_color = color;
    m_num_leds = num_leds;
    m_leds = leds;
    
  }

  void _update(){
    CRGB temp = m_color;
    m_color = m_alt_color;
    m_alt_color = temp;
  }

  void draw(){
    for (int i = 0; i < m_num_leds; i++) {
      if (i % 2 == 0)
        m_leds[i] = m_color;
      else
        m_leds[i] = m_alt_color; 
    }
    _update();
    FastLED.show();
  }

private:
  int m_alt_color {CRGB(0, 0, 0)};
};
