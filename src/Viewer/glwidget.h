#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWidget>

#include "mainwindow.h"

extern "C" {
#include "affin.h"
#include "parser.h"
}

class GLwidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit GLwidget(QWidget* parent = nullptr);

  ObjData obj = {0, 0, NULL, NULL};

  float rcl = 1, bcl = 1, gcl = 1, acl = 1;
  float rcb = 0, bcb = 0, gcb = 0, acb = 1;
  float rcv = 1, bcv = 1, gcv = 1, acv = 1;
  float line_width = 1, verticle_width = 1;
  int line_mod = 0, verticle_mode = 0;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void parse();
  void SetColor(float r, float g, float b, float a, int mod);
  void GetColor(float* r, float* g, float* b, float* a, int mod);
  void stipple();
  void verticleMode();
  void reset_param();
  void rotat(double arg, int mode);
  void reset();
  void cleaner();

  QVector2D mousePos;
  char* fileName = NULL;
  double x_coord = 0, y_coord = 0, z_coord = -10;
  double x_coord_dop = 0, y_coord_dop = 0, z_coord_dop = -10;
  double x_old_coord = 0, y_old_coord = 0;

  double x_rotation = 0, y_rotation = 0, z_rotation = 0;
  double x_old_rotation = 0, y_old_rotation = 0;

  double x_scale = 1, y_scale = 1, z_scale = 1;
  double x_scale_dop = 1, y_scale_dop = 1, z_scale_dop = 1;
  int projection_type = 0;
};

#endif  // GLWIDGET_H
