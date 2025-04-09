#ifndef MAIN_H
#define MAIN_H

#define FINAL_INPUT 18

#define MULTIPLEXER_1_DISABLE 17
#define MULTIPLEXER_2_DISABLE 5

#define MULTIPLEX_A 26
#define MULTIPLEX_B 25
#define MULTIPLEX_C 33

//TX: GPIO4, GPIO12, GPIO14, 

// RX: GPIO5, GPIO13, GPIO15, 

#define NUMBER_OF_COMPARTMENTS 16 // 8, 16, 24 ETC

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
