#ifndef MULTILAYER_PERCEPTRON_CPP_QT_PICTURE_H
#define MULTILAYER_PERCEPTRON_CPP_QT_PICTURE_H

#include <iomanip>
#include <iostream>
#include <vector>

class Picture {
 public:
  Picture();

  [[nodiscard]] const std::vector<double> &GetData() const;
  void SetData(const std::vector<double> &);
  [[nodiscard]] std::size_t GetSize() const;

  inline void PrintPicture() {
    for (int i = 0; i < data_.size(); ++i) {
      if (i % 28 == 0) {
        std::cout << std::endl;
      }
      std::cout << std::setw(4) << std::setprecision(2) << data_[i] << " ";
    }
  }

 private:
  static constexpr int kMaxPictureSize = 784;
  std::vector<double> data_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_PICTURE_H
