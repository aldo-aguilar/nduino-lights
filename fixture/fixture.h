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

// parses incoming messages for fixture class, and will 
// handle sending out any data needed
class SerialPortManager {
friend FixtureManager;
public:
    SerialPortManager() {}

    void setup () {
      Serial.begin(SERIAL_BAUD);
    }

    void reset_msg() {
      m_msg_pos = 0;
      
      // clear out message struct to prevent overflow
      for(int i = 0; i < MAX_MSG_LEN; i++) {
        m_spmsg.data[i] = 0;
      }
    }

    bool handle_serial_message() {
      while (Serial.available() > 0) {
        char curr_byte = Serial.read();

        // still getting data for message
        if(curr_byte != '\n' && (m_msg_pos < MAX_MSG_LEN - 1)) {
          // we add this in case of an issues with messages overlapping
          if (m_msg_pos == 0 && !isAlpha(curr_byte)){
            reset_msg();
          }
          else{
            m_current_msg[m_msg_pos] = curr_byte;
            m_msg_pos++;
          }
        }
        
        // terminating character detected 
        else {
          parse_message();
          return true;
        }
      }

      return false;
    }



    void parse_message(){
      int data_idx = 0;

      switch (m_current_msg[0]) {

        case COLOR_MODE:
          m_spmsg.type = COLOR_MODE;

          for(int i = 1; i < MAX_MSG_LEN; i++) {
            char curr_char = m_current_msg[i]; 

            if(curr_char >= '0' && curr_char <= '9') {
              m_spmsg.data[data_idx] = (m_spmsg.data[data_idx] * 10) + (int)(curr_char - '0');
            }
            else{
              data_idx++;
            }
          }
        break;
        
      case UPDATE_MODE:
        m_spmsg.type = UPDATE_MODE;
        break;
    }
  }

private:
    char m_current_header {0};
    char m_current_msg[MAX_MSG_LEN];
    unsigned int m_msg_pos {0};
    SPMsg m_spmsg;
};

// fixture manager, main class that scripting code needs to interact with
class FixtureManager { 
public:
    FixtureManager(std::vector<LightObject*> light_objs) 
        : m_lighting_objs(light_objs) {
            m_spm.setup();
    }

    void clear() {
        std::for_each(m_lighting_objs.begin(), 
                m_lighting_objs.end(),
                [](LightObject* lo ){ lo->clear(); });
    }

    void draw () {
        std::for_each(m_lighting_objs.begin(), 
                        m_lighting_objs.end(),
                        [](LightObject* lo ){ lo->draw(); });
    }

    void handle_serial_message() {
        // status of serial port message being written to managers field 
        bool sp_msg_status = m_spm.handle_serial_message();

        if (sp_msg_status) {
          switch (m_spm.m_spmsg.type) {            
  
            case COLOR_MODE:  
              update_color(m_spm.m_spmsg.data[0], m_spm.m_spmsg.data[1], m_spm.m_spmsg.data[2]);
              break;
  
             case UPDATE_MODE:
               draw();
               break;
          }
          
          m_spm.reset_msg();
        }
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
    SerialPortManager m_spm {SerialPortManager()};
};
