#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <drawarea.h>

#include <QMainWindow>

#include "i_perceptron.h"
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
  void RecognizePattern(bool cleared);

 private slots:
  void on_clearButton_clicked();
  void on_penRadiusSpinbox_valueChanged(int arg1);
  void on_penRadiusSlider_valueChanged(int value);

  void ConfigureFont();

 private:
  Ui::MainWindow *ui;
  DrawArea drawarea_;
  ImageTransformer image_transformer_;
  IPerceptron *perceptron_;
};

#endif  // MAINWINDOW_H
