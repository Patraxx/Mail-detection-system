#include "tasks.h"
#include "main.h"
volatile bool mailDetected = false; // Flag to indicate if mail is detected

struct_message mailData; 


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
      }   
    } else {

      highStartTime = 0; // Reset the high start time if the pin goes LOW
      mailDetected = false;
      Serial.println("No mail detected, resetting flag");
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
      mailData.a[0] = 'M'; // Set the first character to 'M' to indicate mail detected
      Serial.println("Sending notification to ESP-NOW");
      esp_now_send(MAC_ADRESS_ROUTER_ESP, (uint8_t *)&mailData, sizeof(mailData));    
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
  vTaskDelete(NULL); // Delete the task when done
}




