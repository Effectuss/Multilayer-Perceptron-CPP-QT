#include "trainingdialog.h"

#include <QThread>
#include <QTimer>

#include "ui_trainingdialog.h"

TrainingDialog::TrainingDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TrainingDialog) {
  ui->setupUi(this);
  setModal(true);
}

TrainingDialog::~TrainingDialog() { delete ui; }

bool TrainingDialog::IsCancelled() const { return is_cancelled_; }

void TrainingDialog::on_cancelDialogButtonBox_clicked(QAbstractButton *button) {
  ui->trainingLabel->setText("Cancelling...");
  ui->cancelDialogButtonBox->setDisabled(true);

  is_cancelled_ = true;
}
