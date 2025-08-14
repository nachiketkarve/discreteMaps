import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

isSingleCol = 1
colFrac = 0.45
htFrac = 0.8

doubleColpt = 246
singleColpt = 510

fig_width_pt = (isSingleCol*singleColpt + (1-isSingleCol)*doubleColpt)
inches_per_pt = 1.0/72.27
golden_mean = (np.sqrt(5)-1.0)/2.0
fig_width = fig_width_pt*inches_per_pt
fig_height = fig_width*golden_mean
fig_size = [fig_width*colFrac,fig_width*colFrac*htFrac]
fig_font = 10
params = {'backend' : 'ps',
          'axes.labelsize': fig_font,
          'font.size': fig_font,
          'legend.fontsize': fig_font,
          'xtick.labelsize': fig_font,
          'ytick.labelsize': fig_font,
          'text.usetex': True,
          'figure.figsize': fig_size,
          'font.family': 'serif',
          'font.serif': 'STIX',
          'mathtext.fontset': 'stix'}

plt.rcParams.update(params)

rs = np.array([3.1])

fig = plt.figure()

for i in range(len(rs)):
    r = rs[i]
    FileName = "./../data/logisticCorrFn-R" + "{:.6f}".format(r) + ".csv"
    df = pd.read_csv(FileName)
    Time = np.array(df["Time"].values.tolist())
    CorrFn = np.array(df["CorrFn"].values.tolist())
    plt.plot(Time,CorrFn,label=r"$r = $%.2f"%r)

#plt.legend()
#plt.xscale('log')
#plt.yscale('log')
#plt.xlim([0, 50])
plt.ylim([-0.001, 0.02])
plt.grid()
plt.xlabel(r"$t$")
plt.ylabel(r"$\langle\partial_\lambda H(t)\partial_\lambda H(0)\rangle_c$")
plt.tight_layout()
plt.show()

plt.savefig("./../plot/logisticCorrFn-R" + "{:.6f}".format(r) + ".pdf", dpi=100)
