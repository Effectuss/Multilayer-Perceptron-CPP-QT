#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      image_transformer_({28, 28}, ImageTransformer::RotationSide::kWest,
                         ImageTransformer::Invertion::kVertical) {
  ui->setupUi(this);
  drawarea_.SetPenRadius(ui->penRadiusSlider->value());
  ui->penRadiusSpinbox->setRange(ui->penRadiusSlider->minimum(),
                                 ui->penRadiusSlider->maximum());
  ui->penRadiusSpinbox->setValue(ui->penRadiusSlider->value());
  ui->drawAreaView->setScene(&drawarea_);
  connect(ui->drawAreaView, &CustomGraphicsView::MouseReleasedSignal, this,
          &MainWindow::RecognizePattern);
  connect(ui->drawAreaView, &CustomGraphicsView::MouseReleasedSignal,
          ui->drawAreaView->scene(), &DrawArea::MouseReleasedSlot);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::RecognizePattern() { qDebug() << "Emitted!"; }

void MainWindow::on_penRadiusSlider_valueChanged(int value) {
  drawarea_.SetPenRadius(value);
  ui->penRadiusSpinbox->setValue(value);
}

void MainWindow::on_penRadiusSpinbox_valueChanged(int arg1) {
  ui->penRadiusSlider->setValue(arg1);
}

void MainWindow::on_clearButton_clicked() { drawarea_.ClearImage(); }
