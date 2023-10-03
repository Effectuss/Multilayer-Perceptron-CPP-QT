#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
    : QGraphicsView(parent) {}

void CustomGraphicsView::mouseReleaseEvent(
    [[maybe_unused]] QMouseEvent* event) {
  if (event->buttons().testFlag(Qt::NoButton)) emit MouseReleasedSignal();
}
