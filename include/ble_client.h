#ifndef BLE_CLIENT_H
#define BLE_CLIENT_H
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEClient.h>
#include <BLEAdvertisedDevice.h>
#include <NimBLEDevice.h>
#include "main.h"
#include "compartments.h"
#include "tasks.h"




void clientBLEtask(void *pvParameters);
void writeMailboxStatuses();
void connectAndWrite();

class AdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
    public:
        void onResult(NimBLEAdvertisedDevice* advertisedDevice) override;
    };





#endif