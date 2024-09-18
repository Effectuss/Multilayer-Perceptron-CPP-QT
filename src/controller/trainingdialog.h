#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include <QAbstractButton>
#include <QDialog>
#include <QThread>
#include <QTimer>
#include <atomic>

namespace Ui {
class TrainingDialog;
}

class TrainingDialog : public QDialog {
  Q_OBJECT

 public:
  explicit TrainingDialog(QWidget *parent = nullptr);
  ~TrainingDialog();

  bool IsCancelled() const;

 private slots:
  void on_cancelDialogButtonBox_clicked(QAbstractButton *button);

 private:
  Ui::TrainingDialog *ui;
  std::atomic<bool> is_cancelled_ = false;
};

#endif  // TRAININGDIALOG_H
