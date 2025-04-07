#include "compartments.h"


static void compartmentCreator(Compartment compartments[], int amount){

    
    for (int i = 0; i < amount; i++){
        compartments[i] = Compartment(i+1, multiplexer_array[i % 8]);

        int assignedmultiplexer = i / 8 +1; 
        compartments[i].setAssignedMultiplexer(assignedmultiplexer);

        String compartmentName = "Compartment " + String(i+1);
        compartments[i].setCompartmentName(compartmentName);
        
    }
}