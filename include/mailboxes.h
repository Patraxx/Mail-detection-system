#ifndef MAILBOXES_H
#define MAILBOXES_H
#include <Arduino.h>
#include "main.h"


class Mailbox{
private:
     int sensorArray[3];
     int mailboxNumber;
     String mailboxName;
     bool mailDetected;

public:
    Mailbox(int mailboxNumber){
        this->mailboxNumber = mailboxNumber;
        this->mailDetected = false;
    }
    //skapa en constructor där 8 st fack skapas i taget, initialiseras med multiplexer_array
    Mailbox(int mailboxNumber, int sensorArray[3]){
        this->mailboxNumber = mailboxNumber;
        this->sensorArray[0] = sensorArray[0];
        this->sensorArray[1] = sensorArray[1];
        this->sensorArray[2] = sensorArray[2];
        this->mailDetected = false;
    }
};



#endif