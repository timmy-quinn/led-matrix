#include <Adafruit_NeoPixel.h>
#include <stdint.h>

const int PIXEL_COUNT = 64; 
const int PIXEL_PIN = 13; 
const int PIXEL_BRIGHTNESS = 15; 
static Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
const int ROW = 8; 
const int COL = 8; 

void setPixelByRowCol(int col, int row, uint32_t color) {
  pixels.setPixelColor(row * ROW + col, color); 
}

void setup() {
  // put your setup code here, to run once:
  pixels.setBrightness(PIXEL_BRIGHTNESS);
  pixels.begin(); 
  for(int i = 0; i < PIXEL_COUNT; i++) {
    pixels.setPixelColor(i, pixels.Color(0,255,0));
  }
  pixels.show(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i =0; i < COL; i++) {
    for(int j=0; j < ROW; j++) {
          setPixelByRowCol(i, j, pixels.Color(255, 0, 0)); 
          pixels.show(); 
          delay(500); 
    }
  }
}
