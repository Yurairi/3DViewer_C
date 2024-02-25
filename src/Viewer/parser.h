#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR 1

typedef struct data {
  int num_vertices;
  int num_edges;
  double* vertices;
  int* edges;
} ObjData;

int parser(char* filename, ObjData* obj);
int alloc_m(ObjData* obj, int fl);
void NumbForF(char* temp_numb, ObjData* obj, int* error);

#endif  // PARSER_H_
