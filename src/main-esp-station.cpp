#include <Arduino.h>
#include "main.h"


void setup(){

    Serial.begin(9000);
    delay(2000); // Wait for the serial connection to be established
    WiFi.mode(WIFI_STA); // Set the WiFi mode to station
    uint8_t mac[6]; // Declare a byte array to hold the MAC address
    WiFi.macAddress(mac); // Get the MAC address of the ESP32
    esp_now_init(); // Initialize ESP-NOW

    Serial.println(WiFi.macAddress()); // Print the MAC address to the serial monitor




}
void loop(){

}

// esp_err_t esp_now_register_recv_cb(esp_now_recv_cb_t cb);