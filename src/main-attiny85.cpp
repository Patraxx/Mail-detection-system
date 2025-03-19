#include <Arduino.h>

#define PIN_1 0
#define PIN_2 1
#define PIN_3 2
#define PIN_4 3

int pins[] = {PIN_1, PIN_2, PIN_3, PIN_4};

void setup() {

    for (int i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);
    }
}

void loop() {

  
    digitalWrite(PIN_1, HIGH);
    delay(100);
    printf("LED ON\n");
    digitalWrite(PIN_1, LOW);
    delay(100);
   

  // put your main code here, to run repeatedly:
}
