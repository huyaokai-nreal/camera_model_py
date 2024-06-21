from camera_model import Fisheye624UndistortPoints, Fisheye624distortPoints
import numpy as np
src_pt = np.zeros((10,2))
fc = np.array([240,240]).reshape(2,1)
cc = np.array([128, 128]).reshape(2,1)
kc = (np.ones((12))*0.01).reshape(12, 1)
flag, dst_pt = Fisheye624UndistortPoints(src_pt, fc, cc, kc, fc, cc)
print(flag)
print(dst_pt)
dst_pt = Fisheye624distortPoints(src_pt, fc, cc, kc)
print(dst_pt)