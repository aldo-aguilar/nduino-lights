#ifndef SNAKE_H
#define SNAKE_H
#endif

class Snake : public LightObjectPattern{
public:
  Snake(int _start_pos, int _tail_length, CRGB* leds, int num_leds){
      m_num_leds = num_leds;
      m_leds = leds;
      
      start_pos = _start_pos;
      head_idx = _start_pos; 
      tail_length = _tail_length;

      m_hsv = CHSV(random(100, 255), random(100, 255), random(100, 255));
  }

  void _update(){
    head_idx = head_idx > (m_num_leds + tail_length) ? 0 : head_idx + 1;
  }
  
  void draw() override{
    int fade_scale = 256/(tail_length);
    int fade_step = 0;

    for (int curr_idx = head_idx; curr_idx > (head_idx - (tail_length));  curr_idx--){
      if (curr_idx == head_idx && within_bounds(curr_idx, m_num_leds)){
        m_leds[curr_idx] = m_hsv;
      }

      else if (within_bounds(curr_idx, m_num_leds)){
        m_leds[curr_idx].fadeLightBy(fade_scale);
      }
      fade_step++;
    }
    
    if (within_bounds(head_idx - tail_length, m_num_leds)){
      m_leds[head_idx - tail_length] = CHSV(0, 0, 0);
    }
    _update();
  }

private:  
  int head_idx;
  int tail_length;
  int start_pos;
};
