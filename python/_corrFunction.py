import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

rs = np.array([3.5])

fig = plt.figure()

for i in range(len(rs)):
    r = rs[i]
    FileName = "./../data/logisticCorrFn-R" + "{:.6f}".format(r) + ".csv"
    df = pd.read_csv(FileName)
    Time = np.array(df["Time"].values.tolist())
    CorrFn = np.array(df["CorrFn"].values.tolist())
    plt.plot(Time,CorrFn,label=r"$r = $%.2f"%r)

plt.legend()
#plt.xscale('log')
#plt.yscale('log')
plt.show()
