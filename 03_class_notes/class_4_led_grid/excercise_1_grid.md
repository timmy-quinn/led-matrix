# Set Grid Pixels 
We want to be able to access pixels in the grid one by one. We don't want to 
have to calculate each time which specific pixel in the strip corresponds to 
that position in the grid.


**Write a function that takes a row and column, then sets a specific pixel on 
the grid.**

### Template
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

void setGridPixel(int row, int col, int color) {
    /*
    * Write a function that takes in a row and column, then sets the 
    * corresponding pixel.
    */
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
```
  
### Tips: 
Think of an algorithm that will translate two numbers, the row, and the column, 
into the pixel number. Remember that with the way our LED strip wraps around, 
the pixels in one row are arranged in ascending order. In the other they are 
arranged in descending order (the modulus operator may be helpful here).


### Row, Col to Pixel Number  
| |Row 0| Row 1 | Row 2| Row 3 | Row 4 | Row 5 | Row 6 | Row 7 |
|---|---|---|---|---|---|---|---|---|
|**Col 7**|126|125|124|123|122|121|120|119|
|**Col 6**|102|103|104|105|106|107|108|109|
|**Col 5**|92 |91 |90 |89 |88 |87 |86 |85 |
|**Col 4**|68 |69 |70 |71 |72 |73 |74 |75 |
|**Col 3**|58 |57 |56 |55 |54 |53 |52 |51 |
|**Col 2**|34 |35 |36 |37 |38 |39 |40 |41 |
|**Col 1**|24 |23 |22 |21 |20 |19 |18 |17 |
|**Col 0**| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

