# -*- coding: utf-8 -*-

import numpy as np

def fitness(x):
    t = 0
    for i in range(len(x)):
        t = t + x[i]*x[i]
    return t