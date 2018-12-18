# -*- coding: utf-8 -*-
import numpy as np
from PSO import pso


x, value = pso(100, 0.2, 0.2, 0.5, 300, 3)
print(x, value)