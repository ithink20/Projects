import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

ds = pd.read_csv('./train.csv')  #mnist_train.csv dataset
#print ds.shape

data = ds.values
#print data.shape

y_train = data[:, 0]
X_train = data[:, 1:]
#print y_train.shape, X_train.shape

#Euclidian distance.

def dist(x1, x2):
    return np.sqrt(((x1 - x2)**2).sum())


def knn(X_train, x, y_train, k = 5):
    vals = []
    
    for i in range(X_train.shape[0]):
        v = [dist(x, X_train[i, :]), y_train[i]]
        vals.append(v)
    
    updated_vals = sorted(vals, key = lambda x: x[0])
    pred_arr = np.asarray(updated_vals[ : k])
    pred_arr = np.unique(pred_arr[:, 1], return_counts = True)
    pred = pred_arr[1].argmax()
    # return pred_arr[0][pred]
    return pred_arr, pred_arr[0][pred]

a = 0.0
t = 0.0
for i in range(30):
    idq = int(np.random.random() * X_train.shape[0])
    q = X_train[idq]
    res = knn(X_train[:10000], q, y_train[:10000], k = 7)
    #print res

    print 'Actual : %d'%(y_train[idq])
    print 'Predicted : %d'%(res[1])
    print('')
    if y_train[idq] == res[1]:
        a += 1
    t += 1
   

    plt.figure(0)
    plt.imshow(q.reshape((28, 28)), cmap='gray')
    #plt.show()
ans = (a / t) * 100
print 'Accuracy : %f'%(ans),'%'
