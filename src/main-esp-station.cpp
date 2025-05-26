#include <Arduino.h>
#include "main.h"


// Create a struct_message called myData
struct_message myData;


/*

#define PUSHBULLET_TOKEN "YOUR_ACCESS_TOKEN"
#define PUSHBULLET_URL "https://api.pushbullet.com/v2/pushes"

const char *post_data = "{\"type\": \"note\", \"title\": \"Mailbox\", \"body\": \"You've got mail!\"}";

esp_http_client_config_t config = {
    .url = PUSHBULLET_URL,
};
esp_http_client_handle_t client = esp_http_client_init(&config);

esp_http_client_set_method(client, HTTP_METHOD_POST);
esp_http_client_set_header(client, "Access-Token", PUSHBULLET_TOKEN);
esp_http_client_set_header(client, "Content-Type", "application/json");
esp_http_client_set_post_field(client, post_data, strlen(post_data));

esp_http_client_perform(client);
esp_http_client_cleanup(client);


*/

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
 mailDetected = incomingData[0]; // Assuming the first byte indicates mail detection
 if (mailDetected) {
   Serial.println("Mail detected!");
   digitalWrite(greenLED, HIGH); // Turn on the LED to indicate mail detection
 } else {
   Serial.println("No mail detected.");
   digitalWrite(greenLED, LOW); // Turn off the LED
 }
}

void blinkDebugLED() {
  digitalWrite(greenLED, HIGH); // Turn on the LED
  delay(500); // Wait for 100 milliseconds
  digitalWrite(greenLED, LOW); // Turn off the LED
}


void setup(){

    pinMode(greenLED, OUTPUT); // Set the final input pin as input with pull-down resistorg
    Serial.begin(9600);
    delay(2000); // Wait for the serial connection to be established
    WiFi.mode(WIFI_STA); // Set the WiFi mode to station
    esp_now_init(); // Initialize ESP-NOW
    esp_now_register_recv_cb(OnDataRecv); // Register the callback function for receiving data

    Serial.println(WiFi.macAddress()); // Print the MAC address of the ESP32
    
}
void loop(){

  
}

// esp_err_t esp_now_register_recv_cb(esp_now_recv_cb_t cb);