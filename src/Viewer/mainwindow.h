#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string.h>

#include <QFileDialog>
#include <QMainWindow>
#include <QMovie>
#include <QSettings>

#include "QtWidgets"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void update_values();
  void on_widget_clicked();
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void cat_gif();

 private:
  QSettings settings;
  void save_settings();
  void load_settings();
  Ui::MainWindow *ui;
  bool xyz = true;
  QString gifFileName;
  QGifImage *imageForGif;
  QTimer *timer;
  QMovie *movie;
  QMovie *movie_2;
  QMovie *movie_3;
  QMovie *movie_4;
  int fps = 0;

 private slots:
  void on_toolButton_clicked();
  void on_loadButton_pressed();
  void on_lines_color_b_clicked();
  void on_back_color_b_clicked();
  void on_central_toggled(bool checked);
  void on_parallel_toggled(bool checked);
  void on_dashed_toggled(bool checked);
  void on_solid_toggled(bool checked);
  void gifWithScreenCast();
  void on_xyzCheck_stateChanged(int arg1);
  void on_x_coord_box_valueChanged(double arg1);
  void on_y_coord_box_valueChanged(double arg1);
  void on_z_coord_box_valueChanged(double arg1);
  void on_x_rotation_box_valueChanged(double arg1);
  void on_y_rotation_box_valueChanged(double arg1);
  void on_z_rotation_box_valueChanged(double arg1);
  void on_x_scale_box_valueChanged(double arg1);
  void on_y_scale_box_valueChanged(double arg1);
  void on_z_scale_box_valueChanged(double arg1);
  void on_line_width_valueChanged(double arg1);
  void on_vert_color_b_clicked();
  void on_none_toggled(bool checked);
  void on_round_toggled(bool checked);
  void on_square_toggled(bool checked);
  void on_ver_size_valueChanged(double arg1);
  void on_gif_clicked();
  void on_screensh_clicked();
  void on_resetButton_clicked();
  void on_resetButton_2_clicked();
};

#endif  // MAINWINDOW_H
