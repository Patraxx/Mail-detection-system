#include <Arduino.h>
#include "main.h"
#include "tasks.h"
#include "compartments.h"

CompartmentManager compartmentManager(NUMBER_OF_COMPARTMENTS);

void setup() {

  pinMode(FINAL_INPUT, INPUT_PULLDOWN); 
  pinMode(MULTIPLEXER_1_DISABLE, OUTPUT);
  pinMode(MULTIPLEXER_2_DISABLE, OUTPUT);
  pinMode(MULTIPLEX_A, OUTPUT);
  pinMode(MULTIPLEX_B, OUTPUT);
  pinMode(MULTIPLEX_C, OUTPUT);
 
  Serial.begin(9600);
  delay(1000);

  xTaskCreate(multiplex_looper_task, "Multiplex Task", 10000, &compartmentManager, 1, NULL);


}

void loop() {

  
}

