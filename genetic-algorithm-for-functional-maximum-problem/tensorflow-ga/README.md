# Genetic Algorithm Optimization in TensorFlow

## Description

Implemente Genetic Algorithm with Tensorflow to find out the maximum value of the function *f(x)=x+10sin(5x)+7cos(4x)* in the range [0, 9].

While TensorFlow isn't really the best for GA's, this example shows that we can implement different procedural algorithms with TensorFlow operations.

![ga_function](https://raw.githubusercontent.com/yanshengjia/photo/master/ga_function.png)

## Environment

* Tensorflow 1.4.1
* Python 3.6.2
* numpy 1.13.3
* matplotlib 2.1.1

## Usage

```shell
> cd tensorflow-ga
> python3 train_ga.py
```

## References

* [Working with a Genetic Algorithm](https://github.com/nfmcclure/tensorflow_cookbook/tree/master/11_More_with_TensorFlow/02_Working_with_a_Genetic_Algorithm)
* [TensorFlow Machine Learning Cookbook](https://www.packtpub.com/big-data-and-business-intelligence/tensorflow-machine-learning-cookbook), Nick McClure