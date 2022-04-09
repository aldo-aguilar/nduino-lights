#ifndef FIXTURE_H
#define FIXTURE_H
#endif

class FixtureManager;

// abstract base class of lighting objects effects
class LightObjectPattern {
public:
    virtual void draw();
    
    void fill(CRGB new_color){
        fill_solid(m_leds, m_num_leds, new_color); // this keeps crashing for me
    }
    
    virtual void update_color(int r, int g, int b){
        m_color = CRGB(r, g, b);
    }
    
protected:
    CRGB m_color;
    CRGB* m_leds;
    int m_num_leds;
};

// fixture manager, main class that scripting code needs to interact with
class FixtureManager { 
public:

    FixtureManager() {}

    FixtureManager(std::vector<LightObjectPattern*> light_objs) 
        : m_lighting_objs(light_objs) {}

    void fill(CRGB new_color) {
        std::for_each(m_lighting_objs.begin(), 
                m_lighting_objs.end(),
                [=](LightObjectPattern* lo ){ lo->fill(new_color); });
        FastLED.show();
    }

    void draw () {
        std::for_each(m_lighting_objs.begin(), 
                        m_lighting_objs.end(),
                        [](LightObjectPattern* lo ){ lo->draw(); });
        FastLED.show();
    }

    void update_color(int r, int g, int b) {
        std::for_each(m_lighting_objs.begin(), 
                m_lighting_objs.end(),
                [=](LightObjectPattern* lo ){ lo->update_color(r, g, b); });
    }

private:
    std::vector<LightObjectPattern*> m_lighting_objs;
};
