#ifndef TASKS_H
#define TASKS_H
#include <Arduino.h>
#include "main.h"
#include "compartments.h"


void multiplex_looper_task(void *pvParameters);
void debugPrinter(int i, int selectionArray[8][3]);
void letter_detection_task(void *pvParameters);
void mailbox_printer_task(void *pvParameters);
void sendMailBoxStatusCSV(HardwareSerial &serial, CompartmentManager* compartmentManager);

#endif // TASKS_H