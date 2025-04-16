#include "tasks.h"
#include "main.h"
#include "compartments.h"

void mailChecker(CompartmentManager* compartmentManager) {

  bool previousState = compartmentManager->compartments[compartmentManager->currentCompartment].mailDetected; // Store the previous state of mail detection
  if(digitalRead(FINAL_INPUT) == HIGH) { // Check if the final input pin is HIGH
    compartmentManager->compartments[compartmentManager->currentCompartment].mailDetected = true; // Set mail detected to true for the current compartment
  } else {
    compartmentManager->compartments[compartmentManager->currentCompartment].mailDetected = false; // Set mail detected to false for the current compartment
  }
  if (compartmentManager->compartments[compartmentManager->currentCompartment].mailDetected != previousState) { // If the state has changed

    xTaskNotifyGive(mailboxPrinterTaskHandle); // Notify the mailbox printer task
  }
  compartmentManager->currentCompartment++;
}

void scan_multiplexer(int activeMultiplexer, const int disable_mux[], int num_mux, CompartmentManager* compartmentManager) {

  for (int i = 0; i < num_mux; i++) {
    digitalWrite(disable_mux[i], (i == activeMultiplexer ? LOW : HIGH));  //disable all except the active one, by setting only the active one LOW
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(MULTIPLEX_A, multiplexer_array[i][0]);
    digitalWrite(MULTIPLEX_B, multiplexer_array[i][1]);
    digitalWrite(MULTIPLEX_C, multiplexer_array[i][2]);

    //vTaskDelay(5/portTICK_PERIOD_MS); // Wait for the multiplexer to switch

    if(xSemaphoreTake(compartmentMutex, portMAX_DELAY)){ // Wait for the mutex to be available
     mailChecker(compartmentManager);
     xSemaphoreGive(compartmentMutex); // Release the mutex after accessing the compartment
    }
    compartmentManager->currentCompartmentReset(); // Reset the current compartment if it exceeds the total number of compartments
  }
}

void multiplex_looper_task(void *pvParameters) {

  CompartmentManager* compartmentManager = static_cast<CompartmentManager*>(pvParameters);

  Serial.println("Multiplex task started");

    while (1) {
      #if singleMultiplexerMode
      scan_multiplexer(0, multiplexer_disable_pins, 3, compartmentManager); // Scan the first multiplexer
      #else
      scan_multiplexer(0, multiplexer_disable_pins, 3, compartmentManager); // Scan the first multiplexer
      scan_multiplexer(1, multiplexer_disable_pins, 3, compartmentManager); // Scan the second multiplexer  
      scan_multiplexer(2, multiplexer_disable_pins, 3, compartmentManager); // Scan the third multiplexer  
      #endif
      vTaskDelay(10 / portTICK_PERIOD_MS); // Delay for 1 second before the next scan  
    }
  vTaskDelete(NULL);
}

void mailbox_printer_task(void *pvParameters) {
  CompartmentManager* compartmentManager = static_cast<CompartmentManager*>(pvParameters);
  while(1) {

    //ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(30000)); // Wait for notification from the mailChecker task   //Wait for 30 seconds and then print, unless a change occurs.
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait for notification from the mailChecker task
    if(xSemaphoreTake(compartmentMutex, portMAX_DELAY)) { // Wait for the mutex to be available
      for (int i = 0; i < compartmentManager->totalCompartments; i++) {
        if (compartmentManager->compartments[i].mailDetected) { // Check if mail is detected in the current compartment
          Serial.print("Mail detected in compartment: ");
          Serial.println(compartmentManager->compartments[i].compartmentNumber);
        }
      }
      xSemaphoreGive(compartmentMutex); // Release the mutex after printing
    }
  }
}







