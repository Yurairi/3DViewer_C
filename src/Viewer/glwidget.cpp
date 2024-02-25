#include "glwidget.h"

#include <QDebug>

GLwidget::GLwidget(QWidget *parent) : QOpenGLWidget{parent} {}

void GLwidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void GLwidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glLoadIdentity();
}

void GLwidget::paintGL() {
  glClearColor(rcb, gcb, bcb, acb);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glVertexPointer(3, GL_DOUBLE, 0, obj.vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);

  if (projection_type == 0)
    glOrtho(-5, 5, -5, 5, 0.1f, 2000);
  else
    gluPerspective(90.0f, width() / height(), 0.1f, 1000.0f);

  translate(x_coord, y_coord, z_coord, &obj, &x_coord_dop, &y_coord_dop,
            &z_coord_dop);
  scale(&x_scale, &y_scale, &z_scale, &obj, &x_scale_dop, &y_scale_dop,
        &z_scale_dop);

  glLineWidth(line_width);
  stipple();
  glColor4f(rcl, gcl, bcl, acl);
  glDrawElements(GL_LINES, obj.num_edges, GL_UNSIGNED_INT, obj.edges);

  glColor4f(rcv, gcv, bcv, acv);
  glPointSize(verticle_width);
  verticleMode();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLwidget::rotat(double arg, int mode) {
  translate(0, 0, -10, &obj, &x_coord_dop, &y_coord_dop, &z_coord_dop);
  if (mode == 0) {
    rotation(arg, 0, &obj);
  } else if (mode == 1) {
    rotation(arg, 1, &obj);
  } else {
    rotation(arg, 2, &obj);
  }
  translate(x_coord, y_coord, z_coord, &obj, &x_coord_dop, &y_coord_dop,
            &z_coord_dop);
}

void GLwidget::reset() {
  x_rotation = 0;
  y_rotation = 0;
  z_rotation = 0;
  x_old_rotation = 0;
  y_old_rotation = 0;

  x_coord = 0;
  y_coord = 0;
  z_coord = -10;
  x_coord_dop = 0;
  y_coord_dop = 0;
  z_coord_dop = -10;
  x_old_coord = 0;
  y_old_coord = 0;

  x_scale = 1;
  y_scale = 1;
  z_scale = 1;
  x_scale_dop = 1;
  y_scale_dop = 1;
  z_scale_dop = 1;
}

void GLwidget::reset_param() {
  rcl = 1;
  bcl = 1;
  gcl = 1;
  acl = 1;

  rcb = 0;
  bcb = 0;
  gcb = 0;
  acb = 1;

  rcv = 1;
  bcv = 1;
  gcv = 1;
  acv = 1;

  line_width = 1;
  verticle_width = 1;
  line_mod = 0;
  verticle_mode = 0;
  projection_type = 0;
}

void GLwidget::parse() {
  cleaner();
  if (parser(fileName, &obj)) {
    obj.num_vertices = 0;
    obj.num_edges = 0;
    obj.edges = NULL;
    obj.vertices = NULL;
  }
  free(fileName);
  update();
}

void GLwidget::cleaner() {
  if (obj.num_vertices != 0) {
    obj.num_vertices = 0;
    obj.num_edges = 0;
    free(obj.edges);
    free(obj.vertices);
    obj.edges = NULL;
    obj.vertices = NULL;
  }
}

void GLwidget::SetColor(float r, float g, float b, float a, int mod) {
  if (mod == 0) {
    this->rcl = r;
    this->gcl = g;
    this->bcl = b;
    this->acl = a;
  } else if (mod == 1) {
    this->rcb = r;
    this->gcb = g;
    this->bcb = b;
    this->acb = a;
  } else {
    this->rcv = r;
    this->gcv = g;
    this->bcv = b;
    this->acv = a;
  }
}

void GLwidget::GetColor(float *r, float *g, float *b, float *a, int mod) {
  if (mod == 0) {
    *r = this->rcl;
    *g = this->gcl;
    *b = this->bcl;
    *a = this->acl;
  } else if (mod == 1) {
    *r = this->rcb;
    *g = this->gcb;
    *b = this->bcb;
    *a = this->acb;
  } else {
    *r = this->rcv;
    *g = this->gcv;
    *b = this->bcv;
    *a = this->acv;
  }
}

void GLwidget::stipple() {
  if (line_mod == 0) {
    if (glIsEnabled(GL_LINE_STIPPLE)) glDisable(GL_LINE_STIPPLE);
  } else {
    if (!glIsEnabled(GL_LINE_STIPPLE)) {
      glEnable(GL_LINE_STIPPLE);
    }
    glLineStipple(3, 15);
  }
  update();
}

void GLwidget::verticleMode() {
  if (verticle_mode == 1) {
    if (!glIsEnabled(GL_POINT_SMOOTH)) glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, obj.num_vertices / 3);
  } else if (verticle_mode == 2) {
    if (glIsEnabled(GL_POINT_SMOOTH)) glDisable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, obj.num_vertices / 3);
  }
  update();
}
