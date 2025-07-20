import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

rs = np.array([1.2])
p = 0.5
w = 0.01

fig = plt.figure()

for i in range(len(rs)):
    r = rs[i]
    FileName = "./../data/tent-R" + "{:.6f}".format(r) + "-P" + "{:.6f}".format(p) + "-W" + "{:.6f}".format(w) + ".csv"
    df = pd.read_csv(FileName)
    Iters = np.array(df["Iters"].values.tolist())
    Variance = np.array(df["Variance"].values.tolist())
    plt.plot(Iters,Variance,label=r"$r = $%.2f"%r)

#p = np.polyfit(np.log(Iters[int(len(Iters)*0.99):len(Iters)-1]),np.log(Variance[int(len(Iters)*0.99):len(Iters)-1]),1)

#print(p)

#plt.plot(Iters[int(len(Iters)*0.99):len(Iters)-1],np.exp(p[0]*np.log(Iters[int(len(Iters)*0.99):len(Iters)-1])+p[1]),'k--')
plt.legend()
plt.xscale('log')
plt.yscale('log')
plt.xlabel("Iterations")
plt.ylabel("Variance")
plt.show()