#include "Arduino.h"
#include "synapse_ble.h"
#include "synapse.h"

const int sensorPin = 15;  //EXG_Synapse OUT pin
unsigned long previousMillis = 0; 
unsigned long interval = 4; 
const float blinkThreshold = 400; // Adjust this threshold according to your eye blink, after visualizing
//                                   the EOG signal on visualizer first
const unsigned long debounceTime = 500; // 500 milliseconds for debounce- Next blink will be detected after 500 milliseconds
unsigned long lastBlinkTime = 0;

synapse exg_synapse;

void setup(){
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
}

//Function to detect eye blink
bool isBlink(float signal, unsigned long& lastBlinkTime, unsigned long currentTime) {
  if (signal > blinkThreshold && (currentTime - lastBlinkTime) > debounceTime) {
    lastBlinkTime = currentTime;
    return true;
  }
  return false;
}

void loop(){ 
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read and filter signal from the exg_synapse
    float sensorValue = analogRead(sensorPin);
    float filteredSignal = exg_synapse.apply_EOG_filters(sensorValue);
    Serial.println(filteredSignal);// Print signal for visualization
    if (isBlink(filteredSignal, lastBlinkTime, currentMillis)) {
      Serial.println("Blink Detected");
    }
  }
}


//After Flashing this code on your microcontroller, go the python script named
//"SpaceButton.py" change the COM PORT of your microcontroller there and run the script
//After you run the script, check weather blink is detected properly or not, after the blink is detected
//properly, open chrome dino game in your browser using this link "https://chromedino.com/" 
//and enjoy playing game with your eye blink 