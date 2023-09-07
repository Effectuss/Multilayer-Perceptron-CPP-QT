#include "picture.h"

#include <stdexcept>

Picture::Picture() : data_(kMaxPictureSize) {}

const std::vector<int>& Picture::GetData() const { return data_; }

void Picture::SetData(const std::vector<int>& data) {
  if (data.size() != kMaxPictureSize) {
    throw std::invalid_argument("Wrong picture size!");
  }
  data_ = data;
}