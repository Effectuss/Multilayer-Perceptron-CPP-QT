#include "mapping.h"

void Mapping::AddData(int key, const std::set<int>& value) {
  data_[key] = value;
}

const std::map<int, std::set<int>>& Mapping::GetData() const { return data_; }

std::size_t Mapping::GetDataSize() const { return data_.size(); }

const std::set<int>& Mapping::GetItem(int key) const {
  return data_.find(key)->second;
}
