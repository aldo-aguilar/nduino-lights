#ifndef FIXTURE_H
#define FIXTURE_H
#endif

#include "SerialPortManager.h"

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

class FixtureManager { 
public:
    FixtureManager(std::vector<LightObject*> light_objs) 
        : m_lighting_objs(light_objs) {
            m_sp_man.setup();
        }
    
    void draw () {
        for (LightObject* light_obj : m_lighting_objs) {
          light_obj->draw();
        }
    }

    void update_color(int r, int g, int b) {
        for (LightObject* light_obj : m_lighting_objs) {
          light_obj->update_color(r, g, b);
        }
    }

    void handle_serial_message() {
        // this is a wrapper method from the serial port manager 
        // this will check that a message has been fully parsed
        // and if so it will handle each case calling the proper 
        // method
        // TODO: is this code redundant? I think the wrapper makes
        // TODO: sense in this case but let me know what you think
        SPMsg current_msg = m_sp_man.handle_serial_message();

        if (current_msg.status) {
            switch (current_msg.type){
                case COLOR_MODE:
                    update_color(current_msg.field1, current_msg.field2, current_msg.field3);
                    break;

                case UPDATE_MODE:
                    draw();
                    break;
            }
        }
    }

private:
    std::vector<LightObject*> m_lighting_objs;
    SerialPortManager m_sp_man {SerialPortManager()};
};
