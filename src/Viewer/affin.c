#include "affin.h"

void translate(double x, double y, double z, ObjData* obj, double* dop_x,
               double* dop_y, double* dop_z) {
  for (int i = 0; i < obj->num_vertices; i += 3) {
    obj->vertices[i] -= *dop_x;
    obj->vertices[i] += x;
    obj->vertices[i + 1] -= *dop_y;
    obj->vertices[i + 1] += y;
    obj->vertices[i + 2] -= *dop_z;
    obj->vertices[i + 2] += z;
  }
  *dop_z = z;
  *dop_y = y;
  *dop_x = x;
}

void scale(double* x, double* y, double* z, ObjData* obj, double* dop_x,
           double* dop_y, double* dop_z) {
  for (int i = 0; i < obj->num_vertices; i += 3) {
    obj->vertices[i] /= *dop_x;
    obj->vertices[i] *= *x;
    obj->vertices[i + 1] /= *dop_y;
    obj->vertices[i + 1] *= *y;
    obj->vertices[i + 2] /= *dop_z;
    obj->vertices[i + 2] *= *z;
  }
  *dop_z = *z;
  *dop_y = *y;
  *dop_x = *x;
}

void rotation(double angle, int axis, ObjData* obj) {
  double new_angle = angle * M_PI / 180;
  for (int i = 0; i < obj->num_vertices; i += 3) {
    double x = obj->vertices[i];
    double y = obj->vertices[i + 1];
    double z = obj->vertices[i + 2];
    // Поворот по X
    if (axis == 0) {
      obj->vertices[i + 1] = y * cos(new_angle) - z * sin(new_angle);
      obj->vertices[i + 2] = y * sin(new_angle) + z * cos(new_angle);
      // Поворот по Y
    } else if (axis == 1) {
      obj->vertices[i] = x * cos(new_angle) + z * sin(new_angle);
      obj->vertices[i + 2] = -x * sin(new_angle) + z * cos(new_angle);
      // Поворот по Z
    } else {
      obj->vertices[i] = x * cos(new_angle) - y * sin(new_angle);
      obj->vertices[i + 1] = x * sin(new_angle) + y * cos(new_angle);
    }
  }
}
