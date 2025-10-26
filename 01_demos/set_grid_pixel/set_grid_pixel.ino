// We must include the Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Variables describing the LED grid 
int PIXEL_COLS_VISIBLE = 8;
int PIXEL_COLS_HIDDEN = 9; 
int PIXEL_COLS_TOTAL = PIXEL_COLS_VISIBLE + PIXEL_COLS_HIDDEN;
int PIXEL_ROWS = 8;
int PIXEL_COUNT = PIXEL_ROWS * PIXEL_COLS_TOTAL; 
int PIXEL_PIN = 13; 

// initialize our neopixels
Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setGridPixel(int row, int col, int color) {
  /*
  * Write a function that takes in a row and column, then sets the 
  * corresponding pixel.
  */
  int pixel;
  if(row % 2) {
    pixel = row * PIXEL_COLS_TOTAL + col;
  } 
  else {
    pixel = row * PIXEL_COLS_TOTAL + (PIXEL_COLS_TOTAL - col);
  }
}

void setup() {
    // Set the brightness. 
    // We can set the maximum brightness of our LEDs. 
    // We only need to set this once
    pixels.setBrightness(15);

    // Initialize the pixels. Only needs to be done once
    pixels.begin();


}

void loop() {
    int red = 0;
    int blue = 0;
    int green = 255;
    int color = pixels.Color(red, green, blue);

    // Our pixels are RGB. We can set the value of each LED in the pixels. 
    // The combination will determine the color. 
    for(int row = 0; row < PIXEL_ROWS; row++) {
        for(int col = 0; col < PIXEL_COLS_VISIBLE; i++) {
            setGridPixel(row, col, color);
            delay(300);
            pixels.show();
        }
    }
}
