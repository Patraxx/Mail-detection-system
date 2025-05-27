#include <Arduino.h>
#include "main.h"
#include "tasks.h"





TaskHandle_t letterDetectionTaskHandle;
TaskHandle_t espNowTaskHandle;

volatile unsigned long lastInterruptTime = 0; // Variable to store the last interrupt time

struct_message senderData; 

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Data send failed");
  }
 // Serial.println("Current WiFi channel for sender: " + String(WiFi.channel()));
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
  esp_wifi_set_channel(5, WIFI_SECOND_CHAN_NONE); // Set the WiFi channel to 5

  uint8_t mac[6]; // Declare a byte array to hold the MAC address
 
  WiFi.macAddress(mac); // Get the MAC address of the ESP32

  senderData = {0}; // Initialize the senderData struct

  esp_err_t err = esp_now_init(); // Initialize ESP-NOW
  if (err != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return; // Exit setup if initialization fails
  }

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
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, MAC_ADRESS_ROUTER_ESP, sizeof(MAC_ADRESS_ROUTER_ESP)); // Copy the MAC address of the peer device
  peerInfo.encrypt = false; // Set encryption to false

 esp_now_add_peer(&peerInfo); // Add the peer device to the ESP-NOW peer list
  
 xTaskCreate(letter_detection_task, "Letter Detection Task", 2048, NULL, 1, NULL); // Create the letter detection task
 xTaskCreate(esp_now_task, "ESP-NOW Task", 4086, NULL, 1, &espNowTaskHandle); // Create the ESP-NOW task

}
void loop() {

vTaskDelay(1);

}


