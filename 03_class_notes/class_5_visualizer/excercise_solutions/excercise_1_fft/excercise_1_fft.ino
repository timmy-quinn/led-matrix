#include <arduinoFFT.h>
#include <Adafruit_NeoPixel.h>


///////////////////////////////////////////////////////////////////////////////////////////////////////
// LED Grid 
///////////////////////////////////////////////////////////////////////////////////////////////////////
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
    pixel = row * PIXEL_COLS_TOTAL + col;
    pixels.setPixelColor(pixel, color);
    
}

void setGridColumn(int col, int height, int color) {
    /*
    * Write a function that takes in a column number and height, then sets the 
    * corresponding pixels.
    */
    for(int i = 0; i < height; i++) {
      setGridPixel(i, col, color);
    }

    for(int i = height; i < PIXEL_ROWS; i++) {
      setGridPixel(i, col, 0);
    }
}

int getColumnColor(int col) {
    /*
    * Write a function to get the column color
    */
    int maxHue = 65535;
    int maxSaturation = 255;
    int maxValue = 255;

    // The hue increases in steps across the columns
    int hue = col *(maxHue /PIXEL_COLS_VISIBLE);
    return pixels.ColorHSV(hue, maxSaturation, maxValue); 
}

void setGridColumnWithColor(int col, int height) {
    int color = getColumnColor(col);
    setGridColumn(col, height, color);
}

void setupPixels() {
    // Set the brightness. 
    // We can set the maximum brightness of our LEDs. 
    // We only need to set this once
    pixels.setBrightness(15);

    // Initialize the pixels. Only needs to be done once
    pixels.begin();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
// Microphone
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Micorphone pins
const int MIC_PIN = 32; 
const int GAIN_PIN = 5; 

const int SAMPLING_FREQUENCY = 20000;  
const int SAMPLING_PERIOD_uS = (1.0 / SAMPLING_FREQUENCY) * 1000000; // Sampling period in microseconds
const int SAMPLE_COUNT = 1024; // Must be a power of two
const int USABLE_MAGNITUDE_COUNT = SAMPLE_COUNT / 2; 

// Declare Arduino FFT Object
double vReal[SAMPLE_COUNT];
double vImag[SAMPLE_COUNT];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLE_COUNT, SAMPLING_FREQUENCY);

const int CONDENSED_BIN_COUNT = 8;
double avgBins[CONDENSED_BIN_COUNT];

// Calculate the fast fourier transform
void calculateFFT() {
  int sampleStartTime;
  for(int i = 0; i < SAMPLE_COUNT; i++) {
    sampleStartTime = micros();
    vReal[i] = analogRead(MIC_PIN);
    vImag[i] = 0; 
    while(micros() - sampleStartTime < SAMPLING_PERIOD_uS) {/*wait*/ }
  }
  FFT.dcRemoval();
  FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.compute(FFT_FORWARD); 
  FFT.complexToMagnitude();

}

void averageBins() {
  const int avgBinSize = USABLE_MAGNITUDE_COUNT / CONDENSED_BIN_COUNT;
  for(int i = 0; i < CONDENSED_BIN_COUNT; i++) {
    avgBins[i] = 0;
    for(size_t j = 0; j < avgBinSize; j++) {
      avgBins[i] += vReal[i * avgBinSize + 1];
    }
    avgBins[i] /= avgBinSize;
  }
}

void printFFT() {
  for(int i = 0; i < USABLE_MAGNITUDE_COUNT; i++) {
    Serial.print(vReal[i]);
    Serial.print(", ");
  }
  Serial.println("");
}

void printAverage() {
  for(int i = 0; i < CONDENSED_BIN_COUNT; i++) {
    Serial.print(avgBins[i]);
    Serial.print(", ");
  }
  Serial.println("");
}

void setupMic() {
  // Initialize Serial communication (UART peripheral)
  Serial.begin(115200); 
  // Configure the microphone pin as an input
  pinMode(MIC_PIN, INPUT);
}

////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////

const int NORMALIZATION_FACTOR = 500;

void displayFFT() {
  for(int col = 0; col < PIXEL_COLS_VISIBLE; col++) {
    int normalizedBin = (avgBins[col] / 500);
    int height = max(normalizedBin, 1);
    setGridColumnWithColor(col, height);
  }
  pixels.show();
}

void setup() {
  setupMic();
  setupPixels();
}


void loop() {
  calculateFFT();
  averageBins();
  displayFFT();
}
