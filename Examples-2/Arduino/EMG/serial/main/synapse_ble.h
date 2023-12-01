#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#pragma once

BLEServer* pServer;
BLECharacteristic* pCharacteristic;

const char* serviceUUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
const char* charUUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";

float sensorValue = 0.0;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("BLE Connection Established");
    }

    void onDisconnect(BLEServer* pServer) {
      Serial.println("BLE Disconnected");
    }
};

void setupBLE() {
  BLEDevice::init("EXG Synapse");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(BLEUUID(serviceUUID));

  pCharacteristic = pService->createCharacteristic(BLEUUID(charUUID), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLEUUID(serviceUUID));
  pAdvertising->start();
}
