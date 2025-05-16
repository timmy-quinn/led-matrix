// Plasma effect derived from code found here https://github.com/meharjit/ledtable
// More info can be found https://en.wikipedia.org/wiki/Plasma_effect
#include "plasma_state.h"
#include "led_matrix.h"
#define FRAME_SCALE 0.15
#define INCREMENT_MAX 0xffff

static uint16_t float_hue_to_u16(float hue) {
  return (hue * (0xffff/2)) + 0xffff/2; 
}

static uint32_t get_pixel_color(Adafruit_NeoPixel *pixels, float x_base, float y_base) {
  float hue; 
  float x = x_base * (2 * 3.1415) / PIXEL_COLUMNS * FRAME_SCALE; 
  float y = y_base * (2 * 3.1415) / PIXEL_ROWS * FRAME_SCALE; 

  float scale = 0.1; 

  hue = sin(x -y);
  hue += sin(x * x - (y * y * 2)); 
  hue+=sin(y-x); 
  hue /=3;  
  uint16_t hue_normalized = float_hue_to_u16(hue); 
  
  return pixels->ColorHSV(hue_normalized);
}

static void calc_frame(int increment, Adafruit_NeoPixel *pixels) {
  float hue;
  float wibble = sin(increment / INCREMENT_MAX);  
  float x_norm, y_norm;
  uint32_t color;
  float step = 0.02;
  for(float i = -1; i < 1; i+=step) {
    for (int x = 0; x < PIXEL_COLUMNS; x++) {
        for (int y = 0; y < PIXEL_ROWS; y++) {
            color = get_pixel_color(pixels, x * i, y * (-1 *i)); 
            // color = get_pixel_color(pixels, x, y); 
            setArrColor(pixels, y, x, color);
        }
    }
    pixels->show();
    delay(20);   
  }

for(float i = 1; i > -1; i-=step) {
    for (int x = 0; x < PIXEL_COLUMNS; x++) {
        for (int y = 0; y < PIXEL_ROWS; y++) {
            color = get_pixel_color(pixels, x * i, y * (-1 *i)); 
            // color = get_pixel_color(pixels, x, y); 
            setArrColor(pixels, y, x, color);
        }
    }
    pixels->show();
    delay(20);   
  }
  // delay(100); 
}

void plasma_state :: update() {
  for (uint16_t i = 0; i < INCREMENT_MAX; i+=32) {
    calc_frame(i, mPixels);
  }
}