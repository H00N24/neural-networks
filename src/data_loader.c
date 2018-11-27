
#include "data_loader.h"

void load_data(double *output, char *file_name, int line_size,
               void (*encoder)(), int enc_size) {
  FILE *csv_file = fopen(file_name, "r");
  if (!csv_file) exit(1);
  DPRINT("File opend: %s\n", file_name);
  int c = 0;
  int line_index = 0;
  int inline_index = 0;
  int value = 0;

  while ((c = fgetc(csv_file)) != EOF) {
    if (inline_index == 0) {
      *((output + line_index * line_size) + inline_index) = 1;
      inline_index++;
    }

    switch (c) {
      case '\n': {
        *((output + line_index * line_size) + inline_index) = (double)value;
        // encoder(((output + line_index * line_size) + inline_index), value,
        //        enc_size);
        line_index++;
        value = 0;
        inline_index = 0;
        break;
      }
      case ',': {
        *((output + line_index * line_size) + inline_index) = (double)value;
        // encoder(((output + line_index * line_size) + inline_index), value,
        //        enc_size);
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

void scaler(double *result, int encode, int max) {
  *(result) = encode / (double)max;
}

void one_hot_encoder(double *result, int encode, int size) {
  for (int i; i < size; i++) {
    *(result + i) = (encode == i) ? 1 : 0;
  }
}