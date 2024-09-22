#ifndef SOLVER_H
#define SOLVER_H

#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#include "quadro_structs.h"

double diskr(coefs *coefs);

bool is_zero(double d);

roots quadro_solution(coefs *coefs);

#endif