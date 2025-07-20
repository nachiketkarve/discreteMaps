import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.integrate as integrate
from matplotlib import ticker as mticker

isSingleCol = 1
colFrac = 0.47
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

iters = np.array([0,10,100])
cs = ['b','r','g']
r = 1.3
p = 0.5
w = 0.01
fig,ax = plt.subplots()


FileName = "./../data/tentDensity-R" + "{:.6f}".format(r) + "-P" + "{:.6f}".format(p) + "-W" + "{:.6f}".format(w) + ".csv"
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
    intgrl = integrate.trapezoid(density,xs)
    density = density / intgrl
    plt.plot(xs,np.abs(density),label=r"$N = %d$"%int(keys[iter]),color=cs[np.where(iters==iter)[0][0]])
    print(integrate.trapezoid(np.abs(density-invDensity),xs))

#plt.plot(xs,invDensity,'k')
plt.yscale("log")
plt.yticks(fontsize=7)
plt.xticks(fontsize=7)
plt.xlim([0.2,0.8])
plt.ylim([1e-6, 1e3])
plt.legend(frameon=False,fontsize=8)
plt.xlabel(r"$x$")
plt.ylabel(r"$\bar{\rho}_N(x)$")
ax.yaxis.set_major_locator(mticker.LogLocator(numticks=999))
ax.yaxis.set_minor_locator(mticker.LogLocator(numticks=999, subs="auto"))
plt.tight_layout()
plt.savefig("./../plot/tentDensityNarrow.pdf",dpi=100)
plt.savefig("./../plot/tentDensityNarrow.eps",dpi=100,format='eps')