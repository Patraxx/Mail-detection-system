#include "tasks.h"
#include "sensors.h"
#include "main.h"

int currentPinSelected = 0;


void multiplex_selection_task(void *pvParameters) {

    Serial.println("Multiplex task started");
         /*
         första iterationen
         */
          digitalWrite(MULTIPLEX_A, multiplexer_array[currentPinSelected][0]);
          digitalWrite(MULTIPLEX_B, multiplexer_array[currentPinSelected][1]);
          digitalWrite(MULTIPLEX_C, multiplexer_array[currentPinSelected][2]);
  
    while (1) {
  
        
      if (digitalRead(CYCLE_PIN_BUTTON) == HIGH) 
        // Debounce the button press
      
        if (digitalRead(CYCLE_PIN_BUTTON) == HIGH) {
          currentPinSelected++;
          if (currentPinSelected > 7) {
            currentPinSelected = 0;
          }
          vTaskDelay(150 / portTICK_PERIOD_MS);
    
          // Set the multiplex pins according to the current selection
          digitalWrite(MULTIPLEX_A, multiplexer_array[currentPinSelected][0]);
          digitalWrite(MULTIPLEX_B, multiplexer_array[currentPinSelected][1]);
          digitalWrite(MULTIPLEX_C, multiplexer_array[currentPinSelected][2]);
  
          debugPrinter(currentPinSelected, multiplexer_array);
        }
        vTaskDelay(5/ portTICK_PERIOD_MS);
      }
    vTaskDelete(NULL);
  }


void multiplex_looper_cycle_task(void *pvParameters) {

  digitalWrite(MULTIPLEXER_1_DISABLE, LOW);
  digitalWrite(MULTIPLEXER_2_DISABLE, HIGH);
  Serial.println("Multiplex task started");

    while (1) {
      for (int i = 0; i < 8; i++) {      

          digitalWrite(MULTIPLEX_A, multiplexer_array[i][0]);
          digitalWrite(MULTIPLEX_B, multiplexer_array[i][1]);
          digitalWrite(MULTIPLEX_C, multiplexer_array[i][2]);
          vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    vTaskDelay(10/ portTICK_PERIOD_MS);   
  }
  vTaskDelete(NULL);
}

void multiplex_looper_single_task(void *pvParameters) {

    while (1) {
      for (int i = 0; i < 8; i++) {      

          digitalWrite(MULTIPLEX_A, multiplexer_array[i][0]);
          digitalWrite(MULTIPLEX_B, multiplexer_array[i][1]);
          digitalWrite(MULTIPLEX_C, multiplexer_array[i][2]);     
          vTaskDelay(5 / portTICK_PERIOD_MS);
    }
  }
  vTaskDelete(NULL);
}

void letter_detection_task(void *pvParameters) {


  bool mailDetected = false;





}
