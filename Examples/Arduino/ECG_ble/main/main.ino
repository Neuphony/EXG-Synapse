#include "synapse_ble.h"

const int sensorPin = A0; // Analog input pin
unsigned long previousMillis = 0; // Variable to store the last time a sample was taken
unsigned long interval = 4; // Interval between samples in milliseconds (1000 ms / 250 samples). Change as per requirement

// Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
// Sampling rate: 250.0 Hz, frequency: [0.5, 40.5] Hz.
// Filter is order 4, implemented as second-order sections (biquads).
// Reference: https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
float ecg_filter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - -0.60733220*z1 - 0.12650924*z2;
    output = 0.02287021*x + 0.04574042*z1 + 0.02287021*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.79989305*z1 - 0.51645386*z2;
    output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.97652009*z1 - 0.97668236*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.99042357*z1 - 0.99058175*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}

// Used a Band-Stop Butterworth IIR digital filter, generated using filter_gen.py to reject 50 Hz noise
// Sampling rate: 250.0 Hz, frequency: [49.0, 51.0] Hz.
// Filter is order 4, implemented as second-order sections (biquads).
// Reference: https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
float bandstop_filter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - -0.58621390*z1 - 0.95447062*z2;
    output = 0.93642755*x + -0.57892689*z1 + 0.93642755*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.62207340*z1 - 0.95474810*z2;
    output = 1.00000000*x + -0.61822923*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.56822557*z1 - 0.98081132*z2;
    output = 1.00000000*x + -0.61822923*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.65580392*z1 - 0.98109606*z2;
    output = 1.00000000*x + -0.61822923*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}

float apply_filters(float input_signal){
  float ecg_filter_out = ecg_filter(input_signal);
  float band_stop_out = bandstop_filter(ecg_filter_out);
  return band_stop_out;
}

void setup() {
  Serial.begin(115200); // Initialise serial communication
  setupBLE();
}

void loop() {
  uint8_t * value;
  unsigned long currentMillis = millis(); // Get the current time in milliseconds
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the current time as the last time a sample was taken
    float sensorValue = analogRead(sensorPin); // Read the sensor value
    float filters_out = apply_filters(sensorValue); // generate output after applying filters
    pCharacteristic->setValue(filters_out); // Send Data over BLE
    pCharacteristic->notify();
  }
}



