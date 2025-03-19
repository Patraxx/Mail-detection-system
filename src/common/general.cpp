
#include "general.h"

bool timerRunning = false;
unsigned long startTime = 0;

void timerloop(){


    static bool lastTimerState = LOW;

  bool currentTimerState = digitalRead(TIMER_PIN);

  if (currentTimerState == HIGH && lastTimerState == LOW) {
     startTime = millis();
      timerRunning = true;
      digitalWrite(LED_PIN, HIGH);

  } else if (currentTimerState == LOW && lastTimerState == HIGH) {
     if (timerRunning) {
      unsigned long elapsedTime = millis() - startTime;

      printf("Timer elapsed time: %lu\n", elapsedTime);
      timerRunning = false;
      digitalWrite(LED_PIN, LOW);
      }    
  }


 lastTimerState = currentTimerState;
}



