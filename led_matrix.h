#ifndef led_matrix_h
#define led_matrix_h

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

#define PIXEL_ROWS 8
#define PIXEL_COLUMNS 8

#define MIN(a, b) (((a) < (b)) ? (a): (b))

typedef struct {
  uint8_t bytes[8]; 
} bitmap_t; 

void setArrColor(Adafruit_NeoPixel *px, uint16_t row, uint16_t col, uint32_t color); 

void setBitMapColor(Adafruit_NeoPixel *px, bitmap_t *map, uint32_t color); 


#endif

