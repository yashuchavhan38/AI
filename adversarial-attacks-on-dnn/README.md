# Adversarial Attacks on Deep Neural Networks

## Introduction

In this project, we will investigate adversarial perturbation attacks on Deep Neural Networks using the MNIST digits dataset as a benchmark. We will then evaluate adversarial retraining as a defense against adversarial perturbations.

## Dataset

The MNIST dataset will be used in this project. The MNIST dataset is a commonly used 'toy' benchmarks for machine learning. It contains a train set of 60000 28x28 grayscale images of hand-drawn digits from 0-9, along with the associated labels. Also, it contains a test set of 10000 images. The dataset is available as part of the tensorflow package, which we will be using extensively in this project. For more details, please see the [link](https://colab.research.google.com/github/tensorflow/docs/blob/master/site/en/tutorials/quickstart/beginner.ipynb#scrollTo=7NAbSZiaoJ4z) of how to use MNIST dataset.

## Approach

Adversarial input attacks can be broadly classified into two types, one is non-targeted attack and the other is targeted attack.

- Non-targeted Attack: Aiming to fool the neural network and output a label different than the original one.
- Targeted Attack: Intentionally misleading the network to output a specific label designed by the attacker.

To fool the neural network, we need a special kind of input data called adversarial examples. The process of adding these perturbations is fast gradient sign method (FGSM). It works by using the gradients of the neural network to create an adversarial example.