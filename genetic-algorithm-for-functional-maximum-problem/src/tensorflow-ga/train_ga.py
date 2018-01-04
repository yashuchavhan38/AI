# !/usr/bin/python
# -*- coding:utf-8 -*-  
# @author: Shengjia Yan
# @date: 2018-01-02 Tuesday
# @email: i@yanshengjia.com
#
# Genetic Algorithm Optimization in TensorFlow
#
# We are going to implement a genetic algorithm to optimize to find out the maximum value of the function 
# f(x)=x+10sin(5x)+7cos(4x)
# in the range [0, 9].
#
# We will use TensorFlow's update function to run the different parts of the genetic algorithm.

import os
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.python.framework import ops



