#include "ble_logging.h"


static BLEAddress *serverAddress = nullptr; // Address of the BLE server
static BLERemoteCharacteristic *remoteCharacteristic = nullptr; // Remote characteristic to write to
bool doConnect = false; // Flag to trigger connection
bool connected = false; // Connection status

// UUIDs for the BLE service and characteristic (replace with your server's UUIDs)
#define SERVICE_UUID        "87654321-4321-4321-4321-cba987654321"
#define CHARACTERISTIC_UUID "dcba4321-8765-4321-8765-cba987654321"

// Callback for when a BLE device is discovered
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("Discovered device: ");
    Serial.println(advertisedDevice.toString().c_str());

    // Check if the discovered device matches the server's service UUID
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(BLEUUID(SERVICE_UUID))) {
      serverAddress = new BLEAddress(advertisedDevice.getAddress());
      doConnect = true; // Set the flag to connect
      Serial.println("Found matching server. Connecting...");
    }
  }
};

// Function to connect to the BLE server
void connectToServer() {
  Serial.println("Connecting to server...");
  BLEClient *client = BLEDevice::createClient();
  Serial.println("Client created");

  // Connect to the server
  if (client->connect(*serverAddress)) {
    Serial.println("Connected to server");
    connected = true;

    // Get the service and characteristic
    BLERemoteService *remoteService = client->getService(BLEUUID(SERVICE_UUID));
    if (remoteService == nullptr) {
      Serial.println("Failed to find service");
      client->disconnect();
      return;
    }

    remoteCharacteristic = remoteService->getCharacteristic(BLEUUID(CHARACTERISTIC_UUID));
    if (remoteCharacteristic == nullptr) {
      Serial.println("Failed to find characteristic");
      client->disconnect();
      return;
    }

    Serial.println("Characteristic found");
  } else {
    Serial.println("Failed to connect to server");
  }
}

// Function to send a string to the server
void sendString(const std::string &data) {
  if (connected && remoteCharacteristic != nullptr) {
    remoteCharacteristic->writeValue(data);
  } else {
    Serial.println("Not connected to server or characteristic not found");
  }
}

void setupBLEClient() {
  Serial.println("Initializing BLE client...");
  BLEDevice::init("ESP32_Client"); // Initialize the BLE device with a name

  // Start scanning for BLE devices
  BLEScan *scan = BLEDevice::getScan();
  scan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  scan->setInterval(100);
  scan->setWindow(99);
  scan->start(5, false); // Scan for 5 seconds
}

void loopBLEClient() {
  if (doConnect && !connected) {
    connectToServer(); // Attempt to connect to the server
    doConnect = false; // Reset the flag
  }

  if (connected) {
    sendString("Hello from ESP32 Client!"); // Send a string to the server
    delay(5000); // Wait 5 seconds before sending again
  }
}