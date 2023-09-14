#include "imagetransformer.h"

#include <QRgb>

ImageTransformer::ImageTransformer(const QSize& target_size,
                                   RotationSide rotation_side,
                                   Invertion invertions)
    : target_size_(target_size),
      rotation_side_(rotation_side),
      invertions_(invertions) {}

QImage ImageTransformer::Transform(const QImage& image) const {
  QImage result = image.scaled(target_size_)
                      .transformed(QTransform().rotate(90.0 * rotation_side_));
  result.mirror(invertions_ & Invertion::kHorizontal, Invertion::kVertical);
  return result;
}

Picture ImageTransformer::ImageToDoubleMatrix(const QImage& image) const {
  std::vector<double> result(image.height() * image.width(), 1.0);
  for (unsigned i = 0; i < (unsigned)image.height(); ++i)
    for (unsigned j = 0; j < (unsigned)image.width(); ++j)
      result[i * image.width() + j] = image.pixelColor(i, j).valueF();
  return Picture(std::move(result));
}
