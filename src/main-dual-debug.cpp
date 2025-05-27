#include <Arduino.h>    
#include "main.h"

#define receiverESP 1

int sent_counter = 0; // Counter for sent data
int failed_counter = 0; // Counter for failed data sends
int success_counter = 0; // Counter for successful data sends

void print_transmission_stats() {
    Serial.print("Sent: ");
    Serial.print(sent_counter);
    Serial.print(", Failed: ");
    Serial.print(failed_counter);
    Serial.print(", Success: ");
    Serial.println(success_counter);
} 
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    sent_counter++; // Increment the sent data counter
    if (status == ESP_NOW_SEND_SUCCESS) {
       // Serial.println("Data sent successfully");
        success_counter++; // Increment the success counter
    } else {
       // Serial.println("Data send failed");
        failed_counter++; // Increment the failed counter
    }
}
void onDataReceived(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
    Serial.print("Data received: ");
    for (int i = 0; i < data_len; i++) {
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
}   

#if receiverESP

void setup(){

    Serial.begin(9600); // Initialize serial communication
    while(!Serial); // Wait for the serial connection to be established

    WiFi.mode(WIFI_STA); // Set the WiFi mode to station
    WiFi.begin(hemma_sssid, hemma_password); // Connect to the WiFi network
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000); // Wait for connection
        Serial.println("Connecting to WiFi...");
    }


}
void loop(){
    



}
#else
void setup(){
    WiFi.mode(WIFI_STA); // Set the WiFi mode to station
    
    
    esp_wifi_set_channel(5, WIFI_SECOND_CHAN_NONE); // Set the WiFi channel to 5

    Serial.begin(9600); // Initialize serial communication
    esp_err_t err = esp_now_init(); // Initialize ESP-NOW
    if (err != ESP_OK) {
        Serial.println("ESP-NOW initialization failed");
        return; // Exit setup if initialization fails
    }
    esp_now_peer_info_t peerInfo = {}; // Create a peer info structure
    memcpy(peerInfo.peer_addr, MAC_ADRESS_ROUTER_ESP, sizeof(MAC_ADRESS_ROUTER_ESP)); // Set the peer address
    peerInfo.encrypt = false; // Disable encryption for simplicity
    err = esp_now_add_peer(&peerInfo); // Add the peer to the ESP-NOW network
    esp_now_register_send_cb(onDataSent); // Register the callback function for sending data
    Serial.println("Entering debugmode for Sender-ESP32");
}

void loop() {
    uint8_t dataToSend[1] = {1}; // Data to send, can be any byte array
    esp_now_send(MAC_ADRESS_ROUTER_ESP, dataToSend, sizeof(dataToSend)); // Send the data
    delay(1000); // Delay for 1 second before sending again

    if(sent_counter >= 30) { // Check if 100 data packets have been sent
        print_transmission_stats(); // Print the transmission statistics
        sent_counter = 0; // Reset the sent counter
        success_counter = 0; // Reset the success counter
        failed_counter = 0; // Reset the failed counter
    }
}
#endif