#include "state_machine.h"
#include <stdint.h>

static led_matrix_state **states; 
static size_t state_count;
static size_t current_state_ix;  



uint16_t button_press_count;  
static void IRAM_ATTR button_press_isr() {
  button_press_count++; 
  Serial.println("button");
}

static bool is_button_pressed() {
  static uint16_t prev_button_press_count;
  if(prev_button_press_count != button_press_count) {
    prev_button_press_count = button_press_count; 
    return true; 
  }
  return false; 
}

static void switch_state() {
  states[current_state_ix]->exit(); 
  current_state_ix++; 
  current_state_ix %= state_count;
  states[current_state_ix]->entry(); 
}

void state_machine_init(uint8_t button_pin, led_matrix_state **state, size_t count) {
  states = state; 
  state_count = count; 
  current_state_ix = 0; 
  pinMode(button_pin, INPUT_PULLDOWN);
  attachInterrupt(button_pin, button_press_isr, RISING);
  states[current_state_ix]->entry(); 
}

void state_machine_update() {
  if(is_button_pressed()) {

    switch_state(); 
    Serial.printf("switching states to state: %u", current_state_ix); 
  }
  states[current_state_ix]->update(); 
}