#include "mainwindow.h"

#include <QDir>
#include <QFileDialog>
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

  ConfigureStartingPerceptronParams();
  ConfigureFont();
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

void MainWindow::ConfigureStartingPerceptronParams() {
  perceptron_params_ = PerceptronParams{
      PerceptronParams::Type(ui->perceptronTypeComboBox->currentIndex()),
      ui->hiddenLayersCountSpinBox->value(),
      ui->hiddenLayersSizeSpinBox->value(), ui->loadedMappingPathLabel->text(),
      ui->loadedDatasetPathLabel->text()};
}

void MainWindow::CheckResetAllButtonAndUpdateButtonConditions() {
  ui->resetAllSettingsButton->setEnabled(
      ui->resetDatasetPathButton->isEnabled() ||
      ui->resetMappingPathButton->isEnabled() ||
      ui->resetHiddenLayersCountButton->isEnabled() ||
      ui->resetHiddenLayersSizeButton->isEnabled() ||
      ui->resetPerceptronTypeButton->isEnabled());

  ui->updateModelButton->setEnabled(
      ui->perceptronTypeComboBox->currentIndex() != -1);
}

void MainWindow::on_penRadiusSpinbox_valueChanged(int arg1) {
  ui->penRadiusSlider->setValue(arg1);
}

void MainWindow::on_clearButton_clicked() {
  drawarea_.ClearImage();
  RecognizePattern(true);
}

void MainWindow::on_loadMappingButton_clicked() {
  QString path = QFileDialog::getOpenFileName(this, "Choose mapping file",
                                              QDir::currentPath());
  if (!path.isEmpty()) {
    ui->loadedMappingPathLabel->setText(path);
    ui->resetMappingPathButton->setEnabled(path !=
                                           perceptron_params_.mapping_path);
    CheckResetAllButtonAndUpdateButtonConditions();
  }
}

void MainWindow::on_loadDatasetButton_clicked() {
  QString path = QFileDialog::getOpenFileName(this, "Choose dataset file",
                                              QDir::currentPath());
  if (!path.isEmpty()) {
    ui->loadedDatasetPathLabel->setText(path);
    ui->resetDatasetPathButton->setEnabled(path !=
                                           perceptron_params_.dataset_path);
    CheckResetAllButtonAndUpdateButtonConditions();
  }
}

void MainWindow::on_perceptronTypeComboBox_currentIndexChanged(int index) {
  ui->resetPerceptronTypeButton->setEnabled(perceptron_params_.type !=
                                            PerceptronParams::Type(index));
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetPerceptronTypeButton_clicked() {
  ui->perceptronTypeComboBox->setCurrentIndex(perceptron_params_.type);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_hiddenLayersCountSpinBox_valueChanged(int arg1) {
  ui->resetHiddenLayersCountButton->setEnabled(
      perceptron_params_.hidden_layers_count != arg1);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetHiddenLayersCountButton_clicked() {
  ui->hiddenLayersCountSpinBox->setValue(
      perceptron_params_.hidden_layers_count);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_hiddenLayersSizeSpinBox_valueChanged(int arg1) {
  ui->resetHiddenLayersSizeButton->setEnabled(
      perceptron_params_.hidden_layers_size != arg1);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetHiddenLayersSizeButton_clicked() {
  ui->hiddenLayersSizeSpinBox->setValue(perceptron_params_.hidden_layers_size);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetMappingPathButton_clicked() {
  ui->loadedMappingPathLabel->setText(perceptron_params_.mapping_path);
  ui->resetMappingPathButton->setDisabled(true);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetDatasetPathButton_clicked() {
  ui->loadedDatasetPathLabel->setText(perceptron_params_.dataset_path);
  ui->resetDatasetPathButton->setDisabled(true);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetAllSettingsButton_clicked() {
  on_resetDatasetPathButton_clicked();
  on_resetMappingPathButton_clicked();
  on_resetHiddenLayersCountButton_clicked();
  on_resetHiddenLayersSizeButton_clicked();
  on_resetPerceptronTypeButton_clicked();
  ui->resetAllSettingsButton->setDisabled(true);
}
