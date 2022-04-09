#ifndef ALTERNATOR_H
#define ALTERNATOR_H
#endif

// lighting object that alternates between a list of colors
class Alternator : public LightObjectPattern{
public:
  Alternator(CRGB* leds, int num_leds, std::vector<CRGB> alt_colors) {
    m_leds = leds;
    m_num_leds = num_leds;
    
    m_color_vec.insert(m_color_vec.begin(), alt_colors.begin(), alt_colors.end());
    m_num_colors = m_color_vec.size();
  }

  void update() {
    m_curr_color_idx = (m_curr_color_idx + 1) % m_num_colors;
  }

  void update_color(int r, int g, int b){
        m_color_vec[m_curr_color_idx] = CRGB(r, g, b);
    }

  void draw() {
    fill(m_color_vec[m_curr_color_idx]);
    update();
  }

private:
  std::vector<CRGB> m_color_vec;
  int m_curr_color_idx {0};
  int m_num_colors;
};

