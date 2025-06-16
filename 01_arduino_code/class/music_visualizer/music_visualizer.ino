#include <arduinoFFT.h>
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

const int MIC_PIN = 32; 
const int GAIN_PIN = 5; 
const uint32_t SAMPLING_FREQUENCY = 40000;  
const uint32_t SAMPLING_PERIOD_uS = (1.0 / SAMPLING_FREQUENCY) * 1000000; // Sampling period in microseconds
const int SAMPLE_COUNT = 1024; // Muset be a power of two
const int USABLE_MAGNITUDE_COUNT = SAMPLE_COUNT / 2; 


double vReal[SAMPLE_COUNT];  
double vImag[SAMPLE_COUNT];  
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLE_COUNT, SAMPLING_FREQUENCY);

// FFT Processing
const double MAGNITUDE_SCALE_FACTOR =35.0; 
const double MAGNITUDE_THRESHOLD = 75.0;

const int PIXEL_COUNT = 64; 
const int PIXEL_PIN = 13; 
const uint8_t PIXEL_BRIGHTNESS = 15; 
static Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
const uint16_t PIXEL_ROWS = 8;
const uint16_t PIXEL_COLUMNS = 8;


const size_t BINS_PER_COL = USABLE_MAGNITUDE_COUNT / PIXEL_COLUMNS; 

static double averageMagnitudes[PIXEL_COLUMNS]; 
static double runningAverageMagnitude[PIXEL_COLUMNS]; 
static uint16_t columnHeights[PIXEL_COLUMNS]; 
static uint32_t columnColors[PIXEL_COLUMNS];


static void setArrColor(uint16_t row, uint16_t col, uint32_t color);
void initColumnColors(); 

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
  for(size_t i = 0; i < PIXEL_COLUMNS; i++) {
    hue = (0xffff/PIXEL_COLUMNS) * i; 
    columnColors[i] = pixels.ColorHSV(hue, 255, 255); 
  }
}


static void runningAverage() {  
  for(uint16_t col = 0; col < PIXEL_COLUMNS; col++) {
    runningAverageMagnitude[col] = (static_cast <int>(averageMagnitudes[col]) + runningAverageMagnitude[col])/ 2; 
  }
}


static void averageBinsToColumns() {
    float diff;
    double avg_mag;
    size_t bin; 

    for(size_t i = 0; i < PIXEL_COLUMNS; i++) {
      avg_mag = 0; 
      for(size_t j = 0; j < BINS_PER_COL; j++) {

        bin = i * BINS_PER_COL + j; 
        if(bin < 2) {
          continue; 
        }
        if(bin > 1024) {
          Serial.println("LESS THAN 1024"); 
        }
        if(vReal[bin] < 0.0) {
          Serial.println("magnitude less than ZERO"); 
        }
        avg_mag += vReal[bin] / BINS_PER_COL; 
      }
      averageMagnitudes[i] = avg_mag; 
    } 
    // for(uint16_t i = 0; i < PIXEL_ROWS; i++) {
    //   Serial.printf("%lf, ", averageMagnitudes[i]); 
    // }
    // Serial.println(); 
}


static uint16_t mapMagnitudeToHeight(int magnitude) {
  uint16_t corrected_magnitude = (magnitude > MAGNITUDE_THRESHOLD) ? magnitude - MAGNITUDE_THRESHOLD : 0; 
  uint16_t height = static_cast <uint16_t>( corrected_magnitude / MAGNITUDE_SCALE_FACTOR);
  // Serial.printf("%u ,", height); 
  return height; 
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
  Serial.println(); 
}


void displayFFT(){
  averageBinsToColumns(); 
  runningAverage();  
  displayColumns(); 
}


void setup() {
  Serial.begin(115200); 
  pinMode(MIC_PIN, INPUT);
  pixels.setBrightness(PIXEL_BRIGHTNESS);
  pixels.begin(); 
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
  // FFT.dcRemoval(); 
  FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); 
  FFT.compute(FFT_FORWARD); 
  FFT.complexToMagnitude();
  displayFFT(); 
}
