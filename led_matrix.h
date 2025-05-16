#ifndef led_matrix_h
#define led_matrix_h

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

#define PIXEL_ROWS 8
#define PIXEL_COLUMNS 8

// Some libraries already define a min function
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a): (b))
#endif

typedef struct {
  uint8_t bytes[8]; 
} bitmap_t; 

uint32_t intToColor(uint32_t color, Adafruit_NeoPixel *pixels); 

void setArrColor(Adafruit_NeoPixel *px, uint16_t row, uint16_t col, uint32_t color); 

void setBitMapColor(Adafruit_NeoPixel *px, bitmap_t *map, uint32_t color); 


#endif

