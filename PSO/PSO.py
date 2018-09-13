# -*- coding: utf-8 -*-

import numpy as np
from xxx import fitness
'''
fitness function, import from other package;
the input is 1-dimension np array; the return is a number and smaller is better
'''

def pso(n, c1, c2, w, iter, d):
    '''
    :param n: number of particles
    :param c1: cognitive coefficient
    :param c2: social cognition coefficient
    :param w: inertia weight
    :param iter: iteration times
    :param d: dimension of one particle
    '''
    x_c1=np.arange(100)
    x_c2=x_c1
    x_c3=x_c1
    x=np.array([x_c1,x_c2,x_c1],np.float64).T
    # x = np.random.randn(n, d)   # randomly initialize the position
    v = np.random.randn(n, d)   # randomly initialize the speed

    pbest_fitness = np.zeros(n)
    for i in range(n):
        pbest_fitness[i] = fitness(x[i])    # initialize the present best fitness for each particle
    pbest_position = x    # initialize the present best position for each particle

    gbest_position = x[n-1]    # initialize the global best position
    for i in range(n):
        if fitness(x[i]) < fitness(gbest_position):
            gbest_position = x[i]

    for t in range(iter):
        for i in range(n):

            v[i] = w*v[i] + c1*np.random.rand()*(pbest_position[i]-x[i]) + c2*np.random.rand()*(gbest_position-x[i])   # update the speed
            x[i] = x[i] + v[i]   # update the position

            if fitness(x[i]) < pbest_fitness[i]:
                pbest_fitness[i] = fitness(x[i])
                pbest_position[i] = x[i]   # find the best position for each particle in the movement
            if pbest_fitness[i] < fitness(gbest_position):
                gbest_position = pbest_position[i]   # update the global best position

    return gbest_position, fitness(gbest_position)
