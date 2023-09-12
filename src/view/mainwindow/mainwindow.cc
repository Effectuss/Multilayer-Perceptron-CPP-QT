#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->drawArea->SetPenRadius(ui->penRadiusSlider->value());
  ui->penRadiusSpinbox->setRange(ui->penRadiusSlider->minimum(),
                                 ui->penRadiusSlider->maximum());
  ui->penRadiusSpinbox->setValue(ui->penRadiusSlider->value());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_penRadiusSlider_valueChanged(int value) {
  ui->drawArea->SetPenRadius(value);
  ui->penRadiusSpinbox->setValue(value);
}

void MainWindow::on_penRadiusSpinbox_valueChanged(int arg1) {
  ui->penRadiusSlider->setValue(arg1);
}

void MainWindow::on_clearButton_clicked() { ui->drawArea->ClearImage(); }
