#include <arduinoFFT.h>
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

// Micorphone pins
const int MIC_PIN = 32; 
const int GAIN_PIN = 5; 

// 
const uint32_t SAMPLING_FREQUENCY = 40000;  
const uint32_t SAMPLING_PERIOD_uS = (1.0 / SAMPLING_FREQUENCY) * 1000000; // Sampling period in microseconds
const int SAMPLE_COUNT = 1024; // Muset be a power of two
const int USABLE_MAGNITUDE_COUNT = SAMPLE_COUNT / 2; 

// Declare Arduino FFT Object
double vReal[SAMPLE_COUNT];  
double vImag[SAMPLE_COUNT];  
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLE_COUNT, SAMPLING_FREQUENCY);

// FFT Processing
const double MAGNITUDE_SCALE_FACTOR =200.0; 
const double MAGNITUDE_THRESHOLD = 200.0;


const int PIXEL_COUNT = 64; 
const int PIXEL_PIN = 13; 
const uint8_t PIXEL_BRIGHTNESS = 15; 
static Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
const uint16_t PIXEL_ROWS = 8;
const uint16_t PIXEL_COLUMNS = 8;


const size_t BINS_PER_COL = USABLE_MAGNITUDE_COUNT / PIXEL_COLUMNS; 

static double multipliers[PIXEL_COLUMNS] = {0.9, 1, 1.5, 1.5, 2, 2.0, 2.5, 4}; 
static uint16_t binsPerColumn[PIXEL_COLUMNS] = {3, 4, 6, 12, 25, 47, 92, 323};

static double averageMagnitudes[PIXEL_COLUMNS]; 
static double runningAverageMagnitude[PIXEL_COLUMNS]; 
static uint16_t columnHeights[PIXEL_COLUMNS]; 
static uint32_t columnColors[PIXEL_COLUMNS];


static void setArrColor(uint16_t row, uint16_t col, uint32_t color);
static void initColumnColors(); 
static void averageBinsToColumns(); 
static void normalize(); 
static void runningAverage(); 
static uint16_t mapMagnitudeToHeight(int magnitude); 
static void displayColumns(); 
void displayFFT(); 

static void setArrColor(uint16_t row, uint16_t col, uint32_t color) {
  row = min(row, static_cast <uint16_t>(PIXEL_ROWS - 1u)); 
  col = min(col, static_cast <uint16_t>(PIXEL_COLUMNS - 1u));
  
  uint16_t pixel;
  uint16_t corrected_col = (row%2) ? PIXEL_COLUMNS - 1 - col : col; 
  pixel = row * PIXEL_COLUMNS + corrected_col;  

  pixels.setPixelColor(pixel, color); 
}

// Initialize the array which stores the colors for each channel
static void initColumnColors() {
  uint16_t hue; 
  for(size_t i = 0; i < PIXEL_COLUMNS; i++) {
    hue = (0xffff/PIXEL_COLUMNS) * i; 
    columnColors[i] = pixels.ColorHSV(hue, 255, 255); 
  }
}


// Take all of the frequency bins and average them into PIXEL_COLUMNS number of groups.
static void averageBinsToColumns() {
    float diff;
    double avg_mag;
    uint16_t bin = 0; 

    for(size_t i = 0; i < PIXEL_COLUMNS; i++) {
      averageMagnitudes[i] = 0; 
      // Human perception of sound is not linear. We will group the lower frequency bins
      // in smaller groups. 
      // This will provide a more visually pleasing affect, and be a little more 
      // reflective of how the sound is perceived
      for(size_t j = 0; j < binsPerColumn[i]; j++) {
        averageMagnitudes[i] += vReal[bin] / binsPerColumn[i]; // / BINS_PER_COL; 
        bin++;
      }
    }
}


// Normalize the values
// The FFT calculations result in the lower frequencies
// having higher magnitudes. To correct for that we 
static void normalize(){
  for(uint16_t i = 0; i < PIXEL_COLUMNS; i++) {
    averageMagnitudes[i] *= multipliers[i]; 
  }
}


// Running average, 
// Smooths out the magnitude changes over time. 
static void runningAverage() {  
  for(uint16_t col = 0; col < PIXEL_COLUMNS; col++) {
    runningAverageMagnitude[col] = (static_cast <int>(averageMagnitudes[col]) + runningAverageMagnitude[col])/ 2; 
  }
  for(uint16_t i = 0; i < PIXEL_COLUMNS; i++) {
    Serial.printf("%lf, ", runningAverageMagnitude[i]); 
   }
  Serial.println(); 
}


// Convert the magnitudes, which are a double, into a height, which is an integer
// Scale them 
static uint16_t mapMagnitudeToHeight(int magnitude) {
  uint16_t corrected_magnitude; 
  if (magnitude > MAGNITUDE_THRESHOLD) {
    corrected_magnitude = magnitude - MAGNITUDE_THRESHOLD; 
  }
  else {
    corrected_magnitude = 0; 
  }
  // uint16_t corrected_magnitude = (magnitude > MAGNITUDE_THRESHOLD) ? magnitude - MAGNITUDE_THRESHOLD : 0; 
  uint16_t height = static_cast <uint16_t>( corrected_magnitude / MAGNITUDE_SCALE_FACTOR);
  return height; 
}


// After the heights of each columns are calculated, we display the columns
// Each column has a color that was initialized from the start. 
static void displayColumns() {
  uint16_t height; 
  for(uint16_t col = 0; col < PIXEL_COLUMNS; col++) {
    height = mapMagnitudeToHeight(runningAverageMagnitude[col]); 
    for(uint16_t row = 0; row < PIXEL_ROWS; row++) {
      if(row <= height) {
        setArrColor(row, col, columnColors[col]); 
      }
      else {
        setArrColor(row, col, 0);         
      }
    }
  }
  pixels.show();
  Serial.println(); 
}

// Process the FFT and display the results
void displayFFT() {
  averageBinsToColumns(); 
  normalize(); 
  runningAverage();  
  displayColumns(); 
}


void setup() {
  // Initialize Serial communication (UART peripheral)
  Serial.begin(115200); 
  // Configure the microphone pin as an input
  pinMode(MIC_PIN, INPUT);
  // Set the brightness
  pixels.setBrightness(PIXEL_BRIGHTNESS);
  // Initialize the pixels
  pixels.begin(); 
  // initialize the colors of the columns
  initColumnColors();
}

void loop() {
  uint32_t sampleStartTime;  
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
  displayFFT(); 
}
