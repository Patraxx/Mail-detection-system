#include "tasks.h"
#include "main.h"
#include "compartments.h"


void multiplex_looper_task(void *pvParameters) {

  CompartmentManager* compartmentManager = static_cast<CompartmentManager*>(pvParameters);

  digitalWrite(MULTIPLEXER_1_DISABLE, LOW);
  digitalWrite(MULTIPLEXER_2_DISABLE, HIGH);
  Serial.println("Multiplex task started");

    while (1) {
      for (int i = 0; i < 8; i++) {  

        Compartment* currentCompartment = &compartmentManager->compartments[i];
              

          digitalWrite(MULTIPLEX_A, multiplexer_array[i][0]);
          digitalWrite(MULTIPLEX_B, multiplexer_array[i][1]);
          digitalWrite(MULTIPLEX_C, multiplexer_array[i][2]);
          vTaskDelay(10 / portTICK_PERIOD_MS);

          if (digitalRead(FINAL_INPUT) == HIGH) {   
            
          }
    }

    vTaskDelay(10/ portTICK_PERIOD_MS);   
  }
  vTaskDelete(NULL);
}

void scan_multiplexer(int activeMultiplexer, const int disable_mux[], int num_mux){

  for (int i = 0; i < num_mux; i++) {
    digitalWrite(disable_mux[i], (i == activeMultiplexer ? LOW : HIGH));  //disable all except the active one, by setting only the active one LOW
  }

  for (int i = 0; i < 8; i++) {
    digitalWrite(MULTIPLEX_A, multiplexer_array[i][0]);
    digitalWrite(MULTIPLEX_B, multiplexer_array[i][1]);
    digitalWrite(MULTIPLEX_C, multiplexer_array[i][2]);
  }

}

