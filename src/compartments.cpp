#include "compartments.h"


void Compartment::compartmentCreator(Compartment compartments[], int amount){

    
    for (int i = 0; i < amount; i++){
        compartments[i] = Compartment(i+1, multiplexer_array[i % 8]);

        int assignedmultiplexer = i / 8 +1; 
        compartments[i].setAssignedMultiplexer(assignedmultiplexer);

        String compartmentName = "Compartment " + String(i+1);
        compartments[i].setCompartmentName(compartmentName);
        
    }
}

void Compartment::printCompartmentInfo(Compartment compartments[], int amount){
    for (int i = 0; i < amount; i++){
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