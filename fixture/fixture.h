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

        // for (int i = 0; i < m_num_leds; i++) {
        //     m_leds[i] = new_hsv;
        // }
    }
    
    virtual void update_hsv(CHSV new_hsv){
        m_hsv= new_hsv;
    }
    
protected:
    CHSV m_hsv;
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

    void update_hsv(CHSV new_hsv) {
        std::for_each(m_lighting_objs.begin(), 
                m_lighting_objs.end(),
                [=](LightObjectPattern* lo ){ lo->update_hsv(new_hsv); });
    }

private:
    std::vector<LightObjectPattern*> m_lighting_objs;
};
