#ifndef MAIN_H
#define MAIN_H
#include "sensors.h"

#define OUTPUT_PIN_1 18
#define OUTPUT_PIN_2 0
#define RAW_ADC_PIN 32
#define MULTIPLEXER_1_DISABLE 17
#define MULTIPLEXER_2_DISABLE 5

#define MULTIPLEX_A 26
#define MULTIPLEX_B 25
#define MULTIPLEX_C 33

#define CYCLE_PIN_BUTTON 13

#define NUMBER OF COMPARTMENTS 16 // 8, 16, 24 ETC

const int multiplexer_disable_pins[2] = {MULTIPLEXER_1_DISABLE, MULTIPLEXER_2_DISABLE}; //lägg till om det behövs fler, detta är för 16 mailboxar

#endif // MAIN_H
