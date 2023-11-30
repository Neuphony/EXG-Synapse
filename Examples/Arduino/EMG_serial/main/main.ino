#define SAMPLE_RATE 500
#define INPUT_PIN 15

 
/// Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
// Sampling rate: 500.0 Hz, frequency: [75.5, 149.5] Hz.
// Filter is order 4, implemented as second-order sections (biquads).
// Reference: https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
float emg_filter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.05615394*z1 - 0.37044590*z2;
    output = 0.01777130*x + 0.03554260*z1 + 0.01777130*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.52642081*z1 - 0.40238318*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.47444498*z1 - 0.71086010*z2;
    output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.98462817*z1 - 0.74630556*z2;
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
void setup() {
  // Serial connection begin
  Serial.begin(115200);
}
 
void loop() {
  unsigned long currentMillis = millis(); // Get the current time in milliseconds
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the current time as the last time a sample was taken
    float sensorValue = analogRead(sensorPin); // Read the sensor value
    float filters_out = apply_filters(sensorValue); // generate output after applying filters
    Serial.println(filters_out); // Print the sensor value
  }
}