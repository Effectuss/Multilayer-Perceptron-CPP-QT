#include "drawareaview.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

DrawAreaView::DrawAreaView(QWidget* parent) : QGraphicsView(parent) {
  setAcceptDrops(true);
}

void DrawAreaView::dragEnterEvent(QDragEnterEvent* event) {
  qDebug() << "dragEnterEvent";
  if (event->mimeData()->hasImage() ||
      (event->mimeData()->hasUrls() && event->mimeData()->urls().size() == 1)) {
    event->accept();
  }
}

void DrawAreaView::dropEvent(QDropEvent* event) {
  if (event->mimeData()->hasUrls()) {
    QUrl url = event->mimeData()->urls().front();
    emit FileDroppedSignal(url.toLocalFile());
  } else if (event->mimeData()->hasImage()) {
    QVariant image_data = event->mimeData()->imageData();
    if (image_data.canConvert<QImage>()) {
      emit ImageDroppedSignal(image_data.value<QImage>());
    } else {
      event->ignore();
    }
  } else {
    event->ignore();
  }
}
