#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <drawarea.h>

#include <QMainWindow>

#include "imagetransformer.h"

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

 public slots:
  void RecognizePattern();

 private slots:
  void on_clearButton_clicked();
  void on_penRadiusSpinbox_valueChanged(int arg1);
  void on_penRadiusSlider_valueChanged(int value);

 private:
  Ui::MainWindow *ui;
  DrawArea drawarea_;
  ImageTransformer image_transformer_;
};

#endif  // MAINWINDOW_H
