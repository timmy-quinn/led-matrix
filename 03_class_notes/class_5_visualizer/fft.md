# Fast Fourier Transform

```c++
#include <arduinoFFT.h>
// Microphone pins
const int MIC_PIN = 32; 
const int GAIN_PIN = 5; 
const int SAMPLING_FREQUENCY = 20000;  
const int SAMPLING_PERIOD_uS = (1.0 / SAMPLING_FREQUENCY) * 1000000; // Sampling period in microseconds
const int SAMPLE_COUNT = 8; // Must be a power of two
const int USABLE_MAGNITUDE_COUNT = SAMPLE_COUNT / 2; 

// Declare Arduino FFT Object
double vReal[SAMPLE_COUNT];
double vImag[SAMPLE_COUNT];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLE_COUNT, SAMPLING_FREQUENCY);


// Calculate the fast fourier transform
void gatherSamples() {
    // Gather samples
    // We collect SAMPLE_COUNT number of samples. Between samples we pause 
    // for  
    int sampleStartTime;
    for(int i = 0; i < SAMPLE_COUNT; i++) {
        sampleStartTime = micros();
        // Here, we read from the analog input pin connected to the 
        // Microphone
        vReal[i] = analogRead(MIC_PIN);
        vImag[i] = 0; 
        // Wait between samples until the sampling period has elapsed
        while(micros() - sampleStartTime < SAMPLING_PERIOD_uS) {/*wait*/ }
    }
}
    
void calculateFFT() {
    // Utilise the arduinoFFT library to actually calculate the FFT 
    // Consult the library docs here 
    // https://docs.arduino.cc/libraries/arduinofft/
    FFT.dcRemoval();
    FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(FFT_FORWARD); 
    FFT.complexToMagnitude();
}


void printFFT() {
    static double maxFFT = 500;
    for(int i = 0; i < USABLE_MAGNITUDE_COUNT; i++) {
        if(vReal[i] > maxFFT) {
          maxFFT = vReal[i];
        }
        Serial.print(vReal[i]);
        Serial.print(", ");
    }
    // Print a ceiling. This will prevent the serial plotter from 
    // jumping around so much.
    Serial.println(maxFFT);
    // Or just print a new line
    // Serial.println();
}


void setupMic() {
    // Configure the microphone pin as an input
    pinMode(MIC_PIN, INPUT);
}


void setup() {
    Serial.begin(115200); 
    setupMic();
}


void loop() {
    gatherSamples();
    calculateFFT();
    printFFT(); 
}

```
### Experiment: 
Play around with changing the number of samples taken. 

