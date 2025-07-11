#include "smiley_face.h"
#include <stdint.h>
#include "led_matrix.h"


static uint32_t bitmap_color = 0xff0000; 


class animationPane {
  private:

    const bitmap_t *image; 
  public:
    animationPane(unsigned long duration, const bitmap_t *bitmap) {
      duration_ms = duration; 
      image = bitmap;
    }
    unsigned long duration_ms; 
    void display(uint32_t color, Adafruit_NeoPixel *pix);
}; 

const bitmap_t smileyBitmap = {
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

const bitmap_t smileyHalfBlinkBitmap = {
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


const bitmap_t smileyFullBlinkBitmap = {
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

const bitmap_t smileyHalfWinkBitmap = {
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

const bitmap_t smileyFullWinkBitmap = {
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
#define BLINK_CLOSE_TIME 2000


void animationPane::display(uint32_t color, Adafruit_NeoPixel *pix) {
  setBitMapColor(pix, image, color);
}

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

static unsigned long mStartTime_ms; 


static animationPane panes[] = {
  animationPane(BLINK_STEP_TIME_MS, &smileyBitmap), 
  animationPane(BLINK_STEP_TIME_MS, &smileyHalfBlinkBitmap), 
  animationPane(BLINK_STEP_TIME_MS, &smileyFullBlinkBitmap), 
  // animationPane(BLINK_STEP_TIME_MS, &smileyBitmap), 
}; 

static size_t animationIdx = 0; 
static unsigned long startTime_ms = 0; 

void smiley_face_state::entry() {
  startTime_ms = millis(); 
  panes[animationIdx].display(bitmap_color, mPixels);
}

typedef void (*update_func)(uint32_t, Adafruit_NeoPixel *); 


void smiley_face_state::update() {
  unsigned long currentTime_ms = millis();
  Serial.printf("%lu, %lu\n", currentTime_ms, startTime_ms);  
  if(currentTime_ms - startTime_ms > panes[animationIdx].duration_ms) {
    startTime_ms = currentTime_ms;
    animationIdx++;
    animationIdx %= sizeof(panes) / sizeof(panes[0]); 
    panes[animationIdx].display(bitmap_color, mPixels);
  }
  // static update_func function_pattern[] = {
  //   blink, 
  //   blink, 
  //   delay_state, 
  //   delay_state, 
  //   delay_state, 
  //   delay_state,
  //   delay_state,
  //   delay_state,
  //   delay_state,
  //   delay_state,
  //   delay_state,
  //   delay_state,
  //   wink, 
  //   delay_state, 
  //   delay_state, 
  //   delay_state, 
  //   delay_state,
  //   delay_state, 
  //   delay_state,
  //   delay_state, 
  //   delay_state,
  //   delay_state, 
  //   delay_state,
  // }; 
  // function_pattern[i](bitmap_color, mPixels); 
  // i++; 
  // if( i >= sizeof(function_pattern) / (sizeof(function_pattern[0]))) {
  //   i = 0; 
  // }
}
