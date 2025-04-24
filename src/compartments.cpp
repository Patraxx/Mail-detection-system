#include "compartments.h"

CompartmentManager::CompartmentManager(int numCompartments) {
    totalCompartments = numCompartments;
    compartments = new Compartment[totalCompartments];
    csvString.reserve(100); // Reserve space for the CSV string
}

CompartmentManager::~CompartmentManager() {
    delete[] compartments;
}

void CompartmentManager::initializeCompartments() {
    for (int i = 0; i < totalCompartments; i++) {
        compartments[i].compartmentNumber = i + 1;
        compartments[i].assigned_multiplexer = i / 8; // Assign multiplexer (1-based index)
        compartments[i].sensorArray[0] = multiplexer_array[i % 8][0];
        compartments[i].sensorArray[1] = multiplexer_array[i % 8][1];
        compartments[i].sensorArray[2] = multiplexer_array[i % 8][2];
        compartments[i].compartmentName = "Compartment " + String(i + 1);
        compartments[i].mailDetected = false; // Default value
    }
}

void CompartmentManager::updateCSVString() {
    csvString = ""; // Clear the previous CSV string
    for (int i = 0; i < totalCompartments; i++) {
        csvString += String(compartments[i].mailDetected ? "1" : "0"); // Add 1 or 0 based on mail detection
        if (i < totalCompartments - 1) {
            csvString += ","; // Add comma between values
        }
    }
    Serial.println(csvString); // Print the CSV string to the serial monitor
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