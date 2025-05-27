#include "tasks.h"
#include "main.h"
volatile bool mailDetected = false; // Flag to indicate if mail is detected



void letter_detection_task(void *pvParameters) {
  unsigned long highStartTime = 0;

  while (true) {

    if (digitalRead(FINAL_INPUT) == HIGH) {

      if (highStartTime == 0) {
        highStartTime = millis(); // Record the time when the pin goes HIGH
      }
      if(millis() - highStartTime >= detectionTime && !mailDetected){
        Serial.println("Mail detected, notifying espNOW");
        mailDetected = true; // Set the mail detected flag to true
        xTaskNotifyGive(espNowTaskHandle); // Notify the ESP-NOW task
      }   
  
    } else {
      if (mailDetected) {
        highStartTime = 0; // Reset the high start time if the pin goes LOW 
        mailDetected = false;
        xTaskNotifyGive(espNowTaskHandle); // Notify the ESP-NOW task that no mail is detected     
        Serial.println("Mail no longer detected, resetting flag");
      }
    }
    vTaskDelay(1/ portTICK_PERIOD_MS); // Delay for 10 milliseconds
  }
   vTaskDelete(NULL); // Delete the task when done
}

void esp_now_task(void *pvParameters) {  

  while (true) {

    xTaskNotifyWait(0, 0, NULL, portMAX_DELAY); // Wait for notification from the letter detection task

    if (mailDetected) {
      Serial.println("Sending notification to ESP-NOW");

     esp_err_t err = esp_now_send(MAC_ADRESS_ROUTER_ESP, (uint8_t *)&mailDetected, sizeof(mailDetected));  
    }
    else {
      Serial.println("No mail detected, sending notification");  
      esp_err_t err = esp_now_send(MAC_ADRESS_ROUTER_ESP, (uint8_t *)&mailDetected, sizeof(mailDetected)); // Send notification to ESP-NOW
     
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // Delay for 1 second before checking again
  }
  vTaskDelete(NULL); // Delete the task when done
}




