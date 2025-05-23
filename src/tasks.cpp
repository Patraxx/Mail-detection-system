#include "tasks.h"
#include "main.h"





void letter_detection_task(void *pvParameters) {
  while (true) {

    if (digitalRead(FINAL_INPUT) == HIGH) {
      // If the final input pin is HIGH, print the ADC value
      printADC();
    } else {
      // If the final input pin is LOW, do nothing
      vTaskDelay(100 / portTICK_PERIOD_MS); // Delay for 100 milliseconds
    }
  }
   
}





