import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.integrate as integrate

rs = np.array([1.2])
p = 0.5
w = 0.01
fig = plt.figure()

for r in rs:
    FileName = "./../data/tentDensity-R" + "{:.6f}".format(r) + "-P" + "{:.6f}".format(p) + "-W" + "{:.6f}".format(w) + ".csv"
    #df = pd.read_csv(FileName)
    df = pd.read_csv(FileName, header=None).T   # Read csv, and transpose
    df.columns = df.iloc[0]                                 # Set new column names
    df.drop(0,inplace=True)

    keys = df.keys()
    maxKey = len(keys)-1
    invDensity = df[keys[maxKey]].values
    xs = np.linspace(0,1,len(invDensity))
    deltaX = xs[1]-xs[0]
    intgrl = integrate.trapezoid(invDensity,xs)
    invDensity = invDensity / intgrl

    diff = np.array([])

    for i in range(maxKey+1):
        density = df[keys[i]].values
        intgrl = integrate.trapezoid(density,xs)
        density = density / intgrl
        deltaDensity = np.abs(density - invDensity)
        diff = np.append(diff,integrate.trapezoid(deltaDensity,xs))

    plt.plot(np.array(keys),diff)

    FileName = "./../data/tentDensity-R" + "{:.6f}".format(r) + ".csv"
    #df = pd.read_csv(FileName)
    df = pd.read_csv(FileName, header=None).T   # Read csv, and transpose
    df.columns = df.iloc[0]                                 # Set new column names
    df.drop(0,inplace=True)

    keys = df.keys()
    maxKey = len(keys)-1
    invDensity = df[keys[maxKey]].values
    xs = np.linspace(0,1,len(invDensity))
    deltaX = xs[1]-xs[0]
    intgrl = integrate.trapezoid(invDensity,xs)
    invDensity = invDensity / intgrl

    diff = np.array([])

    for i in range(maxKey+1):
        density = df[keys[i]].values
        intgrl = integrate.trapezoid(density,xs)
        density = density / intgrl
        deltaDensity = np.abs(density - invDensity)
        diff = np.append(diff,integrate.trapezoid(deltaDensity,xs))

    plt.plot(np.array(keys),diff)

plt.yscale("log")
plt.xscale("log")
plt.show()