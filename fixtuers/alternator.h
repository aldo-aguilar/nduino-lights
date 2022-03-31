#ifndef ALTERNATOR_H
#define ALTERNATOR_H
#endif

class Alternator{
public:
  Alternator(CRGB color0, CRGB color1){
    m_color0 = color0;
    m_color1 = color1;
  }

  void _update(){
    CRGB temp = m_color0;
    m_color0 = m_color1;
    m_color1 = temp;
  }
  
  void draw(){
    for (int i = 0; i < NUM_LEDS; i++) {
      Serial.print(i);
      if (i % 2 == 0)
        leds[i] = m_color0;
      else
        leds[i] = m_color1; 
    }
    _update();
    FastLED.show();
  }

private:
  int head_idx;
  int tail_length;
  int start_pos;
  CRGB m_color0;
  CRGB m_color1;
};
