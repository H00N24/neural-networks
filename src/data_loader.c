
#include "data_loader.h"

void load_data(Matrix *output, char *file_name, int line_size, bool one_first,
               void (*encoder)(), double enc_val) {
  FILE *csv_file = fopen(file_name, "r");
  if (!csv_file) exit(1);
  DPRINT("File opened: %s\n", file_name);
  int c = 0;
  int line_index = 0;
  int inline_index = 0;
  int value = 0;

  while (line_index < output->m && (c = fgetc(csv_file)) != EOF) {
    switch (c) {
      case '\n': {
        output->data[line_index][inline_index] = (double)value;
        inline_index++;

        encoder(output->data[line_index], value, output->n, enc_val);

        if (one_first) {
          output->data[line_index][inline_index] = 1;
        }
        line_index++;
        value = 0;
        inline_index = 0;
        break;
      }
      case ',': {
        output->data[line_index][inline_index] = (double)value;
        value = 0;
        inline_index++;
        break;
      }
      default: {
        value *= 10;
        value += c - '0';
        break;
      }
    }
  }

  fclose(csv_file);
}

void scaler(double *output, int encode, int size, double max) {
  for (int i = 0; i < size - 1; i++) {
    output[i] /= max;
  }
}

void one_hot_encoder(double *output, int encode, int size, double max) {
  for (int i = 0; i < size; i++) {
    output[i] = (encode == i) ? 1 : 0;
  }
}