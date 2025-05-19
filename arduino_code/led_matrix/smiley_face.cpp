#include "smiley_face.h"
#include "led_matrix.h"


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
#define BLINK_INTERVAL_MS 5000

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

void smiley_face_state::update() { 
  static uint32_t color = mPixels->Color(255, 0, 0); 
  setBitMapColor(mPixels, &smileyBitmap, color); 
  delay(BLINK_INTERVAL_MS); 
  blink(color, mPixels); 
  blink(color, mPixels); 
  delay(BLINK_INTERVAL_MS); 
  wink(color, mPixels); 
  delay(BLINK_INTERVAL_MS); 
}
