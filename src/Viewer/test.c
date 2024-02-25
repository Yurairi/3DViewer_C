#include <check.h>

#include "affin.h"
#define ACCURACY 1e-4

START_TEST(model_load_test_1) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "test_empty.obj";
  parser(file, &obj);
  ObjData objTest = {0, 0, NULL, NULL};
  ck_assert_int_eq(obj.num_edges, objTest.num_edges);
  ck_assert_int_eq(obj.num_vertices, objTest.num_vertices);
  ck_assert_ptr_null(obj.edges);
  ck_assert_ptr_null(obj.vertices);
}

START_TEST(model_load_test_2) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "test_trash.obj";
  parser(file, &obj);
  ObjData objTest = {0, 0, NULL, NULL};
  ck_assert_int_eq(obj.num_edges, objTest.num_edges);
  ck_assert_int_eq(obj.num_vertices, objTest.num_vertices);
  ck_assert_ptr_null(obj.edges);
  ck_assert_ptr_null(obj.vertices);
}

START_TEST(model_load_test_3) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parser(file, &obj);
  ObjData objTest = {24, 60, NULL, NULL};
  ck_assert_int_eq(obj.num_edges, objTest.num_edges);
  ck_assert_int_eq(obj.num_vertices, objTest.num_vertices);
  ck_assert_ptr_nonnull(obj.edges);
  ck_assert_ptr_nonnull(obj.vertices);
  free(obj.edges);
  free(obj.vertices);
}

START_TEST(model_load_test_4) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "nothing.obj";
  int result = parser(file, &obj);
  ck_assert_int_eq(result, 1);
}

START_TEST(affine_test_1) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parser(file, &obj);
  double rt = 0;
  double rtt = 10;
  translate(0.0, 0.0, 0.0, &obj, &rtt, &rt, &rt);
  ck_assert_int_eq(1, 1);
  double temp = 0;
  for (int i = 0; i < obj.num_vertices; i++) {
    temp += obj.vertices[i];
  }
  free(obj.edges);
  free(obj.vertices);
  ck_assert_double_eq_tol(temp, -56, ACCURACY);
}

START_TEST(affine_test_2) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parser(file, &obj);
  double rt = 0;
  double rtt = 21;
  translate(0.0, 0.0, 0.0, &obj, &rt, &rtt, &rt);
  double temp = 0;
  for (int i = 0; i < obj.num_vertices; i++) {
    temp += obj.vertices[i];
  }
  free(obj.edges);
  free(obj.vertices);
  ck_assert_double_eq_tol(temp, -144, ACCURACY);
}

START_TEST(affine_test_3) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parser(file, &obj);
  double rt = 0;
  double rtt = 99;
  translate(0.0, 0.0, 0.0, &obj, &rt, &rt, &rtt);
  double temp = 0;
  for (int i = 0; i < obj.num_vertices; i++) {
    temp += obj.vertices[i];
  }
  free(obj.edges);
  free(obj.vertices);
  ck_assert_double_eq_tol(temp, -768, ACCURACY);
}

START_TEST(affine_test_4) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parser(file, &obj);
  double rt = 1;
  double rtt = 2;
  scale(&rt, &rt, &rt, &obj, &rtt, &rt, &rt);
  double temp = 0;
  for (int i = 0; i < obj.num_vertices; i++) {
    temp += obj.vertices[i];
  }
  free(obj.edges);
  free(obj.vertices);
  ck_assert_double_eq_tol(temp, 20, ACCURACY);
}

START_TEST(affine_test_5) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parser(file, &obj);
  double rt = 1;
  double rtt = 5;
  scale(&rt, &rt, &rt, &obj, &rt, &rtt, &rt);
  double temp = 0;
  for (int i = 0; i < obj.num_vertices; i++) {
    temp += obj.vertices[i];
  }
  free(obj.edges);
  free(obj.vertices);
  ck_assert_double_eq_tol(temp, 17.6, ACCURACY);
}

START_TEST(affine_test_6) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parser(file, &obj);
  rotation(90, 0, &obj);
  double temp = 0;
  for (int i = 0; i < obj.num_vertices; i++) {
    temp += obj.vertices[i];
  }
  free(obj.edges);
  free(obj.vertices);
  ck_assert_double_eq_tol(temp, 8, ACCURACY);
}

START_TEST(affine_test_7) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parser(file, &obj);
  rotation(45, 1, &obj);
  double temp = 0;
  for (int i = 0; i < obj.num_vertices; i++) {
    temp += obj.vertices[i];
  }
  free(obj.edges);
  free(obj.vertices);
  ck_assert_double_eq_tol(temp, 19.3137, ACCURACY);
}

START_TEST(affine_test_8) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parser(file, &obj);
  rotation(69, 2, &obj);
  double temp = 0;
  for (int i = 0; i < obj.num_vertices; i++) {
    temp += obj.vertices[i];
  }
  free(obj.edges);
  free(obj.vertices);
  ck_assert_double_eq_tol(temp, 13.7339, ACCURACY);
}

int main() {
  Suite *s1 = suite_create("3D Viewer Tests");
  TCase *tc1_1 = tcase_create("3D Viewer Tests");
  SRunner *sr = srunner_create(s1);
  double result = 0;

  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, model_load_test_1);
  tcase_add_test(tc1_1, model_load_test_2);
  tcase_add_test(tc1_1, model_load_test_3);
  tcase_add_test(tc1_1, model_load_test_4);
  tcase_add_test(tc1_1, affine_test_1);
  tcase_add_test(tc1_1, affine_test_2);
  tcase_add_test(tc1_1, affine_test_3);
  tcase_add_test(tc1_1, affine_test_4);
  tcase_add_test(tc1_1, affine_test_5);
  tcase_add_test(tc1_1, affine_test_6);
  tcase_add_test(tc1_1, affine_test_7);
  tcase_add_test(tc1_1, affine_test_8);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}
