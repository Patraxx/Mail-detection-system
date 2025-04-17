#ifndef GENERAL_H
#define GENERAL_H

#include <Arduino.h>
#include "main.h"
#include "compartments.h"

#define LED_PIN 12
#define TIMER_PIN 14

void timerloop();
void sendMailBoxStatusCSV(HardwareSerial &Serial, CompartmentManager* compartmentManager); // Function to send mailbox status as CSV
void continuousTestSerial(); // Function to send test message continuously

#endif // GENERAL_H
