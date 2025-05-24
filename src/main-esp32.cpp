#include <Arduino.h>
#include "main.h"
#include "tasks.h"


#define button_pin 8


volatile unsigned long lastInterruptTime = 0; // Variable to store the last interrupt time

SemaphoreHandle_t compartmentMutex; // Declare the mutex for compartment access

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
  WiFi.mode(WIFI_STA); // Set the WiFi mode to station
  uint8_t mac[6]; // Declare a byte array to hold the MAC address
  WiFi.macAddress(mac); // Get the MAC address of the ESP32

  esp_now_init(); // Initialize ESP-NOW
  pinMode(greenLED, OUTPUT); // Set the built-in LED pin as output
  pinMode(debugButton, INPUT_PULLUP); // Set the debug button pin as input with pull-up resistor
  attachInterrupt(digitalPinToInterrupt(debugButton), buttonOneInterrupt, FALLING); // Attach interrupt to the debug button pin
  pinMode(FINAL_INPUT, INPUT_PULLDOWN);


  Serial.begin(9600);


  compartmentMutex = xSemaphoreCreateMutex(); // Create a mutex for compartment access
  if (compartmentMutex == NULL) {
    Serial.println("Failed to create mutex");
  } else {
    Serial.println("Mutex created successfully");
  }

  Serial.println("Mac Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac[i]); // Print each byte of the MAC address in hexadecimal format
    if (i < 5) {
      Serial.print(":"); // Print a colon between bytes
    }
  }



}
void loop() {


}


