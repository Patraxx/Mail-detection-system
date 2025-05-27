#include "http.h"

#define PUSHBULLET_TOKEN "o.yo5tXDqVNx2LLWGejNJFnmnJ1vNiPbVF"
#define PUSHBULLET_URL "https://api.pushbullet.com/v2/pushes"
#include "esp_crt_bundle.h"
#include <WiFiClientSecure.h>
#include "esp_log.h"


#define TAG "HTTP"



void http_post() {

    WiFiClientSecure client;
    client.setInsecure(); // Disable SSL certificate verification for testing purposes
    HTTPClient http;
    http.begin(client, "https://api.pushbullet.com/v2/pushes");
    http.addHeader("Access-Token", PUSHBULLET_TOKEN);
    http.addHeader("Content-Type", "application/json");
    const char *postData = "{\"type\": \"note\", \"title\": \"Mailbox\", \"body\": \"You've got mail!\"}";
    http.POST(postData);
    http.end(); // Close the connection
}

void wifi_setup() {
    esp_log_level_set(TAG, ESP_LOG_INFO); // Set the log level for this tag
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
        // kolla om det blockar
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY); // Wait for notification from the letter detection task

        Serial.printf("Free stack before post: %d bytes\n", uxTaskGetStackHighWaterMark(NULL) * 4);
        if (mailDetected) {
           
            http_post(); // Call the function to perform the HTTP POST request

            Serial.printf("Free stack after post: %d bytes\n", uxTaskGetStackHighWaterMark(NULL) * 4);
        } else {
            Serial.println("No mail detected, skipping HTTP POST request");
        }
    }
    vTaskDelete(NULL); // Delete the task when done
}

