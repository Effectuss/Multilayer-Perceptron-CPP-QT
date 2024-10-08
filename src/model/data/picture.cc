#include "picture.h"

#include <cmath>
#include <stdexcept>

Picture::Picture() : data_(kMaxPictureSize) {}

Picture::Picture(const std::vector<double> &data) : data_() {
  if (data.size() != kMaxPictureSize)
    throw std::invalid_argument("Wrong picture size!");
  data_ = data;
}

Picture::Picture(std::vector<double> &&data) : data_() {
  if (data.size() != kMaxPictureSize)
    throw std::invalid_argument("Wrong picture size!");
  data_ = std::move(data);
}

const std::vector<double> &Picture::GetData() const { return data_; }

void Picture::SetData(const std::vector<double> &data) {
  if (data.size() != kMaxPictureSize) {
    throw std::invalid_argument("Wrong picture size!");
  }

  data_ = data;
}

std::size_t Picture::GetSize() const { return data_.size(); }

std::size_t Picture::GetSideSize() const { return std::sqrt(data_.size()); }
