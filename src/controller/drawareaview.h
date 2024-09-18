#ifndef DRAWAREAVIEW_H
#define DRAWAREAVIEW_H

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QGraphicsView>
#include <QObject>
#include <QWidget>

class DrawAreaView : public QGraphicsView {
  Q_OBJECT
 public:
  DrawAreaView(QWidget* parent = nullptr);

 public slots:
  virtual void dragEnterEvent(QDragEnterEvent* event) override;
  virtual void dropEvent(QDropEvent* event) override;

 signals:
  void FileDroppedSignal(const QString& path);
  void ImageDroppedSignal(const QImage& image);
};

#endif  // DRAWAREAVIEW_H
