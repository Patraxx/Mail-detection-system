#include <Arduino.h>
#include "main.h"
#include "tasks.h"
#include "compartments.h"
#include "ble_logging.h"
#include "ble_server.h"

#define button_pin 8
CompartmentManager compartmentManager(NUMBER_OF_COMPARTMENTS);

volatile unsigned long lastInterruptTime = 0; // Variable to store the last interrupt time

SemaphoreHandle_t compartmentMutex; // Declare the mutex for compartment access

TaskHandle_t mailboxPrinterTaskHandle; // Declare the task handle for mailbox printer task
volatile bool buttonOne = false;

void IRAM_ATTR buttonOneInterrupt() {
  unsigned long interruptTime = millis(); // Get the current time in milliseconds
  if (interruptTime - lastInterruptTime > 500) { // Check if the interrupt is not too close to the last one
    buttonOne = true; // Set the button state to true
    lastInterruptTime = interruptTime; // Update the last interrupt time
  }
}

void printADC() {
  int adcValue = analogRead(ADC_PIN); // Read the ADC value from the final input pin
  if(adcValue > 500){
    Serial.println(adcValue); // Print the ADC value to the serial monitor
    vTaskDelay(50/portTICK_PERIOD_MS); // Delay for 50 milliseconds

  }
 
}


void setup() {
  pinMode(debugButton, INPUT_PULLUP); // Set the debug button pin as input with pull-up resistor
  attachInterrupt(digitalPinToInterrupt(debugButton), buttonOneInterrupt, FALLING); // Attach interrupt to the debug button pin
  pinMode(FINAL_INPUT, INPUT_PULLDOWN);
  pinMode(ADC_PIN, INPUT_PULLDOWN);
  pinMode(MULTIPLEXER_0_DISABLE, OUTPUT);
  pinMode(MULTIPLEXER_1_DISABLE, OUTPUT);
  pinMode(MULTIPLEXER_2_DISABLE, OUTPUT);
  pinMode(MULTIPLEX_A, OUTPUT);
  pinMode(MULTIPLEX_B, OUTPUT);
  pinMode(MULTIPLEX_C, OUTPUT);
  compartmentManager.initializeCompartments(); // Initialize the compartments

  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 16, 17); // Initialize Serial1 with RX and TX pins
  delay(1000);

  compartmentMutex = xSemaphoreCreateMutex(); // Create a mutex for compartment access
  if (compartmentMutex == NULL) {
    Serial.println("Failed to create mutex");
  } else {
    Serial.println("Mutex created successfully");
  }

  #if receiverCode
  setupBLEserver(); // Setup BLE server
  #else
  setupBLEclient(); // Setup BLE client
  #endif

 // compartmentManager.printCompartmentInfo(); // Print compartment information

  xTaskCreate(multiplex_looper_task, "Multiplex Task", 10000, &compartmentManager, 1, NULL);
  xTaskCreate(mailbox_printer_task, "Mailbox Printer Task", 10000, &compartmentManager, 1, &mailboxPrinterTaskHandle); // Create the mailbox printer task    /// will only print when a change has occured


}
String incomingLine = ""; // Buffer for storing the incoming line



#if receiverCode




void loop(){

}
#else

void loop() {

  if (buttonOne) {
    buttonOne = false;
    #if debugMode
    sendMailBoxStatusCSV(Serial, &compartmentManager); // Print the CSV to the serial monitor when button is pressed
    #else
    sendMailBoxStatusCSV(Serial1, &compartmentManager); // Send mailbox status CSV when button is press
    #endif
     // Reset the button state
  }
  while (Serial1.available()) {
    char c = Serial1.read();
    Serial.print(c); // Print the received character to the serial monitor 
  } 
}
#endif

