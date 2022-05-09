#ifndef FIXTURE_H
#define FIXTURE_H
#endif

class FixtureManager;

// abstract base class of lighting objects effects
class LightObjectPattern {
public:
    virtual void draw();
    
    void fill(CHSV new_hsv){
        fill_solid(m_leds, m_num_leds, new_hsv); 
    }
    
    virtual void update_hsv(uint8_t new_h, uint8_t new_s, uint8_t new_v){
        m_hue = new_h;
        m_sat = new_s;
        m_value = new_v;
    }
    
    int m_id {0};
protected:
    uint8_t m_hue;
    uint8_t m_sat;
    uint8_t m_value;
    CRGB* m_leds;
    int m_num_leds;
};

// fixture manager, main class that scripting code needs to interact with
class FixtureManager { 
public:
    FixtureManager() {}

    FixtureManager(std::vector<LightObjectPattern*> light_objs) 
        : m_lighting_objs(light_objs) {}

    void fill(CHSV new_hsv) {
        std::for_each(m_lighting_objs.begin(), 
                m_lighting_objs.end(),
                [=](LightObjectPattern* lo ){ lo->fill(new_hsv); });
        FastLED.show();
    }

    void draw () {
        std::for_each(m_lighting_objs.begin(), 
                        m_lighting_objs.end(),
                        [](LightObjectPattern* lo ){ lo->draw(); });
        FastLED.show();
    }

    void update_hsv(int group, uint8_t new_h, uint8_t new_s, uint8_t new_v) {
        std::for_each(m_lighting_objs.begin(), 
                m_lighting_objs.end(),
                [=](LightObjectPattern* lo ){
                    lo->update_hsv(new_h, new_s, new_v); 
                  });
    }

private:
    std::vector<LightObjectPattern*> m_lighting_objs;
};
