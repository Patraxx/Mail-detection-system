#include <Arduino.h>

#define LED_PIN 12
#define TIMER_PIN 14

int currentTime = 0;
int lastTime = 0;
int timeElapsed = 0;

void printTime() {
  currentTime = millis();
  timeElapsed = currentTime - lastTime;
  printf("Time Elapsed: %d\n", timeElapsed);
  lastTime = currentTime;
}

void setup() {

  pinMode(TIMER_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World");


}

void loop() {


  if (digitalRead(TIMER_PIN) == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    printTime();
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  




  // put your main code here, to run repeatedly:
}

