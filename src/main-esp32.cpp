#include <Arduino.h>
#include "main.h"
#include "tasks.h"


#define button_pin 8


volatile unsigned long lastInterruptTime = 0; // Variable to store the last interrupt time

struct_message senderData; 

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Data send failed");
  }
}


SemaphoreHandle_t compartmentMutex; // Declare the mutex for compartment access

volatile bool buttonOne = false;

void IRAM_ATTR buttonOneInterrupt() {
  unsigned long interruptTime = millis(); // Get the current time in milliseconds
  if (interruptTime - lastInterruptTime > 500) { // Check if the interrupt is not too close to the last one
    buttonOne = true; // Set the button state to true
    lastInterruptTime = interruptTime; // Update the last interrupt time
  }
}

void setup() {
  WiFi.mode(WIFI_STA); // Set the WiFi mode to station
  uint8_t mac[6]; // Declare a byte array to hold the MAC address
  WiFi.macAddress(mac); // Get the MAC address of the ESP32

  senderData.a[0] = 'H'; // Initialize the struct_message with some data

  esp_now_init(); // Initialize ESP-NOW
  esp_now_register_send_cb(OnDataSent); // Register the callback function for sending data
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



}
void loop() {

  esp_err_t result = esp_now_send(MAC_ADRESS_ROUTER_ESP, (uint8_t *)&senderData, sizeof(senderData)); // Send the data using ESP-NOW
  if (result == ESP_OK) {
    Serial.println("Data sent successfully");
  } else {
    Serial.print("Error sending data: ");
    Serial.println(result);
  }

  delay(5000); // Wait for 5 seconds before sending again
}


