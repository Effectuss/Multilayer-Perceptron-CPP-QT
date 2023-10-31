#ifndef HISTOGRAMPLOT_H
#define HISTOGRAMPLOT_H

#include <qcustomplot.h>

#include <QObject>
#include <QWidget>

class HistogramPlot : public QCustomPlot {
  Q_OBJECT
 public:
  explicit HistogramPlot(QWidget* parent = nullptr);
};

#endif  // HISTOGRAMPLOT_H
