#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <QWidget>

class CustomGraphicsView : public QGraphicsView {
  Q_OBJECT
 public:
  CustomGraphicsView(QWidget* parent = nullptr);

 protected:
  void mouseReleaseEvent(QMouseEvent* event) override;

 signals:
  void MouseReleasedSignal();
};

#endif  // CUSTOMGRAPHICSVIEW_H
