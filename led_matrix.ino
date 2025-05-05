#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include "led_matrix.h"
#include "fft_visuals.h"
#include <driver/i2s.h>

#define DELAY_TIME_MS 10
#define PIXEL_COUNT 64
#define PIXEL_PIN 13
#define PIXEL_BRIGHTNESS 15



static Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

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

void blink(uint32_t color) {
  setBitMapColor(&pixels, &smileyBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  setBitMapColor(&pixels, &smileyHalfBlinkBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  setBitMapColor(&pixels, &smileyFullBlinkBitmap, color); 
  delay(BLINK_STEP_TIME_MS * 3); 
  setBitMapColor(&pixels, &smileyHalfBlinkBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  setBitMapColor(&pixels, &smileyBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  
}

#define WINK_HOLD_TIME_MS 500 
void wink(uint32_t color) {
  setBitMapColor(&pixels, &smileyBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
  setBitMapColor(&pixels, &smileyHalfWinkBitmap, color); 
  delay(WINK_HOLD_TIME_MS); 
  setBitMapColor(&pixels, &smileyBitmap, color); 
  delay(BLINK_STEP_TIME_MS); 
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200); 
  while(!Serial);
  Serial.println("test"); 
  pixels.begin(); 
  pixels.setBrightness(PIXEL_BRIGHTNESS);

  fft_visuals_init(&pixels); 
  Serial.print("Setup complete"); 
  pinMode(4, INPUT); 
}

void loop() {
  fft_visuals_update(); 
  return; 

  static uint32_t color = pixels.Color(255, 0, 0); 
  setBitMapColor(&pixels, &smileyBitmap, color); 
  delay(BLINK_INTERVAL_MS); 
  blink(color); 
  blink(color); 
  delay(BLINK_INTERVAL_MS); 
  wink(color); 
  delay(BLINK_INTERVAL_MS); 
}
