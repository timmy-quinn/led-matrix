# Adafruit Neopixel library basics

## Basic usage
```c++
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


void setup() {
    // Set the brightness. 
    // We can set the maximum brightness of our LEDs. 
    // We only need to set this once
    pixels.setBrightness(15);

    // Initialize the pixels. Only needs to be done once
    pixels.begin();

    // Our pixels are RGB. We can set the value of each LED in the pixels. 
    // The combination will determine the color. 
    int red = 0;
    int green = 0;
    int blue = 255;
    
    pixels.setPixelColor(0, red, green, blue);
    pixels.setPixelColor(1, red, green, blue);
    pixels.setPixelColor(2, red, green, blue);
    
    // Once we've set our LED colors to our desired values, an extra step is 
    // required to get our NeoPixels to actually show those colors
    // Must be called every time we want to change the LEDs
    pixels.show();
}
```

To set all of the pixels, we can also do this: 
```c++
    // Using a for loop, loop over all of the pixels
    for(int pix = 0; i < PIXEL_COUNT; i++) {
      pixels.setPixelColor(pix, red, green, blue);
    }
```

We can also use the ```Adafruit_NeoPixel.Color()``` function to obtain the RGB 
value in a single integer.
```c++
    int color = pixels.Color(red, green, blue);
    // Using a for loop, loop over all of the pixels
    for(int pix = 0; i < PIXEL_COUNT; i++) {
      pixels.setPixelColor(pix, color); // Just pass in the color to the led matrix
    }
```

