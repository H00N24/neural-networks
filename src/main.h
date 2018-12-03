#include "data_loader.h"
#include "debug.h"
#include "matrix.h"
#include "network.h"

#define TRAIN_DATA_FILE "../MNIST_DATA/mnist_train_vectors.csv"
#define TRAIN_LABELS_FILE "../MNIST_DATA/mnist_train_labels.csv"

#define TEST_DATA_FILE "../MNIST_DATA/mnist_test_vectors.csv"
#define TEST_LABELS_FILE "../MNIST_DATA/mnist_test_labels.csv"

#define TRAIN_LABELS_OUTPUT_FILE "../TrainPredictions"
#define TEST_LABELS_OUTPUT_FILE "../TestPredictions"