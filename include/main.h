#ifndef MAIN_H
#define MAIN_H
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "wifi.h"
#include "esp_now.h"

#define hemma_sssid "Cedelerium"
#define hemma_password "kaffemongo"
#define debugMode 1
#define receiverCode 0

static const uint8_t MAC_ADRESS_ROUTER_ESP[6] = {0x8c, 0x4b, 0x14, 0x14, 0x73, 0xb8};

#define sender_mac_address "8c:4b:14:15:b3:64"


#define FINAL_INPUT 18 //ADC


#define debugButton 14
#define greenLED 19

#define detectionTime 2000


void blinkDebugLED();


extern SemaphoreHandle_t compartmentMutex;

extern TaskHandle_t letterDetectionTaskHandle;
extern TaskHandle_t espNowTaskHandle;

extern volatile bool mailDetected;
extern volatile bool esp_now_message_sent;

typedef struct struct_message {
    char a[32];
    int b;
    float c;
    bool d;
} struct_message;

typedef struct ESP_MAIL_BOOL {
    bool mailDetected;
} ESP_MAIL_BOOL;


#endif