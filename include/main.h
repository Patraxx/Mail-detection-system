#ifndef MAIN_H
#define MAIN_H
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "wifi.h"
#include "esp_now.h"
#define singleMultiplexerMode 0
#define debugMode 1
#define receiverCode 0¨

#define MAC_ADRESS_ROUTER_ESP "8c:4b:14:14:73:b8"



#define FINAL_INPUT 18 //ADC
#define ADC_PIN 4


#define debugButton 13
#define greenLED 19

#define SERVICE_UUID_BOXSERVER        "87654321-4321-4321-4321-cba987654321"
#define CHARACTERISTIC_UUID_DEVICE_STATUS "dcba4321-8765-4321-8765-cba987654321"


extern TaskHandle_t mailboxPrinterTaskHandle; // Declare the task handle for mailbox printer task

extern SemaphoreHandle_t compartmentMutex;

extern volatile bool mailDetected;
extern volatile bool esp_now_message_sent;


#endif