from io import StringIO
import tensorflow as tf
import numpy as np
import scipy as sp
import os
#import matplotlib.pyplot as plt
from scipy import signal
#from mpl_toolkits.mplot3d import Axes3D

class ADL_Generator(object):

  def __init__(self, data_dir, resample_rate = 30, sample_period = 5, med_filter = 1):
    self.sample_rate = 32 #Hz
    self.sensor_min = -1.5 * 9.8 #g
    self.sensor_max =  1.5 * 9.8 #g
    self.sample_res = 63

    self.resample_rate = resample_rate #Hz
    self.sample_period = sample_period #seconds
    self.med_filter = med_filter

    self.act_records = []
    self.act_records.append(self.getProcessedRecords(os.path.join(data_dir, "Walk/")))
    self.act_records.append(self.getProcessedRecords(os.path.join(data_dir, "Brush_teeth/")))
    self.act_records.append(self.getProcessedRecords(os.path.join(data_dir, "Climb_stairs/")))
    self.act_records.append(self.getProcessedRecords(os.path.join(data_dir, "Descend_stairs/")))
    #self.act_records.append(getProcessedRecords(os.path.join(data_dir, "Standup_chair/")))
    #self.act_records.append(getProcessedRecords(os.path.join(data_dir, "Sitdown_chair/")))


  def getProcessedRecords(self, file):
    records = self.getRecordsFromTxt(file)
    records = self.applyFil(records)
    return records

  def scaleData(self, _data):
      data = self.sensor_min + (_data/self.sample_res) * (self.sensor_max - self.sensor_min)
      return data

  def parseAdlTxt(self, file):
      data = np.genfromtxt(file, dtype=np.float32, delimiter=" ")
      return data

  def getRecordsFromTxt(self, folderPath):
      records = [] #append a list
      for root, dirs, files in os.walk(folderPath, topdown=False):
  #         print(root)
  #         print(dirs)
          #prev_shape = None
          for name in files:
              data = self.scaleData(self.parseAdlTxt(os.path.join(root, name)))

  #             if(prev_shape != None and prev_shape != data.shape):
  #                 print("Error: data sample length not uniform ", data.shape)
  #                 exit(-1)
  #             else:
  #                 prev_shape = data.shape

              records.append(data)
              #print(name, data.shape)
      return records

  def applyFil(self, records):
      resample_factor = self.resample_rate / self.sample_rate
      for i, r in enumerate(records):
          resample_length = np.ceil(resample_factor * r.shape[0])
          r = sp.signal.medfilt(r, self.med_filter)
          r = sp.signal.resample(r, resample_length.astype(np.int32))
          records[i] = r

      return records

  def randSegFromRecords(self, records, seg_length):
      rand_r_index = np.random.randint(0, len(records))
      r = records[rand_r_index]
      #print("r ", r.shape)
      if(seg_length > r.shape[0]):
          print("desired segment length exceeds sample length")
          exit()
      seg_start = np.random.randint(0, np.maximum(r.shape[0] - seg_length, 1))
      #print("seg_start ", seg_start)
      r_slice = r[seg_start:(seg_start + seg_length)]
      #print("seg_start + seg_length ", seg_start + seg_length)
      #print("r_slice ", r_slice.shape)
      
      return r_slice

  def gen(self):
    num_images = self._images.shape[0]
    rand_index = np.random.random_integers(num_images - 1)
    label = self._labels[rand_index]
    image = self._images[rand_index]
    #mnist.train.images[np.random.random_integers(mnist.train.images.shape[0])]
    return (self.distort_image(image), label)

  def genTrainData(self):
    label = np.random.randint(0, len(self.act_records))
    data = self.randSegFromRecords(self.act_records[label], self.resample_rate * self.sample_period)
    yield (data, float(label))

  def genTestData(self):
    #data are randomly cropped, but there are bound to be dependency
    #use genTrainData() before proper testset is constructed
    yield self.genTrainData()

# def sampleMeanShiftPlot(data, self.sample_rate):
    
#     t = np.arange(0, data.shape[0] / self.sample_rate, 1 / self.sample_rate)

#     data = np.swapaxes(data, 0, 1)
#     [bx, by, bz] = data
#     bx = bx - np.mean(bx)
#     by = by - np.mean(by)
#     bz = bz - np.mean(bz)
    

#     fig = plt.figure()
#     plt.subplot(311)
#     plt.plot(t, bx, 'bo')
#     plt.title('x')

#     plt.subplot(312)
#     plt.plot(t, by, 'bo')
#     plt.title('y')
    
#     plt.subplot(313)
#     plt.plot(t, bz, 'bo')
#     plt.title('z')