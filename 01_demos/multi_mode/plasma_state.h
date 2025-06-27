#ifndef PLASMA_STATE_H
#define PLASMA_STATE_H

#include "led_matrix.h"
#include "state_machine.h"

class plasma_state : public led_matrix_state {
  public: 
    plasma_state(Adafruit_NeoPixel *pix): led_matrix_state(pix) {}
    void update() override;
}; 

#endif