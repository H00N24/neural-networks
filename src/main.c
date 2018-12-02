#include "main.h"

int main(int argc, char const *argv[]) {
  DTIME_INIT;
  srand(42);
  DPRINT("==Start==\n");

  DPRINT("\n==Training data loading: Start==\n");
  DTIME_START_COUNTER;
  Matrix *all_data = matrix_init_lines(60000, 1 + INPUT_L);
  load_data(all_data, TRAIN_DATA_FILE, INPUT_L, true, scaler, 255.0);

  Matrix *all_labels = matrix_init_lines(60000, 10);
  load_data(all_labels, TRAIN_LABELS_FILE, 1, false, one_hot_encoder, 1);

  Matrix *train_data, *train_labels, *eval_data, *eval_labels;

  train_test_split(all_data, all_labels, &train_data, &train_labels, &eval_data,
                   &eval_labels);

  DPRINT("==Training data loading: End (%.2fs)==\n", DTIME_DURATION);

  DPRINT("\n==Network initialization: Start==\n");
  DTIME_START_COUNTER;
  Network *network = final_architecture();
  DPRINT("==Network initialization: End (%.2fs)==\n", DTIME_DURATION);

  train_network(network, 2, 0.2, 32.0, train_data, train_labels, eval_data,
                eval_labels);

  double accuracy;
  DPRINT("\n==Predicting training data: Start ==\n");
  DTIME_START_COUNTER;

  accuracy =
      network_accuracy(network, all_data, all_labels, TRAIN_LABELS_OUTPUT_FILE);

  printf("Test data accuracy %.2f%%\n", accuracy);
  DPRINT("==Predicting training data: End (%.2fs)==\n", DTIME_DURATION);

  matrix_lines_free(all_data);
  matrix_lines_free(all_labels);
  matrix_empty_free(train_data);
  matrix_empty_free(train_labels);
  matrix_empty_free(eval_data);
  matrix_empty_free(eval_labels);

  DPRINT("\n==Predicting testing data: Start ==\n");
  DTIME_START_COUNTER;

  Matrix *test_data = matrix_init_lines(10000, 1 + INPUT_L);
  load_data(test_data, TEST_DATA_FILE, INPUT_L, true, scaler, 255.0);

  Matrix *test_labels = matrix_init_lines(10000, 10);
  load_data(test_labels, TEST_LABELS_FILE, 1, false, one_hot_encoder, 1);

  accuracy = network_accuracy(network, test_data, test_labels,
                              TEST_LABELS_OUTPUT_FILE);

  printf("Test data accuracy %.2f%%\n", accuracy);
  DPRINT("==Predicting testing data: End (%.2fs)==\n", DTIME_DURATION);

  DPRINT("\n==Total time %.2fs==\n", DTIME_END);

  matrix_lines_free(test_data);
  matrix_lines_free(test_labels);
  network_free(network);
  return 0;
}
