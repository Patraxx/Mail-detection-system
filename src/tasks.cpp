#include "tasks.h"
#include "main.h"
#include "compartments.h"

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


void multiplex_looper_task(void *pvParameters) {

  CompartmentManager* compartmentManager = static_cast<CompartmentManager*>(pvParameters);

  Serial.println("Multiplex task started");

    while (1) {

      for (int i = 0; i < NUMBER_OF_COMPARTMENTS; i++) {

        
       
      }


      scan_multiplexer(0, multiplexer_disable_pins, 2); // Scan the first multiplexer
      scan_multiplexer(1, multiplexer_disable_pins, 2); // Scan the second multiplexer

       // Compartment* currentCompartment = &compartmentManager->compartments[i];
            
    }

  vTaskDelete(NULL);

}





