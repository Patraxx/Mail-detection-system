#include <Arduino.h>
#include "main.h"
#include "tasks.h"


void testPins(){

  digitalWrite(MULTIPLEX_A, HIGH);
  digitalWrite(MULTIPLEX_B, HIGH);
  digitalWrite(MULTIPLEX_C, LOW);

}
void setup() {

  pinMode(OUTPUT_PIN_1, INPUT_PULLDOWN); 
  pinMode(OUTPUT_PIN_2, OUTPUT);
  pinMode(RAW_ADC_PIN, INPUT_PULLDOWN);
  pinMode(CYCLE_PIN_BUTTON, INPUT_PULLDOWN);
  pinMode(MULTIPLEX_A, OUTPUT);
  pinMode(MULTIPLEX_B, OUTPUT);
  pinMode(MULTIPLEX_C, OUTPUT);
 
  Serial.begin(9600);
  delay(500);

   xTaskCreate(multiplex_looper_single_task, "multiplex_looper_single_task", 2048, NULL, 1, NULL);

}

void read_adc() {
  int rawValue = analogRead(RAW_ADC_PIN);
  Serial.print("Raw ADC Value: ");
  Serial.println(rawValue);
}


void loop() {

  
}

