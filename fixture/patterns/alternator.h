#ifndef ALTERNATOR_H
#define ALTERNATOR_H
#endif

// lighting object that alternates between a list of colors
class Alternator : public LightObjectPattern{
public:
  Alternator(CRGB* leds, int num_leds, std::vector<CHSV> hsv_vec) {
    m_hsv = hsv_vec[0];
    m_leds = leds;
    m_num_leds = num_leds;
    
    auto it = m_hsv_vec.begin();
    m_hsv_vec.insert(it, hsv_vec.begin(), hsv_vec.end());
  }

  void update() {
    m_curr_color_idx = m_curr_color_idx + 1 % m_hsv_vec.size();
  }

  void update_color(CHSV new_hsv){
        m_hsv_vec[m_curr_color_idx] = new_hsv;
  }

  void draw() {
    CHSV curr_chsv = m_hsv_vec[m_curr_color_idx];
    fill(curr_chsv);
    update();
  }

private:
  std::vector<CHSV> m_hsv_vec;
  int m_curr_color_idx {0};
};

