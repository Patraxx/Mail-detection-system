#include <Arduino.h>
#include "main.h"
#include "tasks.h"


void testPins(){

  digitalWrite(MULTIPLEX_A, HIGH);
  digitalWrite(MULTIPLEX_B, LOW);
  digitalWrite(MULTIPLEX_C, LOW);

}
void setup() {

  pinMode(OUTPUT_PIN_1, OUTPUT);
  pinMode(OUTPUT_PIN_2, OUTPUT);
  
  pinMode(MULTIPLEXER_1_DISABLE, OUTPUT);
  pinMode(MULTIPLEXER_2_DISABLE, OUTPUT);
  digitalWrite(MULTIPLEXER_1_DISABLE, HIGH);
  digitalWrite(MULTIPLEXER_2_DISABLE, HIGH);
  pinMode(CYCLE_PIN_BUTTON, INPUT_PULLDOWN);
  pinMode(MULTIPLEX_A, OUTPUT);
  pinMode(MULTIPLEX_B, OUTPUT);
  pinMode(MULTIPLEX_C, OUTPUT);
  digitalWrite(OUTPUT_PIN_1, HIGH);
  digitalWrite(OUTPUT_PIN_2, HIGH);
  Serial.begin(9600);
  delay(500);

  //xTaskCreate(multiplex_selection_task, "multiplex_selection_task", 2048, NULL, 1, NULL);

  xTaskCreate(multiplex_looper_cycle_task, "multiplex_looper_cycle_task", 2048, NULL, 1, NULL);

  // put your setup code here, to run once:

}


void loop() {

}

