#ifndef MAIN_H
#define MAIN_H
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "wifi.h"
#include "esp_now.h"
#include "esp_wifi.h"

#define hemma_sssid "Cedelerium"
#define hemma_password "kaffemongo"
#define debugMode 1
#define receiverCode 0

static const uint8_t MAC_ADRESS_ROUTER_ESP[6] = {0x8c, 0x4b, 0x14, 0x14, 0x73, 0xb8};
static const uint8_t MAC_ADRESS_SENDER_ESP[6] = {0x8c, 0x4b, 0x14, 0x15, 0xb3, 0x64}; // This is the MAC address of the ESP32 that will send the data


//8c:4b:14:15:b3:64


#define FINAL_INPUT 18 //ADC


#define debugButton 14
#define greenLED 19

#define detectionTime 2000


void blinkDebugLED();


extern SemaphoreHandle_t compartmentMutex;

extern TaskHandle_t letterDetectionTaskHandle;
extern TaskHandle_t espNowTaskHandle;
extern TaskHandle_t httpPostTaskHandle;

extern volatile bool mailDetected;
extern volatile bool esp_now_message_sent;



#endif