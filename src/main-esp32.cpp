#include <Arduino.h>



#define OUTPUT_PIN 32
#define MULTIPLEXER_1_DISABLE 17
#define MULTIPLEXER_2_DISABLE 5

#define MULTIPLEX_A 26
#define MULTIPLEX_B 25
#define MULTIPLEX_C 33

#define CYCLE_PIN_BUTTON 13

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


void multiplex_looper_cycle_task(void *pvParameters) {
  Serial.println("Multiplex task started");

    while (1) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(MULTIPLEX_A, selectionArray[i][0]);
        digitalWrite(MULTIPLEX_B, selectionArray[i][1]);
        digitalWrite(MULTIPLEX_C, selectionArray[i][2]);  
    }
    vTaskDelay(10/ portTICK_PERIOD_MS);   
  }
  vTaskDelete(NULL);
}


void debugPrinter(int i, int selectionArray[8][3]){

    Serial.print("Selection: ");
    Serial.print(" ");
    Serial.print(selectionArray[i][0]);
    Serial.print(" ");
    Serial.print(selectionArray[i][1]);
    Serial.print(" ");
    Serial.println(selectionArray[i][2]);
   
}
void multiplex_selection_task(void *pvParameters) {
  Serial.println("Multiplex task started");

        digitalWrite(MULTIPLEX_A, selectionArray[currentPinSelected][0]);
        digitalWrite(MULTIPLEX_B, selectionArray[currentPinSelected][1]);
        digitalWrite(MULTIPLEX_C, selectionArray[currentPinSelected][2]);

  while (1) {


    if (digitalRead(CYCLE_PIN_BUTTON) == HIGH) 
      // Debounce the button press
    
      if (digitalRead(CYCLE_PIN_BUTTON) == HIGH) {
        currentPinSelected++;
        if (currentPinSelected > 7) {
          currentPinSelected = 0;
        }
        vTaskDelay(150 / portTICK_PERIOD_MS);
  
        // Set the multiplex pins according to the current selection
        digitalWrite(MULTIPLEX_A, selectionArray[currentPinSelected][0]);
        digitalWrite(MULTIPLEX_B, selectionArray[currentPinSelected][1]);
        digitalWrite(MULTIPLEX_C, selectionArray[currentPinSelected][2]);

        debugPrinter(currentPinSelected, selectionArray);
      }
      vTaskDelay(5/ portTICK_PERIOD_MS);
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
  pinMode(MULTIPLEXER_1_DISABLE, OUTPUT);
  pinMode(MULTIPLEXER_2_DISABLE, OUTPUT);
  pinMode(CYCLE_PIN_BUTTON, INPUT_PULLDOWN);
  pinMode(MULTIPLEX_A, OUTPUT);
  pinMode(MULTIPLEX_B, OUTPUT);
  pinMode(MULTIPLEX_C, OUTPUT);
  Serial.begin(9600);
  delay(500);

   xTaskCreate(multiplex_selection_task, "multiplex_selection_task", 2048, NULL, 1, NULL);

  // put your setup code here, to run once:

  // testPins();



}


void loop() {

}

