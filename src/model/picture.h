#ifndef MULTILAYER_PERCEPTRON_CPP_QT_PICTURE_H
#define MULTILAYER_PERCEPTRON_CPP_QT_PICTURE_H

#include <vector>

class Picture {
 public:
  Picture();
  const std::vector<int>& GetData() const;
  void SetData(const std::vector<int>&);

 private:
  // todo type pic
  static constexpr int kMaxPictureSize = 784;
  std::vector<int> data_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_PICTURE_H
