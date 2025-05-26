#include "http.h"

#define PUSHBULLET_TOKEN "o.yo5tXDqVNx2LLWGejNJFnmnJ1vNiPbVF"
#define PUSHBULLET_URL "https://api.pushbullet.com/v2/pushes"
#include "esp_crt_bundle.h"
#include <WiFiClientSecure.h>






void http_post(){
    WiFiClientSecure  client;
    client.setInsecure(); // Disable SSL certificate verification for testing purposes
    HTTPClient http;

    http.begin("https://api.pushbullet.com/v2/pushes");

    http.addHeader("Access-Token", PUSHBULLET_TOKEN);
    http.addHeader("Content-Type", "application/json");

    const char *postData = "{\"type\": \"note\", \"title\": \"Mailbox\", \"body\": \"You've got mail!\"}";

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
        String response = http.getString(); // Get the response from the server
        Serial.println("HTTP Response code: " + String(httpResponseCode));
        Serial.println("Response: " + response);
    } else {
        Serial.println("Error in HTTP request: " + String(httpResponseCode));
    }
    http.end(); // Close the connection
}

void wifi_setup() {
    WiFi.mode(WIFI_STA); // Set the WiFi mode to station
    WiFi.begin(hemma_sssid, hemma_password); // Connect to the WiFi network
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000); // Wait for connection
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void http_post_task(void *pvParameters) {
    while (true) {

        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY); // Wait for notification from the letter detection task
        if (mailDetected) {
            Serial.println("Sending HTTP POST request for mail detection");
            http_post(); // Call the function to perform the HTTP POST request
        } else {
            Serial.println("No mail detected, skipping HTTP POST request");
        }
    }
    vTaskDelete(NULL); // Delete the task when done
}

