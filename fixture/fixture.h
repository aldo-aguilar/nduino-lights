#ifndef FIXTURE_H
#define FIXTURE_H
#endif

class FixtureManager;

// abstract base class of lighting objects effects
class LightObject {
public:
    virtual void draw();

    void clear(){
        fill_leds(0, 0, 0, m_leds, m_num_leds);
    }
    
    void update_color(int r, int g, int b){
        m_color = CRGB(r, g, b);
        return; 
    }
    
protected:
    CRGB m_color;
    CRGB* m_leds;
    int m_num_leds;
};

// fixture manager, main class that scripting code needs to interact with
class FixtureManager { 
public:
    FixtureManager(std::vector<LightObject*> light_objs) 
        : m_lighting_objs(light_objs) {}

    void clear() {
        std::for_each(m_lighting_objs.begin(), 
                m_lighting_objs.end(),
                [](LightObject* lo ){ lo->clear(); });
        FastLED.show();
    }

    void draw () {
        std::for_each(m_lighting_objs.begin(), 
                        m_lighting_objs.end(),
                        [](LightObject* lo ){ lo->draw(); });
        FastLED.show();
    }

    void update_color(int r, int g, int b) {
        r = std::min(r, 255);
        g = std::min(g, 255);
        b = std::min(b, 255);
        
        std::for_each(m_lighting_objs.begin(), 
                m_lighting_objs.end(),
                [=](LightObject* lo ){ lo->update_color(r, g, b); });
    }

private:
    std::vector<LightObject*> m_lighting_objs;
};
