import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

isSingleCol = 0
colFrac = 0.95
htFrac = 0.75

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

K = 1

FileName = "./stdPhase-K" + "{:.6f}".format(K) + ".csv"
df = pd.read_csv(FileName,header=None).values

x0s = np.linspace(0.01,2.0*np.pi-0.01,len(df))
p0s = np.linspace(0.01,2.0*np.pi-0.01,len(df))

ctUp = 0
ctDown = 0
ctLin = 0
for i in range(len(df)):
    for j in range(len(df)):
        if df[i,j] > 2.3:
            ctUp = ctUp + 1
        if df[i,j] < -0.3:
            ctDown = ctDown + 1
        if df[i,j] < 1.5 and df[i,j] > 0.5:
            ctLin = ctLin + 1

print(ctUp)
print(ctDown)
print(ctLin)
print(len(df)**2)

X,Y = np.meshgrid(x0s,p0s)
cs = plt.pcolormesh(X,Y,df,cmap='magma',rasterized=True,vmax=2.3,vmin=-0.3)
cbar = plt.colorbar(cs)
plt.xlabel(r"$x$")
plt.ylabel(r"$p$")
cbar.set_label(r"$\gamma$")
cbar.ax.tick_params(labelsize=8)
plt.xticks(fontsize=8)
plt.yticks(fontsize=8)
plt.tight_layout(pad=0.2)

plt.savefig("stdExponents.pdf",dpi=300)
plt.savefig("stdExponents.eps",dpi=300,format="eps")


#plt.show()
