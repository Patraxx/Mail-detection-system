#include "tasks.h"
#include "main.h"

int currentPinSelected = 0;

int unalteredArray[8][3] = {
  {0, 0, 0},
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 1},
  {1, 0, 0},
  {1, 0, 1},
  {1, 1, 0},
  {1, 1, 1}
};

int descendingSelectionArrayLeft[8][3] = {
  {1, 0, 0}, // 4
  {1, 1, 0}, // 6
  {1, 1, 1}, // 7
  {1, 0, 1}, // 5
  {0, 1, 0}, // 2
  {0, 0, 1}, // 1
  {0, 0, 0}, // 0
  {0, 1, 1}  // 3 (added to complete the array)
};


void multiplex_selection_task(void *pvParameters) {
    Serial.println("Multiplex task started");
         /*
         första iterationen
         */
          digitalWrite(MULTIPLEX_A, unalteredArray[currentPinSelected][0]);
          digitalWrite(MULTIPLEX_B, unalteredArray[currentPinSelected][1]);
          digitalWrite(MULTIPLEX_C, unalteredArray[currentPinSelected][2]);
  
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
          digitalWrite(MULTIPLEX_A, unalteredArray[currentPinSelected][0]);
          digitalWrite(MULTIPLEX_B, unalteredArray[currentPinSelected][1]);
          digitalWrite(MULTIPLEX_C, unalteredArray[currentPinSelected][2]);
  
          debugPrinter(currentPinSelected, unalteredArray);
        }
        vTaskDelay(5/ portTICK_PERIOD_MS);
      }
    vTaskDelete(NULL);
  }


void multiplex_looper_cycle_task(void *pvParameters) {
  bool state = false;
  bool ordered = true;
  digitalWrite(MULTIPLEXER_1_DISABLE, LOW);
  digitalWrite(MULTIPLEXER_2_DISABLE, HIGH);
  Serial.println("Multiplex task started");

    while (1) {
      for (int i = 0; i < 8; i++) {
        if (ordered) {
          digitalWrite(MULTIPLEX_A, descendingSelectionArrayLeft[i][0]);
          digitalWrite(MULTIPLEX_B, descendingSelectionArrayLeft[i][1]);
          digitalWrite(MULTIPLEX_C, descendingSelectionArrayLeft[i][2]);
        } else {
          digitalWrite(MULTIPLEX_A, unalteredArray[i][0]);
          digitalWrite(MULTIPLEX_B, unalteredArray[i][1]);
          digitalWrite(MULTIPLEX_C, unalteredArray[i][2]);
        }
        
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    digitalWrite(MULTIPLEXER_1_DISABLE, state ? HIGH : LOW);
    digitalWrite(MULTIPLEXER_2_DISABLE, state ? LOW : HIGH);
    state = !state;
    vTaskDelay(10/ portTICK_PERIOD_MS);   
  }
  vTaskDelete(NULL);
}
