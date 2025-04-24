#include "ble_server.h"
// UUIDs for the BLE service and characteristic (must match the client)
#define SERVICE_UUID        "87654321-4321-4321-4321-cba987654321"
#define CHARACTERISTIC_UUID "dcba4321-8765-4321-8765-cba987654321"

// Global variables
BLECharacteristic *characteristic;

// Callback for when a client writes to the characteristic
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      Serial.print("Received value: ");
      Serial.println(value.c_str());
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE Server...");

  // Initialize BLE
  BLEDevice::init("ESP32_Server");

  // Create the BLE server
  BLEServer *server = BLEDevice::createServer();

  // Create the BLE service
  BLEService *service = server->createService(SERVICE_UUID);

  // Create the BLE characteristic
  characteristic = service->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_WRITE // Allow the client to write to this characteristic
  );

  // Set the callback for when the client writes to the characteristic
  characteristic->setCallbacks(new MyCharacteristicCallbacks());

  // Start the service
  service->start();

  // Start advertising
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->setScanResponse(true);
  advertising->setMinPreferred(0x06);  // Functions that help with iPhone connections
  advertising->setMinPreferred(0x12);
  advertising->start();

  Serial.println("BLE Server is running and advertising...");
}

void loop() {
  // Do nothing in the loop; the server runs in the background
}