from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import Qt, QThread, pyqtSignal
import pyqtgraph as pg
import numpy as np
import serial
from collections import deque
from scipy.signal import iirfilter


channels = ['Channel 1']
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

class SerialPlotter(pg.GraphicsLayoutWidget):
    def __init__(self, channels, data_length, port, baudrate=115200, timeout=1, bandpass_freq=[1, 45], notch_freq=50, sample_rate=250):
        super().__init__()
        self.channels = channels
        self.num_channels = len(channels)
        self.data_length = data_length
        self.data = np.zeros((self.num_channels, data_length))
        self.curves = []
        self.init_ui()
        self.com = port
        self.baudrate = baudrate
        self.ser_timeout = timeout
        self.serial_thread = SerialThread(port, baudrate, timeout)
        self.serial_thread.data_ready.connect(self.update)
        self.serial_thread.start()
        self.bp = bandpass_freq
        self.notch = notch_freq
        self.fs = sample_rate

        b, a = iirfilter(5, Wn=self.bp, fs=self.fs, btype="bandpass", ftype="butter")
        self.live_lfilter_bp = LiveLFilter(b, a)
        q, p = iirfilter(5, [self.notch - 1.5, self.notch + 1.5], fs=self.fs, btype="bandstop", ftype="butter")
        self.live_lfilter_notch = LiveLFilter(q, p)

    def init_ui(self):
        for i, channel in enumerate(self.channels):
            p = self.addPlot(title=channel)
            p.showGrid(x=True, y=True)
            p.setYRange(-100, 100, padding=0)
            curve = p.plot(pen='g')
            self.curves.append(curve)
            if i < self.num_channels - 1:
                self.nextRow()

    def update(self, data):
        if data != '\r\n' and data != '' and data != '\n':
            print(data)
            data_filtered = [self.live_lfilter_notch(self.live_lfilter_bp(float(value))) for value in data.split("\t")]
            for i in range(self.num_channels):
                self.data[i] = np.roll(self.data[i], -1)
                self.data[i][-1] = float(data_filtered[i])
            for i in range(self.num_channels):
                self.curves[i].setData(self.data[i])

def keyPressEvent(event):
    if event.key() == Qt.Key_Escape:
        app.quit()

app = QApplication([])
app.keyPressEvent = keyPressEvent


viewer = SerialPlotter(channels, 750, 'COM9')

def update():
    pass  # Nothing to do here; updates are handled by the SerialPlotter

timer = pg.QtCore.QTimer()
timer.timeout.connect(update)
timer.start(1)

if __name__ == '__main__':
    viewer.show()
    app.exec_()
