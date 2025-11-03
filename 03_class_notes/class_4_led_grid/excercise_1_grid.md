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
        for(int col = 0; col < PIXEL_COLS_VISIBLE; col++) {
            setGridPixel(row, col, color);
            delay(300);
            pixels.show();
        }
    }
}

```
  
### Tips: 
Think of an algorithm that will translate two numbers, the row, and the column, 
into the pixel number. 
Start out simply. Start with just the first row and write a function that can 
take in a row and column, and accurately control the first row. Then begin 
thinking about the second. 
Don't worry about the LEDs on the back which are not visible. Focus on just the 
visible LEDs.


### Row, Col to Pixel Number  
| |Col 0| Col 1 | Col 2 | Col 3 | Col 4 | Col 5 | Col 6 | Col 7 |
|---|---|---|---|---|---|---|---|---|
|**Row 7**|119|120|121|122|123|124|125|126|
|**Row 6**|102|103|104|105|106|107|108|109|
|**Row 5**|85 |86 |87 |88 |89 |90 |91 |92 |
|**Row 4**|68 |69 |70 |71 |72 |73 |74 |75 |
|**Row 3**|51 |52 |53 |54 |55 |56 |57 |58 |
|**Row 2**|34 |35 |36 |37 |38 |39 |40 |41 |
|**Row 1**|17 |18 |19 |20 |21 |22 |23 |24 |
|**Row 0**| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

