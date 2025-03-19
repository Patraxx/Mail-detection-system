#include <Arduino.h>






void setup() {

  pinMode(TIMER_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World");


}

void loop() {

  

 vTaskDelay(10 / portTICK_PERIOD_MS);
  // put your main code here, to run repeatedly:
}

