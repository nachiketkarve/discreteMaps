import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

isSingleCol = 0
colFrac = 0.97
htFrac = 0.7

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

r = 1.3
p = 0.5
w = 0.01

fig = plt.figure()

FileName = "./../data/tent-R" + "{:.6f}".format(r) + ".csv"
df = pd.read_csv(FileName)
Iters = np.array(df["Iters"].values.tolist())
Variance = np.array(df["Variance"].values.tolist())
plt.plot(Iters,Variance,label=r"Uniform",color='b')

FileName = "./../data/tent-R" + "{:.6f}".format(r) + "-P" + "{:.6f}".format(p) + "-W" + "{:.6f}".format(w) + ".csv"
df = pd.read_csv(FileName)
Iters = np.array(df["Iters"].values.tolist())
Variance = np.array(df["Variance"].values.tolist())
plt.plot(Iters,Variance,label=r"Narrow",color='r')

plt.legend(frameon=False,fontsize=8)
plt.xscale('log')
plt.yscale('log')
plt.xlabel(r"$N$")
plt.ylabel(r"$\langle\sigma^2_N\rangle$")
plt.xlim([100, np.max(Iters)])
plt.xticks(fontsize=7)
plt.yticks(fontsize=7)
plt.tight_layout(pad=0.5)
plt.savefig("./../plot/tentDriftVarComp.pdf",dpi=100)
plt.savefig("./../plot/tentDriftVarComp.eps",dpi=100,format='eps')