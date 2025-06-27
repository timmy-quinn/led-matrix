#ifndef FFT_VISUALS_H
#define FFT_VISUALS_H

#include "led_matrix.h"
#include "state_machine.h"

class fft_visuals_state : public led_matrix_state {
  public: 
    fft_visuals_state(Adafruit_NeoPixel *pix): led_matrix_state(pix) {}
    void entry() override; 
    void update() override;
    void exit() override;  
}; 

void fft_visuals_init(Adafruit_NeoPixel *px);

void fft_visuals_update();

#endif
