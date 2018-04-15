import numpy as np 
from numpy import linalg as LA

x = np.mat('90 80 40;90 60 80;60 50 70;30 40 70;30 20 90')

s = (5, 5)
y = np.ones(s)

A = np.matmul(y, x)
mean = np.divide(A, 5)

a = x - mean
# print a

aT = a.transpose()
# print aT
cov_matrix = np.matmul(aT, a)
cov_matrix = np.divide(cov_matrix, 4) #divide by n-1

print cov_matrix

#eigenvalues and eigenvectors of covariance-matrix
w, v = LA.eig(cov_matrix)

print w
print
print v