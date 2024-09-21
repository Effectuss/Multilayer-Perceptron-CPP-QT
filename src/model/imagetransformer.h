#ifndef IMAGETRANSFORMER_H
#define IMAGETRANSFORMER_H

#include <QImage>
#include <QSize>
#include <vector>

#include "picture.h"

class ImageTransformer {
 public:
  enum RotationSide { kNorth, kEast, kSouth, kWest };
  enum Invertion { kVertical = 0b1, kHorizontal = 0b10, kNoInvertion = 0 };

  ImageTransformer() = delete;
  explicit ImageTransformer(const QSize& target_size,
                            RotationSide rotation_side = kNorth,
                            Invertion invertions = kNoInvertion);

  QImage Transform(const QImage& image) const;
  Picture ImageToDoubleMatrix(const QImage& image) const;

 private:
  QSize target_size_;
  RotationSide rotation_side_;
  Invertion invertions_;
};

#endif  // IMAGETRANSFORMER_H
