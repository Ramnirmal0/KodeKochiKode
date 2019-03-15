import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
dataset =pd.read_csv('machine_learning_dataset.csv')
x=dataset.iloc[:,[0,1,3,4]].values
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
plt.scatter(x[y_kmeans==0,0],x[y_kmeans==0,1],s=100,c='red',label='healthy')
plt.scatter(x[y_kmeans==1,0],x[y_kmeans==1,1],s=100,c='blue',label='normal')
plt.scatter(x[y_kmeans==2,0],x[y_kmeans==2,1],s=100,c='green',label='coders')
plt.scatter(x[y_kmeans==3,0],x[y_kmeans==3,1],s=100,c='cyan',label='lazy')
#ploting centroid
plt.scatter(kmeans.cluster_centers_[:,0],kmeans.cluster_centers_[:,1],s=300,c='yellow')
plt.title('ml analysis')
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.show()