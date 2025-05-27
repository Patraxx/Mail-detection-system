#include <Arduino.h>
#include "main.h"
#include "http.h"



TaskHandle_t httpPostTaskHandle;
// Create a struct_message called myData
struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
 mailDetected = incomingData[0]; // Assuming the first byte indicates mail detection
 if (mailDetected) {
   Serial.println("Mail detected!");
   digitalWrite(greenLED, HIGH); // Turn on the LED to indicate mail detection
//   xTaskNotifyGive(httpPostTaskHandle); // Notify the HTTP post task to send a notification
 } else {
   digitalWrite(greenLED, LOW); // Turn off the LED
 }
}

void setup(){

    Serial.begin(9600);
    while(!Serial); // Wait for the serial connection to be established

    //WiFi.mode(WIFI_STA); // Set the WiFi mode to station
    wifi_setup(); // Initialize WiFi connection
    pinMode(greenLED, OUTPUT); // Set the final input pin as input with pull-down resistorg

    esp_now_init(); // Initialize ESP-NOW
    esp_now_register_recv_cb(OnDataRecv); // Register the callback function for receiving data
    xTaskCreate(http_post_task, "HTTP Post Task", 4096, NULL, 1, &httpPostTaskHandle); // Create the HTTP post task 

    Serial.println(WiFi.macAddress()); // Print the MAC address of the ESP32
    
}
void loop(){
  vTaskDelay(5000 / portTICK_PERIOD_MS); // Delay for 1 second
  Serial.println("Router WiFi channel: " + String(WiFi.channel()));
  Serial.println();
  Serial.println();
}