#ifndef SERIALPORT_MANAGER_H
#define SERIALPORT_MANAGER_H
#endif

// parses incoming messages for fixture class, and will 
// handle sending out any data needed
class SerialPortManager {
public:
    SerialPortManager() {}

    void setup () {
      Serial.begin(m_band);
    }

    void set_band(int band) { m_band = band; }

    SPMsg handle_serial_message() {
      SPMsg output_spmsg;

      if (Serial.available() > 0) {
        int rgb_vals[3] = {0, 0, 0};
        int rgb_idx = 0;

        char curr_msg;
          if (m_current_header == 0){
            curr_msg = Serial.read();
            m_current_header = curr_msg;
          }
          
          switch (m_current_header) {
          case COLOR_MODE:
            output_spmsg.type = COLOR_MODE;

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
            output_spmsg.field1 = rgb_vals[0];
            output_spmsg.field1 = rgb_vals[1];
            output_spmsg.field1 = rgb_vals[2];
            output_spmsg.status = true;
            break;
            
          case UPDATE_MODE:
            output_spmsg.type = UPDATE_MODE;
            output_spmsg.status = true;
            break;
        }
      }
    return output_spmsg;
  }

private:
    long int m_band {96000};
    char m_current_header {0};
};
