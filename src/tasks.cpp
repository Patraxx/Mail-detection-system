#include "tasks.h"
#include "main.h"

int currentPinSelected = 0;


void multiplex_looper_task(void *pvParameters) {

  digitalWrite(MULTIPLEXER_1_DISABLE, LOW);
  digitalWrite(MULTIPLEXER_2_DISABLE, HIGH);
  Serial.println("Multiplex task started");

    while (1) {
      for (int i = 0; i < 8; i++) {      

          digitalWrite(MULTIPLEX_A, multiplexer_array[i][0]);
          digitalWrite(MULTIPLEX_B, multiplexer_array[i][1]);
          digitalWrite(MULTIPLEX_C, multiplexer_array[i][2]);
          vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    vTaskDelay(10/ portTICK_PERIOD_MS);   
  }
  vTaskDelete(NULL);
}

void letter_detection_task(void *pvParameters) {


  bool mailDetected = false;





}
