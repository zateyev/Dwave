from ctypes import cdll, c_float
lib = cdll.LoadLibrary('./libDwave.so')
import threading
import time

class Dwave(object):
    def __init__(self):
        self.obj = lib.Dwave_new()

    def run(self):
        lib.Dwave_start(self.obj)

    def set_cam_settings(self, px, py, pz, ux, uy, uz):
        lib.Dwave_set_cam_settings(self.obj, px, py, pz, ux, uy, uz)
        

f = Dwave()
dw = threading.Thread(target = f.run)
dw.start()
time.sleep(3)
print("start change")
ds = threading.Thread(target = f.set_cam_settings,
                      args = (c_float(0.1), c_float(3.0), c_float(0.0),
                              c_float(0.0), c_float(1.0), c_float(0.0)))
ds.start()

time.sleep(1)
print("start change")
ds1 = threading.Thread(target = f.set_cam_settings,
                      args = (c_float(3.0), c_float(0.0), c_float(0.0),
                              c_float(0.0), c_float(1.0), c_float(0.0)))
ds1.start()
