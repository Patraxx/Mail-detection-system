#include <Arduino.h>
#include "main.h"
#include "http.h"
#include "tasks.h"



TaskHandle_t httpPostTaskHandle;
// Create a struct_message called myData


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {

 mailDetected = incomingData[0]; // Assuming the first byte indicates mail detection
 /*
 if (mailDetected) {
   Serial.println("Mail is: " + String(mailDetected)+" , mail detected, turning on LED"); 
   digitalWrite(greenLED, HIGH); // Turn on the LED to indicate mail detection
  // xTaskNotifyGive(httpPostTaskHandle); // Notify the HTTP post task to send a notification
 } else {
    Serial.println("Mail is: " + String(mailDetected)+" , no mail detected, turning off LED"); 
   digitalWrite(greenLED, LOW); // Turn off the LED
 }*/
  Serial.print("Bool is : " + String(mailDetected));
}

void setup(){

    Serial.begin(9600);
    while(!Serial); // Wait for the serial connection to be established

   
    wifi_setup(); // Initialize WiFi connection
    pinMode(greenLED, OUTPUT); // Set the final input pin as input with pull-down resistorg

    esp_err_t err = esp_now_init(); // Initialize ESP-NOW
    if (err != ESP_OK) {
        Serial.println("ESP-NOW initialization failed");
        return; // Exit setup if initialization fails
    }
    Serial.println("ESP-NOW Initialized");
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Set the WiFi channel to 5
    esp_now_register_recv_cb(OnDataRecv); // Register the callback function for receiving data
    xTaskCreate(http_post_task, "HTTP Post Task", 16400, NULL, 1, &httpPostTaskHandle); // Create the HTTP post task 
    xTaskCreate(blink_led_task, "Blink LED Task", 2048, NULL, 1, &blinkLEDTaskHandle); // Create the blink LED task

    Serial.println(WiFi.macAddress()); // Print the MAC address of the ESP32
   
}
void loop() {


  
}

//Stack used during http_post: 14272 bytes

//Stack used during http_post: 14208 bytes
//