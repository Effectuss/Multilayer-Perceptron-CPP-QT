#include "trainingdialog.h"

#include <QThread>
#include <QTimer>

#include "ui_trainingdialog.h"

TrainingDialog::TrainingDialog(QWidget *parent)
    : QDialog(parent),
      dots_count_(0),
      default_message_(),
      change_thread_(new QThread()),
      change_timer_(new QTimer()),
      ui(new Ui::TrainingDialog) {
  ui->setupUi(this);
  default_message_ = ui->trainingLabel->text();

  change_timer_->setInterval(250);
  connect(change_timer_, &QTimer::timeout, this, &TrainingDialog::ChangeText);
  change_timer_->moveToThread(change_thread_);
}

TrainingDialog::~TrainingDialog() {
  delete ui;
  delete change_thread_;
  delete change_timer_;
}

void TrainingDialog::Exec() {
  change_thread_->start();
  exec();
}

void TrainingDialog::Close() {
  change_thread_->exit();
  close();
}

void TrainingDialog::ChangeText() {
  QString dots;
  dots.reserve(dots_count_);
  for (int i = 0; i < dots_count_; ++i) dots.push_back('.');
  ui->trainingLabel->setText(default_message_ + dots);
  dots_count_ = (dots_count_ + 1) % 7;
}
