#include <Arduino.h>
#include "main.h"
#include "tasks.h"
#include "compartments.h"

CompartmentManager compartmentManager(NUMBER_OF_COMPARTMENTS);

SemaphoreHandle_t compartmentMutex; // Declare the mutex for compartment access

TaskHandle_t mailboxPrinterTaskHandle; // Declare the task handle for mailbox printer task

void receiveAndDecodeMailboxStatus(uint8_t* statusbyteOne, uint8_t* statusbyteTwo) {
  

      uint16_t status = (highByte << 8) | lowByte;

      Serial.print("Received status: 0x");
      Serial.println(status, HEX);

      // Check each bit
      for (int i = 0; i < 16; i++) {
          bool hasMail = (status >> i) & 0x01;
          Serial.print("Mailbox ");
          Serial.print(i);
          Serial.print(": ");
          Serial.println(hasMail ? "📬 Mail" : "📭 Empty");
      }
  }
}

void setup() {

  pinMode(FINAL_INPUT, INPUT_PULLDOWN); 
  pinMode(MULTIPLEXER_1_DISABLE, OUTPUT);
  pinMode(MULTIPLEXER_2_DISABLE, OUTPUT);
  pinMode(MULTIPLEX_A, OUTPUT);
  pinMode(MULTIPLEX_B, OUTPUT);
  pinMode(MULTIPLEX_C, OUTPUT);


  Serial.begin(9600);
  delay(1000);

  compartmentMutex = xSemaphoreCreateMutex(); // Create a mutex for compartment access
  if (compartmentMutex == NULL) {
    Serial.println("Failed to create mutex");
  } else {
    Serial.println("Mutex created successfully");
  }

  xTaskCreate(multiplex_looper_task, "Multiplex Task", 10000, &compartmentManager, 1, NULL);
  xTaskCreate(mailbox_printer_task, "Mailbox Printer Task", 10000, &compartmentManager, 1, &mailboxPrinterTaskHandle); // Create the mailbox printer task


}

void loop() {
  

}

