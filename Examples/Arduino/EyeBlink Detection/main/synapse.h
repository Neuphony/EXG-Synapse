#pragma once
#ifndef SYNAPSE_H
#define SYNAPSE_H
#include <math.h>
#include "CircularBuffer.h"

#define DATA_LENGTH 16

int dataIndex = 0;
bool isPeak = false;

class synapse {
  public:
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

    // Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
    // Sampling rate: 250.0 Hz, frequency: [0.5, 47.0] Hz.
    // Filter is order 4, implemented as second-order sections (biquads).
    // Reference: https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
    float eeg_filter(float input)
    {
      float output = input;
      {
        static float z1, z2; // filter section state
        float x = output - -0.42615248*z1 - 0.08290189*z2;
        output = 0.03701685*x + 0.07403370*z1 + 0.03701685*z2;
        z2 = z1;
        z1 = x;
      }
      {
        static float z1, z2; // filter section state
        float x = output - -0.56685322*z1 - 0.48368568*z2;
        output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
        z2 = z1;
        z1 = x;
      }
      {
        static float z1, z2; // filter section state
        float x = output - -1.97658291*z1 - 0.97674412*z2;
        output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
        z2 = z1;
        z1 = x;
      }
      {
        static float z1, z2; // filter section state
        float x = output - -1.99039779*z1 - 0.99055580*z2;
        output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
        z2 = z1;
        z1 = x;
      }
      return output;
    }

  // Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
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

    // Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
    // Sampling rate: 250.0 Hz, frequency: [0.05, 15.05] Hz.
    // Filter is order 4, implemented as second-order sections (biquads).
    // Reference: https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
    float eog_filter(float input)
    {
      float output = input;
      {
        static float z1, z2; // filter section state
        float x = output - -1.38913662*z1 - 0.49357294*z2;
        output = 0.00080636*x + 0.00161272*z1 + 0.00080636*z2;
        z2 = z1;
        z1 = x;
      }
      {
        static float z1, z2; // filter section state
        float x = output - -1.63002094*z1 - 0.75376141*z2;
        output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
        z2 = z1;
        z1 = x;
      }
      {
        static float z1, z2; // filter section state
        float x = output - -1.99766835*z1 - 0.99766994*z2;
        output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
        z2 = z1;
        z1 = x;
      }
      {
        static float z1, z2; // filter section state
        float x = output - -1.99904157*z1 - 0.99904315*z2;
        output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
        z2 = z1;
        z1 = x;
      }
      return output;
    }

    /**
   * @brief Removes AC noise from the input signal.
   *
   * This function filters out AC noise from the given input signal using
   * specified methods or algorithms based on the 'type' parameter.
   * Used a Band-Stop Butterworth IIR digital filter, generated using filter_gen.py to reject 50 Hz noise
   * Sampling rate: 500.0 Hz, frequency: [49.0, 51.0] Hz for type = 50
   * Sampling rate: 500.0 Hz, frequency: [59.0, 61.0] Hz. for type = 60
   * Filter is order 4, implemented as second-order sections (biquads).
   * Reference: https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
   *
   * @param type   An integer indicating the type/method of noise removal.
   * @param input  The input signal with AC noise.
   * @return       The filtered signal without AC noise as a float.
 */
    float remove_AC_noise_EMG(uint8_t type, float input)
    {
      float output;
      switch(type){
        case 50:
        output = input; 
        {
          static float z1, z2; // filter section state
          float x = output - -1.59384315*z1 - 0.97689595*z2;
          output = 0.96769481*x + -1.56588673*z1 + 0.96769481*z2;
          z2 = z1;
          z1 = x;
        }
        {
          static float z1, z2; // filter section state
          float x = output - -1.60526422*z1 - 0.97719645*z2;
          output = 1.00000000*x + -1.61816175*z1 + 1.00000000*z2;
          z2 = z1;
          z1 = x;
        }
        {
          static float z1, z2; // filter section state
          float x = output - -1.59649601*z1 - 0.99027671*z2;
          output = 1.00000000*x + -1.61816175*z1 + 1.00000000*z2;
          z2 = z1;
          z1 = x;
        }
        {
          static float z1, z2; // filter section state
          float x = output - -1.62390790*z1 - 0.99058117*z2;
          output = 1.00000000*x + -1.61816175*z1 + 1.00000000*z2;
          z2 = z1;
          z1 = x;
        }
        return output;

        case 60:
        output = input;
        {
          static float z1, z2; // filter section state
          float x = output - -1.43469171*z1 - 0.97692996*z2;
          output = 0.96769481*x + -1.41094972*z1 + 0.96769481*z2;
          z2 = z1;
          z1 = x;
        }
        {
          static float z1, z2; // filter section state
          float x = output - -1.44787927*z1 - 0.97716243*z2;
          output = 1.00000000*x + -1.45805238*z1 + 1.00000000*z2;
          z2 = z1;
          z1 = x;
        }
        {
          static float z1, z2; // filter section state
          float x = output - -1.43497551*z1 - 0.99031116*z2;
          output = 1.00000000*x + -1.45805238*z1 + 1.00000000*z2;
          z2 = z1;
          z1 = x;
        }
        {
          static float z1, z2; // filter section state
          float x = output - -1.46678483*z1 - 0.99054671*z2;
          output = 1.00000000*x + -1.45805238*z1 + 1.00000000*z2;
          z2 = z1;
          z1 = x;
        }
        return output;
      }
    }
     /**
   * @brief Removes AC noise from the input signal.
   *
   * This function filters out AC noise from the given input signal using
   * specified methods or algorithms based on the 'type' parameter.
   * Used a Band-Stop Butterworth IIR digital filter, generated using filter_gen.py to reject 50 Hz noise
   * Sampling rate: 250.0 Hz, frequency: [49.0, 51.0] Hz for type = 50
   * Sampling rate: 250.0 Hz, frequency: [59.0, 61.0] Hz. for type = 60
   * Filter is order 4, implemented as second-order sections (biquads).
   * Reference: https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
   *
   * @param type   An integer indicating the type/method of noise removal.
   * @param input  The input signal with AC noise.
   * @return       The filtered signal without AC noise as a float.
 */
    float remove_AC_noise(uint8_t type, float input)
    {
      float output;
      switch(type){
        case 50:
        output = input; 
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

        case 60:
        output = input;
        float output = input;
        {
          static float z1, z2; // filter section state
          float x = output - -0.10398666*z1 - 0.95458249*z2;
          output = 0.93642755*x + -0.11763470*z1 + 0.93642755*z2;
          z2 = z1;
          z1 = x;
        }
        {
          static float z1, z2; // filter section state
          float x = output - -0.14153054*z1 - 0.95463621*z2;
          output = 1.00000000*x + -0.12562071*z1 + 1.00000000*z2;
          z2 = z1;
          z1 = x;
        }
        {
          static float z1, z2; // filter section state
          float x = output - -0.07845058*z1 - 0.98092611*z2;
          output = 1.00000000*x + -0.12562071*z1 + 1.00000000*z2;
          z2 = z1;
          z1 = x;
        }
        {
          static float z1, z2; // filter section state
          float x = output - -0.17026534*z1 - 0.98098125*z2;
          output = 1.00000000*x + -0.12562071*z1 + 1.00000000*z2;
          z2 = z1;
          z1 = x;
       }
        return output;
      }
    }

    float apply_ECG_filters(float input_signal){
      float ecg_filter_out = ecg_filter(input_signal);
      float band_stop_out = remove_AC_noise(50,ecg_filter_out);
      return band_stop_out;
    }

    float apply_EEG_filters(float input_signal){
      float eeg_filter_out = eeg_filter(input_signal);
      float band_stop_out = remove_AC_noise(50,eeg_filter_out);
      return band_stop_out;
    }

    float apply_EMG_filters(float input_signal){
      float emg_filter_out = emg_filter(input_signal);
      float band_stop_out = remove_AC_noise_EMG(50,emg_filter_out);
      return band_stop_out;
    }

    float apply_EOG_filters(float input_signal){
      float eog_filter_out = eog_filter(input_signal);
      float band_stop_out = remove_AC_noise(50,eog_filter_out);
      return band_stop_out;
    }


    /**
  * @brief Detect peaks in the ECG/EOG signal.
  * 
  * @param newSample New sample of the ECG/EOG signal.
  * @return True if a peak is detected, false otherwise.
  */
  bool detectPeak(float newSample) {
    // Buffers for raw data, mean, and standard deviation
    static float rawECGDataBuffer[DATA_LENGTH];
    static float meanECGBuffer[DATA_LENGTH];
    static float stdDevECGBuffer[DATA_LENGTH];
  
    // Check if the new ECG sample is a peak
    if (newSample - meanECGBuffer[dataIndex] > (DATA_LENGTH / 2) * stdDevECGBuffer[dataIndex]) {
      rawECGDataBuffer[dataIndex] = newSample + rawECGDataBuffer[dataIndex];
      isPeak = true;  // Peak detected
    } else {
      rawECGDataBuffer[dataIndex] = newSample;
      isPeak = false; // No peak detected
    }
  
    // Calculate the mean of the raw ECG data
    float sum = 0.0, mean, stdDev = 0.0;
    for (int i = 0; i < DATA_LENGTH; ++i) {
      sum += rawECGDataBuffer[(dataIndex + i) % DATA_LENGTH];
    }
    mean = sum / DATA_LENGTH;
  
    // Calculate the standard deviation of the raw ECG data
    for (int i = 0; i < DATA_LENGTH; ++i) {
      stdDev += pow(rawECGDataBuffer[(i) % DATA_LENGTH] - mean, 2);
    }
  
    // Update the mean buffer
    meanECGBuffer[dataIndex] = mean;
  
    // Update the standard deviation buffer
    stdDevECGBuffer[dataIndex] = sqrt(stdDev / DATA_LENGTH);
  
    // Update the index for the circular buffer
    dataIndex = (dataIndex + 1) % DATA_LENGTH;
  
    // Return whether a peak in the ECG was detected
    return isPeak;
  }

  bool ignoreReading = false;
  bool firstPulseDetected = false;
  unsigned long firstPulseTime = 0 ;
  unsigned long secondPulseTime = 0 ;
  uint8_t pulseInterval = 0 ;
  CircularBuffer<int,30> pulseIntervalBuffer;

  float getHeartRate(float newECGSample) {
    // Buffers for raw data, mean, and standard deviation
    static float rawECGDataBuffer[DATA_LENGTH];
    static float meanECGBuffer[DATA_LENGTH];
    static float stdDevECGBuffer[DATA_LENGTH];
  
    // Check if the new ECG sample is a peak
    if (newECGSample - meanECGBuffer[dataIndex] > (DATA_LENGTH / 2) * stdDevECGBuffer[dataIndex]) {
      rawECGDataBuffer[dataIndex] = newECGSample + rawECGDataBuffer[dataIndex];
      isPeak = true;  // Peak detected
  
      if (!ignoreReading) {
        if (!firstPulseDetected) {
          firstPulseTime = millis();
          firstPulseDetected = true;
        } else {
          secondPulseTime = millis();
          pulseInterval = secondPulseTime - firstPulseTime;
          pulseIntervalBuffer.unshift(pulseInterval);
          firstPulseTime = secondPulseTime;
        }
        ignoreReading = true;
      }
    } else {
      rawECGDataBuffer[dataIndex] = newECGSample;
      isPeak = false; // No peak detected
      ignoreReading = false;
    }
  
    // Calculate the mean of the raw ECG data
    float sum = 0.0, mean, stdDev = 0.0;
    for (int i = 0; i < DATA_LENGTH; ++i) {
      sum += rawECGDataBuffer[(dataIndex + i) % DATA_LENGTH];
    }
    mean = sum / DATA_LENGTH;
  
    // Calculate the standard deviation of the raw ECG data
    for (int i = 0; i < DATA_LENGTH; ++i) {
      stdDev += pow(rawECGDataBuffer[(i) % DATA_LENGTH] - mean, 2);
    }
  
    // Update the mean buffer
    meanECGBuffer[dataIndex] = mean;
  
    // Update the standard deviation buffer
    stdDevECGBuffer[dataIndex] = sqrt(stdDev / DATA_LENGTH);
  
    // Update the index for the circular buffer
    dataIndex = (dataIndex + 1) % DATA_LENGTH;
  
    // Measure heart rate if the circular buffer is full
    if (pulseIntervalBuffer.isFull()) {
      float averagePulseInterval = 0;
      for (int i = 0; i < pulseIntervalBuffer.size(); i++) {
        averagePulseInterval += pulseIntervalBuffer[i];
      }
      averagePulseInterval /= pulseIntervalBuffer.size();
  
      // Calculate heart rate in beats per minute
      float heartRateBPM = (1.0 / averagePulseInterval) * 60.0 * 1000 * pulseIntervalBuffer.size();
  
      if (heartRateBPM > 0.0 && heartRateBPM < 240) {
        return heartRateBPM;
      }
    }
}

};

#endif