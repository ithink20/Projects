from pylab import imread, subplot, imshow, title, gray, figure, show, NullLocator
from numpy import mean, cov, cumsum, dot, linalg, size, flipud, argsort
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

A = imread('valentines-day.jpg')  				#pass image here
A = mean(A, axis = 2)

# print A.shape
plt.figure(0)
plt.imshow(A, cmap='gray')
# plt.show()

i = 1
for numpc in range(0, 40, 10):

	# computing eigenvalues and eigenvectors of covariance matrix
	M = (A - mean(A.T, axis = 1)).T 							# subtract the mean (along columns)
	[latent,coeff] = linalg.eig(cov(M))

	p = size(coeff,axis=1)
	idx = argsort(latent) 								# sorting the eigenvalues
	idx = idx[::-1]       								# in ascending order

	# sorting eigenvectors according to the sorted eigenvalues
	coeff = coeff[:,idx]
	latent = latent[idx] 								# sorting eigenvalues

	if numpc < p and numpc >= 0:
		coeff = coeff[:, range(numpc)] 					# cutting some PCs if needed
		score = dot(coeff.T, M)							# projection of the data in the new space
	Ar = dot(coeff,score).T + mean(A, axis = 0) 				# image reconstruction
	ax = subplot(2, 2, i, frame_on = False)
	ax.xaxis.set_major_locator(NullLocator()) 			# remove ticks
	ax.yaxis.set_major_locator(NullLocator())
	i += 1
	title('PCs # '+str(numpc))
	imshow(Ar)
	gray()

show()