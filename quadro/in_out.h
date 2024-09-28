#ifndef IN_OUT_H
#define IN_OUT_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#include "quadro_structs.h"

void buffer_clean();

double coef_input(char coef_name);

coefs quadro_input();

void quadro_output(roots *roots);

#endif