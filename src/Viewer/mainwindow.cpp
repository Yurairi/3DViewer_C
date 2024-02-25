#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  timer = new QTimer(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(gifWithScreenCast()));
  load_settings();
  cat_gif();
}

MainWindow::~MainWindow() {
  save_settings();
  ui->widget->cleaner();
  delete (movie);
  delete (movie_2);
  delete (movie_3);
  delete (movie_4);
  delete (timer);
  delete ui;
}

void MainWindow::cat_gif() {
  movie = new QMovie(":/img/img_src/lox.gif");
  ui->lox->setMovie(movie);
  movie->start();
  movie_2 = new QMovie(":/img/img_src/jopa_spit.gif");
  ui->lox_2->setMovie(movie_2);
  movie_2->start();
  movie_3 = new QMovie(":/img/img_src/jopa_est (1).gif");
  ui->lox_3->setMovie(movie_3);
  movie_3->start();
  movie_4 = new QMovie(":/img/img_src/kot (1).gif");
  ui->lox_4->setMovie(movie_4);
  movie_4->start();
}

void MainWindow::update_values() {
  ui->x_coord_box->setValue(ui->widget->x_coord);
  ui->y_coord_box->setValue(ui->widget->y_coord);
  ui->z_coord_box->setValue(ui->widget->z_coord);
  ui->x_rotation_box->setValue(fmod(ui->widget->x_rotation, 360));
  ui->y_rotation_box->setValue(fmod(ui->widget->y_rotation, 360));
  ui->z_rotation_box->setValue(fmod(ui->widget->z_rotation, 360));
  ui->x_scale_box->setValue(ui->widget->x_scale);
  ui->y_scale_box->setValue(ui->widget->y_scale);
  ui->z_scale_box->setValue(ui->widget->z_scale);
}

void MainWindow::on_toolButton_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home", tr("Object (*.obj)"));
  ui->lineEdit->setText(fileName);
}

void MainWindow::on_loadButton_pressed() {
  ui->widget->reset();
  update_values();
  std::string str = ui->lineEdit->text().toStdString();
  ui->widget->fileName = new char[str.length() + 1];
  if (ui->widget->fileName != NULL) {
    std::strcpy(ui->widget->fileName, str.c_str());
  }
  ui->widget->parse();
  ui->vertices->setText(QString::number(ui->widget->obj.num_vertices / 3));
  ui->edges->setText(QString::number(ui->widget->obj.num_edges / 2));
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton) {
    ui->widget->mousePos = QVector2D(event->position());
    ui->widget->x_old_coord = ui->widget->x_coord;
    ui->widget->y_old_coord = ui->widget->y_coord;
  } else if (event->buttons() == Qt::RightButton) {
    ui->widget->mousePos = QVector2D(event->position());
    ui->widget->x_old_rotation = ui->widget->x_rotation;
    ui->widget->y_old_rotation = ui->widget->y_rotation;
  }
  update_values();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  QVector2D newPos = QVector2D(event->position());
  if (event->buttons() == Qt::LeftButton && newPos != ui->widget->mousePos) {
    ui->widget->x_coord = ui->widget->x_old_coord +
                          (newPos.x() - ui->widget->mousePos.x()) * 0.01f;
    ui->widget->y_coord = ui->widget->y_old_coord +
                          (newPos.y() - ui->widget->mousePos.y()) * -0.01f;
  } else if (event->buttons() == Qt::RightButton &&
             newPos != ui->widget->mousePos) {
    ui->widget->rotat((ui->widget->x_old_rotation +
                       (newPos.y() - ui->widget->mousePos.y()) * -0.1f) -
                          ui->widget->x_rotation,
                      0);
    ui->widget->rotat((ui->widget->y_old_rotation +
                       (newPos.x() - ui->widget->mousePos.x()) * -0.1f) -
                          ui->widget->y_rotation,
                      1);
    ui->widget->x_rotation = ui->widget->x_old_rotation +
                             (newPos.y() - ui->widget->mousePos.y()) * -0.1f;
    ui->widget->y_rotation = ui->widget->y_old_rotation +
                             (newPos.x() - ui->widget->mousePos.x()) * -0.1f;
  }
  ui->widget->update();
  update_values();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0)  // up Wheel
    ui->widget->z_coord += 0.1f;
  else if (event->angleDelta().y() < 0)  // down Wheel
    ui->widget->z_coord -= 0.1f;
  ui->widget->update();
  update_values();
}

void MainWindow::save_settings() {
  settings.setValue("LineWidth", ui->widget->line_width);
  settings.setValue("LineType", ui->widget->line_mod);
  settings.setValue("LineColorR", ui->widget->rcl);
  settings.setValue("LineColorG", ui->widget->gcl);
  settings.setValue("LineColorB", ui->widget->bcl);
  settings.setValue("LineColorA", ui->widget->acl);
  settings.setValue("VerticesWidth", ui->widget->verticle_width);
  settings.setValue("VerticesType", ui->widget->verticle_mode);
  settings.setValue("VerticesColorR", ui->widget->rcv);
  settings.setValue("VerticesColorG", ui->widget->gcv);
  settings.setValue("VerticesColorB", ui->widget->bcv);
  settings.setValue("VerticesColorA", ui->widget->acv);
  settings.setValue("ProjectionType", ui->widget->projection_type);
  settings.setValue("BackgroundColorR", ui->widget->rcb);
  settings.setValue("BackgroundColorG", ui->widget->gcb);
  settings.setValue("BackgroundColorB", ui->widget->bcb);
  settings.setValue("BackgroundColorA", ui->widget->acb);
}

void MainWindow::load_settings() {
  ui->widget->line_width = settings.value("LineWidth").toDouble();
  ui->line_width->setValue(ui->widget->line_width);
  ui->widget->line_mod = settings.value("LineType").toInt();
  if (ui->widget->line_mod == 0)
    ui->solid->toggle();
  else
    ui->dashed->toggle();
  ui->widget->rcl = settings.value("LineColorR").toDouble();
  ui->widget->gcl = settings.value("LineColorG").toDouble();
  ui->widget->bcl = settings.value("LineColorB").toDouble();
  ui->widget->acl = settings.value("LineColorA").toDouble();
  ui->widget->verticle_width = settings.value("VerticesWidth").toDouble();
  ui->ver_size->setValue(ui->widget->verticle_width);
  ui->widget->verticle_mode = settings.value("VerticesType").toInt();
  if (ui->widget->verticle_mode == 0)
    ui->none->toggle();
  else if (ui->widget->verticle_mode == 1)
    ui->round->toggle();
  else
    ui->square->toggle();
  ui->widget->rcv = settings.value("VerticesColorR").toDouble();
  ui->widget->gcv = settings.value("VerticesColorG").toDouble();
  ui->widget->bcv = settings.value("VerticesColorB").toDouble();
  ui->widget->acv = settings.value("VerticesColorA").toDouble();
  ui->widget->projection_type = settings.value("ProjectionType").toInt();
  if (ui->widget->projection_type == 0)
    ui->parallel->toggle();
  else
    ui->central->toggle();
  ui->widget->rcb = settings.value("BackgroundColorR").toDouble();
  ui->widget->gcb = settings.value("BackgroundColorG").toDouble();
  ui->widget->bcb = settings.value("BackgroundColorB").toDouble();
  ui->widget->acb = settings.value("BackgroundColorA").toDouble();
}

void MainWindow::on_lines_color_b_clicked() {
  float r, g, b, a;
  ui->widget->GetColor(&r, &g, &b, &a, 0);
  QColor tmp;
  tmp.setRgbF(r, g, b, a);
  QColor color = QColorDialog::getColor(tmp);
  color.getRgbF(&r, &g, &b, &a);
  ui->widget->SetColor(r, g, b, a, 0);
  ui->widget->update();
}

void MainWindow::on_back_color_b_clicked() {
  float r, g, b, a;
  ui->widget->GetColor(&r, &g, &b, &a, 1);
  QColor tmp;
  tmp.setRgbF(r, g, b, a);
  QColor color = QColorDialog::getColor(tmp);
  color.getRgbF(&r, &g, &b, &a);
  ui->widget->SetColor(r, g, b, a, 1);
  ui->widget->update();
}

void MainWindow::on_central_toggled(bool checked) {
  ui->widget->projection_type = 1;
  ui->widget->update();
}

void MainWindow::on_parallel_toggled(bool checked) {
  ui->widget->projection_type = 0;
  ui->widget->update();
}

void MainWindow::on_solid_toggled(bool checked) {
  ui->widget->line_mod = 0;
  ui->widget->update();
}

void MainWindow::on_dashed_toggled(bool checked) {
  ui->widget->line_mod = 1;
  ui->widget->update();
}

void MainWindow::on_xyzCheck_stateChanged(int arg1) {
  double x = ui->x_scale_box->value();
  double y = ui->y_scale_box->value();
  double z = ui->z_scale_box->value();
  if (arg1) {
    xyz = true;
    if (x >= y && x >= z) {
      ui->y_scale_box->setValue(x);
      ui->z_scale_box->setValue(x);
    } else if (y >= x && y >= z) {
      ui->x_scale_box->setValue(y);
      ui->z_scale_box->setValue(y);
    } else if (z >= x && z >= y) {
      ui->y_scale_box->setValue(z);
      ui->x_scale_box->setValue(z);
    }
    ui->widget->update();
  } else {
    xyz = false;
  }
}

void MainWindow::on_x_coord_box_valueChanged(double arg1) {
  ui->widget->x_coord = arg1;
  ui->widget->update();
}

void MainWindow::on_y_coord_box_valueChanged(double arg1) {
  ui->widget->y_coord = arg1;
  ui->widget->update();
}

void MainWindow::on_z_coord_box_valueChanged(double arg1) {
  ui->widget->z_coord = arg1;
  ui->widget->update();
}

void MainWindow::on_x_rotation_box_valueChanged(double arg1) {
  ui->widget->rotat(arg1 - ui->widget->x_rotation, 0);
  ui->widget->x_rotation = arg1;
  ui->widget->update();
}

void MainWindow::on_y_rotation_box_valueChanged(double arg1) {
  ui->widget->rotat(arg1 - ui->widget->y_rotation, 1);
  ui->widget->y_rotation = arg1;
  ui->widget->update();
}

void MainWindow::on_z_rotation_box_valueChanged(double arg1) {
  ui->widget->rotat(arg1 - ui->widget->z_rotation, 2);
  ui->widget->z_rotation = arg1;
  ui->widget->update();
}

void MainWindow::on_x_scale_box_valueChanged(double arg1) {
  ui->widget->x_scale = arg1;
  if (xyz) {
    ui->widget->y_scale = arg1;
    ui->widget->z_scale = arg1;
    ui->y_scale_box->setValue(arg1);
    ui->z_scale_box->setValue(arg1);
  }
  ui->widget->update();
}

void MainWindow::on_y_scale_box_valueChanged(double arg1) {
  ui->widget->y_scale = arg1;
  if (xyz) {
    ui->widget->x_scale = arg1;
    ui->widget->z_scale = arg1;
    ui->x_scale_box->setValue(arg1);
    ui->z_scale_box->setValue(arg1);
  }
  ui->widget->update();
}

void MainWindow::on_z_scale_box_valueChanged(double arg1) {
  ui->widget->z_scale = arg1;
  if (xyz) {
    ui->widget->y_scale = arg1;
    ui->widget->x_scale = arg1;
    ui->y_scale_box->setValue(arg1);
    ui->x_scale_box->setValue(arg1);
  }
  ui->widget->update();
}

void MainWindow::on_line_width_valueChanged(double arg1) {
  ui->widget->line_width = arg1;
  ui->widget->update();
}

void MainWindow::on_vert_color_b_clicked() {
  float r, g, b, a;
  ui->widget->GetColor(&r, &g, &b, &a, 2);
  QColor tmp;
  tmp.setRgbF(r, g, b, a);
  QColor color = QColorDialog::getColor(tmp);
  color.getRgbF(&r, &g, &b, &a);
  ui->widget->SetColor(r, g, b, a, 2);
  ui->widget->update();
}

void MainWindow::on_none_toggled(bool checked) {
  ui->widget->verticle_mode = 0;
  ui->widget->update();
}

void MainWindow::on_round_toggled(bool checked) {
  ui->widget->verticle_mode = 1;
  ui->widget->update();
}

void MainWindow::on_square_toggled(bool checked) {
  ui->widget->verticle_mode = 2;
  ui->widget->update();
}

void MainWindow::on_ver_size_valueChanged(double arg1) {
  ui->widget->verticle_width = arg1;
  ui->widget->update();
}

void MainWindow::gifWithScreenCast() {
  QImage image = ui->widget->grabFramebuffer();
  QSize imageSize(640, 480);
  QImage scaledImage = image.scaled(imageSize);
  imageForGif->addFrame(scaledImage);
  if (fps == 50) {
    timer->stop();
    imageForGif->save(gifFileName);
    fps = 0;
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif saved");
    delete imageForGif;
    ui->gif->setText("Gif");
    ui->gif->setEnabled(true);
  }
  fps++;
  //сколько осталось до конца съемки
  if (!ui->gif->isEnabled()) {
    ui->gif->setText(QString::number(fps / 10));
  }
}

void MainWindow::on_gif_clicked() {
  gifFileName = QFileDialog::getSaveFileName(this, tr("Make a GIF"), ".gif",
                                             tr("gif (*.gif)"));
  if (gifFileName != "") {
    ui->gif->setDisabled(true);
    imageForGif = new QGifImage;
    imageForGif->setDefaultDelay(10);
    timer->setInterval(100);
    timer->start();
  }
}

void MainWindow::on_screensh_clicked() {
  QFileDialog dialogConnectImage(this);
  QString imageFileName = dialogConnectImage.getSaveFileName(
      this, tr("Make a screenshot"), ".jpeg", tr("image (*.bmp *.jpeg)"));
  if (imageFileName != "") {
    QImage img = ui->widget->grabFramebuffer();
    img.save(imageFileName);
    QMessageBox messageBoxImage;
    messageBoxImage.information(0, "", "Screenshot saved");
  }
}

void MainWindow::on_resetButton_clicked() {
  ui->widget->reset();
  update_values();
  std::string str = ui->lineEdit->text().toStdString();
  ui->widget->fileName = new char[str.length() + 1];
  if (ui->widget->fileName != NULL) {
    std::strcpy(ui->widget->fileName, str.c_str());
  }
  ui->widget->parse();
}

void MainWindow::on_resetButton_2_clicked() {
  ui->widget->reset_param();
  ui->parallel->toggle();
  ui->solid->toggle();
  ui->none->toggle();
  ui->line_width->setValue(ui->widget->line_width);
  ui->ver_size->setValue(ui->widget->verticle_width);
}
