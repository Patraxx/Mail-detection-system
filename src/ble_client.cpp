#include "ble_client.h"

static NimBLEAdvertisedDevice* targetDevice = nullptr;
static NimBLEClient* pClient = nullptr;

// Replace with your actual UUIDs
static NimBLEUUID serviceUUID("12345678-1234-1234-1234-1234567890ab");
static NimBLEUUID charUUID("abcd1234-5678-90ab-cdef-1234567890ab");

unsigned long lastWriteTime = 0;
const unsigned long interval = 60 * 1000; // 1 minute

void writeMailboxStatuses() {
  if (!pClient || !pClient->isConnected()) return;

  NimBLERemoteService* pService = pClient->getService(serviceUUID);
  if (!pService) {
    Serial.println("Service not found");
    return;
  }

  NimBLERemoteCharacteristic* pChar = pService->getCharacteristic(charUUID);
  if (!pChar) {
    Serial.println("Characteristic not found");
    return;
  }

  // Replace this with your real mailbox data
  uint8_t mailboxes[30] = {
    1,0,0,1,1,0,1,1,0,0,
    1,1,0,1,0,1,1,1,0,0,
    1,1,1,0,1,0,0,0,1,1
  };

  if (pChar->canWrite()) {
    pChar->writeValue(mailboxes, sizeof(mailboxes), false); // no response
    Serial.println("Wrote mailbox statuses.");
  }
}

class AdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice* advDevice) override {
    if (advDevice->getName() == "MailboxServerUnit") {  // Replace with real name
      Serial.println("Found target device, stopping scan...");
      NimBLEDevice::getScan()->stop();
      targetDevice = advDevice;
    }
  }
};

void connectAndWrite() {
  pClient = NimBLEDevice::createClient();

  if (!pClient->connect(targetDevice)) {
    Serial.println("Failed to connect");
    return;
  }

  Serial.println("Connected!");
  writeMailboxStatuses();
  pClient->disconnect();
  Serial.println("Disconnected.");
}

void clientBLEtask(void* pvParameters) {
  NimBLEDevice::init("");
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastWriteTime >= interval || lastWriteTime == 0) {
    Serial.println("Scanning for server...");
    targetDevice = nullptr;

    NimBLEScan* scan = NimBLEDevice::getScan();
    scan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
    scan->setActiveScan(true);
    scan->start(5, false); // Scan for 5 seconds

    unsigned long scanStart = millis();
    while (!targetDevice && (millis() - scanStart) < 6000) {
      delay(100);
    }

    if (targetDevice) {
      connectAndWrite();
    } else {
      Serial.println("Target device not found.");
    }

    lastWriteTime = millis();
  }

  delay(100);
}
