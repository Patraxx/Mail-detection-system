#include <Arduino.h>



#define OUTPUT_PIN 32

#define MULTIPLEX_A 26
#define MULTIPLEX_B 25
#define MULTIPLEX_C 33


int selectionArray[8][3] = {
  {0, 0, 0},
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 1},
  {1, 0, 0},
  {1, 0, 1},
  {1, 1, 0},
  {1, 1, 1}
};


void multiplex_selection_task(void *pvParameters) {
  Serial.println("Multiplex task started");

    while (1) {

      for (int i = 0; i < 8; i++) {
        digitalWrite(MULTIPLEX_A, selectionArray[i][0]);
        digitalWrite(MULTIPLEX_B, selectionArray[i][1]);
        digitalWrite(MULTIPLEX_C, selectionArray[i][2]);
        digitalRead(OUTPUT_PIN); 

        // Read from the OUTPUT_PIN
        int outputValue = digitalRead(OUTPUT_PIN);

        
        // Check if the pin is HIGH
        if (outputValue == HIGH) {
          Serial.print("Output ");
          Serial.print(i);
          Serial.println(" is HIGH");
        }
    }
    vTaskDelay(30 / portTICK_PERIOD_MS);
   
  }
  vTaskDelete(NULL);

}

void testPins(){

  digitalWrite(MULTIPLEX_A, HIGH);
  digitalWrite(MULTIPLEX_B, HIGH);
  digitalWrite(MULTIPLEX_C, HIGH);

}
void setup() {

  pinMode(OUTPUT_PIN, INPUT_PULLDOWN);
  pinMode(MULTIPLEX_A, OUTPUT);
  pinMode(MULTIPLEX_B, OUTPUT);
  pinMode(MULTIPLEX_C, OUTPUT);
  Serial.begin(9600);

  // xTaskCreate(multiplex_selection_task, "multiplex_selection_task", 2048, NULL, 1, NULL);

  // put your setup code here, to run once:

   testPins();



}


void loop() {

  int outputValue = digitalRead(OUTPUT_PIN);

  if (outputValue == HIGH) {
    Serial.println("Output is HIGH");
  }
 vTaskDelay(30 / portTICK_PERIOD_MS);
  // put your main code here, to run repeatedly:
}

