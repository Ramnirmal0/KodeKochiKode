import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
dataset =pd.read_csv('machine_learning_dataset2.csv')
x=dataset.iloc[:,:4].values
from sklearn.cluster import KMeans
wcss=[]
for i in range(1,11):
    kmeans=KMeans(n_clusters=i,init='k-means++',n_init=10,max_iter=300,random_state=0)
    y_kmeans=kmeans.fit(x)
    wcss.append(kmeans.inertia_)
plt.plot(range(1,11),wcss)
plt.title("elbow method")
plt.xlabel("number of cluster")
plt.ylabel("wcss")
plt.show()
kmeans=KMeans(n_clusters=4,init='k-means++',n_init=10,max_iter=300,random_state=0)
y_kmeans=kmeans.fit_predict(x)
#visualising the cluster
plt.scatter(x[y_kmeans==0,0],x[y_kmeans==0,1],s=100,c='red',label='lazy')
plt.scatter(x[y_kmeans==1,0],x[y_kmeans==1,1],s=100,c='blue',label='normal')
plt.scatter(x[y_kmeans==2,0],x[y_kmeans==2,1],s=100,c='green',label='coders')
plt.scatter(x[y_kmeans==3,0],x[y_kmeans==3,1],s=100,c='cyan',label='healthy')
#ploting centroid
plt.scatter(kmeans.cluster_centers_[:,0],kmeans.cluster_centers_[:,1],s=300,c='yellow')
plt.title('ml analysis')
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.show()

#supervised learning

x_r=dataset.iloc[:,:3].values
y_r=dataset.iloc[:,3].values
from sklearn.preprocessing import StandardScaler
sc_X = StandardScaler()
x_r = sc_X.fit_transform(x_r)

from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(x_r, y_r, test_size = 0.2, random_state = 0)

# Feature Scaling


import keras
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Dropout
# Initialising the Ann and Hidden Layers 
regg = Sequential()
regg.add(Dense(units = 100, kernel_initializer = 'uniform', activation = 'relu', input_dim = 3))
regg.add(Dropout(rate = 0.2))
regg.add(Dense(units = 100, kernel_initializer = 'uniform', activation = 'relu'))
regg.add(Dropout(rate = 0.2))
regg.add(Dense(units = 50, kernel_initializer = 'uniform', activation = 'relu'))
regg.add(Dropout(rate = 0.2))
regg.add(Dense(units = 1, kernel_initializer = 'uniform', activation = 'softmax'))

regg.compile(optimizer = 'SGD', loss = 'poisson', metrics = ['accuracy'])

# Fitting the ANN to the Training set
regg.fit(X_train, y_train, batch_size = 200, epochs = 100)

# Part 3 - Making predictions and evaluating the model

# Predicting the Test set results
y_pred = regg.predict(X_test)
#model2
from sklearn.ensemble import RandomForestRegressor
regg=RandomForestRegressor(n_estimators=300,random_state=0)
regg.fit(X_train, y_train)
# Predicting a new result
y_pred = regg.predict(X_test)
