
#include "data_loader.h"

void load_data(double *output, char *file_name, int line_size)
{
    FILE *csv_file = fopen(file_name, "r");
    if (!csv_file)
        exit(1);

    int c = 0;
    int line_index = 0;
    int inline_index = 0;
    int value = 0;
    while ((c = fgetc(csv_file)) != EOF)
    {
        switch (c)
        {
        case '\n':
        {
            line_index++;
            inline_index = 0;
            *((output + line_index * line_size) + inline_index) = 1;
            inline_index++;
            break;
        }
        case ',':
        {
            *((output + line_index * line_size) + inline_index) = (double)value;
            value = 0;
            inline_index++;
            break;
        }
        default:
        {
            value *= 10;
            value += c - '0';
            break;
        }
        }
    }

    fclose(csv_file);
}