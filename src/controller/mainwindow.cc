#include "mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QFontDatabase>
#include <QMessageBox>
#include <QMimeData>
#include <QThread>
#include <algorithm>
#include <thread>

#include "dataset.h"
#include "graph_perceptron.h"
#include "mapping.h"
#include "matrix_perceptron.h"
#include "parser.h"
#include "sigmoid.h"
#include "trainingdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      predict_image_transformer_({28, 28},
                                 ImageTransformer::RotationSide::kWest,
                                 ImageTransformer::Invertion::kVertical),
      load_image_transformer_({512, 512}),
      perceptron_(nullptr),
      mapping_(nullptr) {
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

void MainWindow::LoadAndRecognizeImage(const QString &path) {
  QImage image(path);
  if (image.isNull()) {
    ShowIncorrectImagePathDialogWindow(path);
    return;
  }

  LoadImage(image);
}

void MainWindow::RecognizePattern(bool cleared) {
  if (cleared || !mapping_) {
    ui->recognizedSymbol->setText("-");
    return;
  }
  auto picture = predict_image_transformer_.ImageToDoubleMatrix(
      predict_image_transformer_.Transform(
          ui->drawAreaView->grab(ui->drawAreaView->sceneRect().toRect())
              .toImage()));
  auto result = perceptron_->Predict(picture);

  std::vector<int> indices(result.size());
  std::iota(indices.begin(), indices.end(), 0);
  std::sort(indices.begin(), indices.end(),
            [&result](int a, int b) { return result[a] > result[b]; });

  QString sym(QChar(*mapping_->GetData()[indices.front()].begin()));
  ui->recognizedSymbol->setText(sym);
}

void MainWindow::Delay(int milliseconds) {
  QTime deadline = QTime::currentTime().addMSecs(milliseconds);
  while (QTime::currentTime() < deadline) {
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
  }
}

void MainWindow::ShowIncorrectImagePathDialogWindow(const QString &path) {
  QString message = "Error while loading image";
  if (!path.isEmpty()) {
    message += " at " + path;
  }

  QMessageBox::critical(this, "Load symbol",
                        "Error while loading image at" + path);
}

void MainWindow::LoadImage(const QImage &image) {
  if (!drawarea_.SetPixmap(
          QPixmap::fromImage(load_image_transformer_.Transform(image)))) {
    ShowIncorrectImagePathDialogWindow();
  }
  update();
  RecognizePattern(false);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
  if (QList<QUrl> urls = event->mimeData()->urls();
      (urls.size() == 1 && urls.front().isLocalFile()) ||
      event->mimeData()->hasImage()) {
    event->acceptProposedAction();
  }
}

void MainWindow::dropEvent(QDropEvent *event) {
  if (event->mimeData()->hasImage()) {
    QImage image = event->mimeData()->imageData().value<QImage>();
    LoadImage(image);
  } else if (QList<QUrl> urls = event->mimeData()->urls();
             urls.size() == 1 && urls.front().isLocalFile()) {
    LoadAndRecognizeImage(urls.front().toLocalFile());
  }
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
      ui->hiddenLayersSizeSpinBox->value(),
      ui->loadedMappingPathLineEdit->text(),
      ui->loadedDatasetPathLineEdit->text(),
      ui->epochsCountSpinBox->value()};
}

void MainWindow::CheckResetAllButtonAndUpdateButtonConditions() {
  ui->resetAllSettingsButton->setEnabled(
      ui->resetDatasetPathButton->isEnabled() ||
      ui->resetMappingPathButton->isEnabled() ||
      ui->resetHiddenLayersCountButton->isEnabled() ||
      ui->resetHiddenLayersSizeButton->isEnabled() ||
      ui->resetPerceptronTypeButton->isEnabled() ||
      ui->resetEpochsCountButton->isEnabled());

  bool train_enabled_condition =
      (ui->perceptronTypeComboBox->currentIndex() != perceptron_params_.type ||
       ui->hiddenLayersCountSpinBox->value() !=
           perceptron_params_.hidden_layers_count ||
       ui->hiddenLayersSizeSpinBox->value() !=
           perceptron_params_.hidden_layers_size ||
       ui->loadedDatasetPathLineEdit->text() !=
           perceptron_params_.dataset_path ||
       ui->loadedMappingPathLineEdit->text() !=
           perceptron_params_.mapping_path ||
       ui->epochsCountSpinBox->value() != perceptron_params_.epochs_count) &&
      ui->perceptronTypeComboBox->currentIndex() != -1 &&
      !ui->loadedMappingPathLineEdit->text().isEmpty() &&
      !ui->loadedDatasetPathLineEdit->text().isEmpty();

  ui->trainModelButton->setEnabled(train_enabled_condition);
  ui->actionLoad_bmp->setEnabled(train_enabled_condition);

  ui->loadWeightsButton->setEnabled(
      !ui->loadedMappingPathLineEdit->text().isEmpty());
}

void MainWindow::TrainModel(IPerceptron **new_perceptron) {
  Parser parser;
  Mapping mapping =
      parser.ParseMapping(ui->loadedMappingPathLineEdit->text().toStdString());
  Dataset dataset =
      parser.ParseDataset(ui->loadedDatasetPathLineEdit->text().toStdString(),
                          mapping.GetMinIndex());

  std::shared_ptr<IActivationFunction> func(new Sigmoid());
  if (ui->perceptronTypeComboBox->currentText() == "Graph") {
    *new_perceptron = new GraphPerceptron(ui->hiddenLayersCountSpinBox->value(),
                                          ui->hiddenLayersSizeSpinBox->value(),
                                          mapping.GetDataSize(), func);
  } else {
    *new_perceptron = new MatrixPerceptron(
        ui->hiddenLayersCountSpinBox->value(),
        ui->hiddenLayersSizeSpinBox->value(), mapping, func);
  }
  std::thread train_thread(&IPerceptron::Train, *new_perceptron,
                           ui->epochsCountSpinBox->value(), std::ref(dataset));

  TrainingDialog *training_dialog = new TrainingDialog(this);
  training_dialog->show();

  while (!(*new_perceptron)->IsFinished() && !training_dialog->IsCancelled()) {
    Delay(100);
  }
  if (training_dialog->IsCancelled()) {
    (*new_perceptron)->Cancel();
  }

  train_thread.join();
  training_dialog->close();
  delete training_dialog;

  if ((*new_perceptron)->IsFinished()) {
    delete perceptron_;
    perceptron_ = *new_perceptron;
    delete mapping_;
    mapping_ = new Mapping(std::move(mapping));
    perceptron_params_ = PerceptronParams{
        PerceptronParams::Type(ui->perceptronTypeComboBox->currentIndex()),
        ui->hiddenLayersCountSpinBox->value(),
        ui->hiddenLayersSizeSpinBox->value(),
        ui->loadedMappingPathLineEdit->text(),
        ui->loadedDatasetPathLineEdit->text(),
        ui->epochsCountSpinBox->value()};
  } else {
    delete *new_perceptron;
  }

  ui->exportWeightsButton->setEnabled(perceptron_ != nullptr);
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
    ui->loadedMappingPathLineEdit->setText(path);
    ui->resetMappingPathButton->setEnabled(path !=
                                           perceptron_params_.mapping_path);
    CheckResetAllButtonAndUpdateButtonConditions();
  }
}

void MainWindow::on_loadDatasetButton_clicked() {
  QString path = QFileDialog::getOpenFileName(this, "Choose dataset file",
                                              QDir::currentPath());
  if (!path.isEmpty()) {
    ui->loadedDatasetPathLineEdit->setText(path);
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
  ui->resetPerceptronTypeButton->setDisabled(true);
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
  ui->resetHiddenLayersCountButton->setDisabled(true);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_hiddenLayersSizeSpinBox_valueChanged(int arg1) {
  ui->resetHiddenLayersSizeButton->setEnabled(
      perceptron_params_.hidden_layers_size != arg1);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetHiddenLayersSizeButton_clicked() {
  ui->hiddenLayersSizeSpinBox->setValue(perceptron_params_.hidden_layers_size);
  ui->resetHiddenLayersSizeButton->setDisabled(true);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetMappingPathButton_clicked() {
  ui->loadedMappingPathLineEdit->setText(perceptron_params_.mapping_path);
  ui->resetMappingPathButton->setDisabled(true);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetDatasetPathButton_clicked() {
  ui->loadedDatasetPathLineEdit->setText(perceptron_params_.dataset_path);
  ui->resetDatasetPathButton->setDisabled(true);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetAllSettingsButton_clicked() {
  on_resetDatasetPathButton_clicked();
  on_resetMappingPathButton_clicked();
  on_resetHiddenLayersCountButton_clicked();
  on_resetHiddenLayersSizeButton_clicked();
  on_resetPerceptronTypeButton_clicked();
  on_resetEpochsCountButton_clicked();
  ui->resetAllSettingsButton->setDisabled(true);
}

void MainWindow::on_epochsCountSpinBox_valueChanged(int arg1) {
  ui->resetEpochsCountButton->setEnabled(ui->epochsCountSpinBox->value() !=
                                         perceptron_params_.epochs_count);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_resetEpochsCountButton_clicked() {
  ui->epochsCountSpinBox->setValue(perceptron_params_.epochs_count);
  ui->resetEpochsCountButton->setDisabled(true);
  CheckResetAllButtonAndUpdateButtonConditions();
}

void MainWindow::on_trainModelButton_clicked() {
  IPerceptron *new_perceptron = nullptr;
  TrainModel(&new_perceptron);
}

void MainWindow::on_loadWeightsButton_clicked() {
  QString weights_path =
      QFileDialog::getOpenFileName(this, "Select weights file");
  if (weights_path.isEmpty()) return;

  Parser parser;
  Mapping *new_mapping = new Mapping(
      parser.ParseMapping(ui->loadedMappingPathLineEdit->text().toStdString()));
  std::shared_ptr<IActivationFunction> func(new Sigmoid());

  IPerceptron *new_perceptron = new GraphPerceptron(
      perceptron_params_.hidden_layers_count,
      perceptron_params_.hidden_layers_size, new_mapping->GetDataSize(), func);
  try {
    new_perceptron->LoadWeights(weights_path.toStdString());
    delete perceptron_;
    perceptron_ = new_perceptron;
    delete mapping_;
    mapping_ = new_mapping;
    ui->loadedWeightsPath->setText(weights_path);
    return;
  } catch (const std::exception &e) {
    // ignore
  }

  delete new_perceptron;
  new_perceptron = new MatrixPerceptron(perceptron_params_.hidden_layers_count,
                                        perceptron_params_.hidden_layers_size,
                                        *new_mapping, func);
  try {
    new_perceptron->LoadWeights(weights_path.toStdString());
    delete perceptron_;
    perceptron_ = new_perceptron;
    delete mapping_;
    mapping_ = new_mapping;
    ui->loadedWeightsPath->setText(weights_path);
    return;
  } catch (const std::exception &e) {
    QMessageBox::critical(
        this, "Import",
        "Error while importing weights from " + weights_path + ": " + e.what());
  }

  delete new_perceptron;
}

void MainWindow::on_exportWeightsButton_clicked() {
  QString weights_path = QFileDialog::getSaveFileName(this, "Select file");
  if (weights_path.isEmpty()) return;

  try {
    perceptron_->ExportWeights(weights_path.toStdString());
    QMessageBox::information(this, "Export",
                             "Succesfully exported weights to " + weights_path);
  } catch (const std::exception &e) {
    QMessageBox::critical(
        this, "Export",
        "Error while exporting weights to " + weights_path + ": " + e.what());
  }
}

void MainWindow::on_actionLoad_bmp_triggered() {
  QString image_path =
      QFileDialog::getOpenFileName(this, "Load symbol", QDir::currentPath(),
                                   tr("Images (*.png *.xpm *.jpg)"));
  if (image_path.isEmpty()) return;

  LoadAndRecognizeImage(image_path);
}
