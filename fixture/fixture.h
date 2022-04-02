class LightObject {
public:
    virtual void draw();

    void update_color(int r, int g, int b){
        m_color = CRGB(r, g, b);
        return; 
    }
    
protected:
    
    CRGB m_color;
    int m_num_leds;
    CRGB* m_leds;
};
