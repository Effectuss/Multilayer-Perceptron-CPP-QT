#include "mapping.h"

void Mapping::AppendData(const std::set<int>& value) { data_.push_back(value); }

const std::vector<std::set<int>>& Mapping::GetData() const { return data_; }

std::size_t Mapping::GetDataSize() const { return data_.size(); }

void Mapping::SetMinIndex(std::size_t min_index) { min_index_ = min_index; }

std::size_t Mapping::GetMinIndex() const { return min_index_; }
