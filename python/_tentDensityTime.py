import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.integrate as integrate

iters = np.array([0,10,100])
r = 1.2
fig = plt.figure()


FileName = "./../data/tentDensity-R" + "{:.6f}".format(r) + ".csv"
#df = pd.read_csv(FileName)
df = pd.read_csv(FileName, header=None).T   # Read csv, and transpose
df.columns = df.iloc[0]                                 # Set new column names
df.drop(0,inplace=True)

keys = df.keys()
maxKey = len(keys)-1
invDensity = df[keys[maxKey]].values
xs = np.linspace(0,1,len(invDensity))
intgrl = integrate.trapezoid(invDensity,xs)
invDensity = invDensity / intgrl

for iter in iters:
    density = df[keys[iter]].values
    #print(np.sum(density))
    intgrl = integrate.trapezoid(density,xs)
    density = density / intgrl
    plt.plot(xs,np.abs(density),label=r"$N = %d$"%int(keys[iter]))
    print(integrate.trapezoid(np.abs(density-invDensity),xs))

#plt.plot(xs,invDensity,'k')
plt.yscale("log")
plt.ylim([1e-6, 1e3])
plt.legend()

fig2 = plt.figure()
plt.plot(xs, invDensity)
plt.yscale("log")

plt.show()