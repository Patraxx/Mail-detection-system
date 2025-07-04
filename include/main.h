#ifndef MAIN_H
#define MAIN_H
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#define singleMultiplexerMode 0
#define debugMode 1
#define receiverCode 0



#define FINAL_INPUT 18 //ADC
#define ADC_PIN 4

#define MULTIPLEXER_0_DISABLE 21  //turn high to disable
#define MULTIPLEXER_1_DISABLE 22   //turn high to disable
#define MULTIPLEXER_2_DISABLE 23   //turn high to disable
#define MULTIPLEX_A 26
#define MULTIPLEX_B 25
#define MULTIPLEX_C 33
#define debugButton 13
#define greenLED 19

#define SERVICE_UUID_BOXSERVER        "87654321-4321-4321-4321-cba987654321"
#define CHARACTERISTIC_UUID_DEVICE_STATUS "dcba4321-8765-4321-8765-cba987654321"


//TX: GPIO12, GPIO14, 

// RX: GPIO13, GPIO15, 
#if singleMultiplexerMode
  #define NUMBER_OF_COMPARTMENTS 8 // 8, 16, 24 ETC
#else
  #define NUMBER_OF_COMPARTMENTS 24 // 8, 16, 24 ETC
#endif

extern TaskHandle_t mailboxPrinterTaskHandle; // Declare the task handle for mailbox printer task

extern SemaphoreHandle_t compartmentMutex;


 //rx 4e ner, TX 5:e ner, 
const int multiplexer_disable_pins[3] = {MULTIPLEXER_0_DISABLE, MULTIPLEXER_1_DISABLE, MULTIPLEXER_2_DISABLE}; //lägg till om det behövs fler, detta är för 16 mailboxar

const int multiplexer_array[8][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
  };
#endif // MAIN_H
