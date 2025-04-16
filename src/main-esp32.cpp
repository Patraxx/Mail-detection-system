#include <Arduino.h>
#include "main.h"
#include "tasks.h"
#include "compartments.h"

#define button_pin 8
CompartmentManager compartmentManager(NUMBER_OF_COMPARTMENTS);

SemaphoreHandle_t compartmentMutex; // Declare the mutex for compartment access

TaskHandle_t mailboxPrinterTaskHandle; // Declare the task handle for mailbox printer task
volatile bool buttonOne = false;

void IRAM_ATTR buttonOneInterrupt() {
  buttonOne = true;
}

void printADC() {
  int adcValue = analogRead(FINAL_INPUT); // Read the ADC value from the final input pin
  Serial.println(adcValue); // Print the ADC value to the serial monitor
  vTaskDelay(50/portTICK_PERIOD_MS); // Delay for 50 milliseconds
}


void setup() {

  pinMode(FINAL_INPUT, INPUT_PULLDOWN);
  pinMode(UNUSED_INPUT, INPUT_PULLDOWN);
  pinMode(MULTIPLEXER_1_DISABLE, OUTPUT);
  pinMode(MULTIPLEXER_2_DISABLE, OUTPUT);
  pinMode(MULTIPLEX_A, OUTPUT);
  pinMode(MULTIPLEX_B, OUTPUT);
  pinMode(MULTIPLEX_C, OUTPUT);
  compartmentManager.initializeCompartments(); // Initialize the compartments

  Serial.begin(9600);
  delay(1000);

  compartmentMutex = xSemaphoreCreateMutex(); // Create a mutex for compartment access
  if (compartmentMutex == NULL) {
    Serial.println("Failed to create mutex");
  } else {
    Serial.println("Mutex created successfully");
  }

  compartmentManager.printCompartmentInfo(); // Print compartment information

  



  xTaskCreate(multiplex_looper_task, "Multiplex Task", 10000, &compartmentManager, 1, NULL);
  xTaskCreate(mailbox_printer_task, "Mailbox Printer Task", 10000, &compartmentManager, 1, &mailboxPrinterTaskHandle); // Create the mailbox printer task    /// will only print when a change has occured


}

void loop() {

  if (buttonOne) {
    #if debugMode
    sendMailBoxStatusCSV(Serial, &compartmentManager); // Print the CSV to the serial monitor when button is pressed
    #else
    sendMailBoxStatusCSV(Serial2, &compartmentManager); // Send mailbox status CSV when button is press
    #endif
    buttonOne = false; // Reset the button state
    vTaskDelay(200 / portTICK_PERIOD_MS); // Delay for 1 second to avoid multiple triggers
  }


 // printADC(); // Print the ADC value to the serial monitor



  

}

