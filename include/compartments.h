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


public:

    Compartment* compartments;
    int totalCompartments;
    int currentCompartment = 1; // Current compartment being scanned // Buffer for storing the CSV string

    CompartmentManager(int totalCompartments); 
    ~CompartmentManager();

    void initializeCompartments();
    void printCompartmentInfo();
    void currentCompartmentReset();
    void sendMailboxStatusBinary();
    void sendMailboxStatusCSV();


};
#endif