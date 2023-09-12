#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QFlags>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QWidget>

class DrawArea : public QGraphicsScene {
  Q_OBJECT
 public:
  DrawArea(QWidget* parent = nullptr);

 public slots:
  void ClearImage();
  void SetPenRadius(int radius);

 protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

 private:
  void DrawCircle(const QPointF& point, const QColor& color);
  void DrawLine(const QPointF& p1, const QPointF& p2, const QColor& color);

  QPointF previous_point_;

  const QColor kPenColor{0, 0, 0};
  const QColor kEraserColor{255, 255, 255};
  const QColor kBackgroundColor{255, 255, 255};

  int radius_;
  bool cleared_ = false;
};

#endif  // DRAWAREA_H
