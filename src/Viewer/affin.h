#ifndef INC_AFFINE_H
#define INC_AFFINE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

void rotation(double angle, int axis, ObjData* obj);
void scale(double* x, double* y, double* z, ObjData* obj, double* dop_x,
           double* dop_y, double* dop_z);
void translate(double x, double y, double z, ObjData* obj, double* dop_x,
               double* dop_y, double* dop_z);

#endif  // INC_AFFINE_H
