#ifndef Compartments_H
#define Compartments_H
#include <Arduino.h>
#include "main.h"


class Compartment{
private:
     int sensorArray[3] = {0, 0, 0};
     int assigned_multiplexer = 0;
     int compartmentNumber = 0;
     String compartmentName = "None";
     bool mailDetected = false;

public:

 Compartment(){} //default constructor

    //skapa en constructor där 8 st fack skapas i taget, initialiseras med multiplexer_array
 Compartment(int CompartmentNumber, int sensorArray[3]){
        this-> compartmentNumber = CompartmentNumber;
        this->sensorArray[0] = sensorArray[0];
        this->sensorArray[1] = sensorArray[1];
        this->sensorArray[2] = sensorArray[2];
        this->mailDetected = false;
    }
    void setCompartmentName(String name){
        this->compartmentName = name;
    }
    String getCompartmentName(){
        return this->compartmentName;
    }
    void setMailDetected(bool detected){
        this->mailDetected = detected;
    }
    bool getMailDetected(){
        return this->mailDetected;
    }
    void setAssignedMultiplexer(int multiplexer){
        this->assigned_multiplexer = multiplexer;
    }
    int getAssignedMultiplexer(){
        return this->assigned_multiplexer;
    }

   static void compartmentCreator(Compartment compartments[], int amount);

   static void printCompartmentInfo(Compartment compartments[], int amount);

   
};
#endif