# Set Columns 
To make our music visualizer look nice and pretty, we add colors to each column 
of the LED music visualizer. There are many ways to do this. Feel free to set 
it up however looks best to you.

![LED Matrix](../../04_photos/dark_image.jpg)

**Excercise: Write a function to get the color of each column, then use the 
functions you wrote in the previous excercises to display those colors**

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

void setGridColumn(int col, int height, int color) {
    /*
    * Write a function that takes in a column number and height, then sets the 
    * corresponding pixels.
    */
}

int getColumnColor(int col) {
    /*
    * Write a function to get the column color
    */
}

void setGridColumnWithColor(int col, int height) {
    int color = getColumnColor(col);
    setGridColumn(col, height, color);
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
    int height = 0;
    // Our pixels are RGB. We can set the value of each LED in the pixels. 
    // The combination will determine the color. 
    for(int col = 0; col < PIXEL_COLS_VISIBLE; col++) {
        height = col + 1;
        setGridColumnWithColor(col, height);
        delay(50);
        pixels.show();
    }
    delay(1000);

    for(int col = PIXEL_COLS_VISIBLE - 1; col >= 0; col--) {
        height = PIXEL_COLS_VISIBLE - col;
        setGridColumnWithColor(col, height);
        delay(50);
        pixels.show();
    }
    delay(1000);
}```

### Tips
1. Another way to get a pixel color is to use the ````Adafruit_Neopixel.ColorHSV```` function.
It takes 3 arguments, hue, saturation, and value. You can think of hue as the 
color on the color wheel, (red, purple, blue, green, etc.). Saturation is the 
intensity or purity of the color. Value is the brightness.  
The NeoPixel function takes values between 0 and 65535 for the hue. The saturation 
and value are integers between 0 and 255.  
If you increment the hue, you can create a rainbow effect.
More info can be found [here](https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html#a1f16aee5b96e16e62598f826e292b23b) 
in the Adafruit_NeoPixel documentation.


2. You may want to consider storing the colors of each column in an array. 
(This can be done as an alternative approach to using the ````ColorHSV```` 
function, or in conjunction with it).

