#include "network.h"

int main(int argc, char const *argv[])
{
    srand(42);

    DPRINT("STARTED!\n");

    char training_file[] = "../MNIST_DATA/mnist_train_vectors.csv";
    load_data((double *)training_data, training_file, INPUT_L);

    char labels_file[] = "../MNIST_DATA/mnist_train_labels.csv";
    load_data((double *)training_data, labels_file, 1);

    HiddenLayer hidden_layer;
    weights_initializer((double *)hidden_layer.weights, 1 + INPUT_L, HIDDEN_L, INPUT_L, OUTPUT_L);

    OutputLayer output_layer;
    weights_initializer((double *)output_layer.weights, 1 + HIDDEN_L, OUTPUT_L, HIDDEN_L, 0);

    double error[1][OUTPUT_L];
    double mean_square_error;

    // Froward pass
    for (int i = 0; i < 1; i++)
    {
        matrix_multiplication((double *)hidden_layer.z, (double *)training_data[i], 1, 1 + INPUT_L, (double *)hidden_layer.weights, 1 + INPUT_L, HIDDEN_L, 1);

        hidden_layer.a[0][1] = 1;
        sigmoid((double *)hidden_layer.a + 1, (double *)hidden_layer.z, HIDDEN_L);

        matrix_multiplication((double *)output_layer.z, (double *)hidden_layer.a, 1, OUTPUT_L, (double *)output_layer.weights, 1 + HIDDEN_L, OUTPUT_L, 1);

        sigmoid((double *)output_layer.a, (double *)output_layer.z, OUTPUT_L);

        DPRINT("Sigmoid\n");
        DPRINT_MATRIX((double *)output_layer.a, OUTPUT_L, 1);

        mean_square_vector((double *)error, (double *)output_layer.a, training_labels[i], OUTPUT_L);
        DPRINT("Errors\n");
        DPRINT_MATRIX((double *)error, OUTPUT_L, 1);

        mean_square_error = sum_of_matrix((double *)error, 1, OUTPUT_L);
        DPRINT("Mean squre error %.10e\n", mean_square_error);
    }
    return 0;
}
