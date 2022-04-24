#ifndef LFO_H
#define LFO_H
#endif

#include <functional>

using osc_func = std::function<double(unsigned long, double)>;

osc_func osc_sine = [](unsigned long t0, double f){
  return sin((f)*(2*PI)*(millis()-t0));
};

osc_func osc_square = [](unsigned long t0, double f){
  return sgn(sin((f)*(2*PI)*(millis()-t0)));
};

// abstract base class of all LFOs
class LFO {
public:
    LFO(double frequency, osc_func func) {
      m_creation_time = millis();
      m_frequency = frequency;
      m_osc_func = func;
    }
    
    double current_val() {
      return m_osc_func(m_creation_time, m_frequency);
    }

protected:
    unsigned long m_creation_time;
    double m_frequency;
    double m_spacing; // the spacing (time) between cycles 
    osc_func m_osc_func;
};
