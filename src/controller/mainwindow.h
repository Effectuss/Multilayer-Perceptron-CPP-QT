#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <drawarea.h>

#include <QMainWindow>

#include "i_perceptron.h"
#include "imagetransformer.h"
#include "mapping.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct PerceptronParams {
  enum Type { kNone = -1, kGraph, kMatrix } type;

  int hidden_layers_count;
  int hidden_layers_size;

  QString mapping_path;
  QString dataset_path;

  int epochs_count;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void LoadAndRecognizeImage(const QString &path);
  void RecognizePattern(bool cleared);
  void Delay(int milliseconds);
  void ShowIncorrectImagePathDialogWindow(const QString &path = "");
  void LoadImage(const QImage &image);

 protected:
  virtual void dragEnterEvent(QDragEnterEvent *event) override;
  virtual void dropEvent(QDropEvent *event) override;

 private slots:
  void on_trainModelButton_clicked();
  void on_resetEpochsCountButton_clicked();
  void on_epochsCountSpinBox_valueChanged(int arg1);
  void on_resetAllSettingsButton_clicked();
  void on_resetDatasetPathButton_clicked();
  void on_resetMappingPathButton_clicked();
  void on_resetHiddenLayersSizeButton_clicked();
  void on_hiddenLayersSizeSpinBox_valueChanged(int arg1);
  void on_resetHiddenLayersCountButton_clicked();
  void on_hiddenLayersCountSpinBox_valueChanged(int arg1);
  void on_resetPerceptronTypeButton_clicked();
  void on_perceptronTypeComboBox_currentIndexChanged(int index);
  void on_loadDatasetButton_clicked();
  void on_loadMappingButton_clicked();
  void on_clearButton_clicked();
  void on_penRadiusSpinbox_valueChanged(int arg1);
  void on_penRadiusSlider_valueChanged(int value);

  void on_loadWeightsButton_clicked();
  void on_actionLoad_bmp_triggered();
  void on_exportWeightsButton_clicked();

 private:
  void ConfigureFont();
  void ConfigureStartingPerceptronParams();
  void CheckResetAllButtonAndUpdateButtonConditions();

  void TrainModel(IPerceptron **new_perceptron);

  Ui::MainWindow *ui;
  DrawArea drawarea_;
  ImageTransformer predict_image_transformer_;
  ImageTransformer load_image_transformer_;
  IPerceptron *perceptron_;
  Mapping *mapping_;
  PerceptronParams perceptron_params_;
};

#endif  // MAINWINDOW_H
