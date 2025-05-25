#include <Arduino.h>
#include "main.h"


// Create a struct_message called myData
struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("Bool: ");
  Serial.println(myData.d);
  Serial.println();
  blinkDebugLED(); // Call the function to blink the debug LED
}

void blinkDebugLED() {
  digitalWrite(greenLED, HIGH); // Turn on the LED
  delay(500); // Wait for 100 milliseconds
  digitalWrite(greenLED, LOW); // Turn off the LED
}


void setup(){
    pinMode(greenLED, OUTPUT); // Set the final input pin as input with pull-down resistorg

    Serial.begin(9000);
    delay(2000); // Wait for the serial connection to be established
    WiFi.mode(WIFI_STA); // Set the WiFi mode to station
    esp_now_init(); // Initialize ESP-NOW

    esp_now_register_recv_cb(OnDataRecv); // Register the callback function for receiving data

    Serial.println(WiFi.macAddress()); // Print the MAC address of the ESP32
    
}
void loop(){

  
}

// esp_err_t esp_now_register_recv_cb(esp_now_recv_cb_t cb);