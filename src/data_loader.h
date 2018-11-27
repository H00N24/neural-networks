#ifndef DATA_LOADER_
#define DATA_LOADER_

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

void load_data(double *output, char *file_name, int line_size,
               void (*encoder)(), int enc_size);

void scaler(double *result, int encode, int max);

void one_hot_encoder(double *result, int encode, int size);

#endif