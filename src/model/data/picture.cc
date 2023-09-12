#include "picture.h"

#include <stdexcept>

Picture::Picture() : data_(kMaxPictureSize) {}

const std::vector<double> &Picture::GetData() const { return data_; }

void Picture::SetData(const std::vector<double> &data) {
  if (data.size() != kMaxPictureSize) {
    throw std::invalid_argument("Wrong picture size!");
  }

  data_ = data;
}
std::size_t Picture::GetSize() const { return data_.size(); }