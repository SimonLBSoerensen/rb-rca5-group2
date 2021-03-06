#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  5 14:39:15 2018

@author: simonlbs
"""


import sys
import numpy as np
import matplotlib.pyplot as plt
import json
import tkinter as tk
from tkinter.filedialog import askopenfilename
root = tk.Tk()
root.withdraw()

def movingAvg(x,w):
    return np.convolve(x, np.ones((w,))/w)[(w-1):]

def rooling(l, alfa):
    tl = [l[0]]
    for v in l[1:]:
        tl.append(alfa*v + (1-alfa)*tl[-1])
    return tl

file = askopenfilename(title = "JSON file")
if len(file) == 0:
    sys.exit()
    
with open(file) as f:
    data = json.load(f)

legend = []
plotString = "("
count = 0

windo = 500
alphaColor = 0.5

ydata = []
xdata = []
while True:
    if "xdata_{}".format(count) in data:
        if "legend_{}".format(count) in data:      
            print(data["legend_{}".format(count)])
            greedy = float(data["legend_{}".format(count)].split()[1])
            xdata.append(greedy)
            
            y_data = data["ydata_{}".format(count)]
            y_data = np.mean(y_data, axis=0)
            y_data = np.mean(y_data)
            ydata.append(y_data) 
        else:
            None
        count += 1
    else:
        break

#file = askopenfilename(title = "JSON file")
#if len(file) == 0:
#    sys.exit()
#    
#with open(file) as f:
#    data = json.load(f)
#count = 0
#while True:
#    if "xdata_{}".format(count) in data:
#        if "legend_{}".format(count) in data:      
#            print(data["legend_{}".format(count)])
#            greedy = float(data["legend_{}".format(count)].split()[1])
#            xdata.append(greedy)
#            
#            y_data = data["ydata_{}".format(count)]
#            y_data = np.mean(y_data, axis=0)
#            y_data = np.mean(y_data)
#            ydata.append(y_data) 
#        else:
#            None
#        count += 1
#    else:
#        break    
    
mapTemp = {}
count = 0
for x in xdata:
    mapTemp[x] = count
    count += 1

xdata = list(sorted(xdata))
ydataTemp = []
for x in xdata:
    ydataTemp.append(ydata[mapTemp[x]])
ydata = ydataTemp
alfaRunning = 1#0.35
ydata = rooling(ydata,alfaRunning)

plt.xlabel(r"$\epsilon$")
plt.ylabel("Average reward over the first 200000 episodes")
plt.plot(xdata,ydata)
#plt.legend(bbox_to_anchor=(1,0.5), loc="center left")
plt.rcParams.update({'font.size': 20})
#plt.legend()
plt.grid(color='grey', linestyle='--')
plt.title(data["titel"])

plt.show()

