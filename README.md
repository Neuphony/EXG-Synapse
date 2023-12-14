<h1 id="github---readme">Github - Readme</h1>
<p>Front View<br>        <img src="Resources/Photo_-_Front_View.png" alt="front"></p>
<p>Rear View<br>        <img src="Resources/Photo_-_Rear_View.png" alt="rear"></p>
<p><strong>Setup Instructions</strong></p>
<ol>
<li><p><strong>What is EXG Synapse?</strong>  </p>
<p>  Neuphony EXG Synapse is an innovative, hexagon-shaped chip designed for recording high-quality biopotential signals from various regions of the body, including the heart (ECG), brain (EEG), eyes (EOG), and muscles (EMG). Serving as a robust analog-front-end (AFE) biopotential signal-acquisition board, the Neuphony EXG Synapse can seamlessly integrate with a range of microcontroller units (MCUs) or single-board computers (SBCs) equipped with an analog-to-digital converter (ADC). Compatible platforms include popular options such as Arduino UNO &amp; Nano, Espressif ESP32 and more.</p>
</li>
<li><p><strong>Hardware Requirements</strong> :   EXG Synapse, DOIT-ESP32-DEVKIT-V1, Jumper Wires<br><strong>Software Requirements</strong> : Arduino IDE</p>
</li>
<li><p><strong>PCB Configuration</strong>  </p>
<p>  EXG Synapse has configuration options in terms of gain and bandpass filter bandwidth. The user can modify these values depending on the use case. Here is an image showing the resistor pad R9(for gain) and capacitor pad C2(for filter bandwidth).</p>
<p>  <img src="Resources/Synapse.png" alt="Synapse"></p>
</li>
<li><p><strong>Connection with ESP32</strong>  </p>
<p>  EXG Synapse requires only three wires to connect to any MCU. 3V3 connects to the 3V3 pin on the ESP32 and GND to GND pin on the ESP32. The Output of EXG Synapse can be connected to any ADC pin of ESP32 and configured as an analog input to read the data.</p>
<p>  <img src="Resources/ESPConnection.png" alt="ESPConnection"></p>
</li>
<li><p><strong>Flashing Code on ESP32</strong>  </p>
<p>  To flash the required code on ESP32, you need to install Arduino IDE and setup for flashing to an ESP32. You can follow <a href="https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html">this guide</a> if you don’t find your board listed in Arduino. Once your board is added to Arduino, you can go to <a href="https://github.com/Neuphony/EXG-Synapse">our GitHub repository</a>, here you will find all the necessary files for acquiring the data using EXG Synapse.</p>
<p>  Navigate to the folder of your choice (serial or BLE), and download the required .ino (EEG, ECG, EMG, EOG). Now compile and upload the code on your board.</p>
<p>  Please follow the screenshots given below.</p>
<p>  <strong>Board selection:</strong></p>
<p>  <img src="Resources/BoardSelection.png" alt="BoardSelectiond"></p>
<p>  <strong>COM Port selection:</strong></p>
<p>  <img src="Resources/BoardSelection.png" alt="BoardSelection"></p>
</li>
<li><p><strong>Skin Preparation</strong>  </p>
<p>  Before placing the electrode, skin surface must be cleaned with an alcohol based wet wipe and then Nuprep Gel can be used to enhance the signal quality as it reduces the skin impedance. You can follow <a href="https://www.youtube.com/watch?v=qQSClWIYUwM&t=76s">this guide</a> on how to use Nuprep Gel while preparing for data acquisition.</p>
</li>
<li><p><strong>Data Visualization:</strong>  </p>
<p>  The Lab Streaming Layer (LSL) is a system designed for real-time data streaming and recording. We have provided a python script located in the <a href="https://github.com/Neuphony/EXG-Synapse">GitHub repository</a> used to read the data from serial and create a LSL stream. The stream created by the script can be easily visualized using a LSL-compatible software such as <strong><a href="https://pressrelease.brainproducts.com/lsl-viewer/">BrainVision LSL Viewer</a>.</strong> It can be downloaded for free using this <a href="https://www.brainproducts.com/downloads/more-software/#utilities">link</a>.</p>



# EEG

1. **What is EEG?**
EEG stands for electroencephalography, which is a non-invasive technique used to measure and record electrical activity in the brain. It involves placing electrodes on the scalp to detect and amplify the electrical signals produced by the brain. These signals, known as brainwaves, can provide insights into brain function and activity.

2. **What is EXG Synapse?**
Neuphony EXG Synapse is an innovative, hexagon-shaped chip designed for recording high-quality biopotential signals from various regions of the body, including the heart (ECG), brain (EEG), eyes (EOG), and muscles (EMG). Serving as a robust analog-front-end (AFE) biopotential signal-acquisition board, the Neuphony EXG Synapse can seamlessly integrate with a range of microcontroller units (MCUs) or single-board computers (SBCs) equipped with an analog-to-digital converter (ADC). Compatible platforms include popular options such as Arduino UNO & Nano, Espressif ESP32 and more.

3. **Hardware Requirements** : EXG Synapse, DOIT-ESP32-DEVKIT-V1, Jumper Wires
**Software Requirements** : Arduino IDE

4. **PCB Configuration:**
EXG Synapse has configuration options in terms of gain and bandpass filter bandwidth. The user can modify these values depending on the use case. Here is an image showing the resistor pad R9(for gain) and capacitor pad C2(for filter bandwidth).

    
    ![Synapse](Resources/Synapse.png)
    

1. **Connection with ESP32**
EXG Synapse requires only three wires to connect to any MCU. 3V3 connects to the 3V3 pin on the ESP32 and GND to GND pin on the ESP32. The Output of EXG Synapse can be connected to any ADC pin of ESP32 and configured as an analog input to read the data.

![EEG.png](Resources/EEG%200fb3358243c8403793fba81bb3e7a900/EEG.png)

1. **Flashing Code on ESP32**
To flash the required code on ESP32, you need to install Arduino IDE and setup for flashing to an ESP32. You can follow [this guide](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html) if you don’t find your board listed in Arduino. Once your board is added to Arduino, you can go to [this GitHub repository](https://github.com/Neuphony/EXG-Synapse), here you will find all the necessary files for acquiring the data using EXG Synapse.

Navigate to the EEG folder and then to Arduino, and download required .ino file. Now compile and upload the code on your board.

2. **Skin Preparation**
Before placing the electrode, skin surface must be cleaned with an alcohol based wet wipe and then Nuprep Gel can be used to enhance the signal quality as it reduces the skin impedance. You can follow [this](https://www.youtube.com/watch?v=qQSClWIYUwM) guide on how to use Nuprep Gel while preparing for data acquisition.

3. **Electrode Placement:**
Check above image for correct electrode placement

4. **Data Visualization:**
Serial : The Lab Streaming Layer (LSL) is a system designed for real-time data streaming and recording. We have provided a python script located in the [GitHub repository](https://github.com/Neuphony/EXG-Synapse) used to read the data from serial and create a LSL stream. The stream created by the script can be easily visualized using a LSL-compatible software such as **[BrainVision LSL Viewer](https://pressrelease.brainproducts.com/lsl-viewer/).** It can be downloaded for free using this [link](https://www.brainproducts.com/downloads/more-software/#utilities).

    
    ![Untitled](Resources/EEG%200fb3358243c8403793fba81bb3e7a900/Untitled.png)
    
    BLE : If flashed with the code provided under software\Arduino\ble, ESP32 will stream data continously over BLE. You can create a client side interface to read this data and use it for further applications.


# ECG

1. W**hat is ECG?**
ECG stands for Electrocardiogram. It is a medical test that measures and records the electrical activity of the heart. The ECG helps in diagnosing various heart conditions and evaluating the heart's overall health.

1. **What is EXG Synapse?**
Neuphony EXG Synapse is an innovative, hexagon-shaped chip designed for recording high-quality biopotential signals from various regions of the body, including the heart (ECG), brain (EEG), eyes (EOG), and muscles (EMG). Serving as a robust analog-front-end (AFE) biopotential signal-acquisition board, the Neuphony EXG Synapse can seamlessly integrate with a range of microcontroller units (MCUs) or single-board computers (SBCs) equipped with an analog-to-digital converter (ADC). Compatible platforms include popular options such as Arduino UNO & Nano, Espressif ESP32 and more.

2. **Hardware Requirements** : EXG Synapse, DOIT-ESP32-DEVKIT-V1, Jumper Wires
**Software Requirements** : Arduino IDE

3. **PCB Configuration:**
EXG Synapse has configuration options in terms of gain and bandpass filter bandwidth. The user can modify these values depending on the use case. Here is an image showing the resistor pad R9(for gain) and capacitor pad C2(for filter bandwidth).

![Untitled](Resources/Untitled.png)

1. **Connection with ESP32**
EXG Synapse requires only three wires to connect to any MCU. 3V3 connects to the 3V3 pin on the ESP32 and GND to GND pin on the ESP32. The Output of EXG Synapse can be connected to any ADC pin of ESP32 and configured as an analog input to read the data.

![ECG.png](Resources/ECG%20fd74b5218530485baab3d220836dfc0d/ECG.png)

1. **Flashing Code on ESP32**
To flash the required code on ESP32, you need to install Arduino IDE and setup for flashing to an ESP32. You can follow [this guide](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html) if you don’t find your board listed in Arduino. Once your board is added to Arduino, you can go to [this GitHub repository](https://github.com/Neuphony/EXG-Synapse), here you will find all the necessary files for acquiring the data using EXG Synapse.
Navigate to the EEG folder and then to Arduino, and download required .ino file. Now compile and upload the code on your board.

2. **Skin Preparation**
Before placing the electrode, skin surface must be cleaned with an alcohol based wet wipe and then Nuprep Gel can be used to enhance the signal quality as it reduces the skin impedance. You can follow [this](https://www.youtube.com/watch?v=qQSClWIYUwM) guide on how to use Nuprep Gel while preparing for data acquisition.

3. **Electrode Placement:**
Check above image for correct electrode placement

1. **Data Visualization:**
Serial : The Lab Streaming Layer (LSL) is a system designed for real-time data streaming and recording. We have provided a python script located in the [GitHub repository](https://github.com/Neuphony/EXG-Synapse) used to read the data from serial and create a LSL stream. The stream created by the script can be easily visualized using a LSL-compatible software such as **[BrainVision LSL Viewer](https://pressrelease.brainproducts.com/lsl-viewer/).** It can be downloaded for free using this [link](https://www.brainproducts.com/downloads/more-software/#utilities).

    
    ![Untitled](Resources/ECG%20fd74b5218530485baab3d220836dfc0d/Untitled.png)
    
    BLE : If flashed with the code provided under software\Arduino\ble, ESP32 will stream data continously over BLE. You can create a client side interface to read this data and use it for further applications.


# EMG

1. **What is EMG?**
    
    EMG stands for Electromyography. It is a technique used to measure and record the electrical activity produced by skeletal muscles. This information can be useful in various applications, such as studying muscle function, diagnosing neuromuscular disorders, and monitoring muscle activity during physical therapy or athletic training.
    
2. **What is EXG Synapse?**
Neuphony EXG Synapse is an innovative, hexagon-shaped chip designed for recording high-quality biopotential signals from various regions of the body, including the heart (ECG), brain (EEG), eyes (EOG), and muscles (EMG). Serving as a robust analog-front-end (AFE) biopotential signal-acquisition board, the Neuphony EXG Synapse can seamlessly integrate with a range of microcontroller units (MCUs) or single-board computers (SBCs) equipped with an analog-to-digital converter (ADC). Compatible platforms include popular options such as Arduino UNO & Nano, Espressif ESP32 and more.

3. **Hardware Requirements** : EXG Synapse, DOIT-ESP32-DEVKIT-V1, Jumper Wires
**Software Requirements** : Arduino IDE

4. **PCB Configuration:**
EXG Synapse has configuration options in terms of gain and bandpass filter bandwidth. The user can modify these values depending on the use case. Here is an image showing the resistor pad R9(for gain) and capacitor pad C2(for filter bandwidth).

![Untitled](Resources/Untitled.png)

1. **Connection with ESP32**
EXG Synapse requires only three wires to connect to any MCU. 3V3 connects to the 3V3 pin on the ESP32 and GND to GND pin on the ESP32. The Output of EXG Synapse can be connected to any ADC pin of ESP32 and configured as an analog input to read the data.

![EMG.png](Resources/EMG%209782323bfa9f4984893c2f4c79499155/EMG.png)

1. **Flashing Code on ESP32**
To flash the required code on ESP32, you need to install Arduino IDE and setup for flashing to an ESP32. You can follow [this guide](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html) if you don’t find your board listed in Arduino. Once your board is added to Arduino, you can go to [this GitHub repository](https://github.com/Neuphony/EXG-Synapse), here you will find all the necessary files for acquiring the data using EXG Synapse.
Navigate to the EMG folder and then to Arduino, and download required .ino file. Now compile and upload the code on your board.

2. **Skin Preparation**
Before placing the electrode, skin surface must be cleaned with an alcohol based wet wipe and then Nuprep Gel can be used to enhance the signal quality as it reduces the skin impedance. You can follow [this](https://www.youtube.com/watch?v=qQSClWIYUwM) guide on how to use Nuprep Gel while preparing for data acquisition.

3. **Electrode Placement**
    
    Check above image for correct electrode placement
    
4. **Data Visualization:**
Serial : The Lab Streaming Layer (LSL) is a system designed for real-time data streaming and recording. We have provided a python script located in the [GitHub repository](https://github.com/Neuphony/EXG-Synapse) used to read the data from serial and create a LSL stream. The stream created by the script can be easily visualized using a LSL-compatible software such as **[BrainVision LSL Viewer](https://pressrelease.brainproducts.com/lsl-viewer/).** It can be downloaded for free using this [link](https://www.brainproducts.com/downloads/more-software/#utilities).

    
    ![EMG - Data Screen.png](Resources/EMG%209782323bfa9f4984893c2f4c79499155/EMG_-_Data_Screen.png)
    
    BLE : If flashed with the code provided under software\Arduino\emg\ble, ESP32 will stream data continously over BLE. You can create a client side interface to read this data and use it for further applications.

# EOG

1. **What is EOG?**
    
    EOG stands for "Electrooculography." It refers to a technique used to measure and record the electrical activity of the muscles that control eye movements. This technique is often used in medical and research settings to study eye movements and diagnose certain eye disorders.
    
2. **What is EXG Synapse?**
Neuphony EXG Synapse is an innovative, hexagon-shaped chip designed for recording high-quality biopotential signals from various regions of the body, including the heart (ECG), brain (EEG), eyes (EOG), and muscles (EMG). Serving as a robust analog-front-end (AFE) biopotential signal-acquisition board, the Neuphony EXG Synapse can seamlessly integrate with a range of microcontroller units (MCUs) or single-board computers (SBCs) equipped with an analog-to-digital converter (ADC). Compatible platforms include popular options such as Arduino UNO & Nano, Espressif ESP32 and more.

3. **Hardware Requirements** : EXG Synapse, DOIT-ESP32-DEVKIT-V1, Jumper Wires
**Software Requirements** : Arduino IDE

4. **PCB Configuration:**
EXG Synapse has configuration options in terms of gain and bandpass filter bandwidth. The user can modify these values depending on the use case. Here is an image showing the resistor pad R9(for gain) and capacitor pad C2(for filter bandwidth).

![Untitled](Resources/Untitled.png)

1. **Connection with ESP32**
EXG Synapse requires only three wires to connect to any MCU. 3V3 connects to the 3V3 pin on the ESP32 and GND to GND pin on the ESP32. The Output of EXG Synapse can be connected to any ADC pin of ESP32 and configured as an analog input to read the data. 

**Horizontal Eye Movements**

![hEOG.png](Resources/EOG%204a754757329e42eda3236df74f409dec/hEOG.png)

**Vertical Eye Movements**

![vEOG.png](Resources/EOG%204a754757329e42eda3236df74f409dec/vEOG.png)

1. **Flashing Code on ESP32**
To flash the required code on ESP32, you need to install Arduino IDE and setup for flashing to an ESP32. You can follow [this guide](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html) if you don’t find your board listed in Arduino. Once your board is added to Arduino, you can go to [this GitHub repository](https://github.com/Neuphony/EXG-Synapse), here you will find all the necessary files for acquiring the data using EXG Synapse.
Navigate to the EOG folder and then to Arduino, and download required .ino file. Now compile and upload the code on your board.

2. **Skin Preparation**
Before placing the electrode, skin surface must be cleaned with an alcohol based wet wipe and then Nuprep Gel can be used to enhance the signal quality as it reduces the skin impedance. You can follow [this](https://www.youtube.com/watch?v=qQSClWIYUwM) guide on how to use Nuprep Gel while preparing for data acquisition.
    
    
3. **Electrode Placement:**
Check above image for correct electrode placement

1. **Data Visualization:**
Serial : The Lab Streaming Layer (LSL) is a system designed for real-time data streaming and recording. We have provided a python script located in the [GitHub repository](https://github.com/Neuphony/EXG-Synapse) used to read the data from serial and create a LSL stream. The stream created by the script can be easily visualized using a LSL-compatible software such as **[BrainVision LSL Viewer](https://pressrelease.brainproducts.com/lsl-viewer/).** It can be downloaded for free using this [link](https://www.brainproducts.com/downloads/more-software/#utilities).

**Horizontal EOG Data**
    
![Untitled](Resources/EOG%204a754757329e42eda3236df74f409dec/Untitled.png)

**Vertical EOG Data**
    
![vEOG- data screen.png](Resources/EOG%204a754757329e42eda3236df74f409dec/vEOG-_data_screen.png)

BLE : If flashed with the code provided under software\Arduino\eog\ble, ESP32 will stream data continously over BLE. You can create a client side interface to read this data and use it for further applications.

</li>
</ol>
<p><strong>Dimensions</strong></p>
<p><img src="Resources/Dimensions.png" alt="Dimensions.png"></p>
<p><strong>Pinout</strong></p>
<p><img src="Resources/Pinout.png" alt="Pinout.png"></p>
<p><strong>Schematic</strong></p>
<p><img src="Resources/Screenshot_2023-12-01_at_4.57.04_PM.png" alt="Screenshot 2023-12-01 at 4.57.04 PM.png"></p>
<p><strong>Licenses</strong>
Hardware - CERN-OHL-S-2.0
Software - MIT
Documentation - CC BY-SA 4.0</p>
<p>Certification - </p>
<p><img src="Resources/OSHWACertificate.png" alt="OSHWACertificate.png" style="width:200px;">, <img src="Resources/License.png" alt="License.png" style="width:400px;"></p>
<!-- <p><img src="Resources/License.png" alt="License.png" style="width:200px;"></p> -->
