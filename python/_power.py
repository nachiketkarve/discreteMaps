import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

rs = np.arange(0,4.0,0.01)

fig = plt.figure()

nonLins = np.array([])
powers = np.array([])

for i in range(len(rs)):
    r = rs[i]
    FileName = "./../data/logistic-R" + "{:.6f}".format(r) + ".csv"
    try:
        df = pd.read_csv(FileName)
        Iters = np.array(df["Iters"].values.tolist())
        Variance = np.array(df["Variance"].values.tolist())
        ItersEnd = Iters[int(len(Iters)*5.0/10.0):len(Iters)-1]
        VarianceEnd = Variance[int(len(Iters)*5.0/10.0):len(Iters)-1]

        nonLins = np.append(nonLins, r)
        powers = np.append(powers, np.polyfit(np.log(ItersEnd), np.log(VarianceEnd), 1)[0])

    except FileNotFoundError:
        continue

plt.plot(nonLins, powers)
plt.grid()
plt.savefig('../plot/_power.pdf',dpi=100)
plt.show()