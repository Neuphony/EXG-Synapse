from PyQt5.QtWidgets import QApplication, QDialog, QVBoxLayout, QHBoxLayout, QLabel, QComboBox, QSpinBox, QPushButton, QMainWindow
from PyQt5.QtCore import Qt, QThread, pyqtSignal
import pyqtgraph as pg
import numpy as np
import serial
from collections import deque
from scipy.signal import iirfilter
import sys
import serial.tools.list_ports
from PyQt5.QtGui import QIcon
 
# Configuration Dialog Class
class ConfigDialog(QDialog):
    def __init__(self):
        super().__init__()
        self.setWindowFlags(self.windowFlags() & ~Qt.WindowContextHelpButtonHint)
        self.setWindowTitle('Configuration')
        icon_path = "Resources/Icon.png"  # Ensure this path is correct
        if icon_path:
            self.setWindowIcon(QIcon(icon_path))
 
        self.setFixedSize(370, 300)  # Adjust size as needed
 
        layout = QVBoxLayout(self)
 
        # COM Port Selection
        com_layout = QHBoxLayout()
        self.com_label = QLabel('Select COM Port:', self)
        com_layout.addWidget(self.com_label)
        self.com_select = QComboBox(self)
        self.com_select.setFixedSize(100, 25)  # Set fixed size for COM port selection
        self.populate_com_ports()
        com_layout.addWidget(self.com_select)
        layout.addLayout(com_layout)
 
        # Amplitude Setting
        amp_layout = QHBoxLayout()
        self.amp_label = QLabel('Set Amplitude Range:', self)
        amp_layout.addWidget(self.amp_label)
        self.amp_select = QSpinBox(self)
        self.amp_select.setFixedSize(100, 25)  # Set fixed size for Amplitude selection
        self.amp_select.setRange(-1000, 1000)
        self.amp_select.setValue(500)
        amp_layout.addWidget(self.amp_select)
        layout.addLayout(amp_layout)
 
        # Number of Channels Setting
        ch_layout = QHBoxLayout()
        self.ch_label = QLabel('Number of Channels:', self)
        ch_layout.addWidget(self.ch_label)
        self.ch_select = QSpinBox(self)
        self.ch_select.setFixedSize(100, 25)  # Set fixed size for Channel selection
        self.ch_select.setRange(1, 10)
        self.ch_select.setValue(1)
        ch_layout.addWidget(self.ch_select)
        layout.addLayout(ch_layout)
 
        # Number of Seconds of Data Setting
        sec_layout = QHBoxLayout()
        self.sec_label = QLabel('Data View Duration (Seconds):', self)
        sec_layout.addWidget(self.sec_label)
        self.sec_select = QSpinBox(self)
        self.sec_select.setFixedSize(100, 25)  # Set fixed size for Seconds selection
        self.sec_select.setRange(5, 20)
        self.sec_select.setValue(5)
        sec_layout.addWidget(self.sec_select)
        layout.addLayout(sec_layout)
       
        # Bandpass Filter Cutoff
        bp_layout = QHBoxLayout()
        self.bp_label = QLabel('Bandpass Filter Cutoff (Hz):', self)
        bp_layout.addWidget(self.bp_label)
        self.bp_low_select = QSpinBox(self)
        self.bp_low_select.setRange(1, 100)  # Example range
        self.bp_low_select.setValue(1)
        bp_layout.addWidget(self.bp_low_select)
 
        self.bp_high_select = QSpinBox(self)
        self.bp_high_select.setRange(1, 100)  # Example range
        self.bp_high_select.setValue(45)
        self.bp_low_select.setFixedSize(45,25)
        self.bp_high_select.setFixedSize(45,25)
        bp_layout.addWidget(self.bp_high_select)
        layout.addLayout(bp_layout)
 
        # Notch Filter Frequency
        notch_layout = QHBoxLayout()
        self.notch_label = QLabel('Notch Filter Frequency (Hz):', self)
        notch_layout.addWidget(self.notch_label)
        self.notch_select = QSpinBox(self)
        self.notch_select.setRange(40, 60)  # Example range
        self.notch_select.setValue(50)
        self.notch_select.setFixedSize(100,25)
        notch_layout.addWidget(self.notch_select)
        layout.addLayout(notch_layout)
 
        # Buttons
        button_layout = QHBoxLayout()
        self.ok_button = QPushButton('OK', self)
        self.ok_button.setFixedSize(100, 30)  # Set fixed size for OK button
        self.ok_button.clicked.connect(self.accept)
        button_layout.addWidget(self.ok_button)
 
        layout.addLayout(button_layout)
 
    def populate_com_ports(self):
        com_ports = serial.tools.list_ports.comports()
        available_ports = [port.device for port in com_ports]
        self.com_select.addItems(available_ports)
 
    def get_config(self):
        return {
            "type": "COM",
            "port": self.com_select.currentText(),
            "amplitude": self.amp_select.value(),
            "channels": self.ch_select.value(),
            "duration": self.sec_select.value(),
            "bp_low": self.bp_low_select.value(),
            "bp_high": self.bp_high_select.value(),
            "notch": self.notch_select.value()
        }
 
 
class LiveFilter:
    def process(self, x):
        if np.isnan(x):
            return x
        return self._process(x)
 
    def __call__(self, x):
        return self.process(x)
 
    def _process(self, x):
        raise NotImplementedError("Derived class must implement _process")
 
class LiveLFilter(LiveFilter):
    def __init__(self, b, a):
        self.b = b
        self.a = a
        self._xs = deque([0] * len(b), maxlen=len(b))
        self._ys = deque([0] * (len(a) - 1), maxlen=len(a) - 1)
 
    def _process(self, x):
        self._xs.appendleft(x)
        y = np.dot(self.b, self._xs) - np.dot(self.a[1:], self._ys)
        y = y / self.a[0]
        self._ys.appendleft(y)
        return y
 
class LiveSosFilter(LiveFilter):
    def __init__(self, sos):
        self.sos = sos
        self.n_sections = sos.shape[0]
        self.state = np.zeros((self.n_sections, 2))
 
    def _process(self, x):
        for s in range(self.n_sections):
            b0, b1, b2, a0, a1, a2 = self.sos[s, :]
            y = b0 * x + self.state[s, 0]
            self.state[s, 0] = b1 * x - a1 * y + self.state[s, 1]
            self.state[s, 1] = b2 * x - a2 * y
            x = y
        return y
 
class SerialThread(QThread):
    data_ready = pyqtSignal(str)
 
    def __init__(self, port, baudrate=115200, timeout=1):
        super().__init__()
        self.ser_port = serial.Serial(port, baudrate=baudrate, timeout=timeout)
 
    def run(self):
        while True:
            data = self.ser_port.readline().decode().strip()
            if data:
                self.data_ready.emit(data)
 
# SerialPlotter class with modifications for amplitude
class SerialPlotter(pg.GraphicsLayoutWidget):
    def __init__(self, channels, data_length, port, amplitude, baudrate=115200, timeout=1, bandpass_freq=[1, 45], notch_freq=50, sample_rate=250):
        super().__init__()
        self.channels = channels
        self.num_channels = len(channels)
        self.data_length = data_length
        self.data = [np.zeros(data_length) for _ in range(self.num_channels)]  # Independent data storage for each channel
        self.curves = []
        self.init_ui(amplitude)
        self.com = port
        self.baudrate = baudrate
        self.ser_timeout = timeout
        self.serial_thread = SerialThread(port, baudrate, timeout)
        self.serial_thread.data_ready.connect(self.update)
        self.serial_thread.start()
        self.bp = bandpass_freq
        self.notch = notch_freq
        self.fs = sample_rate
 
        # Filters for each channel (if needed)
        self.filters = [self.create_filters() for _ in range(self.num_channels)]
 
 
    def create_filters(self):
        b, a = iirfilter(5, Wn=self.bp, fs=self.fs, btype="bandpass", ftype="butter")
        live_lfilter_bp = LiveLFilter(b, a)
        q, p = iirfilter(5, [self.notch - 1.5, self.notch + 1.5], fs=self.fs, btype="bandstop", ftype="butter")
        live_lfilter_notch = LiveLFilter(q, p)
        return (live_lfilter_bp, live_lfilter_notch)
 
 
    def init_ui(self, amplitude):
        for i, channel in enumerate(self.channels):
            p = self.addPlot(title=channel)
            p.showGrid(x=True, y=True)
            p.setYRange(-amplitude, amplitude, padding=0)
            curve=p.plot(pen='g')
            self.curves.append(curve)
            if i < self.num_channels - 1:
                self.nextRow()
 
    def update(self, data):
        if data != '\r\n' and data != '' and data != '\n':
            try:  
                data_values = [float(value) for value in data.split("\t")]
                print(data_values)
                if len(data_values) != self.num_channels:
                    raise ValueError("Data length mismatch")
 
                for i in range(self.num_channels):
                    filtered_value = self.filters[i][1](self.filters[i][0](data_values[i]))  # Apply filters
                    self.data[i] = np.roll(self.data[i], -1)
                    self.data[i][-1] = filtered_value
                    self.curves[i].setData(self.data[i])
            except ValueError as e:
                print(f"Error processing data: {e}")
               
 
 
def create_channel_list(num_channels):
    """
    Creates a list of channel names in sequence.
 
    Args:
    num_channels (int): The number of channels to create.
 
    Returns:
    list: A list of channel names.
    """
    return [f"Channel {i+1}" for i in range(num_channels)]
 
 
# Main application setup
if __name__ == '__main__':
    app = QApplication(sys.argv)
 
    config_dialog = ConfigDialog()
    if config_dialog.exec_() == QDialog.Accepted:
        config = config_dialog.get_config()
        channels = create_channel_list(config['channels'])
        duration = int(config['duration'])*250
        viewer = SerialPlotter(channels, duration, config['port'], config['amplitude'],
                                   bandpass_freq=[config['bp_low'], config['bp_high']],
                                   notch_freq=config['notch'])
        viewer.show()
        sys.exit(app.exec_())