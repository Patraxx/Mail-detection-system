#ifndef Compartments_H
#define Compartments_H
#include <Arduino.h>
#include "main.h"



struct Compartment {
    int sensorArray[3] = {0, 0, 0};
    int assigned_multiplexer = 0;
    int compartmentNumber = 0;
    String compartmentName = "None";
    bool mailDetected = false;
};


class CompartmentManager{
 
private: 
    Compartment* compartments;
    int totalCompartments;

public:

    CompartmentManager(int totalCompartments); 


    ~CompartmentManager();

    void initializeCompartments();
    void printCompartmentInfo();


};
#endif