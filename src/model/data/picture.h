#ifndef MULTILAYER_PERCEPTRON_CPP_QT_PICTURE_H
#define MULTILAYER_PERCEPTRON_CPP_QT_PICTURE_H

#include <vector>

class Picture {
 public:
  Picture();
  explicit Picture(const std::vector<double> &data);
  explicit Picture(std::vector<double> &&data);

  [[nodiscard]] const std::vector<double> &GetData() const;
  void SetData(const std::vector<double> &);
  [[nodiscard]] std::size_t GetSize() const;

 private:
  static constexpr int kMaxPictureSize = 784;
  std::vector<double> data_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_PICTURE_H
