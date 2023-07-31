#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QFlags>
#include <QMouseEvent>
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

class DrawArea : public QWidget {
  Q_OBJECT
 public:
  DrawArea(QWidget* parent = nullptr);

  void ClearImage();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

 private:
  void DrawCircle(const QPoint& point, const QColor& color);

  const QColor kPenColor{0, 0, 0};
  const QColor kEraserColor{255, 255, 255};
  const QColor kBackgroundColor{255, 255, 255};

  QImage image_{512, 512, QImage::Format_RGBA8888};
  int radius_ = 15;
};

#endif  // DRAWAREA_H
