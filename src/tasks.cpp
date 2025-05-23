#include "tasks.h"
#include "main.h"


void letter_detection_task(void *pvParameters) {
  unsigned long highStartTime = 0;
  bool mailDetected = false; // Flag to indicate if mail is detected

  while (true) {
    

    if (digitalRead(FINAL_INPUT) == HIGH) {

      if (highStartTime == 0) {
        highStartTime = millis(); // Record the time when the pin goes HIGH
      }
      if(millis() - highStartTime >= 5000 && !mailDetected){
        Serial.println("Mail detected, notifying espNOW");
        mailDetected = true; // Set the mail detected flag to true
      }   
    } else {

      highStartTime = 0; // Reset the high start time if the pin goes LOW
      mailDetected = false;
      vTaskDelay(100 / portTICK_PERIOD_MS); // Delay for 100 milliseconds
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // Delay for 10 milliseconds
  }
   vTaskDelete(NULL); // Delete the task when done
}

void esp_now_task(void *pvParameters) {  
  while (true) {
    if (mailDetected) {
      // Send notification to ESP-NOW
      Serial.println("Sending notification to ESP-NOW");
      
      mailDetected = false; // Reset the mail detected flag
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
  vTaskDelete(NULL); // Delete the task when done
}




