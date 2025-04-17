
#include "general.h"

void sendMailBoxStatusCSV(HardwareSerial &Serial, CompartmentManager* compartmentManager) {
  #if debugMode
  Serial.println("Sending mailbox status as CSV...");
  #endif
  int totalCompartments = compartmentManager->totalCompartments; // Get the total number of compartments
  if (xSemaphoreTake(compartmentMutex, portMAX_DELAY)) {
    for (int i = 0; i < totalCompartments; i++) {
      Serial.print(compartmentManager->compartments[i].mailDetected ? "1" : "0"); // Send 1 if mail is detected, otherwise send 0
      if (i < totalCompartments - 1) {
        Serial.print(","); // Add comma between values
      }
    }
    Serial.print("\n"); // Send newline after all values
    xSemaphoreGive(compartmentMutex); // Release the mutex after sending the header
  }
}

void continuousTestSerial(){
  Serial.println("Test message from box-esp"); // Print a test message to the serial monitor
  vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
}