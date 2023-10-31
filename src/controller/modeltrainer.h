#ifndef MODELTRAINER_H
#define MODELTRAINER_H

#include <QObject>

#include "graph_perceptron.h"

class ModelTrainer : public QObject {
  Q_OBJECT
 public:
  explicit ModelTrainer(QObject* parent = nullptr);

 public slots:
  void StartTraining();

 signals:
  void TrainingFinished(IPerceptron* perceptron);
};

#endif  // MODELTRAINER_H
