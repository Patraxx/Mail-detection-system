#include "compartments.h"

CompartmentManager::CompartmentManager(int numCompartments) {
    totalCompartments = numCompartments;
    compartments = new Compartment[totalCompartments];
}

CompartmentManager::~CompartmentManager() {
    delete[] compartments;
}

void CompartmentManager::initializeCompartments() {
    for (int i = 0; i < totalCompartments; i++) {
        compartments[i].compartmentNumber = i + 1;
        compartments[i].assigned_multiplexer = i / 8 + 1; // Assign multiplexer (1-based index)
        compartments[i].sensorArray[0] = multiplexer_array[i % 8][0];
        compartments[i].sensorArray[1] = multiplexer_array[i % 8][1];
        compartments[i].sensorArray[2] = multiplexer_array[i % 8][2];
        compartments[i].compartmentName = "Compartment " + String(i + 1);
        compartments[i].mailDetected = false; // Default value
    }
}

void CompartmentManager::sendMailboxStatusCSV() {
  
        for (int i = 0; i < totalCompartments; i++) {
        Serial2.print(compartments[i].mailDetected ? "1" : "0"); // Send 1 if mail is detected, otherwise send 0
        if (i < totalCompartments - 1) {
            Serial2.print(","); // Add comma between values
        }  
    }
}

void CompartmentManager::printCompartmentInfo(){
    for (int i = 0; i < totalCompartments; i++){
        Serial.print("Compartment Number: ");
        Serial.println(compartments[i].compartmentNumber);
        Serial.print("Assigned Multiplexer: ");
        Serial.println(compartments[i].assigned_multiplexer);
        Serial.print("Sensor Array: ");
        Serial.print(compartments[i].sensorArray[0]);
        Serial.print(", ");
        Serial.print(compartments[i].sensorArray[1]);
        Serial.print(", ");
        Serial.println(compartments[i].sensorArray[2]);
        Serial.println();
    }
}

void CompartmentManager::currentCompartmentReset() {
    if (this->currentCompartment >= this->totalCompartments) {
        this->currentCompartment = 0; // Reset to the first compartment if we reach the end
    }
}

void CompartmentManager::sendMailboxStatusBinary() {
    uint16_t status = 0;

    // Encode the mailDetected status into a 16-bit integer
    for (int i = 0; i < this->totalCompartments; i++) {
        if (compartments[i].mailDetected) {
            status |= (1 << i); // Set the bit corresponding to the mailbox
        }
    }

    // Send the 16-bit status as two bytes
    Serial2.write((status >> 8) & 0xFF); // Send the high byte
    Serial2.write(status & 0xFF);        // Send the low byte
}