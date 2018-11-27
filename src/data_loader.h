#ifndef DATA_LOADER_
#define DATA_LOADER_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "matrix.h"

void load_data(Matrix *output, char *file_name, int line_size, bool one_first,
               void (*encoder)(), int enc_val);

void scaler(double *output, int encode, int size, double max);

void one_hot_encoder(double *output, int encode, int size, double max);

#endif