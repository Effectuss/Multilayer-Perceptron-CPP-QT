#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->drawArea->SetPenRadius(ui->penRadiusSlider->value());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_penRadiusSlider_valueChanged(int value) {
  ui->drawArea->SetPenRadius(value);
}
