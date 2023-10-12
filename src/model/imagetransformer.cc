#include "imagetransformer.h"

#include <QDebug>
#include <QRgb>

ImageTransformer::ImageTransformer(const QSize& target_size,
                                   RotationSide rotation_side,
                                   Invertion invertions)
    : target_size_(target_size),
      rotation_side_(rotation_side),
      invertions_(invertions) {}

QImage ImageTransformer::Transform(const QImage& image) const {
  QImage result =
      image
          .scaled(target_size_, Qt::AspectRatioMode::KeepAspectRatio,
                  Qt::TransformationMode::SmoothTransformation)
          .transformed(QTransform().rotate(90.0 * rotation_side_));
  result.mirror(invertions_ & Invertion::kHorizontal,
                invertions_ & Invertion::kVertical);
  return result;
}

Picture ImageTransformer::ImageToDoubleMatrix(const QImage& image) const {
  std::vector<double> result;
  result.reserve(image.height() * image.width());
  for (unsigned i = 0; i < (unsigned)image.height(); ++i)
    for (unsigned j = 0; j < (unsigned)image.width(); ++j)
      result.push_back(1.0 - image.pixelColor(j, i).valueF());

  return Picture(std::move(result));
}
