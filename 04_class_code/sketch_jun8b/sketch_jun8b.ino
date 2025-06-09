#include <arduinoFFT.h>
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

const int MIC_PIN = 32; 
const int GAIN_PIN = 5; 
const uint32_t SAMPLING_FREQUENCY = 40000;  
const uint32_t SAMPLING_PERIOD_uS = (1.0 / SAMPLING_FREQUENCY) * 1000000; // Sampling period in microseconds
const int SAMPLE_COUNT = 1024; // Muset be a power of two 
double vReal[SAMPLE_COUNT];  
double vImag[SAMPLE_COUNT];  
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLE_COUNT, SAMPLING_FREQUENCY);

// FFT Processing
const unsigned int MAGNITUDE_SCALE_FACTOR =200; 
const unsigned int MAGNITUDE_OFFSET = 1350;

const int PIXEL_COUNT = 64; 
const int PIXEL_PIN = 13; 
static Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
const uint16_t PIXEL_ROWS = 8;
const uint16_t PIXEL_COLUMNS = 8;


const size_t BINS_PER_COL = SAMPLE_COUNT / PIXEL_COLUMNS; 


static void setArrColor(uint16_t row, uint16_t col, uint32_t color);
void initColumnColors(); 

static unsigned int averageMagnitudes[PIXEL_COLUMNS]; 
static unsigned int runningAverageMagnitude[PIXEL_COLUMNS]; 
static uint16_t runningAverageHeights[PIXEL_COLUMNS]; 
static uint32_t columnColors[PIXEL_COLUMNS];

static void setArrColor(uint16_t row, uint16_t col, uint32_t color) {
  row = min(row, static_cast <uint16_t>(PIXEL_ROWS - 1u)); 
  col = min(col, static_cast <uint16_t>(PIXEL_COLUMNS - 1u));
  
  uint16_t pixel;
  uint16_t corrected_col = (row%2) ? PIXEL_COLUMNS - 1 - col : col; 
  pixel = row * PIXEL_COLUMNS + corrected_col;  

  pixels.setPixelColor(pixel, color); 
}

// Initialize the array which stores the colors for each channel
void initColumnColors() {
  uint16_t hue; 
  for(size_t i = 0; hue < PIXEL_COLUMNS; hue++) {
    hue = (0xffff/PIXEL_COLUMNS) * i; 
    columnColors[i] = pixels.ColorHSV(hue, 255, 255); 
  }
}


static void runningAverage() {  
  for(uint16_t col = 0; col < PIXEL_COLUMNS; col++) {
    runningAverageMagnitude[col] = (static_cast <unsigned int>(averageMagnitudes[col]) + runningAverageMagnitude[col])/ 2; 
  }
}


static void averageBinsToColumns() {
    float diff;
    float start_freq, end_freq, avg_mag;
    size_t bin; 

    for(size_t i = 0; i < PIXEL_COLUMNS; i++) {
      avg_mag = 0; 
      for(size_t j = 0; j < BINS_PER_COL; j++) {
        bin = i * BINS_PER_COL + j; 
        avg_mag += vReal[bin] / BINS_PER_COL; 
      }
      averageMagnitudes[i] = avg_mag; 
    } 
}

static uint16_t mapMagnitudeToHeight(int magnitude) {
  uint16_t corrected_magnitude = (magnitude > MAGNITUDE_OFFSET) ? magnitude - MAGNITUDE_OFFSET : 0; 
  return static_cast <uint16_t>( corrected_magnitude / MAGNITUDE_SCALE_FACTOR);
}

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
}


void displayFFT(){
  averageBinsToColumns(); 
  runningAverage();  
  displayColumns(); 
}


void setup() {
  Serial.begin(115200); 
  pinMode(MIC_PIN, INPUT);
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
  
  for(int i = 0; i < SAMPLE_COUNT; i++) {
    Serial.printf("%lf , ", vReal[i]); 
  }
  Serial.println(); 
}
