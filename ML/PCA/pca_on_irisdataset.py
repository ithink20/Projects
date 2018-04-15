

## NOTE: This is Python 3 code.
import pandas as pd
import numpy as np
import random as rd
from sklearn.decomposition import PCA
from sklearn import preprocessing
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
 
url = "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data"

#load dataset into pandas dataFrame

df = pd.read_csv(url, names=['sepal length','sepal width','petal length','petal width','target'])
features = ['sepal length', 'sepal width', 'petal length', 'petal width']

# Separating out the features
x = df.loc[:, features].values
# print (x)

# Standardizing the features
x = StandardScaler().fit_transform(x)



# print (np.cov(x.T))
cov_mat = np.cov(x.T)
eig_vals, eig_vecs = np.linalg.eig(cov_mat)

total = sum(eig_vals)
var_exp = [(i/total) * 100 for i in sorted(eig_vals, reverse = True)]
cum_var_exp = np.cumsum(var_exp)
# print cum_var_exp

with plt.style.context('seaborn-whitegrid'):
	plt.figure(figsize=(6, 4))
	plt.bar(range(4), var_exp, alpha= 0.5, align='center', label='individual explained variance')
	plt.step(range(4), cum_var_exp, where='mid', label='cumulative explained variance')
	plt.ylabel('Explained variance ratio')
	plt.xlabel('Principal components')
	plt.legend(loc='best')
	plt.tight_layout()
	# plt.savefig('/home/ithink/Desktop/pca2.pdf')
	plt.show()



# pca = PCA(.95) #needed components of variance amount.
pca = PCA(n_components = 2)

pc = pca.fit_transform(x)
# print (pca.n_components_)
pDf = pd.DataFrame(data = pc, columns = ['principal component 1', 'principal component 2'])

finalDf = pd.concat([pDf, df[['target']]], axis = 1)

# print (finalDf)

fig = plt.figure(figsize = (8,8))
ax = fig.add_subplot(1,1,1)
ax.set_xlabel('Principal Component 1', fontsize = 15)
ax.set_ylabel('Principal Component 2', fontsize = 15)
ax.set_title('2 component PCA', fontsize = 20)

targets = ['Iris-setosa', 'Iris-versicolor', 'Iris-virginica']
colors = ['r', 'g', 'b']

for target, color in zip(targets,colors):
    indicesToKeep = finalDf['target'] == target
    ax.scatter(finalDf.loc[indicesToKeep, 'principal component 1']
               , finalDf.loc[indicesToKeep, 'principal component 2']
               , c = color
               , s = 50)
ax.legend(targets)
ax.grid()
# plt.show()

pc1 = pca.explained_variance_ratio_[0]
pc2 = pca.explained_variance_ratio_[1]

print ("Together two components : {:.2%}".format(pc1 + pc2))