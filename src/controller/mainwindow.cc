#include "mainwindow.h"

#include <QFontDatabase>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      image_transformer_({28, 28}, ImageTransformer::RotationSide::kWest,
                         ImageTransformer::Invertion::kVertical),
      perceptron_(nullptr) {
  ui->setupUi(this);
  drawarea_.SetPenRadius(ui->penRadiusSlider->value());
  ui->penRadiusSpinbox->setRange(ui->penRadiusSlider->minimum(),
                                 ui->penRadiusSlider->maximum());
  ui->penRadiusSpinbox->setValue(ui->penRadiusSlider->value());
  ui->drawAreaView->setScene(&drawarea_);
  connect(static_cast<DrawArea *>(ui->drawAreaView->scene()),
          &DrawArea::MouseReleasedSignal, this, &MainWindow::RecognizePattern);
}

MainWindow::~MainWindow() {
  delete ui;
  delete perceptron_;
}

void MainWindow::RecognizePattern(bool cleared) {
  if (cleared) {
    ui->recognizedSymbol->setText("-");
    return;
  }
  qDebug() << "Emitted!";
}

void MainWindow::on_penRadiusSlider_valueChanged(int value) {
  drawarea_.SetPenRadius(value);
  ui->penRadiusSpinbox->setValue(value);
}

void MainWindow::ConfigureFont() {
  QFont fixed_font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  fixed_font.setBold(true);
  fixed_font.setCapitalization(QFont::Capitalization::AllUppercase);
  fixed_font.setPointSize(90);
  ui->recognizedSymbol->setFont(fixed_font);
}

void MainWindow::on_penRadiusSpinbox_valueChanged(int arg1) {
  ui->penRadiusSlider->setValue(arg1);
}

void MainWindow::on_clearButton_clicked() {
  drawarea_.ClearImage();
  RecognizePattern(true);
}
