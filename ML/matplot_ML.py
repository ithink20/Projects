import matplotlib.pyplot as plt
import numpy as np

#random values between 0 and 1
a = np.random.random((10, 2))

"""
matrix formed of 2x10
[x1, y1]
[x2, y2]
 .....
 .....
[x10, y10]

"""
print a.shape
#scattered plot

plt.figure(0)

#first param: x-cord, sec param: y-cord

plt.scatter(a[: , 0], a[:, 1], color = 'black')
#plt.show()