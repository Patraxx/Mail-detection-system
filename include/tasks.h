#ifndef TASKS_H
#define TASKS_H
#include <Arduino.h>
#include "main.h"


void multiplex_selection_task(void *pvParameters);
void multiplex_looper_cycle_task(void *pvParameters);
void debugPrinter(int i, int selectionArray[8][3]);

#endif // TASKS_H