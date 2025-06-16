#include <Adafruit_NeoPixel.h>

const int PIXEL_COUNT = 64; 
const int PIXEL_PIN = 13; 
const int PIXEL_BRIGHTNESS = 15; 
static Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.setBrightness(PIXEL_BRIGHTNESS);
  pixels.begin(); 
  for(int i = 0; i < PIXEL_COUNT; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
