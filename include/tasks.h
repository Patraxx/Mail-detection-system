#ifndef TASKS_H
#define TASKS_H
#include <Arduino.h>
#include "main.h"


void letter_detection_task(void *pvParameters);
void esp_now_task(void *pvParameters);
void blink_led_task(void *pvParameters);

#endif // 