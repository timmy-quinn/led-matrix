#ifndef SMILEY_FACE_H
#define SMILEY_FACE_H

#include "state_machine.h"

class smiley_face_state : public led_matrix_state {
  public: 
    smiley_face_state(Adafruit_NeoPixel *pix): led_matrix_state(pix) {}
    void entry() override; 
    void update() override;
}; 

void smiley_face_update(); 

#endif