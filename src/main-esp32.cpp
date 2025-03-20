#include <Arduino.h>



#define TESTPIN 32

#define MULTIPLEX_A 26
#define MULTIPLEX_B 25
#define MULTIPLEX_C 33

#define OUTPU_0_BINARY 0b000
#define OUTPU_1_BINARY 0b001
#define OUTPU_2_BINARY 0b010
#define OUTPU_3_BINARY 0b011
#define OUTPU_4_BINARY 0b100
#define OUTPU_5_BINARY 0b101
#define OUTPU_6_BINARY 0b110
#define OUTPU_7_BINARY 0b111

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



  while (1) {

    for (int i = 0; i < 8; i++) {
      digitalWrite(MULTIPLEX_A, selectionArray[i][0]);
      digitalWrite(MULTIPLEX_B, selectionArray[i][1]);
      digitalWrite(MULTIPLEX_C, selectionArray[i][2]);
      vTaskDelay(20 / portTICK_PERIOD_MS);
    }


    // put your main code here, to run repeatedly:
   
    
    vTaskDelay(5/ portTICK_PERIOD_MS);
  }
}
void setup() {

  pinMode(TESTPIN, INPUT_PULLDOWN);
  Serial.begin(9600);

  // put your setup code here, to run once:



}


void loop() {

  

  // put your main code here, to run repeatedly:
}

