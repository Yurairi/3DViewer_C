#include "parser.h"

int parser(char* filename, ObjData* obj) {
  int error = OK;
  size_t len = 256;
  FILE* f = fopen(filename, "r");
  printf(filename);
  if (!f) {
    error = ERROR;
  } else {
    char* str = NULL;
    while (getline(&str, &len, f) != EOF) {
      char dop_num[256] = "a";
      if ((str[0] == 'v' || str[0] == 'f') && str[1] == ' ') {
        char temp_numb[256];
        int count = 0;
        int fl = 0;

        for (int i = 2; i < (int)strlen(str) + 1 && !error; i++) {
          if (str[i] == '/') {
            while (str[i] != ' ' && str[i] != '\n') i++;
          }
          if (('0' <= str[i] && str[i] <= '9') || str[i] == '.' ||
              str[i] == '-' || str[i] == 'e') {
            temp_numb[count] = str[i];
            count++;
            fl = 1;
          } else if (fl) {
            if (str[0] == 'v') {
              obj->num_vertices += 1;
              error = alloc_m(obj, 1);
              obj->vertices[obj->num_vertices - 1] = atof(temp_numb);
            } else if (str[0] == 'f') {
              if (dop_num[0] == 'a') strcpy(dop_num, temp_numb);
              NumbForF(temp_numb, obj, &error);
              if (obj->num_edges % 2 == 0) NumbForF(temp_numb, obj, &error);
            }
            for (int j = 0; j < 256; j++) temp_numb[j] = '\0';
            count = 0;
            fl = 0;
          }
          if ((i == (int)strlen(str)) && str[0] == 'f')
            NumbForF(dop_num, obj, &error);
        }
      }
      free(str);
      str = NULL;
    }
    fclose(f);
    free(str);
  }
  return error;
}

void NumbForF(char* temp_numb, ObjData* obj, int* error) {
  obj->num_edges += 1;
  *error = alloc_m(obj, 0);
  if (atoi(temp_numb) < 0) {
    obj->edges[obj->num_edges - 1] = obj->num_vertices / 3 + atoi(temp_numb);
  } else {
    obj->edges[obj->num_edges - 1] = atoi(temp_numb) - 1;
  }
}

int alloc_m(ObjData* obj, int fl) {  // fl - 1 vertices, 0 - edges
  int error = OK;
  if (fl) {
    if (obj->vertices == NULL) {
      obj->vertices = calloc(1, sizeof(double));
    } else {
      obj->vertices =
          realloc(obj->vertices, (obj->num_vertices + 1) * sizeof(double));
    }
    if (obj->vertices == NULL) {
      error = ERROR;
      free(obj->vertices);
    }
  } else {
    if (obj->edges == NULL) {
      obj->edges = calloc(1, sizeof(int));
    } else {
      obj->edges = realloc(obj->edges, (obj->num_edges + 1) * sizeof(int));
    }
    if (obj->edges == NULL) {
      error = ERROR;
      free(obj->edges);
    }
  }
  return error;
}
