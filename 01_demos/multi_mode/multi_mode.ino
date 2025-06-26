#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include <driver/i2s.h>


#include "state_machine.h"
#include "led_matrix.h"
#include "fft_visuals.h"
#include "smiley_face.h"
#include "plasma_state.h"


#define DELAY_TIME_MS 10
#define PIXEL_COUNT 64
#define PIXEL_PIN 13
#define PIXEL_BRIGHTNESS 15

#define BTN_HIGH_PIN 33U
#define STATE_PIN 25U
#define GAIN_PIN 5U

#define GAIN_40DB HIGH
#define GAIN_50DB LOW

static Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

smiley_face_state smiley_state(&pixels);
fft_visuals_state fft_state(&pixels);
plasma_state plas_state(&pixels); 

static led_matrix_state *matrix_states[] = {
  &fft_state, 
  &smiley_state, 
  &plas_state, 

}; 

void setup() { 
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH); 

  Serial.begin(115200); 
  while(!Serial); 
  Serial.println("test"); 
  pixels.begin(); 
  pixels.setBrightness(PIXEL_BRIGHTNESS); 

  pinMode(BTN_HIGH_PIN, OUTPUT);
  digitalWrite(BTN_HIGH_PIN, HIGH); 
  state_machine_init(STATE_PIN, matrix_states, sizeof(matrix_states)/sizeof(matrix_states[0])); 
  
  Serial.print("Setup complete"); 
} 

void loop() { 
  state_machine_update(); 
} 
