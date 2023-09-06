#include "dataset.h"

#include <stdexcept>

void Dataset::AppendPair(const std::pair<Picture, int> &data) {
  data_.push_back(data);
}

void Dataset::SetSizeOutputLayers(int size_output_layers) {
  if (size_output_layers <= 0) {
    throw std::invalid_argument("Invalid size output layers");
  }
  size_output_layers_ = size_output_layers;
}

int Dataset::GetSizeOutputLayers() const { return size_output_layers_; }

int Dataset::GetSizeDataset() const { return data_.size(); }