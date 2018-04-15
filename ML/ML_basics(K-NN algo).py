import matplotlib.pyplot as plt
import numpy as np
from math import sqrt

#lemons are sour, avg sweetness low, they have some value of color
# Red value is heigher, yellow is lower
# sweetness higher, sourness lower

mean_01 = np.array([3.0, 4.0])

# 2x2 identity matrix
cov_01 = np.array([[1.0, -0.5], [-0.5, 1.0]])

mean_02 = np.array([0.0, 0.0])  #-1.0 for sour, means sweet in -ve sense.

# how changing color of lemon will affect it's sweetness: cov_02

cov_02 = np.array([[1.0, 0.5], [0.5, 0.6]])

dist_01 = np.random.multivariate_normal(mean_01, cov_01, 200)
dist_02 = np.random.multivariate_normal(mean_02, cov_02, 200)

print dist_01.shape
print dist_02.shape
# print dist_01

# scatter plot of these points
"""
plt.figure(0)

for x in range(dist_01.shape[0]):
    plt.scatter(dist_01[x, 0], dist_01[x, 1], color = 'red')
    plt.scatter(dist_02[x, 0], dist_02[x, 1], color = 'yellow')
plt.show()
"""
# you can see in graph, most of the points concentrated near
# the mean

#Training data preperation (common dataset)
                                                                        #common dataset
labels = np.zeros((400, 1))                                     #data(size = 400)       label(size = 400)
labels[200 : ] = 1.0                                           # |__|__|                |__|
                                                               # |__|__|                |__|
X_data = np.zeros((400, 2))                                    # |__|__|                |__|
X_data[: 200, : ] = dist_01                                    # |__|__|                |__|
X_data[200 : , : ] = dist_02                                   # |__|__|                |__|
                                                               # |__|__|                |__|
#print X_data                                                   # first 200 data - apple : label = 0
#print labels                                                   # next 200 data - lemon  : label = 1

            #K-NN ALGORITHM

#distance of query point to all other points in the space (O(N)) for every point + sort these - O(Q*N)

#Euclidian distance

def dist(x1, x2):
    return np.sqrt(((x1 - x2)**2).sum())

x1 = np.array([0.0, 0.0])
x2 = np.array([1.0, 1.0])

#print dist(x1, x2)

# k can't be too high or too low
#y_train - labels (400, 1)
# X_train - training data (400, 2)
#query_point - to predict whether apple/lemon
# 0 : apple, 1 : lemon

def knn(X_train, query_point, y_train, k = 5):
    val = []

    for ix in range(X_train.shape[0]):
        #v = [ distance, label]
        v = [dist(query_point, X_train[ix, :]), y_train[ix]]
        val.append(v)

    # val is a list containing distances and labels
    updated_val = sorted(val)
    # let's pickup top k values
    predict_arr = np.asarray(updated_val[ : k])

    predict_arr = np.unique(predict_arr[:, 1], return_counts = True)

    #largest occurrence

    index = predict_arr[1].argmax()

    return predict_arr[0][index]

    # print predict_arr # o/p: (array([0., 1.]), array([1, 4]))  /// array([1, 4]) this is predict_arr[1] i.e
                                            # 0 has occurred 1 time and 1 has occurred 4 times select largest


q = np.array([0.0, 4.0])
predicted_label = knn(X_data, q, labels)

if predicted_label == 0.0:
    print "predicted-label : Lemon"
else:
    print "predicted-label : Apple"     
