#ifndef Compartments_H
#define Compartments_H
#include <Arduino.h>
#include "main.h"


class Compartments{
private:
     int sensorArray[3];
     int CompartmentNumber;
     String CompartmentName;
     bool mailDetected;

public:
 Compartments(int CompartmentNumber){
        this-> CompartmentNumber = CompartmentNumber;
        this->mailDetected = false;
    }
    //skapa en constructor där 8 st fack skapas i taget, initialiseras med multiplexer_array
 Compartments(int CompartmentNumber, int sensorArray[3]){
        this-> CompartmentNumber = CompartmentNumber;
        this->sensorArray[0] = sensorArray[0];
        this->sensorArray[1] = sensorArray[1];
        this->sensorArray[2] = sensorArray[2];
        this->mailDetected = false;
    }
};
#endif