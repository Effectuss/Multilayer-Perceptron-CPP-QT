#include "mapping.h"

void Mapping::AddData(int key, const std::set<int> &value) {
  data_[key] = value;
}

std::map<int, std::set<int> > Mapping::GetData() const { return data_; }

int Mapping::GetDataSize() const { return data_.size(); }

std::set<int> Mapping::GetItem(int key) const {
  return data_.find(key)->second;
}
