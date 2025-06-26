#include "smiley_face.h"
#include "led_matrix.h"

static uint32_t bitmap_color = 0xff0000; 
bitmap_t smileyBitmap = {
  {
    0b00000000, 
    0b01100110, 
    0b01100110, 
    0b00000000, 
    0b00000000,
    0b01000010, 
    0b00111100, 
    0b00000000, 
  }
}; 

bitmap_t smileyHalfBlinkBitmap = {
  {
    0b00000000, 
    0b00000000, 
    0b01100110, 
    0b00000000, 
    0b00000000,
    0b01000010, 
    0b00111100, 
    0b00000000, 
  }
}; 

bitmap_t smileyFullBlinkBitmap = {
  {
    0b00000000, 
    0b00000000, 
    0b00000000, 
    0b00000000, 
    0b00000000,
    0b01000010, 
    0b00111100, 
    0b00000000, 
  }
}; 

bitmap_t smileyHalfWinkBitmap = {
  {
    0b00000000, 
    0b00000110, 
    0b01100110, 
    0b00000000, 
    0b00000000,
    0b01000010, 
    0b00111100, 
    0b00000000, 
  }
}; 

bitmap_t smileyFullWinkBitmap = {
  {
    0b00000000, 
    0b00000110, 
    0b00000110, 
    0b00000000, 
    0b00000000,
    0b01000010, 
    0b00111100, 
    0b00000000, 
  }
}; 

#define BLINK_STEP_TIME_MS 50
#define BLINK_INTERVAL_MS 500

void blink(uint32_t color, Adafruit_NeoPixel *pix) {
  setBitMapColor(pix, &smileyBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  setBitMapColor(pix, &smileyHalfBlinkBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  setBitMapColor(pix, &smileyFullBlinkBitmap, color); 
  delay(BLINK_STEP_TIME_MS * 3); 
  setBitMapColor(pix, &smileyHalfBlinkBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  setBitMapColor(pix, &smileyBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  
}

#define WINK_HOLD_TIME_MS 500 
void wink(uint32_t color, Adafruit_NeoPixel *pix) {
  setBitMapColor(pix, &smileyBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  setBitMapColor(pix, &smileyHalfWinkBitmap, color); 
  delay(WINK_HOLD_TIME_MS); 
  setBitMapColor(pix, &smileyBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
}

void delay_state(uint32_t color, Adafruit_NeoPixel *pix) {
  delay(BLINK_INTERVAL_MS); 
}

void smiley_face_state::entry() {
  setBitMapColor(mPixels, &smileyBitmap, bitmap_color);  
}

typedef void (*update_func)(uint32_t, Adafruit_NeoPixel *); 


void smiley_face_state::update() { 
  static size_t i = 0; 
  static update_func function_pattern[] = {
    blink, 
    blink, 
    delay_state, 
    delay_state, 
    delay_state, 
    delay_state,
    delay_state,
    delay_state,
    delay_state,
    delay_state,
    delay_state,
    delay_state,
    wink, 
    delay_state, 
    delay_state, 
    delay_state, 
    delay_state,
    delay_state, 
    delay_state,
    delay_state, 
    delay_state,
    delay_state, 
    delay_state,
  }; 
  function_pattern[i](bitmap_color, mPixels); 
  i++; 
  if( i >= sizeof(function_pattern) / (sizeof(function_pattern[0]))) {
    i = 0; 
  }
}
