#include <Arduino.h>



#define OUTPUT_PIN 32

#define MULTIPLEX_A 26
#define MULTIPLEX_B 25
#define MULTIPLEX_C 33

#define CYCLE_PIN_BUTTON 31

int currentPinSelected = 0;


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

void cyclePinButtonTask(void *pvParameters) {

  while(1)  {


    if(digitalRead(CYCLE_PIN_BUTTON) == HIGH) {
      currentPinSelected++;
      if(currentPinSelected > 7) {
        currentPinSelected = 0;
      }
      Serial.println("Current Pin Selected: " + String(currentPinSelected));
    }
    vTaskDelay(300/ portTICK_PERIOD_MS);
 
  }  





}
void multiplex_selection_task(void *pvParameters) {
  Serial.println("Multiplex task started");

    while (1) {

      for (int i = 0; i < 8; i++) {
        digitalWrite(MULTIPLEX_A, selectionArray[i][0]);
        digitalWrite(MULTIPLEX_B, selectionArray[i][1]);
        digitalWrite(MULTIPLEX_C, selectionArray[i][2]);

        Serial.print("Current Button is: " + String(i));
        Serial.println(" || Status " + String(digitalRead(OUTPUT_PIN)));

        vTaskDelay(500 / portTICK_PERIOD_MS);
        // Read from the OUTPUT_PI
    }
    


  }
  vTaskDelete(NULL);

}

void testPins(){

  digitalWrite(MULTIPLEX_A, HIGH);
  digitalWrite(MULTIPLEX_B, LOW);
  digitalWrite(MULTIPLEX_C, LOW);

}
void setup() {

  pinMode(OUTPUT_PIN, INPUT_PULLDOWN);
  pinMode(CYCLE_PIN_BUTTON, INPUT_PULLDOWN);
  pinMode(MULTIPLEX_A, OUTPUT);
  pinMode(MULTIPLEX_B, OUTPUT);
  pinMode(MULTIPLEX_C, OUTPUT);
  Serial.begin(9600);

   xTaskCreate(multiplex_selection_task, "multiplex_selection_task", 2048, NULL, 1, NULL);

  // put your setup code here, to run once:

  // testPins();



}


void loop() {

}

