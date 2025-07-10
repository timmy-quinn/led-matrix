#include "fft_visuals.h"

#include "driver/adc.h"
#include "AudioTools.h"
#include "AudioTools/AudioLibs/AudioRealFFT.h" 
#include "led_matrix.h"

const size_t CHANNEL_COUNT= 1; 
const size_t BITS_PER_SAMPLE = 16; 
const size_t SAMPLES_PER_SECOND = 40000; 
const size_t FREQ_WINDOW_COUNT = 8;
const size_t NUM_COLUMNS = 8; 

const uint16_t average_weight = 3; 
const uint32_t normalizing_offsets[NUM_COLUMNS] = {18000, 225, 400, 650, 900, 1100, 1300, 1400}; 
const uint32_t normalizing_scales[NUM_COLUMNS] = {115, 105, 75, 10, 10, 45, 65, 50}; 
static uint16_t binsPerColumn[NUM_COLUMNS] = {3, 4, 6, 12, 25, 47, 92, 323}; 

AudioInfo info(SAMPLES_PER_SECOND, CHANNEL_COUNT, BITS_PER_SAMPLE);
I2SStream i2sStream; // Access I2S as stream
AnalogAudioStream analogIn; 
AudioRealFFT fft; 
StreamCopy copier(fft, analogIn); // copy i2sStream to csvOutput
static Adafruit_NeoPixel *pixels;  

static uint32_t channel_colors[NUM_COLUMNS];
static float channels[NUM_COLUMNS]; 

static void printChannels(); 
static void plotAllMagnitudes(AudioFFTBase &fft); 

// Debug Functions
// Not neccessary for FFT display, but useful when debugging 
static void printChannels() {
  for(size_t i = 0; i < NUM_COLUMNS; i++) {
    Serial.printf("%f, ", channels[i]); 
  }
  Serial.println(); 
}

static void plotAllMagnitudes(AudioFFTBase &fft) {
  auto magnitudes = fft.magnitudes(); 
  for(size_t i = 0; i < fft.size(); i++) {
    Serial.printf("%f, ", magnitudes[i]); 
  }
  Serial.println(); 
}

// FFT Display Functions

// Initialize the array which stores the colors for each channel
void initColumnColors() {
  size_t colorVal; 
  for(size_t i = 0; i < NUM_COLUMNS; i++) {
    colorVal = (i * 0xff * 3 / NUM_COLUMNS);
    channel_colors[i] = intToColor(colorVal, pixels); 
  }
}

static size_t runningAverageHeights[NUM_COLUMNS] = {0}; 
static int runningAverageMagnitude[NUM_COLUMNS] = {0}; 

static void runningAverage() {
  for(size_t col = 0; col < NUM_COLUMNS; col++) {
    runningAverageMagnitude[col] = (static_cast <int>(channels[col]) + runningAverageMagnitude[col])/ 2; 
  }
}

static void normalize() {
  for(size_t col = 0; col < NUM_COLUMNS; col++) {
    channels[col] = channels[col]; 
  }
}


static void averageBinsToColumns() {
    float diff;
    auto magnitudes = fft.magnitudes(); 
    size_t fft_size = fft.size(); 
    float start_freq, end_freq, avg_mag;
    size_t bins_per_column = fft_size/NUM_COLUMNS;
    size_t bin = 0; 

    for(size_t i = 0; i < NUM_COLUMNS; i++) {
      channels[i] = 0;  
      // Human perception of sound is not linear. We will group the lower frequency bins
      // in smaller groups. 
      // This will provide a more visually pleasing affect, and be a little more 
      // reflective of how the sound is perceived
      for(size_t j = 0; j < bins_per_column; j++) {
        channels[i] += magnitudes[bin] / bins_per_column; 
        bin++;  
      }
    }
}

static size_t mapMagnitudeToHeight(int magnitude, uint32_t offset, uint32_t scale) {
  size_t corrected_magnitude = (magnitude > offset) ? magnitude - offset : 0;
  return min(static_cast <size_t>( corrected_magnitude / scale), static_cast<size_t>(PIXEL_COLUMNS -1));
}

static void displayFullColumns(uint16_t col) {
  uint16_t height = mapMagnitudeToHeight(runningAverageMagnitude[col], normalizing_offsets[col], normalizing_scales[col]); 
  for(size_t row = 0; row < PIXEL_ROWS; row++) {
    if(row <= height) {
      setArrColor(pixels, row, col, channel_colors[col]); 
    }
    else {
      setArrColor(pixels, row, col, 0);         
    }
  }
}

static void displayColumnTops(uint16_t col) {
  uint16_t height = mapMagnitudeToHeight(runningAverageMagnitude[col], normalizing_offsets[col], normalizing_scales[col]); 
  for(size_t row = 0; row < PIXEL_ROWS; row++) {
    if(row == height) {
      setArrColor(pixels, row, col, channel_colors[col]); 
    }
    else {
      setArrColor(pixels, row, col, 0);         
    }
  }
}

static void displayColumns() {

  for(size_t col = 0; col < NUM_COLUMNS; col++) {
    displayFullColumns(col);
  }
  pixels->show(); 
}

void displayFFT(AudioFFTBase &fft){
  averageBinsToColumns(); 
  runningAverage();  
  displayColumns(); 
}


void fft_visuals_state::entry() {
    pixels = mPixels; 
    AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Warning);

    initColumnColors(); 
    
    auto cfgRx = analogIn.defaultConfig(RX_MODE);

    cfgRx.copyFrom(info);
    cfgRx.adc_channels[0] = ADC_CHANNEL_4;
    analogIn.begin(cfgRx);
    
    auto fft_cfg = fft.defaultConfig(); 
    fft_cfg.window_function = new BufferedWindow(new Hamming());
    fft_cfg.length = 2048; 
    fft_cfg.channels = CHANNEL_COUNT;
    fft_cfg.sample_rate = SAMPLES_PER_SECOND; 
    fft_cfg.bits_per_sample = BITS_PER_SAMPLE; 
    fft_cfg.callback = &displayFFT; 

    fft.begin(fft_cfg);

    Serial.printf("buffer size: %u\n", copier.bufferSize()); 
}


// Arduino loop - copy data
void fft_visuals_state::update() {
    copier.copy();
}


void fft_visuals_state::exit() {
  fft.end();
}