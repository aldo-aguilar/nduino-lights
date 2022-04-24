#ifndef SNAKE_H
#define SNAKE_H
#endif

class Snake : public LightObjectPattern{
public:
  Snake(CRGB* leds, int num_leds, int tail_length){
      m_leds = leds;
      m_num_leds = num_leds;
      m_hsv = CHSV(random(0, 255), 255, 255);

      m_tail_length = tail_length;
  }

  void update(){
    m_head_idx = (m_head_idx + 1) >= (m_num_leds - 1) ? 0 : m_head_idx + 1;
  }
  
  void draw() override{
    m_leds[m_head_idx] = m_hsv;

    for (int i = 1; i < m_tail_length; i++) {
      int current_pos = m_head_idx - i;
      if (current_pos >= 0 && current_pos <= m_head_idx - 1)
        m_leds[current_pos] = m_hsv;
    }
    int tail_delete = (m_head_idx - m_tail_length) < 0 ? m_num_leds + (m_head_idx - m_tail_length) :  (m_head_idx - m_tail_length);
    m_leds[tail_delete] = CHSV(0,0,0);
    update();
  }

private:  
  int m_head_idx{0};
  int m_tail_length;
  int m_start_pos;
  uint8_t m_hue;
  uint8_t m_value {255};
};
