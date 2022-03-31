#ifndef LFO_H
#define LFO_H
#endif

// abstract base class of all LFOs
class LFO {
public:
    LFO(unsigned int frequency) {
      m_creation_time = millis();
      m_frequency = frequency;
    }
    
    virtual double current_val() = 0;

protected:
    unsigned long m_creation_time;
    unsigned int m_frequency;
    double m_spacing; // the spacing (time) between cycles 
};

// LFO using sine waves for its cycles 
class SineLFO : private LFO{
public:
  double current_val(){
    return sin((2*PI)*(millis()-m_creation_time));
  }
};

// LFO using square waves for its cycles 
class SquareLFO : private LFO{
public:
  double current_val(){
    return sgn(sin((2*PI)*(millis()-m_creation_time)));
  }
};
