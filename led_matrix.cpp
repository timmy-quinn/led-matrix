#include "led_matrix.h"


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

void setBitMapColor(Adafruit_NeoPixel *px, bitmap_t *map, uint32_t color) {
  uint32_t newColor; 
  for(size_t row = 0; row < 8; row++) {
    for(size_t col = 0; col < 8; col++) {
      newColor = color * ((map->bytes[row] >> col) & 0x01); 
      setArrColor(px, row, col, newColor); 
    }
  }
  px->show(); 
}
