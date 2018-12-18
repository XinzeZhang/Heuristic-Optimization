# -*- coding: utf-8 -*-

import numpy as np
from xxx import fitness
'''
fitness function, import from other package;
the input is 1-dimension np array; the return is a number and smaller is better
'''

# position, value = pso(100, 0.2, 0.2, 0.5, 300, 3)

def pso(num, c1, c2, w, iter, d):
    '''
    :param num: number of particles
    :param c1: cognitive coefficient
    :param c2: social cognition coefficient
    :param w: inertia weight
    :param iter: iteration times
    :param d: dimension of one particle
    '''
    # x_c1=np.arange(100)
    # x_c2=x_c1
    # x_c3=x_c1
    # position=np.array([x_c1,x_c2,x_c1],np.float64).T
    # randomly initialize the position; shape: (num,d)
    position = np.random.randn(num, d)
    # randomly initialize the speed; shape: (num,d)
    delta = np.random.randn(num, d)

    pbest_fitness = np.zeros(num)  # shape: (num,)
    pbest_position = np.zeros(num,d) #shape: (num,d)
    gbest_position = position[num-1]    # initialize the global best position ; shape: (1,d)

    # initialization
    for i in range(num):
        # initialize the present best fitness for each particle
        pbest_fitness[i] = fitness(position[i])
    pbest_position = position    # initialize the present best position for each particle

    for i in range(num):
        # find the smaller gBest
        if fitness(position[i]) < fitness(gbest_position):
            gbest_position = position[i]

    # update
    for t in range(iter):
        for i in range(num):

            delta[i] = w*delta[i] + c1*np.random.rand()*(pbest_position[i]-position[i]) + \
                c2*np.random.rand()*(gbest_position -
                                     position[i])   # update the speed
            position[i] = position[i] + delta[i]   # update the position

            p_i_t_Fitness = fitness(position[i])

            if p_i_t_Fitness < pbest_fitness[i]:  # find the smaller pBest from history of pBest
                pbest_fitness[i] = p_i_t_Fitness
                # find the best position for each particle in the movement
                pbest_position[i] = position[i]
            if pbest_fitness[i] < fitness(gbest_position): # find the smaller gBest from pBest
                # update the global best position
                gbest_position = pbest_position[i]

    return gbest_position, fitness(gbest_position)
