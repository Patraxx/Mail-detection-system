#ifndef MAIN_H
#define MAIN_H
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#define ADC_MODE 1


#if ADC_MODE
  #define FINAL_INPUT 4  //ADC
  #define UNUSED_INPUT 18
#else
  #define FINAL_INPUT 18
  #define UNUSED_INPUT 4
#endif
#define MULTIPLEXER_1_DISABLE 21  //turn high to disable
#define MULTIPLEXER_2_DISABLE 22   //turn high to disable
#define MULTIPLEXER_3_DISABLE 23   //turn high to disable
#define MULTIPLEX_A 26
#define MULTIPLEX_B 25
#define MULTIPLEX_C 33



//TX: GPIO4, GPIO12, GPIO14, 

// RX: GPIO5, GPIO13, GPIO15, 

#define NUMBER_OF_COMPARTMENTS 16 // 8, 16, 24 ETC

extern TaskHandle_t mailboxPrinterTaskHandle; // Declare the task handle for mailbox printer task

extern SemaphoreHandle_t compartmentMutex;

const int multiplexer_disable_pins[2] = {MULTIPLEXER_1_DISABLE, MULTIPLEXER_2_DISABLE}; //lägg till om det behövs fler, detta är för 16 mailboxar

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
