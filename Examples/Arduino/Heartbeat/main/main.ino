
#include "synapse_ble.h"
#include "synapse.h"


const int sensorPin = 15; // Analog input pin
unsigned long previousMillis = 0; // Variable to store the last time a sample was taken
unsigned long interval = 4; // Interval between samples in milliseconds (1000 ms / 250 samples). Change as per requirement

synapse exg_synapse;

void setup(){
  Serial.begin(115200);
}

void loop(){ 
  unsigned long currentMillis = millis(); // Get the current time in milliseconds
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the current time as the last time a sample was taken
    float sensorValue = analogRead(sensorPin); // Read the sensor value
    float filters_out = exg_synapse.apply_ECG_filters(sensorValue); // generate output after applying filters
    bool beat = exg_synapse.detectPeak(filters_out); // Detect a beat
    Serial.print(filters_out);
    Serial.print("/t");
    Serial.println(beat);
  }
}