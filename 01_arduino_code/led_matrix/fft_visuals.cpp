#include "fft_visuals.h"

#include "AudioConfigLocal.h"
#include "AudioTools.h"
#include "AudioTools/AudioLibs/AudioRealFFT.h" 
#include "led_matrix.h"

const size_t channel_count= 1; 
const size_t bits_per_sample = 16; 
const size_t samples_per_second = 40000; 
const size_t freq_window_count = 8; 
const size_t freq_window = (samples_per_second/2)/freq_window_count; 
const size_t num_channels = 8; 
const float min_frequency = 500; 

const size_t min_display_rows = 1; 
const size_t max_display_rows = 8;  
const float magnitude_division = 2.5; 

AudioInfo info(samples_per_second, channel_count, bits_per_sample);
I2SStream i2sStream; // Access I2S as stream
AnalogAudioStream analogIn; 
AudioRealFFT fft; 
StreamCopy copier(fft, analogIn); // copy i2sStream to csvOutput
static Adafruit_NeoPixel *pixels;  

static float channels[num_channels]; 
static uint32_t channel_colors[num_channels]; 


void printChannels() {
  for(size_t i = 0; i < num_channels; i++) {
    Serial.printf("%f, ", channels[i]); 
  }
  Serial.println(); 
}



void initChannelColors() {
  size_t colorVal; 
  for(size_t i = 0; i < num_channels; i++) {
    colorVal = (i * 0xff * 3 / num_channels); 
    Serial.printf("%u, " ,colorVal); 
    
    channel_colors[i] = intToColor(colorVal, pixels); 
  }
  Serial.println(); 
}

void displayLEDChannels() {
  size_t height = min_display_rows; 
  static size_t runningAverageHeights[num_channels] = {0}; 
  for(size_t col = 0; col < num_channels; col++) {
    height = static_cast <size_t>(channels[col]/magnitude_division); 
    height = min(height, 9u);
    height = max(height, min_display_rows);
    runningAverageHeights[col] = (height + runningAverageHeights[col])/ 2u; 
    for(size_t row = 0; row < PIXEL_ROWS; row++) {
      if(row < runningAverageHeights[col]) {
        setArrColor(pixels, row, col, channel_colors[col]); 
      }
      else {
        setArrColor(pixels, row, col, 0);         
      }
    }
  }
  pixels->show(); 
}

void fftResult(AudioFFTBase &fft){
    float diff;
    auto magnitudes = fft.magnitudes(); 
    size_t fft_size = fft.size(); 
    float start_freq, end_freq, avg_mag;
    size_t magnitudes_in_range = fft_size/8;
    size_t bin; 
    for(size_t i = 0; i < 8; i++) {
      avg_mag = 0; 
      for(size_t j = 0; j < magnitudes_in_range; j ++) {
        bin = i * magnitudes_in_range + j; 
        if(fft.frequency(bin) < min_frequency) {
          continue; 
        }
        if(i*magnitudes_in_range + j >= fft_size) {
          Serial.print("WARNGING!!!!!"); 
        }
        avg_mag += magnitudes[bin] / magnitudes_in_range; 
      }
      channels[i] = avg_mag; 
    }   
    displayLEDChannels(); 
}

void plotAllMagnitudes(AudioFFTBase &fft) {
  auto magnitudes = fft.magnitudes(); 
  for(size_t i = 0; i < fft.size(); i++) {
    Serial.printf("%f, ", magnitudes[i]); 
  }
  Serial.println(); 
}


void fft_visuals_state::entry() {
    pixels = mPixels; 
    AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Warning);

    initChannelColors(); 
    
    auto cfgRx = analogIn.defaultConfig(RX_MODE);
    cfgRx.copyFrom(info); 
    analogIn.begin(cfgRx);
    
    auto fft_cfg = fft.defaultConfig(); 
    fft_cfg.length = 512; 
    fft_cfg.channels = channel_count;
    fft_cfg.sample_rate = samples_per_second; 
    fft_cfg.bits_per_sample = bits_per_sample; 
    fft_cfg.callback = &fftResult; 
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