#include "drawarea.h"

DrawArea::DrawArea(QWidget* parent) : QWidget(parent) { ClearImage(); }

void DrawArea::ClearImage() {
  image_.fill(kBackgroundColor);
  update();
}

void DrawArea::mousePressEvent(QMouseEvent* event) {
  qDebug() << event->pos();
  if (event->buttons().testFlags({Qt::LeftButton, Qt::RightButton})) {
    ClearImage();
  } else if (event->buttons().testFlag(Qt::LeftButton)) {
    DrawCircle(event->pos(), kPenColor);
  } else if (event->buttons().testFlag(Qt::RightButton)) {
    DrawCircle(event->pos(), kEraserColor);
  }
}

void DrawArea::mouseMoveEvent(QMouseEvent* event) {
  if (!event->buttons().testFlags({Qt::LeftButton, Qt::RightButton})) {
    mousePressEvent(event);
  }
}

void DrawArea::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.drawImage(event->rect(), image_, event->rect());
}

void DrawArea::DrawCircle(const QPoint& point, const QColor& color) {
  QPainter painter(&image_);
  painter.setPen(QPen(color, radius_));
  painter.drawEllipse(point.x(), point.y(), radius_, radius_);
  update();
}
