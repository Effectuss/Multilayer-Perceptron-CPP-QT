#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
    : QGraphicsView(parent) {}

void CustomGraphicsView::mouseReleaseEvent(
    [[maybe_unused]] QMouseEvent* event) {
  emit MouseReleasedSignal();
}
