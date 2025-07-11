#include "led_matrix.h"

// Wrote this before I learned about the Adafruit Neopixel Hue function
uint32_t intToColor(uint32_t color, Adafruit_NeoPixel *pixels) {
  // for now just RGB order
  if (color <= 0xff) {
    return pixels->Color(color, 0xff - color, 0); 
  }
  uint8_t normalized_color = color % 0xff; 
  if(color <= 0xff *2) {
    return pixels->Color(0xff- normalized_color, 0, color); 
  }
  
  if(color <= 0xff * 3) {
      return pixels->Color(0, normalized_color, 0xff - normalized_color); 
  }
  return 0; 
}

void setArrColor(Adafruit_NeoPixel *px, uint16_t row, uint16_t col, uint32_t color) {
  if(px == NULL) {
    return; 
  }

  row = MIN(row, (PIXEL_ROWS - 1)); 
  col = MIN(col, (PIXEL_COLUMNS - 1)); 

  size_t pixel;
  uint16_t corrected_col = (row%2) ? PIXEL_COLUMNS - 1 - col : col; 
  pixel = row * PIXEL_COLUMNS + corrected_col;  

  px->setPixelColor(pixel, color); 
}

void setBitMapColor(Adafruit_NeoPixel *px, const bitmap_t *map, uint32_t color) {
  uint32_t newColor; 
  for(size_t row = 0; row < PIXEL_ROWS; row++) {
    for(size_t col = 0; col < PIXEL_COLUMNS; col++) {
      newColor = color * ((map->bytes[PIXEL_ROWS - 1 - row] >> (PIXEL_COLUMNS - 1 - col)) & 0x01); 
      setArrColor(px, row, col, newColor); 
    }
  }
  px->show(); 
}
