import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

rs = np.array([3.1,3.2,3.3,3.4])
fig = plt.figure()

for r in rs:
    FileName = "./../data/logisticDensity-R" + "{:.6f}".format(r) + ".csv"
    #df = pd.read_csv(FileName)
    df = pd.read_csv(FileName, header=None).T   # Read csv, and transpose
    df.columns = df.iloc[0]                                 # Set new column names
    df.drop(0,inplace=True)

    keys = df.keys()
    maxKey = len(keys)-1
    invDensity = df[keys[maxKey]].values
    xs = np.linspace(0,1,len(invDensity))
    deltaX = xs[1]-xs[0]

    diff = np.array([])

    for i in range(maxKey+1):
        density = df[keys[i]].values
        deltaDensity = np.abs(density - invDensity)
        diff = np.append(diff,np.sum(deltaDensity)*deltaX)

    plt.plot(np.array(keys),diff)

plt.yscale("log")
plt.xscale("log")
plt.show()