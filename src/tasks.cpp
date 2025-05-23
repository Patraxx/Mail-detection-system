#include "tasks.h"
#include "main.h"


void letter_detection_task(void *pvParameters) {
  while (true) {

    unsigned long highStartTime = 0;

    if (digitalRead(FINAL_INPUT) == HIGH) {

      if (highStartTime == 0) {
        highStartTime = millis(); // Record the time when the pin goes HIGH
      }
      if(millis() - highStartTime >= 5000 && !mailDetected){
        Serial.println("Mail detected, notifying espNOW");
        mailDetected = true; // Set the mail detected flag to true
      }
      // If the final input pin is HIGH, print the ADC valu

    } else {
      highStartTime = 0; // Reset the high start time if the pin goes LOW
      mailDetected = false;
      vTaskDelay(10 / portTICK_PERIOD_MS); // Delay for 100 milliseconds
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // Delay for 10 milliseconds
  }
   vTaskDelete(NULL); // Delete the task when done
}





