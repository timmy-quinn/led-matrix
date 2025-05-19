 #ifndef STATE_MACHINE_H
 #define STATE_MACHINE_H

#include <Adafruit_NeoPixel.h>

class led_matrix_state {
  protected: 
    Adafruit_NeoPixel *mPixels; 
  public: 
    led_matrix_state(Adafruit_NeoPixel *pixels) {
      mPixels = pixels; 
    }
    void virtual entry() {
      return; 
    }
    void virtual update() {
      return; 
    }
    void virtual exit() {
      return; 
    }
}; 

void state_machine_init(uint8_t button_pin, led_matrix_state **state, size_t state_count); 
void state_machine_update();

 #endif