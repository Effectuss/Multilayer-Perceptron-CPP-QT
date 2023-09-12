#include "dataset.h"

void Dataset::AppendDataToVector(const std::pair<Picture, int> &data) {
  data_.push_back(data);
}

std::size_t Dataset::GetDataSize() const { return data_.size(); }

std::vector<std::pair<Picture, int>> Dataset::GetData() const { return data_; }
