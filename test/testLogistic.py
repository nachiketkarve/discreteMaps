import numpy as np
import matplotlib.pyplot as plt

def logistic(x,r):
    return r * x * (1 - x)

iters = 1000
r = 0.5
x = 0.8

for i in range(iters):
    x = logistic(x,r)
    print(f"Iteration {i}: x = {x:.100f}")
