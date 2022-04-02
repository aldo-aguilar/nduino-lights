#ifndef SERIALPORT_MANAGER_H
#define SERIALPORT_MANAGER_H
#endif

// serial port message codes
#define COLOR_MODE 'c'
#define PATTERN_MODE 'p'

class SerialPortManager {
public:
    SerialPortManager(std::vector<LightObject*> light_objs) {
      m_lighting_objs = light_objs;
    }

    void setup () {
    Serial.begin(9600);
    }

    void draw () {
        for (LightObject* light_obj : m_lighting_objs) {
          light_obj->draw();
        }
    }

    void update_color(int r, int g, int b) {
        for (LightObject* light_obj : m_lighting_objs) {
          Serial.print("updating colors...\n");
          light_obj->update_color(r, g, b);
        }
    }

    void handle_serial_message() {
        if (Serial.available() > 0) {
          int rgb_vals[3] = {0, 0, 0};
          int rgb_idx = 0;

          char curr_msg;
            if (m_current_header == 0){
              curr_msg = Serial.read();
              m_current_header = curr_msg;
            }
            
            switch (m_current_header)
            {
            case COLOR_MODE:
                while(Serial.available() > 0) { // && msg != '\n'
                    curr_msg = Serial.read();
                    while (curr_msg != ',' && curr_msg != '!') {
                      if(curr_msg >= '0' && curr_msg <= '9') {
                        Serial.println((int)(curr_msg - '0'));
                        rgb_vals[rgb_idx] = (rgb_vals[rgb_idx] * 10) + (int)(curr_msg - '0');
                      }
                      curr_msg = Serial.read();
                    }

                    if (curr_msg == ',')
                      rgb_idx++;
                  
                 }

                update_color(rgb_vals[0], rgb_vals[1], rgb_vals[2]);
                break;
                
              case 'u':
                draw();
                break;
            }
            Serial.print('\n');
        }
}

private:
    char m_current_header {0};
    std::vector<LightObject*> m_lighting_objs;
};
