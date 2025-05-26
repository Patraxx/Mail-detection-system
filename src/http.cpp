#include "http.h"

#define PUSHBULLET_TOKEN "o.Wzp43tQ6iZDGsHBdJkfQRnI1QOhTTQZU"
#define PUSHBULLET_URL "https://api.pushbullet.com/v2/pushes"



const char *post_data = "{\"type\": \"note\", \"title\": \"Mailbox\", \"body\": \"You've got mail!\"}";

esp_http_client_config_t config = {
    .url = PUSHBULLET_URL,
};
esp_http_client_handle_t client = esp_http_client_init(&config);

void http_setup(){

esp_http_client_set_method(client, HTTP_METHOD_POST);
esp_http_client_set_header(client, "Access-Token", PUSHBULLET_TOKEN);
esp_http_client_set_header(client, "Content-Type", "application/json");
esp_http_client_set_post_field(client, post_data, strlen(post_data));

esp_http_client_perform(client);
esp_http_client_cleanup(client);
}
void http_post(){
esp_http_client_perform(client);
esp_http_client_cleanup(client);

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

