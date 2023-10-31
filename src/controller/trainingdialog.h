#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include <QDialog>
#include <QThread>
#include <QTimer>

namespace Ui {
class TrainingDialog;
}

class TrainingDialog : public QDialog {
  Q_OBJECT

 public:
  explicit TrainingDialog(QWidget *parent = nullptr);
  ~TrainingDialog();

 public slots:
  void Exec();
  void Close();

 private slots:
  void ChangeText();

 private:
  int dots_count_;
  QString default_message_;
  QThread *change_thread_;
  QTimer *change_timer_;

  Ui::TrainingDialog *ui;
};

#endif  // TRAININGDIALOG_H
