#include "compartments.h"


static void compartmentCreator(Compartment compartments[], int amount){

    
    for (int i = 0; i < amount; i++){
        compartments[i] = Compartment(i, multiplexer_array[i]);
        if(amount < 8){
            compartments[i].assigned_multiplexer = 1;         
        }
        
    }
}