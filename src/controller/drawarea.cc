#include "drawarea.h"

DrawArea::DrawArea(QWidget* parent) : QGraphicsScene(parent) { ClearImage(); }

void DrawArea::ClearImage() { clear(); }

void DrawArea::SetPenRadius(int radius) { radius_ = radius; }

void DrawArea::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  if (!cleared_) {
    if (event->buttons().testFlags({Qt::LeftButton, Qt::RightButton})) {
      ClearImage();
      cleared_ = true;
    } else if (event->buttons().testFlag(Qt::LeftButton)) {
      DrawCircle(event->scenePos(), kPenColor);
    } else if (event->buttons().testFlag(Qt::RightButton)) {
      DrawCircle(event->pos(), kEraserColor);
    }
  }
  previous_point_ = event->scenePos();
}

void DrawArea::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
  if (!event->buttons().testFlags({Qt::LeftButton, Qt::RightButton})) {
    if (event->buttons().testFlag(Qt::LeftButton))
      DrawLine(event->scenePos(), previous_point_, kPenColor);
    else if (event->buttons().testFlag(Qt::RightButton))
      DrawLine(event->scenePos(), previous_point_, kEraserColor);
  }
  previous_point_ = event->scenePos();
}

void DrawArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  if (event->buttons().testFlag(Qt::NoButton)) {
    cleared_ = false;
  }
}

void DrawArea::DrawCircle(const QPointF& point, const QColor& color) {
  addEllipse(point.x() - radius_ / 2.0, point.y() - radius_ / 2.0, radius_,
             radius_, QPen(Qt::NoPen), QBrush(color));
}

void DrawArea::DrawLine(const QPointF& p1, const QPointF& p2,
                        const QColor& color) {
  addLine(p1.x(), p1.y(), p2.x(), p2.y(),
          QPen(color, radius_, Qt::SolidLine, Qt::RoundCap));
}
