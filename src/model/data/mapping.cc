#include "mapping.h"

void Mapping::AppendData(const std::set<int>& value) { data_.push_back(value); }

const std::vector<std::set<int>>& Mapping::GetData() const { return data_; }

std::size_t Mapping::GetDataSize() const { return data_.size(); }
