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


  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World");


}

void loop() {

   for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], HIGH);
    delay(500);
    printf("LED ON\n");
    digitalWrite(pins[i], LOW);
    delay(500);
   }

  // put your main code here, to run repeatedly:
}
