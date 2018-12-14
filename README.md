# PV021 Neural networks project

Simple feedforward neural network trained by SGD, backpropagation and mean square error.
* [Repository](https://github.com/H00N24/neural-networks/)

## Authors
* Róbert Kolcún [@NoName115](https://github.com/NoName115)
* Ondrej Kurák [@H00N24](https://github.com/H00N24)

## Usage
```
$ ./RUN
```

#### Outputs
* `trainPredictions` - predicted labels for train vectors (train + eval)
* `actualTestPredictions` - predicted labels fot test vectors


### Makefile
`src/Makefile`
#### Debug
* Enables debug prints
```
$ make debug
$ ./network
==Start==

==Training data loading: Start==
File opened: ../MNIST_DATA/mnist_train_vectors.csv
File opened: ../MNIST_DATA/mnist_train_labels.csv
==Training data loading: End (1.00s)==

==Network initialization: Start==
==Network initialization: End (0.02s)==

==Training: Start==
2 epochs, 0.200 training rate, 32 batch size
Training data shape: (48000, 785)
Training labels shape: (48000, 10)
Eval data shape: (12000, 785)
Eval labels shape: (12000, 10)
Epoch 1: 100%
  Time: 76.25s
  Eval accuracy: 94.17%
Epoch 2: 100%
  Time: 76.17s
  Eval accuracy: 95.88%
==Training: End==

==Predicting training data: Start ==
Test data accuracy 96.48%
==Predicting training data: End (37.96s)==

==Predicting testing data: Start ==
File opened: ../MNIST_DATA/mnist_test_vectors.csv
File opened: ../MNIST_DATA/mnist_test_labels.csv
Test data accuracy 96.20%
==Predicting testing data: End (6.51s)==

==Total time 212.80s==
```
#### Test
- Compiles and runs unit tests
```
$ make test
./test
............

OK (12 tests)
```

#### Profile
- profiling using `gprof`
```
$ make profile
$ ./network
$ gprof ./network
```