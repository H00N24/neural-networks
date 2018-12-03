#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdbool.h>
#include <stdlib.h>
#include "activation_functions.h"
#include "error_functions.h"
#include "layer.h"
#include "matrix.h"
#include "utils.h"

#define INPUT_L 28 * 28
#define HIDDEN_L 300
#define OUTPUT_L 10

typedef struct network_obj {
  int num_of_layers;
  Layer **layers;

} Network;

Network *network_init(int num_of_layers);

void network_free(Network *network);

Network *final_architecture();

double network_accuracy(Network *network, Matrix *test_data,
                        Matrix *test_labels, char *output_file_name);

void train_network(Network *network, int epochs, double training_rate,
                   double mini_batch_size, Matrix *train_data,
                   Matrix *train_labels, Matrix *eval_data,
                   Matrix *eval_labels);
#endif